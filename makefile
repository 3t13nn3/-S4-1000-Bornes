#Makefile Générique
#1000 Bornes

OBJS	= main.o memory.o game.o affichage.o init.o player.o jouerCarte.o test.o
OUT	= 1000bornes
CC	 = gcc
FLAGS	 = -c 
CFLAGS	= -O3 -Wall
HEADER = head.h

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT)

main.o: main.c $(HEADER)
	$(CC) $(FLAGS) main.c

memory.o: memory.c $(HEADER)
	$(CC) $(FLAGS) memory.c

game.o: game.c $(HEADER)
	$(CC) $(FLAGS) game.c

affichage.o: affichage.c $(HEADER)
	$(CC) $(FLAGS) affichage.c

init.o: init.c $(HEADER)
	$(CC) $(FLAGS) init.c

player.o: player.c $(HEADER)
	$(CC) $(FLAGS) player.c

jouerCarte.o: jouerCarte.c $(HEADER)
	$(CC) $(FLAGS) jouerCarte.c
	
test.o: test.c $(HEADER)
	$(CC) $(FLAGS) test.c

clean:
	rm -f $(OBJS) $(OUT)
