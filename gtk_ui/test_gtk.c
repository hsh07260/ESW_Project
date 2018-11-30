#include <gtk/gtk.h>
#include <time.h>
#include <stdlib.h>


enum{
  LIST_ITEM = 0,
  N_COLUMNS
};

GtkWidget *list;

GtkWidget *window;

GtkWidget *height_entry;
GtkWidget *weight_entry;

GtkWidget *input_button;
GtkWidget *add_button;
GtkWidget *remove_button;
GtkWidget *rewrite_button;
GtkWidget *save_button;

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

const gchar *height_buff;
const gchar *weight_buff;
gchar standard_buff[10];
double standard_weight;

void input_clicked(){
  height_buff = gtk_entry_get_text(GTK_ENTRY(height_entry));
  weight_buff = gtk_entry_get_text(GTK_ENTRY(weight_entry));
  standard_weight = (atof(height_buff)-100)*0.9;
  sprintf(standard_buff,"%.1f kg",standard_weight);
  gtk_label_set_text(GTK_LABEL(std_weight_label),standard_buff);

}
void add_clicked(){
}
void remove_clicked(){
}
void rewrite_clicked(){
}



void init_list(GtkWidget *list) {

  GtkCellRenderer    *renderer;
  GtkTreeViewColumn  *column;
  GtkListStore       *store;

  renderer = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes(NULL,
          renderer, "text", LIST_ITEM, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

  store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING);

  gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));

  g_object_unref(store);
}

static void activate (GtkApplication* app, gpointer user_data){

  struct tm *t;

  //int year,month,day;

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

  //input height area
  height_entry=gtk_entry_new();
  gtk_fixed_put(GTK_FIXED(fixed),height_entry,15,15);
  gtk_entry_set_placeholder_text(GTK_ENTRY(height_entry),"height (cm)");
  //input weight area
  weight_entry=gtk_entry_new();
  gtk_fixed_put(GTK_FIXED(fixed),weight_entry,15,50);
  gtk_entry_set_placeholder_text(GTK_ENTRY(weight_entry),"weight (kg)");

  //input_button area
  input_button=gtk_button_new_with_label("enter");
  gtk_fixed_put(GTK_FIXED(fixed),input_button,180,15);
  gtk_widget_set_size_request(input_button,50,60);
  g_signal_connect(input_button,"clicked",
                   G_CALLBACK(input_clicked),NULL);
  //add_button area
  add_button=gtk_button_new_with_label("add");
  gtk_fixed_put(GTK_FIXED(fixed),add_button,25,365);
  //remove_button area
  remove_button=gtk_button_new_with_label("remove");
  gtk_fixed_put(GTK_FIXED(fixed),remove_button,70,365);
  //rewrite_button area
  rewrite_button=gtk_button_new_with_label("rewrite");
  gtk_fixed_put(GTK_FIXED(fixed),rewrite_button,140,365);

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

