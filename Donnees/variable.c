#include "variable.h"

/* Fonction d'utilisation de la liste de variables */


variables creer_liste_var_vide(){

  return NULL;
}

variables ajouter_var(variables V, char* nom_var){


  variables new = (variables)xmalloc(1, sizeof(variable));
  new->id = -1;
  new->nom = nom_var;
  new->precedent = NULL;
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
  variables courant;
  while (V != NULL){
    courant = V;
    V = V->suivant;
    vider_liste_contrainte(courant->contraintes);
    free(courant->nom);
    free(courant);
  }
  vider_liste_contrainte(courant->contraintes);
  free(courant->nom);
  free(courant);
}

variable* premiere_variable(variables V){
  while (V->precedent != NULL)
    V = V->precedent;
  return V;
}

variable* derniere_variable(variables V){
  while (V->suivant != NULL)
    V = V->suivant;
  return V;
}


int fin_de_liste(variables V){
  return (V == NULL);
}

/* -------------------------------------- */


/* Fonction de gestion des variables */

int affecter_valeur(variables V){
  domaine d = V->domaines.dom;
  while(d != NULL && V->valeur > d->valeur){
    d = d->suivant;

  }
  if (d != NULL){
    V->valeur = d->valeur;
    return 1;
  }
  return 0;
}

variable* suivante(variable* var){
  return var->suivant;
}

variable* precedente(variable* var){
  return var->precedent;
}



/* ------------------------------------------- */

/* Fonction d'affichage */


void afficher_liste(variables V){

  while(V != NULL){
    if ( V->precedent == NULL)
      fprintf(stderr, "Debut \n");
    afficher_variable(*V);
    if (V->suivant == NULL)
      fprintf(stderr, "Fin\n");
    V = V->suivant;
  }
}

void afficher_variable(variable var){

  fprintf(stderr, "Nom : %s Valeur : %d, ID : %d\n", var.nom, (int)(var.valeur), var.id);


}

void affecterDommaineDansVariables(variables V, domaine d){
  pile_domaines p = creer_pile_domaines();
  empiler(&p, d);
  while(V != NULL){
        V->domaines = p;
        V = V->suivant;
    }
}
