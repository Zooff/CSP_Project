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
	  //arc_consistance(V);
            while( (existeSolution=affecter_valeur(Xi)) )
            {
                existeSolution = verifier_les_contraintes(Xi);
                if(existeSolution == 1)
                    break;
            }
            if(existeSolution == 1)
	      {
		//majdomaineFC(V);
                Xi = suivante(Xi);
	      }
            else
	      {
		// depile_tout_domaine(V);
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
