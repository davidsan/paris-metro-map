#include "truc.h"
#include <stdlib.h>
#include <stdio.h>

Un_truc *creer_truc(Une_coord coord, Ttype type, Tdata data, double uv){
  Un_truc *nouveau =(Un_truc*)malloc(sizeof(Un_truc));
  if(!nouveau){
    fprintf(stderr, "Erreur : allocation mémoire\n");
    return NULL;
  }
  nouveau->coord=coord;
  nouveau->type=type;
  nouveau->data=data;
  nouveau->user_val=(float)uv;
  return nouveau;
}

void detruire_truc(Un_truc *truc){
  if(truc){
    if(truc->type == STA){
      free(truc->data.sta.nom);
      free(truc->data.sta.tab_con);
      free(truc->data.sta.con_pcc);
    }
    free(truc);
  }
}
