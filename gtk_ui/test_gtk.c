#include <gtk/gtk.h>

static void activate (GtkApplication* app, gpointer user_data){

  GtkWidget *window;
  GtkWidget *height_entry;
  GtkWidget *weight_entry;
  GtkWidget *fixed;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 600,400);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_MOUSE);

  fixed = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window),fixed);

  //input height area
  height_entry=gtk_entry_new();
  gtk_fixed_put(GTK_FIXED(fixed),height_entry,15,15);
  
  //input weight area
  weight_entry=gtk_entry_new();
  gtk_fixed_put(GTK_FIXED(fixed),weight_entry,15,48);
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
