#include "liste.h"
#include "abr.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LIGNE 256
Un_elem *inserer_liste_trie(Un_elem *liste, Un_truc *truc){
  Un_elem *n=(Un_elem*)malloc(sizeof(Un_elem));
  if (!n){
    fprintf(stderr, "Erreur : allocation mémoire\n");
    return NULL;
  }
  n->truc=truc;
  n->suiv=NULL;
  if(!liste) return n;
  if(liste->truc->user_val > truc->user_val){
    n->suiv=liste;
    return n;
  }
  Un_elem *p=liste;
  while(liste->suiv){
    if(liste->suiv->truc->user_val > truc->user_val){
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
  FILE *f=NULL;
  char buff[1024];
  char tmp[1024];
  Un_elem *liste=NULL;
  Un_truc *truc=NULL;
  Une_coord coord_lu;
  Une_station station_lu;
 
  f=fopen(nom_fichier, "r");
  if (!f){
    fprintf(stderr, "Erreur : lecture fichier\n");
    return NULL;
  }
  
  while(fgets(buff, 1024, f)!=NULL){
    if(sscanf(buff, "%f;%f;%[^\t\n]", &(coord_lu.lon), &(coord_lu.lat), tmp)!=3){
      fprintf(stderr, "Erreur : lecture ligne du fichier\n");
      return NULL;
    }
    station_lu.nom=strdup(tmp);
    station_lu.tab_con=NULL;
    station_lu.nb_con=0;
    station_lu.con_pcc=NULL;
    truc=creer_truc(coord_lu, STA, (Tdata)station_lu, coord_lu.lat);
    if(truc==NULL){
      fprintf(stderr, "Erreur création truc\n");
      return NULL;
    }
    
    /** TEST
     * fprintf(stdout,"%s \n", tmp);
     **/
    
    liste=inserer_liste_trie(liste, truc);
  }
  fclose(f);
  return liste;
}

Un_elem *inserer_deb_liste(Un_elem *liste, Un_truc *truc){
  Un_elem *n=(Un_elem*)malloc(sizeof(Un_elem));
  if (!n){
    fprintf(stderr, "Erreur : allocation mémoire\n");
    return NULL;
  }
  n->truc=truc;
  n->suiv=liste;
  return n;
}

Un_elem *lire_connexions(char *nom_fichier, Une_ligne *liste_ligne, Un_nabr *abr_sta){
  FILE *f=NULL;
  Un_elem *deb=NULL;
  Un_truc *truc=NULL;
  char buff[MAX_LIGNE];
  char *str=NULL;
  float lat_d, lat_a, long_d, long_a, d=0;
  f=fopen(nom_fichier, "r");
  if (!f){
    fprintf(stderr, "Erreur : lecture fichier\n");
    return NULL;
  }

  while(fgets(buff, MAX_LIGNE, f)){
    // Skip comments (eg. "# A3")
    if(strncmp(buff, "#", 1)==0){
      continue;
    }
    truc=(Un_truc*)malloc(sizeof(Un_truc));
    if(!truc){
      fprintf(stderr, "Erreur : allocation mémoire\n");
      return NULL;
    }

    truc->type=CON;

    // Code de la ligne
    str=strtok(buff, ";");
    if(!str){
      fprintf(stderr, "Erreur : lecture code de la ligne\n");
      free(truc);
      return NULL;
    }
    truc->data.con.ligne=chercher_ligne(liste_ligne, str);
    if(!truc->data.con.ligne){
      fprintf(stderr, "Erreur : code ligne non trouvée\n");
      free(str);
      free(truc);
    }

    // Station départ
    str=strtok(NULL, ";");
    if(!str){
      fprintf(stderr, "Erreur : lecture station de départ\n");
      free(truc);
      return NULL;
    }
    truc->data.con.sta_dep=chercher_station(abr_sta, str);
    if(truc->data.con.sta_dep==NULL){
      fprintf(stderr, "Erreur : station non trouvée\n");
      free(truc);
      return NULL;
    }

    // Station arrivée
    str=strtok(NULL, ";");
    if(!str){
      fprintf(stderr, "Erreur : lecture station d'arrivée\n");
      free(truc);
      return NULL;
    }
    truc->data.con.sta_arr=chercher_station(abr_sta, str);
    if(truc->data.con.sta_arr==NULL){
      fprintf(stderr, "Erreur : station non trouvée\n");
      free(truc);
      return NULL;
    }

    // Lecture du user_val et calcul de celui-ci
    str=strtok(NULL, "\n");
    if(!str){
      fprintf(stderr, "Erreur : lecture user_val\n");
      free(truc);
      return NULL;
    }
    truc->user_val = atof(str);

    // Calcul du user_val si != 0.0
    if(truc->user_val != 0.0){
      
      //* initialisation
      lat_d = truc->data.con.sta_dep->coord.lat;  
      long_d = truc->data.con.sta_dep->coord.lon;
      lat_a = truc->data.con.sta_arr->coord.lat;
      long_a = truc->data.con.sta_arr->coord.lon;

      //** calcul distance D séparant sta_dep et sta_arr
      d = sqrt(powf(((lat_d-lat_a)*M_PI/180*6370), 2.0)+powf(((long_d-long_a)*M_PI/180*6370), 2.0));

      //*** affectation
      truc->user_val=d*60/(truc->data.con.ligne->vitesse);
    }

    // mise à jour du tableau des connexions de la station sta_dep
    
    
    deb=inserer_deb_liste(deb, truc);
  }
  fclose(f);
  return deb;
}


Un_truc *extraire_deb_liste(Un_elem **liste){
  Un_elem *tmp=NULL;
  Un_truc *extract=NULL;  
  tmp=*liste;
  *liste=(*liste)->suiv;
  extract=tmp->truc;
  free(tmp);
  return extract;
}


Un_truc *extraire_liste(Un_elem **liste, Un_truc *truc){
  Un_elem *tmp=NULL;
  Un_elem *prec=NULL;
  Un_truc *extract=NULL;
  
  // truc trouvé en position 1
  if((*liste)->truc==truc){
    return extraire_deb_liste(liste);
  }

  // truc ne sera pas en position 1
  tmp=*liste;
  
  while((*liste)->suiv){
    prec=*liste;
    *liste=(*liste)->suiv;
    if((*liste)->truc==truc){
      extract=extraire_deb_liste(liste);
      // raccord de la liste
      prec->suiv=*liste;
      break;
    }
  }
  
  *liste=tmp;
  return extract;  
}
