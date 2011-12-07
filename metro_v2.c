#include <stdlib.h>
#include <gtk/gtk.h>
#include <ctype.h>

#include "metro_callback_v2.h"

#include "liste.h"
#include "abr.h"
#include "aqrtopo.h"

#define WORIGIN 500
#define HORIGIN 500
#define ESPACE_BOUTON 5

Une_coord lim_no;
Une_coord lim_se;
Un_elem *liste_sta;
Une_ligne *liste_ligne;
Un_elem *liste_con;
Un_noeud *aqr_sta, *aqr_con;
Un_elem *lsta = NULL;
Un_elem *lcon = NULL;

GtkWidget *pDA;


int main(int argc, char **argv)
{
	GtkWidget *pWindow;
	GtkWidget *pVBoxBtn;
	GtkWidget *pHBoxBtnH;
	GtkWidget *pHBoxBtnGD;
	GtkWidget *pHBoxBtnB;
	GtkWidget *pHBoxBtnZ;
	GtkWidget *pHBox;
	GtkWidget *pSeparator;

	GtkWidget *pHautBtn;
	GtkWidget *pGaucheBtn;
	GtkWidget *pDroiteBtn;
	GtkWidget *pBasBtn;
	GtkWidget *pZoomPBtn;
	GtkWidget *pZoomMBtn;

	Un_nabr *abr_sta;

	gtk_init(&argc, &argv);

	//initialisation reseau
	liste_sta = lire_stations("Stations_IDF_fr.csv");
	limites_zone(liste_sta, &lim_no, &lim_se);
	abr_sta = construire_abr(liste_sta);
	liste_ligne = lire_lignes("Lignes_IDF_fr.csv");
	liste_con = lire_connexions("Connexions_IDF_fr.csv", liste_ligne, abr_sta);
	aqr_sta = construire_aqr(liste_sta);
	aqr_con = construire_aqr(liste_con);

	/* Creation de la fenetre */
	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(pWindow), "metro");
	gtk_window_set_default_size(GTK_WINDOW(pWindow), -1, -1);
	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	/* Creation de la GtkHBox */

	pHBox = gtk_hbox_new(FALSE, 2);
	gtk_container_add(GTK_CONTAINER(pWindow), pHBox);

	/* A gauche Le plan et a droite les boutons */

	// une DrawingArea
	pDA = gtk_drawing_area_new ();
	gtk_widget_set_size_request (pDA, WORIGIN, HORIGIN);

	// Gestion des click sur la DA
	// Autorisation des evenements
	gtk_widget_set_events (pDA, gtk_widget_get_events (pDA)
									| GDK_BUTTON_PRESS_MASK
									| GDK_POINTER_MOTION_MASK
									| GDK_POINTER_MOTION_HINT_MASK
									| GDK_BUTTON_RELEASE_MASK);
	// connexion de callbacks
	g_signal_connect (pDA, "expose-event", G_CALLBACK (OnExpose), (GtkWidget*) pWindow);
	g_signal_connect (pDA, "button-press-event", G_CALLBACK (OnBtPress), NULL);
	g_signal_connect (pDA, "motion-notify-event", G_CALLBACK (OnMouseMove), NULL);
	//g_signal_connect (pDA, "button-release-event", G_CALLBACK (OnBtRelease), NULL);


	gtk_box_pack_start(GTK_BOX(pHBox), pDA, TRUE, TRUE, 0);


	// le separateur vertical
	pSeparator = gtk_vseparator_new();
	gtk_box_pack_start(GTK_BOX(pHBox), pSeparator, FALSE, FALSE, 0);

	// Zone des boutons

	pVBoxBtn = gtk_vbox_new(FALSE, ESPACE_BOUTON);

	// Boutons de deplacement
	// Bouton Haut
	pHBoxBtnH = gtk_hbox_new(FALSE, ESPACE_BOUTON);
	pHautBtn = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(pHautBtn),
							gtk_image_new_from_stock( GTK_STOCK_GO_UP, GTK_ICON_SIZE_BUTTON));
	g_signal_connect (pHautBtn, "clicked", G_CALLBACK (OnClickH), (GtkWidget*) NULL);
	gtk_box_pack_start(GTK_BOX(pHBoxBtnH), pHautBtn, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pVBoxBtn), pHBoxBtnH, FALSE, FALSE, 0);

	// Boutons Gauche Droite
	pHBoxBtnGD = gtk_hbox_new(FALSE, ESPACE_BOUTON);
	pGaucheBtn = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(pGaucheBtn),
							gtk_image_new_from_stock( GTK_STOCK_GO_BACK, GTK_ICON_SIZE_BUTTON));
	g_signal_connect (pGaucheBtn, "clicked", G_CALLBACK (OnClickG), (GtkWidget*) NULL);
	gtk_box_pack_start(GTK_BOX(pHBoxBtnGD), pGaucheBtn, FALSE, FALSE, 0);
	pDroiteBtn = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(pDroiteBtn),
							gtk_image_new_from_stock( GTK_STOCK_GO_FORWARD, GTK_ICON_SIZE_BUTTON));
	g_signal_connect (pDroiteBtn, "clicked", G_CALLBACK (OnClickD), (GtkWidget*) NULL);
	gtk_box_pack_start(GTK_BOX(pHBoxBtnGD), pDroiteBtn, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pVBoxBtn), pHBoxBtnGD, FALSE, FALSE, 0);

	// Bouton Bas
	pHBoxBtnB = gtk_hbox_new(FALSE, ESPACE_BOUTON);
	pBasBtn = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(pBasBtn),
							gtk_image_new_from_stock( GTK_STOCK_GO_DOWN, GTK_ICON_SIZE_BUTTON));
	g_signal_connect (pBasBtn, "clicked", G_CALLBACK (OnClickB), (GtkWidget*) NULL);
	gtk_box_pack_start(GTK_BOX(pHBoxBtnB), pBasBtn, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pVBoxBtn), pHBoxBtnB, FALSE, FALSE, 0);


	// le separateur vertical
	pSeparator = gtk_hseparator_new();
	gtk_box_pack_start(GTK_BOX(pVBoxBtn), pSeparator, FALSE, FALSE, 0);

	// Boutons Zoom Plus Moins
	pHBoxBtnZ = gtk_hbox_new(FALSE, ESPACE_BOUTON);
	pZoomPBtn = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(pZoomPBtn),
							gtk_image_new_from_stock( GTK_STOCK_ZOOM_IN, GTK_ICON_SIZE_BUTTON));
	g_signal_connect (pZoomPBtn, "clicked", G_CALLBACK (OnClickZP), (GtkWidget*) NULL);
	gtk_box_pack_start(GTK_BOX(pHBoxBtnZ), pZoomPBtn, FALSE, FALSE, 0);
	pZoomMBtn = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(pZoomMBtn),
							gtk_image_new_from_stock( GTK_STOCK_ZOOM_OUT, GTK_ICON_SIZE_BUTTON));
	g_signal_connect (pZoomMBtn, "clicked", G_CALLBACK (OnClickZM), (GtkWidget*) NULL);
	gtk_box_pack_start(GTK_BOX(pHBoxBtnZ), pZoomMBtn, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pVBoxBtn), pHBoxBtnZ, FALSE, FALSE, 0);

	//fin zone des boutons
	gtk_box_pack_start(GTK_BOX(pHBox), pVBoxBtn, FALSE, FALSE, 0);

	gtk_widget_show_all(pWindow);

	gtk_main();

	// destruction listes et arbres

	detruire_abr(abr_sta);
	detruire_liste(lsta);
	detruire_liste(lcon);
	detruire_liste_et_truc(liste_sta);
	detruire_liste_et_truc(liste_con);

	return EXIT_SUCCESS;
}
