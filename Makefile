#C_FLAGS = -Wall -g -std=c99
C_FLAGS = -Wall -g
LD_FLAGS = -lm
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
CC = gcc

all : depend test_sta test_ligne test_connexion test_dijkstra metro_v0 metro_v1 metro_v2 #metro_v3

depend : $(SRC)
	$(CC) -MM $^ > .depend

-include .depend

%.o: %.c
	$(CC) $(C_FLAGS) -c $<

metro_callback_v0.o : metro_callback_v0.c
	$(CC) $(C_FLAGS) `pkg-config --cflags gtk+-2.0` -c $^

metro_v0.o : metro_v0.c
	$(CC) $(C_FLAGS) `pkg-config --cflags gtk+-2.0` -c $^

metro_callback_v1.o : metro_callback_v1.c
	$(CC) $(C_FLAGS) `pkg-config --cflags gtk+-2.0` -c $^

metro_v1.o : metro_v1.c
	$(CC) $(C_FLAGS) `pkg-config --cflags gtk+-2.0` -c $^

metro_callback_v2.o : metro_callback_v2.c
	$(CC) $(C_FLAGS) `pkg-config --cflags gtk+-2.0` -c $^

metro_v2.o : metro_v2.c
	$(CC) $(C_FLAGS) `pkg-config --cflags gtk+-2.0` -c $^

metro_callback_v3.o : metro_callback_v3.c
	$(CC) $(C_FLAGS) `pkg-config --cflags gtk+-2.0` -c $^

metro_v3.o : metro_v3.c
	$(CC) $(C_FLAGS) `pkg-config --cflags gtk+-2.0` -c $^


test_sta : test_sta.o liste.o truc.o abr.o ligne.o
	$(CC) $(C_FLAGS) $(LD_FLAGS) -o $@ $^	

test_ligne : test_ligne.o ligne.o
	$(CC) $(C_FLAGS) $(LD_FLAGS) -o $@ $^

test_connexion : test_connexion.o ligne.o abr.o liste.o truc.o
	$(CC) $(C_FLAGS) $(LD_FLAGS) -o $@ $^

test_dijkstra : test_dijkstra.o ligne.o abr.o liste.o truc.o dijkstra.o
	$(CC) $(C_FLAGS) $(LD_FLAGS) -o $@ $^

test_aqr : test_aqr.o ligne.o abr.o liste.o truc.o aqrtopo.o
	$(CC) $(C_FLAGS) $(LD_FLAGS) -o $@ $^

metro_v0 : metro_v0.o metro_callback_v0.o liste.o truc.o ligne.o abr.o
	$(CC) $(C_FLAGS) `pkg-config --libs gtk+-2.0` -o $@ $^

metro_v1 : metro_v1.o metro_callback_v1.o liste.o truc.o ligne.o abr.o
	$(CC) $(C_FLAGS) `pkg-config --libs gtk+-2.0` -o $@ $^

metro_v2 : metro_v2.o metro_callback_v2.o liste.o truc.o ligne.o abr.o aqrtopo.o
	$(CC) $(C_FLAGS) `pkg-config --libs gtk+-2.0` -o $@ $^

metro_v3 : metro_v3.o metro_callback_v3.o liste.o truc.o ligne.o abr.o aqrtopo.o
	$(CC) $(C_FLAGS) `pkg-config --libs gtk+-2.0` -o $@ $^

clean :
	rm -f $(OBJ) test_sta test_ligne test_connexion test_dijkstra .depend metro_v0 metro_v1 metro_v2 metro_v3

.PHONY: all clean depend