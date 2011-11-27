#include <stdio.h>
#include <stdlib.h>

int main(){
  Un_truc c*=NULL;
  Une_coord coord;
  coord.lon=2;
  coord.lat=5;
  Ttype type = 1;
  Une_station sta;
  sta.nom=strdup("jussieu");
  sta.tab_con=NULL;
  sta.nb_con=0;
  sta.con_pcc=NULL;
  Une_connexion conn;
  conn.sta_dep=NULL;
  conn.sta_arr=NULL;
  conn.ligne=NULL;
  Tdata data;
  data.sta=sta;
  data.con=conn;
  c=creer_truc(Une_coord coord, Ttype type, Tdata data, double uv);

}
