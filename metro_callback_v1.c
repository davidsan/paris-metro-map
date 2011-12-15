#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>
#include <cairo.h>

#include "liste.h"

#define STA_R 3
#define BORD 6
#define BORDD 140

extern Une_coord lim_no;
extern Une_coord lim_se;
extern Un_elem *liste_sta;
extern Un_elem *liste_con;
extern Une_ligne *liste_ligne;

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
	double xd, yd, xa, ya;
	double angle;
	double r, v, b;
	unsigned int rvb;
	Une_coord coord_dep, coord_arr;


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
				// couleur ligne
				rvb = strtol(liste->truc->data.con.ligne->color + 1, NULL, 16);
				r = (rvb >> 16) / 255.0;
				v = ((rvb >> 8) & 0xff) / 255.0;
				b = (rvb & 0xff) / 255.0;
				cairo_set_source_rgb( cr, r, v, b);

				coord_arr = liste->truc->data.con.sta_arr->coord;
				coord_dep = liste->truc->data.con.sta_dep->coord;
				angle = atan2(coord_arr.lat - coord_dep.lat, coord_arr.lon - coord_dep.lon);
				xd = lontox(coord_dep.lon) + (STA_R * cos(angle));
				yd = lattoy(coord_dep.lat) - (STA_R * sin(angle));
				xa = lontox(coord_arr.lon) + (STA_R * cos(angle + M_PI));
				ya = lattoy(coord_arr.lat) - (STA_R * sin(angle + M_PI));
				cairo_move_to (cr, xd, yd);
				cairo_line_to(cr, xa, ya);
				cairo_stroke (cr);
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
	// trace connexions
	tracer_liste(liste_con, cr);

	cairo_destroy(cr);
	//cairo_surface_destroy(image);
	}
