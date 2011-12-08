#include <stdio.h>
#include "liste.h"
#include "truc.h"
#include "abr.h"
#include "ligne.h"
#include "aqrtopo.h"

int main(int argc, char *argv[])
{
  Un_elem *liste_sta = NULL;
  Une_ligne *liste_ligne = NULL;
  // Un_elem *liste_con = NULL;
  Un_nabr *abr_sta=NULL;
  Un_noeud *aqr_sta=NULL;

  if (argc != 4)
    {
      fprintf(stderr, "Usage : test_connexion fichier_stations fichier_ligne fichier connexion\n");
      return 1;
    }
	
  if ((liste_sta = lire_stations(argv[1])) == NULL)
    {
      fprintf(stderr, "Erreur : Lecture fichier stations\n");
      return 1;
    }
  ecrire_liste(stdout,liste_sta);

  printf("Prépare à construire ABR\n");
  abr_sta = construire_abr(liste_sta);
  printf("ABR construit\n");


  if ((liste_ligne = lire_lignes(argv[2])) == NULL)
    {
      fprintf(stderr, "Erreur : Lecture fichier lignes\n");
      return 1;
    }
  /*
  if ((liste_con = lire_connexions(argv[3], liste_ligne, abr_sta)) == NULL)
    {
      fprintf(stderr, "Erreur : Lecture fichier connexion\n");
      return 1;
    }
	
  ecrire_liste(stdout,liste_con);
  */
  printf("Prepare à construire AQR\n");
  aqr_sta=construire_aqr(liste_sta);
  printf("AQR construit\n");
  detruire_abr(abr_sta);
	
  // detruire_liste_et_truc(liste_con);

  detruire_liste_et_truc(liste_sta);
	
  detruire_lignes(liste_ligne);

  return 0;
}
