#include <stdlib.h>
#include <gtk/gtk.h>
#include <ctype.h>

#include "metro_callback_v3.h"

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
Un_elem *lcon_pcc = NULL;

GtkWidget *pDA;
GtkWidget *pLabelPCC;


static void inserer_stations(GtkTreeStore *store, GtkTreeIter ItNiv0[], Un_nabr *abr)
	{
	GtkTreeIter ItChoix;

	if (abr)
		{
		char Plettre = toupper(*(abr->truc->data.sta.nom));
		inserer_stations(store, ItNiv0, abr->g);
		gtk_tree_store_append (store, &ItChoix, ItNiv0 + Plettre - 'A');
		gtk_tree_store_set (store, &ItChoix, 0, abr->truc->data.sta.nom, 1, abr->truc,  -1);
		inserer_stations(store, ItNiv0, abr->d);
		}
	}

static GtkTreeModel *creerTreeStoreStations(Un_nabr *abr, GtkTreeIter *pItChoixIni, char *MIni)
	{
	GtkTreeStore *store;
	GtkTreeIter ItNiv0[26];
	int i;

	store = gtk_tree_store_new (2, G_TYPE_STRING, G_TYPE_POINTER);

	gtk_tree_store_append (store, pItChoixIni, NULL);
	gtk_tree_store_set (store, pItChoixIni, 0, MIni, 1, NULL, -1);

	for(i=0; i<26; i++)
		{
		char choix[2] = "A";
		choix[0] = 'A' + i;
		gtk_tree_store_append (store, ItNiv0 + i, NULL);
		gtk_tree_store_set (store, ItNiv0 + i, 0, choix, 1, NULL, -1);
		}

	inserer_stations(store, ItNiv0, abr);

	return GTK_TREE_MODEL (store);
	}

int main(int argc, char **argv)
{
	GtkWidget *pWindow;
	GtkWidget *pVBoxBtn;
	GtkWidget *pHBoxBtnH;
	GtkWidget *pHBoxBtnGD;
	GtkWidget *pHBoxBtnB;
	GtkWidget *pHBoxBtnZ;
	GtkWidget *pHBox;
	GtkWidget *pVBox;
	GtkWidget *pHBoxSel;
	GtkWidget *pSeparator;
	GtkWidget *pComboStaDep, *pComboStaArr;

	GtkWidget *pHautBtn;
	GtkWidget *pGaucheBtn;
	GtkWidget *pDroiteBtn;
	GtkWidget *pBasBtn;
	GtkWidget *pZoomPBtn;
	GtkWidget *pZoomMBtn;

	GtkTreeModel *model_dep;
	GtkTreeModel *model_arr;
	GtkCellRenderer *renderer;
	GtkTreeIter ItChoixIniD;
	GtkTreeIter ItChoixIniA;

	Un_nabr *abr_sta;
	const int dep = 0;
	const int arr = 1;

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

	// Creation de la pVBox
	pVBox = gtk_vbox_new(FALSE, 2);
	gtk_container_add(GTK_CONTAINER(pWindow), pVBox);

	/* Creation de la GtkHBox */

	pHBox = gtk_hbox_new(FALSE, 2);

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

	// fin de la Hbox
	gtk_box_pack_start(GTK_BOX(pVBox), pHBox, TRUE, TRUE, 0);

	// le separateur horizontal
	pSeparator = gtk_hseparator_new();
	gtk_box_pack_start(GTK_BOX(pVBox), pSeparator, FALSE, FALSE, 0);

	// Zone de selection des stations de depart et arrivee

	pHBoxSel = gtk_hbox_new(FALSE, 2);

	model_dep = creerTreeStoreStations(abr_sta, &ItChoixIniD, "Station depart");
	pComboStaDep = gtk_combo_box_new_with_model (model_dep);
	g_object_unref (model_dep);
	model_arr = creerTreeStoreStations(abr_sta, &ItChoixIniA, "Station arrivee");
	pComboStaArr = gtk_combo_box_new_with_model (model_arr);
	g_object_unref (model_arr);

	renderer = gtk_cell_renderer_text_new ();
	gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (pComboStaDep), renderer, TRUE);
	gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (pComboStaArr), renderer, TRUE);
	gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (pComboStaDep), renderer, "text", 0, NULL);
	gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (pComboStaArr), renderer, "text", 0, NULL);
	gtk_combo_box_set_active_iter (GTK_COMBO_BOX (pComboStaDep), &ItChoixIniD);
	gtk_combo_box_set_active_iter (GTK_COMBO_BOX (pComboStaArr), &ItChoixIniA);
	g_signal_connect (pComboStaDep, "changed", G_CALLBACK (OnChangeSta), (GtkWidget*) &dep);
	g_signal_connect (pComboStaArr, "changed", G_CALLBACK (OnChangeSta), (GtkWidget*) &arr);

	gtk_box_pack_start(GTK_BOX(pHBoxSel), pComboStaDep, TRUE, TRUE, 0);

	// le separateur vertical
	pSeparator = gtk_vseparator_new();
	gtk_box_pack_start(GTK_BOX(pHBoxSel), pSeparator, FALSE, FALSE, 0);

	gtk_box_pack_start(GTK_BOX(pHBoxSel), pComboStaArr, TRUE, TRUE, 0);
	
	// le separateur vertical
	pSeparator = gtk_vseparator_new();
	gtk_box_pack_start(GTK_BOX(pHBoxSel), pSeparator, FALSE, FALSE, 0);

	// Plus court chemin
	pLabelPCC = gtk_label_new("Pas de parcours selectionne");
	gtk_box_pack_start(GTK_BOX(pHBoxSel), pLabelPCC, TRUE, FALSE, 0);


	gtk_box_pack_start(GTK_BOX(pVBox), pHBoxSel, FALSE, FALSE, 0);


	gtk_widget_show_all(pWindow);

	gtk_main();

	// destruction listes et arbres

	detruire_aqr(aqr_sta);
	detruire_aqr(aqr_con);
	detruire_abr(abr_sta);
	detruire_liste(lsta);
	detruire_liste(lcon);
	detruire_liste(lcon_pcc);
	detruire_liste_et_truc(liste_sta);
	detruire_liste_et_truc(liste_con);

	return EXIT_SUCCESS;
}
