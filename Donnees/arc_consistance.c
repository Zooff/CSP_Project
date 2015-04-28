#include "arc_consistance.h"

void majdomaineFC(variables X_instanciee){
	variables V = suivante(X_instanciee);
	listeContrainte l;
	domaine D;
	while( !fin_de_liste(V)){
		l = V->contraintes;
		while(l!= NULL){
			if((l->presenceVariable)[((int)floor(X_instanciee->id))]=='1') {
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
      if(est_initialise(Xi))
	Xi->valeur = (float)(Xi->domaines->dom->valeur - 1);
      Xi = suivante(Xi);
    }
}

void reduction_domaine_AC(variables V, listeContrainte contrainte, variables ListeVariable){
 float val = V->valeur;
  while(affecter_valeur(V))
    {
      if(!evalue_contrainte(contrainte->a))
	retirer_valeur(&(V->domaines->dom),V->valeur);
    }
  V->valeur = valeurinf(val,V->domaines->dom);
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

float valeurinf(float val, domaine d)
{
   while(!est_vide(d))
   {
    if(d->valeur==((int)floor(val)))
	return(val);
    if(d->valeur>((int)floor(val)))
        return(d->valeur-1);
    d = d->suivant;
   }
   return 0;
}



variables* variables_non_instancies_contrainte(listeContrainte contrainte, variables V)
{
  variables* tableauPointeurs=(variables*)malloc(longueur(V)*sizeof(variables));
  variable* Xi = premiere_variable(V);
  int indice=0;
  while( !fin_de_liste(Xi) )
    {
      if(contrainte->presenceVariable[((int)floor(Xi->id))]=='1')
	{
	   if(est_initialise(Xi))
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
  while(!fin_de_liste(Xi))
  {
    empiler(&(Xi->domaines),dupliquer_domaine(Xi->domaines->dom));
    Xi = Xi->suivant;
  }
  Xi = premiere_variable(V);
  while( !fin_de_liste(Xi))
    {
      //fprintf(fileToWrite,"variable en cours de modif: %s\n",Xi->nom);
      listeContrainte contraintes = Xi->contraintes;
      while(!est_vide_liste_contrainte(contraintes))
	{
	  variables* V2 = variables_non_instancies_contrainte(contraintes,V); 
	  //fprintf(fileToWrite,"nb variable non_instancié contraintes: %d\n",longueurTable(V2));
	  if(longueurTable(V2)==1)
	    reduction_domaine_AC(V2[0],contraintes,V);
	  if(longueurTable(V2)==2)
	    reduction_domaine_AC_2_variables(V2[0],V2[1],contraintes,V);
	  free(V2);
	  contraintes = contraintes->suivant;
       /*   fprintf(fileToWrite, "variable: %s domaine:\n",V->nom);
          afficher_domaine(V->domaines->dom);
	  fprintf(fileToWrite, "\nvariable: %s domaine:\n",V->suivant->nom);
	  afficher_domaine(V->suivant->domaines->dom);
	  fprintf(fileToWrite, "\nvariable: %s domaine:\n",V->suivant->suivant->nom);
	  afficher_domaine(V->suivant->suivant->domaines->dom);
    	  fprintf(fileToWrite, "\n");*/
	}
      Xi = suivante(Xi);
    }

}
