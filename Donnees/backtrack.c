#include "backtrack.h"

void afficheSolution(variables V)
{
	int i, j;
	switch(typeCSP)
	{
	case 1: // type normale
		while( !fin_de_liste(V) )
        {
            afficher_variable(*V);
            V = suivante(V);
        }
		break;
	case 2: // type sudoku
		for(i=0 ; i<9 ; i++)
		{ // affichage des 9 lignes
			for(j=0 ; j<9 ; j++)
			{ // affichages des 9 chiffres d'une ligne
				if(j == 3 || j == 6)
					fprintf(fileToWrite, "  ");
				fprintf(fileToWrite, "%d ", (int)(V->valeur));
				V = suivante(V);
			}
			if(i == 2 || i == 5)
				fprintf(fileToWrite, "\n");
			fprintf(fileToWrite, "\n");
		}
		fprintf(fileToWrite, "\n");
		break;
	default:
		fprintf(fileToWrite, "Type de CSP inconnu\n");
	}
}

void resolutionBacktrackUneSolution(variables V)
{
    variable* Xi = premiere_variable(V);
    float booleen;
	if(!modeSilence)
		fprintf(fileToWrite, "\nLancement de l'algorithme de backtrack donnant une seule solution\n");
    while( !fin_de_liste(Xi) )
    {
        while( (booleen=affecter_valeur(Xi)) )
        {
			if(forwardChecking)
				forward_check(Xi);
			
            booleen = verifier_les_contraintes(Xi);
            if(booleen == 1)
                break;
        }
        if(booleen == 1)
            Xi = suivante(Xi);
        else
            Xi = precedente(Xi);
    }

    if(booleen == 1)
    {
		if(!modeSilence)
			fprintf(fileToWrite, "Solution fonctionnant:\n");
		afficheSolution(V);
    }
    else if(!modeSilence)
        fprintf(fileToWrite, "Pas de solution\n");
}

void resolutionBacktrackToutesSolutions(variables V)
{
    variable* Xi = premiere_variable(V);
    variable* derniereVariable = derniere_variable(V);
    float existeSolution = 1;
	if(!modeSilence)
		fprintf(fileToWrite, "\nLancement de l'algorithme de backtrack donnant toutes les solutions\n");
    while(existeSolution)
    {
        while( !fin_de_liste(Xi) )
        {
            while( (existeSolution=affecter_valeur(Xi)) )
            {
                existeSolution = verifier_les_contraintes(Xi);
                if(existeSolution == 1)
                    break;
            }
            if(existeSolution == 1)
	      {
                Xi = suivante(Xi);
	      }
            else
	      {
                Xi = precedente(Xi);
	      }
        }

        if(existeSolution == 1)
        {
			if(!modeSilence)
				fprintf(fileToWrite, "Solution fonctionnant:\n");
			afficheSolution(V);		
                        Xi = derniereVariable;
			if(!modeSilence)
			{
				fprintf(fileToWrite, "Appuyez sur entrée pour la prochaine solution\n");
				fgetc(stdin);
			}
        }
        else if(!modeSilence)
            fprintf(fileToWrite, "Plus de solution\n");
    }
}

void resolutionBacktrackToutesSolutionsAC(variables V)
{
    arc_consistance(V);
    variable* Xi2;
    variable* Xi = premiere_variable(V);
    variable* derniereVariable = derniere_variable(V); 
    int i;
    float existeSolution = 1;
	if(!modeSilence)
		fprintf(fileToWrite, "\nLancement de l'algorithme de backtrack donnant toutes les solutions\n");
    while(existeSolution)
    {
        while( !fin_de_liste(Xi) )
        {
		//TEST
		  fprintf(fileToWrite, "variable actuel: %s\n",Xi->nom);
		  Xi2 = premiere_variable(V);
		  /*while(!fin_de_liste(Xi2))
		  {
		  fprintf(fileToWrite, "variable: %s domaine:\n",Xi2->nom);
		  afficher_domaine(Xi2->domaines->dom);
		  fprintf(fileToWrite, "\n");
		  Xi2 = Xi2->suivant;
		  }*/
	/*	  i = 0;
		  while(!fin_de_liste(Xi2))
		  {
		  if(i%9==0)
			fprintf(fileToWrite, "\n");
		  if(i%3==0)
			fprintf(fileToWrite, "\t");
                  if(est_initialise(Xi2))
			fprintf(fileToWrite, "- ");
		  else
		  {
			if(Xi2->domaines->dom==NULL)
				fprintf(fileToWrite, "X ");
			else
				fprintf(fileToWrite, "%d ",((int)floor(Xi2->valeur)));
		  }
		  Xi2 = Xi2->suivant;
		  i++;
		  }*/
		//FINTEST
            while( (existeSolution=affecter_valeur(Xi)) )
            {
                existeSolution = verifier_les_contraintes(Xi);
                if(existeSolution == 1)
                    break;
            }
            if(existeSolution == 1)
	      {
                Xi = suivante(Xi);
		arc_consistance(V);
		//majdomaineFC(V);
	      }
            else
	      {
		Xi = precedente(Xi);
		depile_tout_domaine(V);
	      }
        }

        if(existeSolution == 1)
        {
			if(!modeSilence)
				fprintf(fileToWrite, "Solution fonctionnant:\n");
			afficheSolution(V);		
                        Xi = derniereVariable;
                        depile_tout_domaine(V);
			if(!modeSilence)
			{
				fprintf(fileToWrite, "Appuyez sur entrée pour la prochaine solution\n");
				fgetc(stdin);
			}
        }
        else if(!modeSilence)
            fprintf(fileToWrite, "Plus de solution\n");
    }
}



void forward_check(variables X_instanciee){
	variables V = suivante(X_instanciee);
	listeContrainte l;
	domaine D;
	while( !fin_de_liste(V)){
		l = V->contraintes;
		while(l!= NULL){
			if((l->presenceVariable)[(int)X_instanciee->id]=='1') {
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
