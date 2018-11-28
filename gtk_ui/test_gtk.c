#include <gtk/gtk.h>
#include <time.h>

enum{
  LIST_ITEM = 0,
  N_COLUMNS
};

GtkWidget *list;

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

  GtkWidget *window;

  GtkWidget *height_entry;
  GtkWidget *weight_entry;

  GtkWidget *input_button;
  GtkWidget *add_button;
  GtkWidget *remove_button;
  GtkWidget *rewrite_button;

  GtkWidget *std_weight_label;

  GtkWidget *weight_frame;
  GtkWidget *main_frame;
  GtkWidget *fixed;
  GtkWidget *list_frame;
  GtkWidget *sw;

  struct tm *t;

  //int year,month,day;

  //window setting
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW(window), "Sal-BBae");
  gtk_window_set_default_size (GTK_WINDOW(window), 600,400);
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

  //main_frame area
  main_frame=gtk_frame_new(NULL);
  gtk_fixed_put(GTK_FIXED(fixed),main_frame,240,15);
  gtk_widget_set_size_request(main_frame,350,375);

  //label showing standard weight
  std_weight_label=gtk_label_new("65kg");
  gtk_container_add(GTK_CONTAINER(weight_frame),std_weight_label);

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

