#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>

void input_clicked(GtkWidget *label, GtkWidget *h_entry, GtkWidget *w_entry){
  const gchar *height_buff;
  const gchar *weight_buff;
  double standard_weight;
  gchar standard_buff[10];

  height_buff = gtk_entry_get_text(GTK_ENTRY(h_entry));
  weight_buff = gtk_entry_get_text(GTK_ENTRY(w_entry));
  standard_weight = (atof(height_buff)-100)*0.9;
  sprintf(standard_buff,"%.1f kg",standard_weight);
  gtk_label_set_text(GTK_LABEL(label),standard_buff);

}

