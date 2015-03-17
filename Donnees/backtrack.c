#include "backtrack.h"

void resolutionBacktrackUneSolution(variables V)
{
    variable* Xi = premiere_variable(V);
    float booleen;
    fprintf(stderr, "\nLancement de l'algorithme de backtrack donnant une seule solution\n");
    while( !fin_de_liste(Xi) )
    {
        while( (booleen=affecter_valeur(Xi)) )
        {
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
        fprintf(stderr, "Solution fonctionnant:\n");
        Xi = premiere_variable(V);
        while( !fin_de_liste(Xi) )
        {
            afficher_variable(*Xi);
            Xi = suivante(Xi);
        }
    }
    else
        fprintf(stderr, "Pas de solution\n");
}

void resolutionBacktrackToutesSolutions(variables V)
{
    variable* Xi = premiere_variable(V);
    variable* derniereVariable = derniere_variable(V);
    float existeSolution = 1;
    fprintf(stderr, "\nLancement de l'algorithme de backtrack donnant toutes les solutions\n");
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
            fprintf(stderr, "Solution fonctionnant:\n");
            Xi = premiere_variable(V);
            while( !fin_de_liste(Xi) )
            {
                afficher_variable(*Xi);
                Xi = suivante(Xi);
            }
            Xi = derniereVariable;
            fprintf(stderr, "Appuyez sur entrée pour la prochaine solution\n");
            fgetc(stdin);
        }
        else
            fprintf(stderr, "Plus de solution\n");
    }
}
