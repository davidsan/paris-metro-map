#C_FLAGS = -Wall -g -std=c99
C_FLAGS = -Wall -g

all : test_sta test_ligne test_connexion test_dijkstra test_aqr metro_v0 metro_v1 metro_v2

truc.o : truc.c
	gcc ${C_FLAGS} -c truc.c

liste.o : liste.c
	gcc ${C_FLAGS} -c liste.c

station.o : station.c
	gcc ${C_FLAGS} -c station.c

abr.o : abr.c
	gcc ${C_FLAGS} -c abr.c

test_sta.o : test_sta.c
	gcc ${C_FLAGS} -c test_sta.c

test_sta : test_sta.o liste.o truc.o abr.o station.o
	gcc ${C_FLAGS} -o test_sta test_sta.o truc.o liste.o abr.o station.o

ligne.o : ligne.c
	gcc ${C_FLAGS} -c ligne.c

test_ligne.o : test_ligne.c
	gcc ${C_FLAGS} -c test_ligne.c

test_ligne : test_ligne.o ligne.o
	gcc ${C_FLAGS} -o test_ligne test_ligne.o ligne.o

connexion.o : connexion.c
	gcc ${C_FLAGS} -c connexion.c

test_connexion.o : test_connexion.c
	gcc ${C_FLAGS} -c test_connexion.c

test_connexion : test_connexion.o connexion.o ligne.o abr.o liste.o truc.o station.o
	gcc ${C_FLAGS} -lm -o test_connexion test_connexion.o connexion.o ligne.o abr.o liste.o truc.o station.o

dijkstra.o : dijkstra.c
	gcc ${C_FLAGS} -c dijkstra.c

test_dijkstra.o : test_dijkstra.c
	gcc ${C_FLAGS} -c test_dijkstra.c

test_dijkstra : test_dijkstra.o connexion.o ligne.o abr.o liste.o truc.o station.o dijkstra.o
	gcc ${C_FLAGS} -lm -o test_dijkstra test_dijkstra.o connexion.o ligne.o abr.o liste.o truc.o station.o dijkstra.o

aqrtopo.o : aqrtopo.c
	gcc ${C_FLAGS} -c aqrtopo.c

test_aqr.o : test_aqr.c
	gcc ${C_FLAGS} -c test_aqr.c

test_aqr : test_aqr.o connexion.o ligne.o abr.o liste.o truc.o station.o aqrtopo.o
	gcc ${C_FLAGS} -lm -o test_aqr test_aqr.o connexion.o ligne.o abr.o liste.o truc.o station.o aqrtopo.o

metro_callback_v0.o : metro_callback_v0.c
	gcc ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c metro_callback_v0.c

metro_v0.o : metro_v0.c
	gcc ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c metro_v0.c

metro_v0 : metro_v0.o metro_callback_v0.o liste.o truc.o station.o
	gcc ${C_FLAGS} `pkg-config --libs gtk+-2.0` -o metro_v0 metro_v0.o metro_callback_v0.o liste.o truc.o station.o

metro_callback_v1.o : metro_callback_v1.c
	gcc ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c metro_callback_v1.c

metro_v1.o : metro_v1.c
	gcc ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c metro_v1.c

metro_v1 : metro_v1.o metro_callback_v1.o liste.o truc.o station.o ligne.o connexion.o abr.o
	gcc ${C_FLAGS} `pkg-config --libs gtk+-2.0` -o metro_v1 metro_v1.o metro_callback_v1.o liste.o truc.o station.o connexion.o ligne.o abr.o

metro_callback_v2.o : metro_callback_v2.c
	gcc ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c metro_callback_v2.c

metro_v2.o : metro_v2.c
	gcc ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c metro_v2.c

metro_v2 : metro_v2.o metro_callback_v2.o liste.o truc.o station.o ligne.o connexion.o abr.o aqrtopo.o
	gcc ${C_FLAGS} `pkg-config --libs gtk+-2.0` -o metro_v2 metro_v2.o metro_callback_v2.o liste.o truc.o station.o connexion.o ligne.o abr.o aqrtopo.o

clean :
	rm -f *.o test_sta test_ligne test_connexion test_dijksra test_aqr metro_v0 metro_v1 metro_v2
