#include "listes.h"
#include <stdio.h>
#include <stdlib.h>

int liste_est_vide(liste_de_contraintes l){
  if(l == NULL)
    return 1;
  else return 0;
}

liste_de_contraintes ajouter_element(liste_de_contraintes l, element e) // ajoute un élément au début de la liste_de_contraintes
{
  liste_de_contraintes new = NULL;
  new =(liste_de_contraintes) malloc(1 * sizeof(maillon));
  new -> info = e;
  new-> suivant = l;

  return new;
}

liste_de_contraintes supprimer_element(liste_de_contraintes l, element e){
  if(liste_est_vide(l))
    return l;

  if(l->info == e ){
    liste_de_contraintes new_debut = l->suivant;
    free(l);
    return new_debut;
    }
  else {
    liste_de_contraintes courant = l->suivant;
    liste_de_contraintes precedent = l;

    while (courant != NULL && courant -> info != e){
      courant = courant -> suivant;
      precedent = precedent -> suivant;
    }

    if(courant != NULL){
      precedent -> suivant = courant -> suivant;
      free(courant);
    }

    return l;
  }
}

void afficher_liste_de_contraintes(liste_de_contraintes l){
  liste_de_contraintes courant = l;
  while (courant!=NULL){
    printf("%d\n", courant -> info);
    courant = courant -> suivant;
  }
}

//initialiser la liste_de_contraintes à NULL avant de l'utiliser
