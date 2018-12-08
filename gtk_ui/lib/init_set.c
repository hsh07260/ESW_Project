#include <gtk/gtk.h>
#include <string.h>

void init_set(GtkWidget *weight_entry,GtkWidget *m1,GtkWidget *m2,
              GtkWidget *l1,GtkWidget *l2,GtkWidget *d1,GtkWidget *d2,
              GtkWidget *calorie_label,GtkWidget *txt_vw)
{
  GtkTextBuffer *buffer=gtk_text_buffer_new(NULL);

  gtk_entry_set_text(GTK_ENTRY(weight_entry), "");

  gtk_entry_set_text(GTK_ENTRY(m1), "");
  gtk_entry_set_text(GTK_ENTRY(m2), "");

  gtk_entry_set_text(GTK_ENTRY(l1), "");
  gtk_entry_set_text(GTK_ENTRY(l2), "");

  gtk_entry_set_text(GTK_ENTRY(d1), "");
  gtk_entry_set_text(GTK_ENTRY(d2), "");

  gtk_label_set_text(GTK_LABEL(calorie_label), "");

  gtk_text_buffer_set_text(buffer,"",strlen(""));
  gtk_text_view_set_buffer(GTK_TEXT_VIEW(txt_vw), buffer);
}
