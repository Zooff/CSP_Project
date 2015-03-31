 #ifndef _VARIABLE
#define _VARIABLE

/* Bibliotheque permettant l'implémentation des variables */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xmalloc.h"
#include "pile_domaines.h"
#include "listeContrainte.h"

extern int num_ligne; // recouvre la variable num_ligne du fichier lex.l
int typeCSP;
int modeSilence;
FILE* fileToWrite;

typedef struct variable{
  int id; // Chaque variable possède un id unique (initialement à -1, valeur fixé lors du tri des variables)
  char * nom; // Nom de la variable
  float valeur; // Valeur prise par la variable (initialement à borne_inférieur - 1 du domaine)
  pile_domaines domaines; //Pointeur sur le premier domaine de la pile
  listeContrainte contraintes; // Les contraintes à vérifier pour cette variable lorsqu'elle est affectée
  struct variable * suivant; // Pointeur sur la variable suivante
  struct variable * precedent; //Pointeur sur la variable precedent
} variable;

typedef variable* variables;

// Initialise un pointeur NULL
variables creer_liste_var_vide();

// Ajoute une variable en début de liste
variables ajouter_var(variables V, char* nom_var);

// Supprime une variable de la liste (La recherche est pour l'instant effectuer avec son nom, peux être modifier)
variables supprimer_variable(variables V, char* nom_var);

// Libere la liste de variables
void liberer_liste(variables V);

// Retourne la premiere variable
variable* premiere_variable(variables V);

// Retourne la dernière variable
variable* derniere_variable(variables V);

// Affecte la valeur suivante du domaine a la variable
int affecter_valeur(variables V);

// Retourne la variable suivante
variable* suivante(variable* var);

// Retourne la variable precedente
variable* precedente(variable* var);

// Indique la fin de liste, 1 si en fin, 0 sinon
int fin_de_liste(variables V);

// Fonction d'affichage de la liste de variables, a tout les coup mieux que celle de Julien :p
void afficher_liste(variables V);

// Fonction d'affichage d'une variable
void afficher_variable(variable var);

// Fonction d'affichage du résultat
void afficherResultat(variables V);

// Procédure d'affectation d'un domaine à une liste de variables. On créer une pile de domaines contenant d et on met cette pile dans V->domaines
void affecterDommaineDansVariables(variables V, domaine d);

// met v2 apres v1 en modifiant v1. pour cela on change le pointeur suivant du dernier element de v1 et le pointeur precedent du premier de v2
void concat_variables(variables* v1, variables* v2);

// retourne un pointeur sur la variable portant ce nom si elle existe, sinon quitte le programme. on place aussi l'indice de cette variable dans *indiceVariable
variable* retournerVariablePortantNom(variables V, char* nom, int* indiceVariable);

// renvoi 0 si l'evaluation d'au moins un des arbres de contrainte dans variable->contraintes vaut 0
// sinon renvoi 1
// renvoi aussi 1 si la variable n'a pas de contrainte
int verifier_les_contraintes(variable* variable);

// pour chaque variable de V, on prend un sous-ensemble des contraintes de lc et on les met dans la liste des contraintes de cette variable.
// une contrainte est mise dans la liste d'une variable
//  - si la contrainte fait intervenir cette variable
//  - si la contrainte ne fait pas intervenir de variable d'indice plus grand
// si il reste des contraintes non asignee a une variable en fin de cette procedure, on les supprime
void affecterContraintesDansVariables(variables V, listeContrainte* lc, int nombreVariable);

// met la premiere valeur du domaine -1 dans chaque variable
void initialiserValeurVariables(variables V);

// ajout des contraintes differents entre la variable dont le nom est dans nomVariable et toutes les variables dans la liste variablesAlldiff
// fonction utile pour faire les contraintes ALLDIFF
void ajouterContraintesDifferent(char* nomVariable, variables variablesAlldiff, listeContrainte* contraintes, variables V, int nombreVariable);



#endif
