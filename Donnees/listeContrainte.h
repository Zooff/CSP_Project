#ifndef _LISTECONTRAINTE_
#define _LISTECONTRAINTE_

#include "arbre.h"

typedef struct maillonContrainte
{
  arbre a; // arbre des contraintes
  char* presenceVariable; // chaine de 0 et 1. si presenceVariable[i] == 1, alors il y a la variable d'indice i dans l'arbre de la contrainte, sinon elle n'y est pas
  struct maillonContrainte* suivant;
}maillonContrainte;
typedef maillonContrainte* listeContrainte;

listeContrainte creer_liste_contrainte();
// renvoi un pointeur sur NULL

void ajouter_contrainte(listeContrainte* l, arbre a, char* presenceVariable);
// creer une contrainte et la place au debut de l

int est_vide_liste_contrainte(listeContrainte l);
// retourne 1 si l est vide, 0 sinon

int enlever_contrainte(listeContrainte* l, int indice);
// retourne 1 si arrive a enlever la contrainte d'indice dans l, 0 sinon

void vider_liste_contrainte(listeContrainte* l);
// vide la liste

void afficher_liste_contrainte(listeContrainte l);
// affiche les arbre de chaque contraintes

#endif
