# Plan Interactif 

## Présentation
L'objectif de ce mini-projet est de réaliser un plan interactif d'un réseau de transport en commun. Il doit être possible de représenter un ensemble d'objets de nature différentes en ayant la possibilité de faire varier l'échelle d’affichage, se déplacer dans le plan, sélectionner graphiquement un objet. Au delà de la représentation graphique du réseau, il devra en être fait une interprétation algorithmique notamment pour déterminer le plus cours chemin entre deux noeuds du réseau.

Le réseau de transport RER, Métro et Tramway d'île de France servira d'illustration à ce problème et les fichiers le décrivant sont fournis.


## Execution 
```
$ ./test_dijkstra Stations_IDF.csv Lignes_IDF.csv Connexions_IDF.csv "Jussieu" "Chatelet"
0;2.354660;48.845989;Jussieu
0;2.362300;48.851250;Sully Morland
0;2.357220;48.853649;Pont Marie
0;2.347220;48.858768;Chatelet
temps de parcours = 10.979761 minutes

$ ./test_dijkstra Stations_IDF.csv Lignes_IDF.csv Connexions_IDF.csv "Creil" "Melun"
0;2.469200;49.263802;Creil
0;2.418005;49.214245;Saint Leu d'Esserent
0;2.376789;49.203426;Precy sur Oise
0;2.362595;49.166985;Boran sur Oise
0;2.326231;49.155239;Bruyeres sur Oise
0;2.279254;49.148293;Persan Beaumont
0;2.280515;49.132542;Nointel Mours
0;2.287794;49.113491;Presles Courcelles
0;2.322854;49.066208;Montsoult Maffliers
0;2.322802;49.045277;Bouffemont Moisselles
0;2.337530;49.032738;Domont
0;2.362980;49.022701;Ecouen Ezanville
0;2.368653;48.995720;Sarcelles Saint-Brice
0;2.353718;48.984486;Groslay
0;2.337936;48.975742;Deuil Montmagny
0;2.328270;48.958279;Epinay Villetaneuse
0;2.345400;48.934429;St Denis
0;2.354870;48.880611;Gare du Nord
0;2.346620;48.861568;Chatelet Les Halles
0;2.373760;48.844681;Gare de Lyon
0;2.426640;48.801781;Maisons Alfort Alfortville
0;2.432230;48.788460;Le Vert de Maisons
0;2.434500;48.766361;Villeneuve Pairie
0;2.438100;48.745361;Villeneuve Triage
0;2.446260;48.728882;Villeneuve St Georges
0;2.462490;48.708179;Montgeron Crosne
0;2.483660;48.706539;Yerres
0;2.507050;48.698849;Brunoy
0;2.533060;48.680920;Boussy St Antoine
0;2.547470;48.667801;Combs la Ville Quincy
0;2.569450;48.628361;Lieusaint Moissy
0;2.583330;48.596931;Savigny le Temple Nandy
0;2.594360;48.565411;Cesson
0;2.624300;48.539680;La Mee sur Seine
0;2.655020;48.527359;Melun
temps de parcours = 195.344177 minutes 


$ ./test_dijkstra Stations_IDF.csv Lignes_IDF.csv Connexions_IDF.csv "Jaures" "Laumiere"
0;2.370660;48.882950;Jaures
0;2.379370;48.885342;Laumiere
temps de parcours = 6.721475 minutes

```


## Aperçu (Linux seulement)
```
$ ./metro_v4
```
![](https://github.com/sandavid/paris-metro-map/raw/master/screen01.png)

## Bugs
- Boutons de déplacement et zoom ne fonctionnent pas.