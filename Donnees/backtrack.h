#ifndef _BACKTRACK
#define _BACKTRACK

#include "variable.h"

extern FILE* fileToWrite;
extern int typeCSP;

extern int forwardChecking;

void afficheSolution(variables V);

void resolutionBacktrackUneSolution(variables V);

void resolutionBacktrackToutesSolutions(variables V);

void forward_check(variables X_instanciee);

#endif
