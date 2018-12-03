#include "/usr/include/mysql/mysql.h"
#include <stdio.h>
#include <gtk/gtk.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

enum{
  LIST_ITEM = 0,
  N_COLUMNS
};
void finish_with_error(MYSQL *conn)
{
  fprintf(stderr, "%s\n",mysql_error(conn));
  mysql_close(conn);
  exit(1);
}

typedef struct item{
  char *date;
  char *height;
  char *weight;
  char *std_wieght;
  char *m1;
  char *m2;
  char *m3;
  char *l1;
  char *l2;
  char *l3;
  char *d1;
  char *d2;
  char *d3;
  char *total_calorie;
  GtkTextBuffer *comments;
}item;

item db;

GtkWidget *list;

GtkWidget *window;

GtkWidget *height_entry;
GtkWidget *weight_entry;

GtkWidget *input_button;
GtkWidget *add_button;
GtkWidget *remove_button;
GtkWidget *rewrite_button;
GtkWidget *save_button;
GtkWidget *calculate;

GtkWidget *std_weight_label;
GtkWidget *morning_label;
GtkWidget *lunch_label;
GtkWidget *dinner_label;

GtkWidget *weight_frame;
GtkWidget *main_frame;
GtkWidget *fixed;
GtkWidget *list_frame;
GtkWidget *sw;

GtkWidget *main_fixed;

GtkWidget *morning_entry;
GtkWidget *lunch_entry;
GtkWidget *dinner_entry;

GtkWidget *morning1;
GtkWidget *morning2;
GtkWidget *morning3;

GtkWidget *lunch1;
GtkWidget *lunch2;
GtkWidget *lunch3;

GtkWidget *dinner1;
GtkWidget *dinner2;
GtkWidget *dinner3;

GtkWidget *calorie_frame;
GtkWidget *calorie_label;

GtkWidget *txt_frame;
GtkWidget *txt_vw;


GtkTreeSelection *selection;


void input_clicked(){
  const gchar *height_buff;
  const gchar *weight_buff;
  double standard_weight;
  gchar standard_buff[10];

  height_buff = gtk_entry_get_text(GTK_ENTRY(height_entry));
  weight_buff = gtk_entry_get_text(GTK_ENTRY(weight_entry));
  standard_weight = (atof(height_buff)-100)*0.9;
  sprintf(standard_buff,"%.1f kg",standard_weight);
  gtk_label_set_text(GTK_LABEL(std_weight_label),standard_buff);

}
void add_clicked(){
  GtkListStore *store;
  GtkTreeIter iter;
  gchar str[20];

  time_t timer=time(NULL);
  struct tm *t=localtime(&timer);
  int year,month,day;

  store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));

  gtk_list_store_append(store, &iter);
  sprintf(str,"%d/%d/%d",(t->tm_year)+1900,t->tm_mon+1,t->tm_mday);
  gtk_list_store_set(store, &iter, LIST_ITEM, str, -1);

  gtk_editable_set_editable(GTK_EDITABLE(height_entry), TRUE);
  gtk_editable_set_editable(GTK_EDITABLE(weight_entry), TRUE);
  gtk_text_view_set_editable(GTK_TEXT_VIEW(txt_vw),TRUE);

}

void remove_clicked(){
  GtkListStore *store;
  GtkTreeModel *model;
  GtkTreeIter  iter;

  store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
  model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

  if (gtk_tree_model_get_iter_first(model, &iter) == FALSE) {
      return;
  }

  if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection),
     &model, &iter)) {
    gtk_list_store_remove(store, &iter);
  }
}
void save_clicked(){

  char *txt_vw_buff;
  GtkTextBuffer *written_txt_buff;
  GtkTextIter start;
  GtkTextIter end;

  written_txt_buff=gtk_text_view_get_buffer(GTK_TEXT_VIEW(txt_vw));
  gtk_text_buffer_get_start_iter(written_txt_buff,&start);
  gtk_text_buffer_get_end_iter(written_txt_buff,&end);
  txt_vw_buff = gtk_text_buffer_get_text(written_txt_buff,
                &start,&end,FALSE);

  printf("%s\n",txt_vw_buff);

}

