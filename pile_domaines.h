#ifndef _DOMAINE
#define _DOMAINE

#include "domaine.h"

//typedef int domaine;

typedef struct pile_domaines{
  domaine dom;
  struct pile_domaines *precedent;
}pile_domaines;


void empiler(pile_domaines **p, domaine d);
void depiler(pile_domaines **p);
void afficher_pile(pile_domaines **p);

#endif
