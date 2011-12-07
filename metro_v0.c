#include <stdlib.h>
#include <gtk/gtk.h>
#include <ctype.h>

#include "metro_callback_v0.h"

#include "liste.h"

#define WORIGIN 500
#define HORIGIN 500

Une_coord lim_no;
Une_coord lim_se;
Un_elem *liste_sta;

GtkWidget *pDA;


int main(int argc, char **argv)
{
	GtkWidget *pWindow;

	gtk_init(&argc, &argv);

	//initialisation reseau
	liste_sta = lire_stations("Stations_IDF_fr.csv");
	limites_zone(liste_sta, &lim_no, &lim_se);

	/* Creation de la fenetre */
	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(pWindow), "metro");
	gtk_window_set_default_size(GTK_WINDOW(pWindow), -1, -1);
	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);


	// une DrawingArea
	pDA = gtk_drawing_area_new ();
	gtk_widget_set_size_request (pDA, WORIGIN, HORIGIN);
	gtk_container_add(GTK_CONTAINER(pWindow), pDA);

	// Gestion des click sur la DA
	// Autorisation des evenements
	gtk_widget_set_events (pDA, gtk_widget_get_events (pDA)
									| GDK_BUTTON_PRESS_MASK
									| GDK_POINTER_MOTION_MASK
									| GDK_POINTER_MOTION_HINT_MASK
									| GDK_BUTTON_RELEASE_MASK);
	// connexion de callbacks
	g_signal_connect (pDA, "expose-event", G_CALLBACK (OnExpose), (GtkWidget*) pWindow);

	gtk_widget_show_all(pWindow);

	gtk_main();

	// destruction listes et arbres

	detruire_liste_et_truc(liste_sta);

	return EXIT_SUCCESS;
}
