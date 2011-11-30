# Project 215 (aka RATP)


Test stations

``` bash
$ make -f Makefile2 test_sta
$ ./test_sta Stations_MRT.csv 

```

Test lignes

``` bash
$ make -f Makefile2 test_ligne
$ ./test_ligne Lignes_MRT.csv 

```

Test connexions

``` bash
$ make -f Makefile2 test_connexion
$ ./test_connexion Stations_MRT.csv Lignes_MRT.csv Connections_MRT.csv 

```

