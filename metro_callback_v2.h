#ifndef METRO_CALLBACK
#define METRO_CALLBACK

void OnExpose(GtkWidget* widget, gpointer data);

void OnClickZP(GtkWidget* widget, gpointer data);
void OnClickZM(GtkWidget* widget, gpointer data);

void OnClickH(GtkWidget* widget, gpointer data);
void OnClickB(GtkWidget* widget, gpointer data);
void OnClickG(GtkWidget* widget, gpointer data);
void OnClickD(GtkWidget* widget, gpointer data);

void OnBtPress (GtkWidget *widget, GdkEventButton *event, gpointer data);
void OnMouseMove (GtkWidget *widget, GdkEventButton *event, gpointer data);
void OnBtRelease (GtkWidget *widget, GdkEventButton *event, gpointer data);
#endif
