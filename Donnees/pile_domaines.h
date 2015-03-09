#ifndef _DOMAINE
#define _DOMAINE

#include "domaine.h"

typedef struct maillon_pile_domaines{
  domaine dom;
  struct maillon_pile_domaines *precedent;
}maillon_pile_domaines;

typedef maillon_pile_domaines* pile_domaines;

pile_domaines creer_pile_domaines();
void empiler(pile_domaines *p, domaine d);
void depiler(pile_domaines *p);
void afficher_pile(pile_domaines p);
void vider_pile_domaines(pile_domaines p);

#endif
