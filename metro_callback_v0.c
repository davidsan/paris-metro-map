#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>

#include "liste.h"

#define STA_R 3
#define BORD 6
#define BORDD 140

extern Une_coord lim_no;
extern Une_coord lim_se;
extern Un_elem *liste_sta;

extern GtkWidget *pDA;

int w,h;

double lontox(double lon)
	{
	return ((lon - lim_no.lon) * w) / (lim_se.lon - lim_no.lon) + BORD;
	}

double lattoy(double lat)
	{
	return ((lim_no.lat - lat) * h) / (lim_no.lat - lim_se.lat) + BORD;
	}

double xtolon(int x)
	{
	return (((x - BORD) * (lim_se.lon - lim_no.lon)) / w) + lim_no.lon;
	}

double ytolat(int y)
	{
	return lim_no.lon - (((y - BORD) * (lim_no.lat - lim_se.lat)) / h);
	}

void tracer_liste(Un_elem *liste, cairo_t *cr)
	{
	double xc, yc;

	cairo_set_line_width (cr, 2);
	while(liste)
		{
		switch (liste->truc->type)
			{
			case STA :
				cairo_set_source_rgb( cr, 0.0, 0.0, 0.0);
				xc = lontox(liste->truc->coord.lon);
				yc = lattoy(liste->truc->coord.lat);
				cairo_new_sub_path(cr);
				cairo_arc(cr, xc , yc , STA_R, 0.0, 2 * M_PI);
				cairo_move_to (cr, xc + STA_R + 2 ,yc + STA_R);
				cairo_show_text(cr, liste->truc->data.sta.nom);
				cairo_stroke (cr);
			break;

			case CON :
			break;

			default :
				fprintf(stderr, "Erreur : type truc inconnu!!\n");
			}
		liste = liste->suiv;
		}
	}

// affichage de l image drawing_area
void OnExpose(GtkWidget* widget, gpointer data)
	{
	cairo_t *cr;

	cr = gdk_cairo_create (pDA->window);

	w = pDA->allocation.width - BORD - BORDD;
	h = pDA->allocation.height - (2 * BORD);

	// peinture du fond
	cairo_set_source_rgb( cr, 1.0, 1.0, 1.0);
	cairo_paint(cr);
	
	// trace stations
	tracer_liste(liste_sta, cr);

	cairo_destroy(cr);
	//cairo_surface_destroy(image);
	}
