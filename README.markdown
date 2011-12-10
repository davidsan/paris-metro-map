# Project 215 (aka RATP)

## Progress : 5 / 6

## Preview
![](https://github.com/sandavid/RATP/raw/master/screen01.png)

## Usage
``` bash
$ make metro_v1
$ ./metro_v1

```

## Test file
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

