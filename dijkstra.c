#include "dijkstra.h"
#include <float.h>

void dijkstra(Un_elem *liste_sta, Un_truc *sta_dep){
  Un_elem *mem=NULL;
  Un_elem *q=NULL;
  Un_truc *truc=NULL;
  Un_truc *trucArr=NULL;
  int i;
  float tpsDeParcours;
	
  // 2. Initialiser la valeur de toutes les (autres) stations à +00
  mem=liste_sta;
  while(liste_sta){
    liste_sta->truc->user_val=DBL_MAX;
    liste_sta=liste_sta->suiv;
  }
  liste_sta=mem;
  
  // 1. Initialiser la valeur de la station d'origine (user_val) à 0.0
  sta_dep->user_val=0.0;
  
  // 3. Constituer Q un ensemble de toutes les stations
  //    ordonnées suivant leurs user_val croissantes
  mem=liste_sta;
  while(liste_sta){
    q=inserer_liste_trie(q, liste_sta->truc);
    liste_sta=liste_sta->suiv;
  }
  liste_sta=mem;

  // 4. Tant que Q est non vide, en extraire la première station.
  while(q!=NULL){
    truc=extraire_deb_liste(&q);

    // 5. Pour toutes les connexions partant de cette station
    for(i=0; i < truc->data.sta.nb_con; i++){
      //    a. Mettre à jour les valeurs des stations destinations de ces connexions
      //       si nécessaire (nouvelle valeur calculée du temps de parcours inférieure)
      //       tout en préservant l'ordre de l'ensemble Q.
      //       i. Calcul du temps de parcours
      tpsDeParcours=truc->user_val; 
      tpsDeParcours+=truc->data.sta.tab_con[i]->user_val;
        
      if(truc->data.sta.con_pcc != NULL){
	if(truc->data.sta.con_pcc->data.con.ligne == truc->data.sta.tab_con[i]->data.con.ligne){
	  //       i.a Pause à chaque station (30 sec)
	  tpsDeParcours+=T_PAU;
	}
	else{
	  //       i.b Correspondance (2 minutes 30 sec)
	  tpsDeParcours+=T_COR;
	}	  
      }
      else{
	//       i.c Temps de parcours supplémentaire si station de départ (intervalle)
	tpsDeParcours+=truc->data.sta.tab_con[i]->data.con.ligne->intervalle;
      }
          
      //       ii. Temps de parcours inférieur ?
      if(tpsDeParcours < truc->data.sta.tab_con[i]->data.con.sta_arr->user_val){

	//        ii.a Extraire la station d'arrivée
	trucArr=extraire_liste(&q, truc->data.sta.tab_con[i]->data.con.sta_arr);

	//        ii.b Modifier user_val = tpsDeParcours
	trucArr->user_val = tpsDeParcours;
	
	//        iii.c Remettre la station d'arrivée dans q à la bonne place
	q=inserer_liste_trie(q, trucArr);

	//    b. Si la valeur d'une station est mise à jour, mémoriser la connexion
	trucArr->data.sta.con_pcc=truc->data.sta.tab_con[i];
      }
    }   
  }
  //    c. Répéter 4. 
}

Un_elem *cherche_chemin(Un_truc *sta_arr){
  Un_elem *res=NULL;
  Un_truc *tmp=NULL;
 
  if(sta_arr->data.sta.con_pcc==NULL){
    fprintf(stdout, "Erreur : Le plus court chemin n'a pas été trouvé.\n");
    return NULL;
  }
  tmp=sta_arr;
  res=inserer_deb_liste(res, tmp);  

  while(tmp->data.sta.con_pcc!=NULL){
    tmp=tmp->data.sta.con_pcc->data.con.sta_dep;
    res=inserer_deb_liste(res, tmp);  
  }
  return res;
}
