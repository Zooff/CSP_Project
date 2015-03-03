#include "variable.h"

/* Fonction d'utilisation de la liste de variables */


variables creer_liste_var_vide(){

  return NULL;
}

variables ajouter_var(variables V, char* nom_var, pile_domaines doms, liste_de_contraintes liste){


  variables new = (variables)xmalloc(1, sizeof(variable));
  new->id = -1;
  new->nom = nom_var;
  new->domaines = doms;
  new->valeur = doms.dom->valeur - 1;
  new->contraintes = liste;
  new->precedent = NULL;
  if (V == NULL)
    new->suivant = NULL;
  else
    new->suivant = V;
  if (V != NULL)
    V->precedent = new;
  return new;

}

variables supprimer_variable(variables V, char* nom_var){

  variables courant = V;

  while(courant != NULL && strcmp(nom_var, courant->nom) != 0)
    courant = courant->suivant;

  if (courant == NULL){
    fprintf(stderr, " Suppresion impossible\n");
    return V;
  }

  if(courant->suivant == NULL){
    courant->precedent->suivant = NULL;
  }

  else if (courant->precedent == NULL){
    courant->suivant->precedent = NULL;
  }

  else{
    courant->suivant->precedent = courant->precedent;
    courant->precedent->suivant = courant->suivant;
  }

  free(courant);
  return V;
}

void liberer_liste(variables V){
  while (V != NULL){
    variables courant = V;
    V = V->suivant;
    free(courant);
  }
  free(V);
  V = NULL;
}

variable premiere_variable(variables V){
  while (V->precedent != NULL)
    V = V->precedent;
  return *V;
}

variable derniere_variable(variables V){
  while (V->suivant != NULL)
    V = V->suivant;
  return *V;
}


int fin_de_liste(variables V){
  return (V == NULL);
}

/* -------------------------------------- */


/* Fonction de gestion des variables */

int affecter_valeur(variables V){
  domaine d = V->domaines.dom;
  while(V->valeur > d->valeur){
    d = d->suivant;

  }
  if (d != NULL && d->suivant != NULL){
    V->valeur = d->valeur;
    return 1;
  }
  return 0;
}

variable suivante(variable var){
  return *var.suivant;
}

variable precedente(variable var){
  return *var.precedent;
}



/* ------------------------------------------- */

/* Fonction d'affichage */


void afficher_liste(variables V){

  while(V != NULL){
    if ( V->precedent == NULL)
      fprintf(stderr, "Debut \n");
    fprintf(stderr,"Nom : %s, Valeur : %d, ID : %d\n", V->nom, V->valeur, V->id);
    if (V->suivant == NULL)
      fprintf(stderr, "Fin\n");
    V = V->suivant;
  }
}

void afficher_variable(variable var){

  fprintf(stderr, "Nom : %s Valeur : %d, ID : %d\n", var.nom, var.valeur, var.id);


}
