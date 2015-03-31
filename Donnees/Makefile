CC = gcc
CFLAGS = -Wall -lm -g
LISTE = main.c y.tab.o lex.o variable.o xmalloc.o domaine.o pile_domaines.o arbre.o  listeContrainte.o backtrack.o

all: main clean

main: $(LISTE)
	$(CC) $(LISTE) -o main  $(CFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

y.tab.c: yacc.y
	yacc -d yacc.y -o y.tab.c

lex.o: lex.yy.c y.tab.c

lex.yy.c: lex.l
	flex -o lex.yy.c lex.l

clean:
	rm -rf *.o y.tab.c y.tab.h lex.yy.c
