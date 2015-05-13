#ifndef _BACKTRACK
#define _BACKTRACK

#include "variable.h"
#include "arc_consistance.h"

extern FILE* fileToWrite;
extern int typeCSP;

extern int forwardChecking;
extern int modeSilence;

void afficheSolution(variables V);
// cette routine affiche les valeurs dans chaque variable de liste V
// l'affichage est different suivant la valeur de la variable typeCSP

void afficherSolutionSudoku(variables V);
// cette routine affiche les valeurs des variables sous forme d'un sudoku

void resolutionBacktrackUneSolution(variables V);
// la resolution par backtrack ne cherchant qu'une solution

void resolutionBacktrackToutesSolutions(variables V);
// la resolution par backtrack cherchant toutes les solutions

void resolutionBacktrackToutesSolutionsAC(variables V);
// la resolution par arc consistance cherchant toutes les solutions

void resolutionBacktrackToutesSolutionsFC(variables V);
// toutes les solutions avec Forward Checking

void forward_check(variables X_instanciee);
// cette routine doit permettre de reduire la taille des domaines des variables n'ayant pas encore de valeur via les contraintes qu'impose les variables ayant une valeur

#endif
