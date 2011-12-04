#include <stdio.h>
#include <math.h>
#include <gtk/gtk.h>
#include <cairo.h>

#include "liste.h"

#define STA_R 3
#define BORD 6
#define BORDD 140

extern Une_coord lim_no;
extern Une_coord lim_se;
extern Un_elem *liste_sta_aff;

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
  return lim_no.lon - (((y - BORD) * (lim_no.lat - lim_se.lat)) / w);
}

void tracer_liste(Un_elem *liste, cairo_t *cr)
{
  cairo_pattern_t * black;
  double xc;
  double yc;

  black = cairo_pattern_create_rgb (0.0, 0.0, 0.0);
  cairo_set_source( cr, black);

  while(liste)
    {
      switch (liste->truc->type)
	{
	case STA :
	  xc = lontox(liste->truc->coord.lon);
	  yc = lattoy(liste->truc->coord.lat);
	  cairo_new_sub_path(cr);
	  cairo_arc(cr, xc , yc , STA_R, 0.0, 2 * M_PI);
	  cairo_move_to (cr, xc + STA_R + 2 ,yc + STA_R);
	  cairo_show_text(cr, liste->truc->data.sta.nom);
	  break;

	case CON :
	  break;

	default :
	  fprintf(stderr, "Erreur : type truc inconnu!!\n");
	}
      liste = liste->suiv;
    }
  cairo_set_line_width (cr, 2);
  cairo_stroke_preserve (cr);

  cairo_pattern_destroy (black);
}

// affichage de l image drawing_area
void OnExpose(GtkWidget* widget, gpointer data)
{
  cairo_t *cr;
  //cairo_surface_t *image;
  cairo_pattern_t *white;

  cr = gdk_cairo_create (pDA->window);

  w = pDA->allocation.width - BORD - BORDD;
  h = pDA->allocation.height - (2 * BORD);

  //printf("dimension pDA Direct: %dx%d\n", widget->allocation.width, widget->allocation.height);
  // Dessin image
  /*
    image = cairo_image_surface_create_from_png("start.png");
    cairo_set_source_surface(cr, image, 0, 0);
    cairo_paint(cr);
  */

  // peinture du fond
  white = cairo_pattern_create_rgb (1.0, 1.0, 1.0);
  cairo_set_source( cr, white);
  cairo_paint(cr);
	
  // trace stations
  tracer_liste(liste_sta_aff, cr);


  cairo_pattern_destroy (white);
  cairo_destroy(cr);
  //cairo_surface_destroy(image);
}
