#ifndef _LISTECONTRAINTE
#define _LISTECONTRAINTE

#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct struct_liste{
  element info;
  struct struct_liste *suivant;
}maillon;

typedef maillon* liste_de_contraintes;


#endif