void changed_item(){
  GtkListStore *store;
  GtkTreeModel *model;
  GtkTreeIter  iter;
  char *get_date;

  store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
  model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

  if (gtk_tree_model_get_iter_first(model, &iter) == FALSE) {
      return;
  }

  if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection),
     &model, &iter)) {
    gtk_tree_model_get(model, &iter,LIST_ITEM, &get_date, -1);
  }
  printf("%s\n",get_date);

}

void calcul_clicked(){

  int mor_kcal1 = 0;
  int mor_kcal2 = 0;
  int mor_kcal3 = 0;
  int lun_kcal1 = 0;
  int lun_kcal2 = 0;
  int lun_kcal3 = 0;
  int din_kcal1 = 0;
  int din_kcal2 = 0;
  int din_kcal3 = 0;
  int total_kcal = 0;
  MYSQL *conn;
  conn = mysql_init(NULL);

  if( conn == NULL )
  {
    fprintf(stderr, "mysql_init() fail\n");
    exit(1);
  }
  if( mysql_real_connect(conn, "localhost", NULL, "123456", "SalBBAE", 0, NULL,0)==NULL)
  {
    finish_with_error(conn);
  }

  if(mysql_query(conn, "SELECT * FROM kcal_table"))
  {
    finish_with_error(conn);
  }
  MYSQL_RES *result;
  MYSQL_FIELD *fields;
  result = mysql_store_result(conn);
  if (result == NULL)
  {
    printf("result error\n");
    finish_with_error(conn);
  }
  int num_fields = mysql_num_fields(result);
  MYSQL_ROW row;
  fields = mysql_fetch_fields(result);
  printf("%s\n",fields[1].name);

  while(row = mysql_fetch_row(result))
  {
    if(strcmp((char *)gtk_entry_get_text(GTK_ENTRY(morning1)),row[0]) == 0)
    {
      mor_kcal1 = atoi(row[1]);
      printf("%s 's kcal is %d\n",row[0],atoi(row[1]));
    }
    if(strcmp((char *)gtk_entry_get_text(GTK_ENTRY(morning2)),row[0]) == 0)
    {
      mor_kcal2 = atoi(row[1]);
      printf("%s 's kcal is %d\n",row[0],atoi(row[1]));
    }
    if(strcmp((char *)gtk_entry_get_text(GTK_ENTRY(morning3)),row[0]) == 0)
    {
      mor_kcal3 = atoi(row[1]);
      printf("%s 's kcal is %d\n",row[0],atoi(row[1]));
    }
    if(strcmp((char *)gtk_entry_get_text(GTK_ENTRY(lunch1)),row[0]) == 0)
    {
      lun_kcal1 = atoi(row[1]);
      printf("%s 's kcal is %d\n",row[0],atoi(row[1]));
    }
    if(strcmp((char *)gtk_entry_get_text(GTK_ENTRY(lunch2)),row[0]) == 0)
    {
      lun_kcal2 = atoi(row[1]);
      printf("%s 's kcal is %d\n",row[0],atoi(row[1]));
    }
    if(strcmp((char *)gtk_entry_get_text(GTK_ENTRY(lunch3)),row[0]) == 0)
    {
      lun_kcal3 = atoi(row[1]);
      printf("%s 's kcal is %d\n",row[0],atoi(row[1]));
    }
    if(strcmp((char *)gtk_entry_get_text(GTK_ENTRY(dinner1)),row[0]) == 0)
    {
      din_kcal1 = atoi(row[1]);
      printf("%s 's kcal is %d\n",row[0],atoi(row[1]));
    }
    if(strcmp((char *)gtk_entry_get_text(GTK_ENTRY(dinner2)),row[0]) == 0)
    {
      din_kcal2 = atoi(row[1]);
      printf("%s 's kcal is %d\n",row[0],atoi(row[1]));
    }
    if(strcmp((char *)gtk_entry_get_text(GTK_ENTRY(dinner3)),row[0]) == 0)
    {
      din_kcal3 = atoi(row[1]);
      printf("%s 's kcal is %d\n",row[0],atoi(row[1]));
    }

    //printf("row   %s\n",row[0]);
    //printf("row  %d\n",atoi(row[1]));
    //printf("\n");
  }
  total_kcal = mor_kcal1+mor_kcal2+mor_kcal3+lun_kcal1+lun_kcal2+lun_kcal3+din_kcal1+din_kcal2+din_kcal3;
  printf("total kcal is %d \n",total_kcal);
  mysql_free_result(result);
  mysql_close(conn);
  return 0;


}

