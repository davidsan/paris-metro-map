#include "abr.h"
#include <stdlib.h>

Un_nabr *construire_abr(Un_elem *liste_sta){
  Un_nabr *abr=NULL;
  abr = (Un_nabr*)malloc(sizeof(Un_nabr));
  if (!abr){
    fprintf(stderr, "Erreur d'allocation mémoire. \n");
    return NULL;
  }
  
  return NULL;
}

int est_feuille(Un_nabr *noeud){
  if(noeud->g==NULL && noeud->d==NULL){
    return 1; // true
  }
  else{
    return 0;
  }
}


void detruire_abr(Un_nabr *abr){
  // free que les nabr
  // recursion easier ?
}

Un_truc *chercher_station(Un_nabr *abr, char *nom){
  Un_truc *station=NULL;
  
  return NULL;

}
