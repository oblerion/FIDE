#! /bin/bash

CC=gcc
DSRC=src
DOBJ=build/linux64/obj
DEXEC=build/linux64
EXEC=main

all: link run

link: main.o ui.o kbd_layout.o ide.o ide_menu.o ide_parameter.o math.o
	$(CC) $(DOBJ)/main.o $(DOBJ)/ui.o $(DOBJ)/kbd_layout.o $(DOBJ)/ide.o $(DOBJ)/ide_menu.o $(DOBJ)/ide_parameter.o $(DOBJ)/math.o -g -Wall -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o $(DEXEC)/$(EXEC)

main.o: ${DSRC}/main.c
	$(CC) -c $(DSRC)/main.c -Isrc -Wall -o $(DOBJ)/main.o

ui.o: $(DSRC)/ui.c
	$(CC) -c $(DSRC)/ui.c -Isrc -Wall -o $(DOBJ)/ui.o

kbd_layout.o: $(DSRC)/kbd_layout.c
	$(CC) -c $(DSRC)/kbd_layout.c -Isrc -Wall -o $(DOBJ)/kbd_layout.o
	
ide.o: $(DSRC)/ide.c
		$(CC) -c $(DSRC)/ide.c -Isrc -Wall -o $(DOBJ)/ide.o

ide_menu.o: $(DSRC)/ide_menu.c
		$(CC) -c $(DSRC)/ide_menu.c -Isrc -Wall -o $(DOBJ)/ide_menu.o
		
ide_parameter.o: $(DSRC)/ide_parameter.c
		$(CC) -c $(DSRC)/ide_parameter.c -Isrc -Wall -o $(DOBJ)/ide_parameter.o
	
math.o: $(DSRC)/math.c
		$(CC) -c $(DSRC)/math.c -Isrc -Wall -o $(DOBJ)/math.o
		
run:
	cd $(DEXEC)
	./$(EXEC)

clean:
	rm -rf $(DOBJ)/*.o
