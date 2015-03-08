#include "listeContrainte.h"

listeContrainte creer_liste_contrainte()
{
  return NULL;
}

void ajouter_contrainte(listeContrainte* l, arbre a, char* presenceVariable)
{ // ajout en debut de liste
  listeContrainte new = (listeContrainte) malloc(1 * sizeof(maillonContrainte));
  new->a = a;
  new->presenceVariable = presenceVariable;
  new->suivant = *l;
  *l = new;
}

int est_vide_liste_contrainte(listeContrainte l)
{
  return l == NULL;
}

int enlever_contrainte(listeContrainte* l, int indice)
{
  listeContrainte precedent, courant = *l;
  if(est_vide_liste_contrainte(*l))
    return 0;
  if(indice == 0) // si on supprime le premier de la liste
  { // il faut changer l
    *l = (*l)->suivant;
    free(courant);
    return 1;
  }
  while(courant != NULL && indice != 0)
  {
    precedent = courant;
    courant = courant->suivant;
    indice--;
  }
  if(courant != NULL)
  {
    precedent->suivant = courant->suivant;
    free(courant);
    return 1;
  }
  return 0;
}

void vider_liste_contrainte(listeContrainte* l)
{
  while(enlever_contrainte(l, 0)) // tant qu'on arrive a enlever un element, on continue
    ;
}


void afficher_liste_contrainte(listeContrainte l)
{
  int i=1;
  fprintf(stderr, "Debut d'affichage d'un ensemble de contraintes");
  while(l != NULL)
  {
    fprintf(stderr, "\nPresence de variables dans contrainte %d: %s\n", i, l->presenceVariable);
    fprintf(stderr, "Arbre de contrainte %d:\n", i++);
    afficheArbre(l->a, 0);
    l = l->suivant;
  }
  fprintf(stderr, "Fin d'affichage d'un ensemble de contraintes\n");
}
