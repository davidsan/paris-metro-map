#include "liste.h"
#include <stdlib.h>
#include <string.h>

Un_elem *inserer_liste_trie(Un_elem *liste, Un_truc *truc){
  Un_elem *n=(Un_elem*)malloc(sizeof(Un_elem));
  n->truc=truc;
  n->suiv=NULL;
  if(!liste) return n;
  if(liste->truc->coord.lat > truc->coord.lat){
    n->suiv=liste;
    return n;
  }
  Un_elem *p=liste;
  while(liste->suiv){
    if(liste->suiv->truc->coord.lat > truc->coord.lat){
      n->suiv=liste->suiv;
      liste->suiv=n;
      break;
    }
    liste=liste->suiv;
  }
  if(liste->suiv==NULL){
    liste->suiv=n;
  }
  return p;
}

void detruire_liste(Un_elem *liste){
  Un_elem *tmp;
  while(liste){
    tmp=liste->suiv;
    free(liste);
    liste=tmp;
  }
}

void detruire_liste_et_truc(Un_elem *liste){
  Un_elem *tmp;
  while(liste){
    tmp=liste->suiv;
    detruire_truc(liste->truc);
    free(liste);
    liste=tmp;
  }
}

void ecrire_liste(FILE *flux, Un_elem *liste){
  while(liste){
    if(liste->truc->type == STA){
      fprintf(flux,"%d;%f;%f;%s\n", liste->truc->type, liste->truc->coord.lon, liste->truc->coord.lat,liste->truc->data.sta.nom);
    }
    if(liste->truc->type == CON){
      fprintf(flux,"%d;%s;%s;%s\n", liste->truc->type, liste->truc->data.con.ligne->code, liste->truc->data.con.sta_dep->data.sta.nom, liste->truc->data.con.sta_arr->data.sta.nom);
    }
    liste=liste->suiv;
  }
}


Un_elem *lire_stations( char *nom_fichier){
  FILE *f;
  char buff[1024];
  char tmp[1024];
  Un_elem *liste=NULL;
  Un_truc *truc=NULL;
  
  truc=(Un_truc*)malloc(sizeof(Un_truc));
  if (!truc){
    fprintf(stderr, "Erreur allocation mémoire\n");
    return NULL;
  }
    
  f=fopen(nom_fichier, "r");
  if (!f){
    fprintf(stderr, "Erreur lecture fichier\n");
    free(truc);
    return NULL;
  }
  truc->type=STA;
  while(fgets(buff, 1024, f)!=NULL){
   
    
    sscanf(buff, "%f;%f;%[^\t\n]", &(truc->coord.lon), &(truc->coord.lat), tmp);
    truc->data.sta.nom=strdup(tmp);

    /** TEST
     * 
     * fprintf(stdout,"%s \n", tmp);
     *
     **/
    
    liste=inserer_liste_trie(liste, truc);
    truc=(Un_truc*)malloc(sizeof(Un_truc));

  }
  return liste;
}
