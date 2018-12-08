#include <gtk/gtk.h>

enum{
  LIST_ITEM = 0,
  N_COLUMNS
};

void init_list(GtkWidget *list);
void init_set(GtkWidget *weight_entry,GtkWidget *m1,GtkWidget *m2,
              GtkWidget *l1,GtkWidget *l2,GtkWidget *d1,GtkWidget *d2,
              GtkWidget *calorie_label,GtkWidget *text_vw);

