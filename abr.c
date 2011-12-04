#include "abr.h"
#include <stdlib.h>
#include <string.h>


Un_nabr *creer_nabr(Un_truc *truc){
  Un_nabr *tmp=NULL;
  tmp=(Un_nabr *)malloc(sizeof(Un_nabr));
  if(!tmp){
    fprintf(stderr, "Erreur : allocation mémoire\n");
    return NULL;
  }
  tmp->truc=truc;
  tmp->g=NULL;
  tmp->d=NULL;
  return tmp;
}

Un_nabr *inserer_abr(Un_nabr *abr, Un_nabr *n){
  if (!abr)
    return n;
  if (strcmp (n->truc->data.sta.nom,abr->truc->data.sta.nom)<=0){
    abr->g = inserer_abr(abr->g, n);
  }
  else{
    abr->d = inserer_abr(abr->d, n);
  }
  return abr;
}

Un_nabr *construire_abr(Un_elem *liste_sta){
  Un_nabr *abr=NULL;
  Un_nabr *noeud=NULL;
  Un_elem *mem=liste_sta;
  while(liste_sta){
    noeud = creer_nabr(liste_sta->truc);
    abr = inserer_abr(abr, noeud);
    liste_sta = liste_sta->suiv;
  }
  liste_sta=mem;
  return abr;
}


void detruire_abr(Un_nabr *abr){
  if(abr){
    detruire_abr(abr->g);
    detruire_abr(abr->d);
    free(abr);
  }
}

Un_truc *chercher_station(Un_nabr *abr, char *nom){
  int cmp;
  if(abr){
    cmp=strcmp(nom, abr->truc->data.sta.nom);
    if(cmp==0){
      return abr->truc;
    }
    if(cmp<0)
      return chercher_station(abr->g, nom);
    else
      return chercher_station(abr->d, nom);
  }
  else{
    return NULL;
  }
}
