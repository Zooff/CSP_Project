#include "pile_domaines.h"


void empiler(pile_domaines **p, domaine d){

  pile_domaines *new = malloc(sizeof (*new));
  if(new != NULL){
    new->dom = d;
    new->precedent = *p;
    *p = new;
  }
}

void depiler(pile_domaines **p){

  if(p != NULL){
    pile_domaines *temp = (*p)->precedent;
    free(*p), *p = NULL;
    *p = temp;
  }
}

void afficher_pile(pile_domaines **p){

  pile_domaines *temp = *p;
  printf("\nPile de domaines :\n");

  while((*p)->precedent != NULL){
    afficher_domaine( (*p)->dom);
    *p = (*p)->precedent;
  }
  afficher_domaine ((*p)->dom);

  *p = temp;
}

/*
int main(int argc, char **argv){

  pile_domaines *p1;
  empiler(&p1,5);
  empiler(&p1,6);
  empiler(&p1,7);
  empiler(&p1,8);
  afficher_pile(&p1);
  depiler(&p1);
  afficher_pile(&p1);

  return EXIT_SUCCESS;

}
*/
