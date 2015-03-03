CC = gcc
CFLAGS = -Wall
LDFLAGS =

all: debug_variable clean

debug_variable: variable.o debug_variable.o xmalloc.o domaine.o pile_domaines.o listes.o
	$(CC) -o $@ $^ $(LDFLAGS)

debug_variable.o: variable.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper:
	rm -rf debug_variable
