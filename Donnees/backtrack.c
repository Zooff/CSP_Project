#include "backtrack.h"

void afficheSolution(variables V)
{
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
		afficherSolutionSudoku(V);
		break;
	default:
		fprintf(fileToWrite, "Type de CSP inconnu\n");
	}
}

void afficherSolutionSudoku(variables V)
{
	int i, j, indiceVariable;
	variables variable;
	char *nomsVariables[81] = // on stocke l'ensemble des noms des variables du sudoku
		{"x_1", "x_2", "x_3",   "x_4", "x_5", "x_6",   "x_7", "x_8", "x_9",
		 "x10", "x11", "x12",   "x13", "x14", "x15",   "x16", "x17", "x18",
		 "x19", "x20", "x21",   "x22", "x23", "x24",   "x25", "x26", "x27",

		 "x28", "x29", "x30",   "x31", "x32", "x33",   "x34", "x35", "x36",
		 "x37", "x38", "x39",   "x40", "x41", "x42",   "x43", "x44", "x45",
		 "x46", "x47", "x48",   "x49", "x50", "x51",   "x52", "x53", "x54",

		 "x55", "x56", "x57",   "x58", "x59", "x60",   "x61", "x62", "x63",
		 "x64", "x65", "x66",   "x67", "x68", "x69",   "x70", "x71", "x72",
		 "x73", "x74", "x75",   "x76", "x77", "x78",   "x79", "x80", "x81"};
	for(i=0, indiceVariable=0 ; i<9 ; i++)
	{ // affichage des 9 lignes du sudoku
		for(j=0 ; j<9 ; j++)
		{ // affichages des 9 chiffres d'une ligne du sudoku
			if(j == 3 || j == 6) // on affiche un espace suplementaire toutes les 3 colonnes de chiffres pour avoir un meilleur affichage
				fprintf(fileToWrite, "  ");

			variable = premiere_variable(V);
			while((!fin_de_liste(variable)) && (strcmp(variable->nom, nomsVariables[indiceVariable])!=0))
				variable = suivante(variable); // on cherche la variable portant le nom de la indiceVariable-eme variable
			// car il est possible que les variables ne soit pas dans la liste V dans l'ordre du tableau nomsVariables du fait du tri des variables
			if(variable == NULL)
			{
				fprintf(fileToWrite, "\nErreur, la variable %s n'existe pas\n", nomsVariables[indiceVariable]);
				return ;
			}
			fprintf(fileToWrite, "%d ", (int)(variable->valeur));
			indiceVariable++;
		}
		fprintf(fileToWrite, "\n"); // dans tous les cas, on affiche un saut de ligne apres chaque ligne de 9 chiffres
		if(i == 2 || i == 5) // on affiche un saut de ligne suplementaire toutes les 3 lignes de chiffres pour avoir un meilleur affichage
			fprintf(fileToWrite, "\n");
	}
	fprintf(fileToWrite, "\n");
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
    variable* Xi = premiere_variable(V);
    variable* derniereVariable = derniere_variable(V); 
    //int i;
    //variable* Xi2;
    float existeSolution = 1;
    arc_consistance(V);
	if(!modeSilence)
		fprintf(fileToWrite, "\nLancement de l'algorithme d'arc consistance donnant toutes les solutions\n");
    while(existeSolution)
    {
        while( !fin_de_liste(Xi) )
        {
			//TEST
			/*fprintf(fileToWrite, "variable actuel: %s\n",Xi->nom);
			  Xi2 = premiere_variable(V);
			  while(!fin_de_liste(Xi2))
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
