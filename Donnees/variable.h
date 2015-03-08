 #ifndef _VARIABLE
#define _VARIABLE

/* Bibliotheque permettant l'implémentation des variables */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xmalloc.h"
#include "pile_domaines.h"
#include "listes.h"


typedef struct variable{
  int id; // Chaque variable possède un id unique (initialement à -1, valeur fixé lors du tri des variables)
  char * nom; // Nom de la variable
  float valeur; // Valeur prise par la variable (initialement à borne_inférieur - 1 du domaine)
  pile_domaines domaines; //Pointeur sur le premier domaine de la pile
  liste_de_contraintes contraintes; // Les contraintes à vérifier pour cette variable lorsqu'elle est affectée
  struct variable * suivant; // Pointeur sur la variable suivante
  struct variable * precedent; //Pointeur sur la variable precedent
} variable;

typedef variable* variables;

// Initialise un pointeur NULL
variables creer_liste_var_vide();

// Ajoute une variable en début de liste (Seul le nom sera passé en parametre, sauf pour l'instant pour les divers tests)
variables ajouter_var(variables V, char* nom_var, pile_domaines domaines, liste_de_contraintes listes);

// Supprime une variable de la liste (La recherche est pour l'instant effectuer avec son nom, peux être modifier)
variables supprimer_variable(variables V, char* nom_var);

// Libere la liste de variables
void liberer_liste(variables V);

// Retourne la premiere variable
variable premiere_variable(variables V);

// Retourne la dernière variable
variable derniere_variable(variables V);

// Affecte la valeur suivante du domaine a la variable
int affecter_valeur(variables V);

// Retourne la variable suivante
variable suivante(variable var);

// Retourne la variable precedente
variable precedente(variable var);

// Indique la fin de liste, 1 si en fin, 0 sinon
int fin_de_liste(variables V);

// Fonction d'affichage de la liste de variables, a tout les coup mieux que celle de Julien :p
void afficher_liste(variables V);

// Fonction d'affichage d'une variable
void afficher_variable(variable var);



  #endif
