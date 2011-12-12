#include <stdio.h>
#include "liste.h"
#include "truc.h"
#include "abr.h"
#include "aqrtopo.h"

int main(int argc, char *argv[])
{
  Un_elem *liste_sta = NULL;  
  Un_noeud *aqr_sta=NULL;
  Une_coord limite_no;
  Une_coord limite_se;
  limite_no.lon=0;
  limite_no.lat=90;
  limite_se.lon=60;
  limite_se.lat=0;
   

  if (argc != 2)
    {
      fprintf(stderr, "Usage : test_aqr fichier_stations\n");
      return 1;
    }
	
  if ((liste_sta = lire_stations(argv[1])) == NULL)
    {
      fprintf(stderr, "Erreur : Lecture fichier stations\n");
      return 1;
    }
  ecrire_liste(stdout,liste_sta);

  /* test creer_noeud 
     aqr_sta=creer_noeud(limite_no, limite_se, liste_sta->truc); 
     printf("%s\n", aqr_sta->truc->data.sta.nom);
     aqr_sta=creer_noeud(limite_no, limite_se, liste_sta->suiv->truc);
     printf("%s\n", aqr_sta->truc->data.sta.nom);
  */
  
  aqr_sta=construire_aqr(liste_sta);
  
  detruire_aqr(aqr_sta);
  
  detruire_liste_et_truc(liste_sta);
  return 0;
}
