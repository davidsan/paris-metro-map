# Project 215 (aka RATP)


## Progress : 5 / 6

```
23/11 correction Stralingrad -> Stalingrad
23/11 correction Abebesses -> Abbesses
23/11 correction F-Mitterand -> Francois Mitterand
23/11 Stations_MRT_v2.csv reduction des doublons
25/11 Stations_MRT_v2.csv corrections de bugs
25/11 Connexions_MRT_v2.csv ajout des correspondances pietonnes
25/11 Lignes_MRT_v2.csv ajout des correspondances pietonnes P
30/11 V0 de l'interface graphique (metro_v0) affiche seulement une liste de
stations.
30/11 Du fait de l'intégration dans GTK, les paramètres linguistiques sont
pris en compte donc strtof ne veut pas lire les flotants avec des points mais
des virgules. -> Stations_MRT_v2fr.csv
02/12 Mise à Jours des fichiers csv (v2 et v2fr).
02/12 Affichage des connexions (metro_v1)
02/12 Zoom et deplacement (metro_v2)
02/12 Remarque : pb identifié dans aqr lors de l'insertion de 2 truc aux mêmes
coordonnées (-> récursion infinie). Solution : détecter la proximité de 2 trucs
et dans ce cas décaler d'un epsilon l'un des 2.
07/12 Nouvelles versions du reseau Stations_IDF.csv Lignes_IDF.csv Connexions_IDF.csv
integration de la ligne H, idem en _fr.csv (pour gtk français).
07/12 Ajout de metro_v3 selection et affichage du plus court chemin.
07/12 Mise a jours de metro_v0 v1 et v2.
07/12 Mise à jours du Makefile.
07/12 Remarque : si n'avez rien mis dans station.c ou connexion.c vous pouvez
suprimer toute référence à ces fichiers dans le Makefile.
```

## Usage

### Test stations

``` bash
$ make test_sta
$ ./test_sta Stations_MRT.csv 

```

### Test lignes

``` bash
$ make test_ligne
$ ./test_ligne Lignes_MRT.csv 

```

### Test connexions

``` bash
$ make test_connexion
$ ./test_connexion Stations_MRT.csv Lignes_MRT.csv Connections_MRT.csv

```

### Test dijkstra

``` bash
$ make test_dijkstra
$ ./test_dijkstra Stations_MRT.csv Lignes_MRT.csv Connections_MRT.csv "Jussieu" "Republique"

```

### Test aqr

``` bash
$ make test_aqr
$ ./test_dijkstra Stations_MRT.csv Lignes_MRT.csv Connections_MRT.csv

```
