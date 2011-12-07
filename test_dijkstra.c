#include<stdio.h>

#include "liste.h"
#include "truc.h"
#include "abr.h"
#include "ligne.h"
#include "dijkstra.h"

int main(int argc, char *argv[])
{
  Un_elem *liste_sta = NULL;
  Une_ligne *liste_ligne = NULL;
  Un_elem *liste_con = NULL;
  Un_elem *pcc = NULL;
  Un_truc *sta_dep, *sta_arr;
  Un_nabr *abr_sta;

  if (argc != 6)
    {
      fprintf(stderr, "Usage : test_dijkstra f_stations f_ligne f_connexion sta_dep sta_arr\n");
      return 1;
    }
	
  if ((liste_sta = lire_stations(argv[1])) == NULL)
    {
      fprintf(stderr, "Erreur : Lecture fichier stations\n");
      return 1;
    }
	
  abr_sta = construire_abr(liste_sta);

  if ((liste_ligne = lire_lignes(argv[2])) == NULL)
    {
      fprintf(stderr, "Erreur : Lecture fichier lignes\n");
      detruire_liste_et_truc(liste_sta);
      detruire_abr(abr_sta);
      return 1;
    }
	
  if ((liste_con = lire_connexions(argv[3], liste_ligne, abr_sta)) == NULL)
    {
      fprintf(stderr, "Erreur : Lecture fichier connexion\n");
      detruire_liste_et_truc(liste_sta);
      detruire_lignes(liste_ligne);
      detruire_abr(abr_sta);
      return 1;
    }

  if ((sta_dep = chercher_station(abr_sta, argv[4])) == NULL)
    {
      fprintf(stderr, "Erreur : Station depart inconnue : %s\n", argv[4]);
      detruire_liste_et_truc(liste_sta);
      detruire_lignes(liste_ligne);
      detruire_abr(abr_sta);
      return 1;
    }

  if ((sta_arr = chercher_station(abr_sta, argv[5])) == NULL)
    {
      fprintf(stderr, "Erreur : Station arrivee inconnue : %s\n", argv[5]);
      detruire_liste_et_truc(liste_sta);
      detruire_lignes(liste_ligne);
      detruire_abr(abr_sta);
      return 1;
    }
	
  dijkstra(liste_sta, sta_dep);
  
  pcc = cherche_chemin(sta_arr);

  ecrire_liste(stdout, pcc);
   
  printf("temps de parcours = %f minutes \n", sta_arr->user_val);
		
  detruire_liste(pcc);
   
  detruire_abr(abr_sta);

  detruire_liste_et_truc(liste_sta);

  detruire_lignes(liste_ligne);

  return 0;
}
