#include <gtk/gtk.h>
#include <time.h>


static void activate (GtkApplication* app, gpointer user_data){

  GtkWidget *window;
  GtkWidget *height_entry;
  GtkWidget *weight_entry;
  GtkWidget *input_button;
  GtkWidget *calendar;
  GtkWidget *std_weight_label;
  GtkWidget *frame;
  GtkWidget *fixed;

  struct tm *t;
  int year,month,day;

  //window setting
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Sal-BBae");
  gtk_window_set_default_size (GTK_WINDOW (window), 600,400);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_MOUSE);

  //widget container
  fixed = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window),fixed);

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

  //standard weight frame area
  frame=gtk_frame_new("↓ Standard weight ↓");
  gtk_fixed_put(GTK_FIXED(fixed),frame,15,100);
  gtk_widget_set_size_request(frame,220,100);
  gtk_frame_set_label_align(GTK_FRAME(frame),0.5,0.5);

  //label showing standard weight
  std_weight_label=gtk_label_new("65kg");
  gtk_container_add(GTK_CONTAINER(frame),std_weight_label);

  //calendar area
  calendar=gtk_calendar_new();
  gtk_fixed_put(GTK_FIXED(fixed),calendar,15,230);
  year=t->tm_year+1900;
  month=t->tm_mon+1;
  gtk_calendar_select_month(GTK_CALENDAR(calendar),month,year);
  //gtk_calendar_mark_day(GTK_CALENDAR(calendar),20);
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

