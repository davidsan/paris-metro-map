# Project 215 (aka RATP)


## Progress : 4 / 6

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
```

## Usage

### Test stations

``` bash
$ make -f Makefile2 test_sta
$ ./test_sta Stations_MRT.csv 

```

### Test lignes

``` bash
$ make -f Makefile2 test_ligne
$ ./test_ligne Lignes_MRT.csv 

```

### Test connexions

``` bash
$ make -f Makefile2 test_connexion
$ ./test_connexion Stations_MRT.csv Lignes_MRT.csv Connections_MRT.csv

```