void init_list(GtkWidget *list) {

  GtkCellRenderer    *renderer;
  GtkTreeViewColumn  *column;
  GtkListStore       *store;

  renderer = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes(NULL,
          renderer, "text", LIST_ITEM, NULL);
  gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list),FALSE);
  gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

  store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING);

  gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));

  g_object_unref(store);
}



static void activate (GtkApplication* app, gpointer user_data){

  //window setting
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW(window), "Sal-BBae");
  gtk_window_set_default_size (GTK_WINDOW(window), 800,400);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_MOUSE);

  //widget container
  fixed = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window),fixed);

  //list_frame area
  list_frame =gtk_frame_new("History");
  gtk_frame_set_label_align(GTK_FRAME(list_frame),0.5,0.5);
  gtk_widget_set_size_request(list_frame,200,180);
  gtk_fixed_put(GTK_FIXED(fixed),list_frame,15,180);

  //scroll_window area
  sw = gtk_scrolled_window_new(NULL, NULL);
  gtk_container_add(GTK_CONTAINER(list_frame),sw);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw),
             GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  //list area
  list = gtk_tree_view_new();
  gtk_container_add(GTK_CONTAINER(sw), list);
  init_list(list);
  g_signal_connect(list,"row-activated",G_CALLBACK(changed_item),NULL);

  //input height area
  height_entry=gtk_entry_new();
  gtk_fixed_put(GTK_FIXED(fixed),height_entry,15,15);
  gtk_entry_set_placeholder_text(GTK_ENTRY(height_entry),"height (cm)");
  gtk_editable_set_editable(GTK_EDITABLE(height_entry), FALSE);

  //input weight area
  weight_entry=gtk_entry_new();
  gtk_fixed_put(GTK_FIXED(fixed),weight_entry,15,50);
  gtk_entry_set_placeholder_text(GTK_ENTRY(weight_entry),"weight (kg)");
  gtk_editable_set_editable(GTK_EDITABLE(weight_entry), FALSE);

  //input_button area
  input_button=gtk_button_new_with_label("enter");
  gtk_fixed_put(GTK_FIXED(fixed),input_button,180,15);
  gtk_widget_set_size_request(input_button,50,60);
  g_signal_connect(input_button,"clicked",
                   G_CALLBACK(input_clicked),NULL);

  //add_button area
  add_button=gtk_button_new_with_label("add");
  gtk_fixed_put(GTK_FIXED(fixed),add_button,25,365);
  g_signal_connect(add_button,"clicked",
                   G_CALLBACK(add_clicked),NULL);

  //remove_button area
  remove_button=gtk_button_new_with_label("remove");
  gtk_fixed_put(GTK_FIXED(fixed),remove_button,70,365);
  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));
  g_signal_connect(remove_button,"clicked",
                   G_CALLBACK(remove_clicked), selection);

  //standard weight frame area
  weight_frame=gtk_frame_new("↓ Standard weight ↓");
  gtk_fixed_put(GTK_FIXED(fixed),weight_frame,15,100);
  gtk_widget_set_size_request(weight_frame,200,70);
  gtk_frame_set_label_align(GTK_FRAME(weight_frame),0.5,0.5);

  //label showing standard weight
  std_weight_label=gtk_label_new(NULL);
  gtk_container_add(GTK_CONTAINER(weight_frame),std_weight_label);

  //main_frame area
  main_frame=gtk_frame_new(NULL);
  gtk_fixed_put(GTK_FIXED(fixed),main_frame,240,15);
  gtk_widget_set_size_request(main_frame,550,375);

  //main_fixed;
  main_fixed=gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(main_frame),main_fixed);

  //calorie_frame
  calorie_frame=gtk_frame_new("today total Calorie");
  gtk_frame_set_label_align(GTK_FRAME(calorie_frame),0.5,0.5);
  gtk_widget_set_size_request(calorie_frame,220,100);
  gtk_fixed_put(GTK_FIXED(main_fixed),calorie_frame,300,20);

  calorie_label=gtk_label_new("kcal");
  gtk_container_add(GTK_CONTAINER(calorie_frame),calorie_label);

  //input diary in text view
  txt_frame=gtk_frame_new("Today Comments");
  gtk_frame_set_label_align(GTK_FRAME(txt_frame),0.5,0.5);
  gtk_widget_set_size_request(txt_frame,220,180);
  gtk_fixed_put(GTK_FIXED(main_fixed),txt_frame,300,130);

  txt_vw=gtk_text_view_new();
  gtk_text_view_set_editable(GTK_TEXT_VIEW(txt_vw),FALSE);
  gtk_widget_set_size_request(txt_vw,220,140);
  gtk_container_add(GTK_CONTAINER(txt_frame),txt_vw);

  //Save button
  save_button=gtk_button_new_with_label("Save");
  gtk_fixed_put(GTK_FIXED(main_fixed),save_button,475,320);
  g_signal_connect(save_button,"clicked",
                   G_CALLBACK(save_clicked), NULL);

  //calculate_button
  calculate=gtk_button_new_with_label("Calculate");
  gtk_fixed_put(GTK_FIXED(main_fixed),calculate,300,320);
  g_signal_connect(calculate,"clicked",G_CALLBACK(calcul_clicked),NULL);
  //morning,lunch,dinner entry vbox
  morning_entry=gtk_box_new(GTK_ORIENTATION_VERTICAL,2);
  lunch_entry=gtk_box_new(GTK_ORIENTATION_VERTICAL,2);
  dinner_entry=gtk_box_new(GTK_ORIENTATION_VERTICAL,2);

  //morning area
  morning_label=gtk_label_new("morning");
  gtk_container_add(GTK_CONTAINER(main_fixed),morning_label);
  gtk_fixed_put(GTK_FIXED(main_fixed),morning_label,15,60);

  morning1=gtk_entry_new();
  morning2=gtk_entry_new();
  morning3=gtk_entry_new();

  gtk_box_pack_start(GTK_BOX(morning_entry),morning1,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(morning_entry),morning2,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(morning_entry),morning3,FALSE,FALSE,0);

  gtk_fixed_put(GTK_FIXED(main_fixed),morning_entry,100,25);

  //lunch area
  lunch_label=gtk_label_new("       lunch");
  gtk_container_add(GTK_CONTAINER(main_fixed),lunch_label);
  gtk_fixed_put(GTK_FIXED(main_fixed),lunch_label,15,175);

  lunch1=gtk_entry_new();
  lunch2=gtk_entry_new();
  lunch3=gtk_entry_new();

  gtk_box_pack_start(GTK_BOX(lunch_entry),lunch1,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(lunch_entry),lunch2,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(lunch_entry),lunch3,FALSE,FALSE,0);

  gtk_fixed_put(GTK_FIXED(main_fixed),lunch_entry,100,140);

  //dinner area
  dinner_label=gtk_label_new("     dinner");
  gtk_container_add(GTK_CONTAINER(main_fixed),dinner_label);
  gtk_fixed_put(GTK_FIXED(main_fixed),dinner_label,15,300);

  dinner1=gtk_entry_new();
  dinner2=gtk_entry_new();
  dinner3=gtk_entry_new();

  gtk_box_pack_start(GTK_BOX(dinner_entry),dinner1,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(dinner_entry),dinner2,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(dinner_entry),dinner3,FALSE,FALSE,0);

  gtk_fixed_put(GTK_FIXED(main_fixed),dinner_entry,100,260);

  //show all of widget in winodow
  gtk_widget_show_all(window);
}

int main (int argc, char **argv){

  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

