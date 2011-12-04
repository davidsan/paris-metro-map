#include<stdio.h>
#include <stdlib.h>
#include "liste.h"
#include "abr.h"

int main(int argc, char *argv[])
{
  Un_elem *liste_sta = NULL, *l;
  Un_nabr *abr=NULL;
  Une_coord no, se;

  if (argc != 2)
    {
      fprintf(stderr, "Usage : test_sta fichier_stations\n");
      return 1;
    }
	
  if ((liste_sta = lire_stations(argv[1])) == NULL)
    {
      fprintf(stderr, "Erreur : Lecture fichier stations\n");
      return 1;
    }

	
  limites_zone(liste_sta, &no, &se);
	 
  printf("Stations dans [%f,%f] et [%f,%f]\n", no.lon, no.lat, se.lon, se.lat);
	
  ecrire_liste(stdout, liste_sta);
	
  /** Test
   *  doit afficher "Malesherbes (Loiret)"
   *  c.-à-d.le nom de la station extraite au début de liste_sta
   printf("\n%s\n", extraire_deb_liste(&liste_sta)->data.sta.nom);
  **/

  /** Test
   *  extrait la station en début de liste
   *  ne pas oublier de la détruire (memory leak)
   detruire_truc(extraire_deb_liste(&liste_sta));
  **/

  /** Test
   *  extrait la station passé en argument
   *  ne pas oublier de la détruire (memory leak)
   detruire_truc(extraire_liste(&liste_sta,liste_sta->suiv->suiv->truc)->data.sta.nom));
   **/

  /** Test
   *  doit afficher "Buno Gironville"
   *  c.-à-d. le nom de la station n°3 extraite de liste_sta
   printf("\n%s\n", extraire_liste(&liste_sta,liste_sta->suiv->suiv->truc)->data.sta.nom);
  **/
  
  abr = construire_abr(liste_sta);
	
  for(l=liste_sta; l; l=l->suiv){
    if (chercher_station(abr, l->truc->data.sta.nom) == NULL){
      fprintf(stderr, "Station non trouvee!!!\n");
    }
  }
	
  detruire_abr(abr);
	
  detruire_liste_et_truc(liste_sta);
	
  return 1;
}
