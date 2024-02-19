#! /bin/bash

CC=gcc
DSRC=src
DOBJ=build/linux64/obj
DEXEC=build/linux64
EXEC=main

all: link run

link: main.o ide_menu.o fide.o
	$(CC) $(DOBJ)/main.o $(DOBJ)/fide.o $(DOBJ)/ide_menu.o -g -Wall -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o $(DEXEC)/$(EXEC)
main.o: ${DSRC}/main.c
	$(CC) -c $(DSRC)/main.c -Isrc -Wall -o $(DOBJ)/main.o
ide_menu.o: $(DSRC)/ide_menu.c
	$(CC) -c $(DSRC)/ide_menu.c -Isrc -Wall -o $(DOBJ)/ide_menu.o
		
fide.o: $(DSRC)/fide.c
	$(CC) -c $(DSRC)/fide.c -Isrc -Wall -o $(DOBJ)/fide.o
		
run:
	cd $(DEXEC)
	./$(EXEC)

clean:
	rm -rf $(DOBJ)/*.o
