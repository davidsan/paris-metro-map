#ifndef LISTES
#define LISTES

/* includes */

#include "truc.h"
#include "ligne.h"
#include "abr_type.h"
#include <stdio.h>

/* defines */

#define MAX_LIGNE 1024

/* types */

typedef struct _un_elem
	{
	Un_truc *truc; //Une station ou une connexion
	struct _un_elem *suiv;
	} Un_elem;

/* fonctions de manipulation de liste de stations*/

Un_elem *lire_stations( char *nom_fichier);

/* fonctions de manipulation de liste de connexions*/

Un_elem *lire_connexions(char *nom_fichier, Une_ligne *liste_ligne, Un_nabr *abr_sta);

/* fonctions generiques */

Un_elem *inserer_deb_liste(Un_elem *liste, Un_truc *truc);

Un_elem *inserer_liste_trie(Un_elem *liste, Un_truc *truc);

Un_truc *extraire_deb_liste(Un_elem **liste);

Un_truc *extraire_liste(Un_elem **liste, Un_truc *truc);

void ecrire_liste( FILE *flux, Un_elem *liste);

void detruire_liste(Un_elem *liste);

void detruire_liste_et_truc(Un_elem *liste);

void limites_zone(Un_elem *liste, Une_coord *limite_no, Une_coord *limite_se);

#endif
