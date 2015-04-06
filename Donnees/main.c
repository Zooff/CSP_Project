#include <unistd.h>
#include "variable.h"
#include "backtrack.h"

extern FILE* yyin; /* pour remplacer stdin par un fichier */
extern FILE* fileToWrite;

extern variables listeVariables;
extern pile_domaines listeDomaines;

int afficherContributeur = 0;
int algorithmeUtilise = 1;
int ecrireDansFichier = 0;
int listeVariable = 0;
int forwardChecking =0;

extern void yylex_destroy();
extern void yyparse();

void affichageContributeur()
{
	fprintf(fileToWrite, "\nContributeurs du projet:\n");
	fprintf(fileToWrite, "Leo:\n");
	fprintf(fileToWrite, "\tregroupement du travail des autres et vérification du fonctionement globale du projet\n");
	fprintf(fileToWrite, "\tremplir lex et yacc d'instruction C (et correction de l'ordre des regles dans yacc et dans lex)\n");
	fprintf(fileToWrite, "\tfonction main\n");
	fprintf(fileToWrite, "\tmodule arbre\n");
	fprintf(fileToWrite, "\tmodule listeContrainte\n");
	fprintf(fileToWrite, "\tmodule backtrack\n");
	fprintf(fileToWrite, "\tquelques fonctions du module variable\n");
	fprintf(fileToWrite, "\tfichier de tests sudoku.txt et csp.txt\n\n");
	
	fprintf(fileToWrite, "Dimitri:\n");
	fprintf(fileToWrite, "\tcreateur du github du projet (https://github.com/Zooff/CSP_Project)\n");
	fprintf(fileToWrite, "\tMakefile\n");
	fprintf(fileToWrite, "\tmodule variable\n\n");
	
	fprintf(fileToWrite, "françis:\n");
	fprintf(fileToWrite, "\tmodule domaine\n");
	fprintf(fileToWrite, "\trecuperation et traitement des arguments en ligne de commande\n");
	fprintf(fileToWrite, "\tfonction d'usage du programme\n\n");
	
	fprintf(fileToWrite, "Line KévinG Josselin:\n");
	fprintf(fileToWrite, "\tlex\n");
	fprintf(fileToWrite, "\tyacc (sans instruction C)\n");
	fprintf(fileToWrite, "\tun (seul) fichier de test\n\n");

	fprintf(fileToWrite, "KévinV Damien Benjamin:\n");
	fprintf(fileToWrite, "\tForward checking: (non fonctionnel du fait du groupe donnés devant faire le tri des variables)\n");
	fprintf(fileToWrite, "\t\tCreation et empilement des domaines retrecis\n");
	fprintf(fileToWrite, "\t\tdepilement des domaines lors du backtrack\n\n");
	
	fprintf(fileToWrite, "Julien:\n");
	fprintf(fileToWrite, "\tmodule pile domaine\n\n");
	
	fprintf(fileToWrite, "Hugo:\n");
	fprintf(fileToWrite, "\tCreateur du forum\n\n");

	fprintf(fileToWrite, "Nabil:\n");
	fprintf(fileToWrite, "\tTri des variables (non fonctionnel)\n\n");
}

void usage(char* prog){
	fprintf(fileToWrite, "Usage : %s [-a nombre] [-o fichier_où_ecrire] [-s] [-t nombre] [-v] [-z] fichier_contenant_le_CSP\n", prog);
	fprintf(fileToWrite, "\t-a nombre : permet d'utiliser l'algorithme de numéro nombre, nombre peut prendre plusieurs valeurs :\n");
	fprintf(fileToWrite, "\t\t1 : l'algorithme utilisé sera l'algorithme de backtrack (comportement de base si l'option n'est pas renseignée)\n");
	fprintf(fileToWrite, "\t\tTO DO\n");
	fprintf(fileToWrite, "\t-o fichier_où_ecrire : le résultat du CSP sera écrit dans le fichier fichier_où_ecrire\n");
	fprintf(fileToWrite, "\t-s : active le mode silence\n");
	fprintf(fileToWrite, "\t-t nombre : permet de résoudre le CSP de numéro nombre, nombre peut prendre plusieurs valeurs :\n");
	fprintf(fileToWrite, "\t\t1 : le CSP résolu sera un CSP classique (comportement de base si l'option n'est pas renseignée)\n");
	fprintf(fileToWrite, "\t\t2 : le CSP résolu sera un sudoku\n");
	fprintf(fileToWrite, "\t\tTO DO\n");
	fprintf(fileToWrite, "\t-v : affiche la liste des variables\n");
	fprintf(fileToWrite, "\t-z : affiche les contributeurs du programme\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
	char c;
	char* fileName;
	fileToWrite = stderr;
	typeCSP = 1;
	modeSilence = 0;
	opterr = 0; //on bloque les messages d'erreurs de getopt
		
	while((c = getopt(argc, argv, "a:o:st:vz")) != -1){
		switch (c) {
		case 'a':
			algorithmeUtilise = atoi(optarg);
			break;
		case 'o':
			ecrireDansFichier++;
			fileToWrite = fopen(optarg, "w");
			break;
		case 's':
			modeSilence++;
			break;
		case 't':
			typeCSP = atoi(optarg);
			break;
		case 'v':
			listeVariable++;
			break;
		case 'z' :
			afficherContributeur++;
			break;
		default:
			usage(argv[0]);
		}
	}
		
	if (optind < argc)
		fileName = argv[optind];
	else
		usage(argv[0]);

	//analyse du fichier
    yyin=fopen(fileName, "r"); /* ouverture du fichier contenant le CSP */
    yyparse();
    fclose(yyin);
    
	// affichage resultat
	if(listeVariable)
	    afficher_liste(listeVariables);

    initialiserValeurVariables(listeVariables);
    
    switch(algorithmeUtilise){
	case 1 :
		resolutionBacktrackUneSolution(listeVariables);
		break;
	case 2:
		resolutionBacktrackToutesSolutions(listeVariables);
		break;
	case 3:
		forwardChecking = 1;
		resolutionBacktrackUneSolution(listeVariables);
		break;
	default :
		fprintf(fileToWrite, "Numero d'algo de resolution inconnu\n");
		usage(argv[0]);
    }

	if(afficherContributeur)
		affichageContributeur();

	// vidages
    vider_pile_domaines(listeDomaines);
    liberer_liste(listeVariables);
    yylex_destroy();
    return EXIT_SUCCESS;
}
