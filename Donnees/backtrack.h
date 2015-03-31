#ifndef _BACKTRACK
#define _BACKTRACK

#include "variable.h"

extern FILE* fileToWrite;

extern int forwardChecking;

void resolutionBacktrackUneSolution(variables V);

void resolutionBacktrackToutesSolutions(variables V);

void forward_check(variables X_instanciee);

#endif
