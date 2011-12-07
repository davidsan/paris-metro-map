#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ligne.h"

#define MAX_LIGNE 256

Une_ligne *lire_lignes(char *nom_fichier){
  char *str=NULL;
  Une_ligne *deb=NULL;
  Une_ligne *prec=NULL;
  Une_ligne *ligne=NULL;
  char buff[MAX_LIGNE];
  FILE *f = fopen(nom_fichier,"r");
  if(!f){
    fprintf(stderr,"Erreur : ouverture fichier %s impossible\n", nom_fichier);
    return NULL;
  }
  while (fgets(buff,MAX_LIGNE,f)){
    str=strtok(buff,";");
    if (!str){
      fprintf(stderr,"Erreur : lecture du code de la ligne\n");
      fclose(f);
      return NULL;
    }
    ligne=(Une_ligne*)malloc(sizeof(Une_ligne));
    if(!ligne){
      fprintf(stderr,"Erreur : allocation mémoire\n");
      fclose(f);
      return NULL;
    }
    ligne->code=strdup(str);
    str=strtok(NULL,";");
    if (!str){
      fprintf(stderr,"Erreur : lecture de la vitesse\n");
      fclose(f);
      return NULL;
    }
    ligne->vitesse=atof(str);
    str=strtok(NULL,";");
    if (!str){
      fprintf(stderr,"Erreur : lecture de l'intervalle\n");
      free(ligne);
      fclose(f);
      return NULL;
    }
    ligne->intervalle=atof(str);
    str=strtok(NULL,";");
    if (!str){
      fprintf(stderr,"Erreur : lecture de la couleur de la ligne\n");
      free(ligne);
      fclose(f);
      return NULL;
    }
    ligne->color=strdup(str);
    if(prec)
      prec->suiv=ligne;
    else
      deb=ligne;
    prec=ligne;
  }
  prec->suiv=NULL;
  fclose(f);
  return deb;
}

void afficher_lignes(Une_ligne *lligne){
  while(lligne){
    fprintf(stdout, "%s;%f;%f;%s", lligne->code, lligne->vitesse, lligne->intervalle, lligne->color);
    lligne=lligne->suiv;
  }
}

void detruire_lignes(Une_ligne *lligne){
  if(lligne!=NULL){
    detruire_lignes(lligne->suiv);
    free(lligne->code);
    free(lligne->color);
    free(lligne);
  }
}

Une_ligne *chercher_ligne(Une_ligne *lligne, char *code){
  while(lligne){
    if(strcmp(code, lligne->code)==0){
      return lligne;
    }
    lligne=lligne->suiv;
  }
  fprintf(stderr, "Erreur : ligne non trouvée\n");
  return NULL;
}
