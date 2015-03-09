#include "pile_domaines.h"

pile_domaines creer_pile_domaines(){
  return NULL;
}

void empiler(pile_domaines *p, domaine d){

  pile_domaines new = (pile_domaines) malloc(1 * sizeof (maillon_pile_domaines));
  if(new != NULL){
    new->dom = d;
    new->precedent = *p;
    *p = new;
  }
  else
    fprintf(stderr, "Impossible d'empiler un domaine\n");
}

void depiler(pile_domaines *p){

  if(*p != NULL){
    pile_domaines temp = (*p)->precedent;
    free(*p); 
    *p = temp;
  }
}

void afficher_pile(pile_domaines p){

  fprintf(stderr, "\nPile de domaines :\n");
  
  while(p->precedent != NULL){
    afficher_domaine(p->dom);
    p = p->precedent;
  }
  afficher_domaine (p->dom);
}

void vider_pile_domaines(pile_domaines p){
  if(p != NULL){
    vider_pile_domaines(p->precedent);
    vider_domaine(p->dom);
    free(p);
  }
}
