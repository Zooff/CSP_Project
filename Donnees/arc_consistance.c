#include "arc_consistance.h"

void majdomaineFC(variables X_instanciee){
	variables V = suivante(X_instanciee);
	listeContrainte l;
	domaine D;
	while( !fin_de_liste(V)){
		l = V->contraintes;
		while(l!= NULL){
			if((l->presenceVariable)[X_instanciee->id]=='1') {
				while(affecter_valeur(V)){
					if (evalue_contrainte(l->a))
						ajouter_valeur(&D,V->valeur);
					empiler(&(V->domaines), D) ;
				}
			}
			l = l->suivant;
		}
	}
	V = suivante(V);
}

void depile_tout_domaine(variables V){
  variable* Xi = premiere_variable(V);
  while( !fin_de_liste(Xi) )
    {
      depiler(&Xi->domaines);
      Xi = suivante(Xi);
    }
}

void reduction_domaine_AC(variables V, listeContrainte contrainte, variables ListeVariable){
  while(affecter_valeur(V))
    {
      if(!evalue_contrainte(contrainte->a))
	retirer_valeur(&(V->domaines->dom),V->valeur);
    }
  V->valeur = (float)(V->domaines->dom->valeur - 1);
}

void reduction_domaine_AC_2_variables(variables V1, variables V2, listeContrainte contrainte, variables ListeVariable){
  domaine dV1 = creer_domaine();
  domaine dV2 = creer_domaine();
  while(affecter_valeur(V2))
    {
      while(affecter_valeur(V1))
	{
	  if(evalue_contrainte(contrainte->a))
	    {
	      ajouter_valeur(&dV1,V1->valeur);
	      ajouter_valeur(&dV2,V2->valeur);
	    }
	}
      V1->valeur = (float)(V1->domaines->dom->valeur - 1);
    }
  V2->domaines->dom = dV2;
  V1->domaines->dom = dV1;
  V2->valeur = (float)(V2->domaines->dom->valeur - 1);
  V1->valeur = (float)(V1->domaines->dom->valeur - 1);  
}

variables* variables_non_instancies_contrainte(listeContrainte contrainte, variables V)
{
  variables* tableauPointeurs=(variables*)malloc(longueur(V)*sizeof(variables));
  variable* Xi = premiere_variable(V);
  int indice=0;
  while( !fin_de_liste(Xi) )
    {
      if(contrainte->presenceVariable[Xi->id]=='1')
	{
	  if(!est_initialise(Xi))
	    {
	      tableauPointeurs[indice]=Xi;
	      indice++;
	    }
	}
      Xi = suivante(Xi);
    }
  tableauPointeurs[indice]=NULL;
  return tableauPointeurs;
}

int longueurTable(variables* tablePointeurs){
  int i;
  for(i=0;tablePointeurs[i]!=NULL;i++);
  return(i);
}

void arc_consistance(variables V){
  variable* Xi = premiere_variable(V);
  while( !fin_de_liste(Xi))
    {
      listeContrainte contraintes = Xi->contraintes;
      while(!est_vide_liste_contrainte(contraintes))
	{
	  variables* V2 = variables_non_instancies_contrainte(contraintes,V); 
	  if(longueurTable(V2)==1)
	    reduction_domaine_AC(V2[0],contraintes,V);
	  if(longueurTable(V2)==2)
	    reduction_domaine_AC_2_variables(V2[0],V2[1],contraintes,V);
	  free(V2);
	}
    }
}
