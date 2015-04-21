#include <unistd.h>
#include "variable.h"
#include "backtrack.h"

extern FILE* yyin; /* pour remplacer stdin par un fichier */

extern variables listeVariables;
extern pile_domaines listeDomaines;

int typeCSP;
int modeSilence;
FILE* fileToWrite;
int algorithmeUtilise = 1;
int afficherListeVariable = 0;
int forwardChecking = 0;

extern void yylex_destroy();
extern void yyparse();

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
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
	char c;
	char* fileName;
	fileToWrite = stderr;
	typeCSP = 1;
	opterr = 0; //on bloque les messages d'erreurs de getopt
		
	while((c = getopt(argc, argv, "a:o:st:v")) != -1){
		switch (c) {
		case 'a':
			algorithmeUtilise = atoi(optarg);
			break;
		case 'o':
			fileToWrite = fopen(optarg, "w");
			break;
		case 's':
			modeSilence++;
			break;
		case 't':
			typeCSP = atoi(optarg);
			break;
		case 'v':
			afficherListeVariable++;
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
	if(afficherListeVariable)
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

	// vidages
    vider_pile_domaines(listeDomaines);
    liberer_liste(listeVariables);
    yylex_destroy();
    return EXIT_SUCCESS;
}
