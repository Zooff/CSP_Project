#include "variable.h"

void majdomaineFC(variables V);
void depile_tout_domaine(variables V);
void reduction_domaine_AC(variables V, listeContrainte contrainte, variables ListeVariable);
void reduction_domaine_AC_2_variables(variables V1, variables V2, listeContrainte contrainte, variables ListeVariable);
void arc_consistance(variables V);
