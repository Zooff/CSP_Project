#include "backtrack.h"

void resolutionBacktrackUneSolution(variables V)
{
    variable* Xi = premiere_variable(V);
    float booleen;
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
        fprintf(fileToWrite, "Solution fonctionnant:\n");
        Xi = premiere_variable(V);
        while( !fin_de_liste(Xi) )
        {
            afficher_variable(*Xi);
            Xi = suivante(Xi);
        }
    }
    else
        fprintf(fileToWrite, "Pas de solution\n");
}

void resolutionBacktrackToutesSolutions(variables V)
{
    variable* Xi = premiere_variable(V);
    variable* derniereVariable = derniere_variable(V);
    float existeSolution = 1;
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
                Xi = suivante(Xi);
            else
                Xi = precedente(Xi);
        }

        if(existeSolution == 1)
        {
            fprintf(fileToWrite, "Solution fonctionnant:\n");
            Xi = premiere_variable(V);
            while( !fin_de_liste(Xi) )
            {
                afficher_variable(*Xi);
                Xi = suivante(Xi);
            }
            Xi = derniereVariable;
            fprintf(fileToWrite, "Appuyez sur entrée pour la prochaine solution\n");
            fgetc(stdin);
        }
        else
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
