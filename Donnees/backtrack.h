#ifndef _BACKTRACK
#define _BACKTRACK

#include "variable.h"
#include "arc_consistance.h"

extern FILE* fileToWrite;
extern int typeCSP;

extern int forwardChecking;
extern int modeSilence;

void afficheSolution(variables V);

void resolutionBacktrackUneSolution(variables V);

void resolutionBacktrackToutesSolutions(variables V);

void forward_check(variables X_instanciee);

#endif
