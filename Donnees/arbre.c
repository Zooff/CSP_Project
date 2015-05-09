#include "arbre.h"

arbre cons_noeud(int nature, float* valeur)
{
	arbre a = (arbre)malloc(1 * sizeof(noeud)); /* allocation dynamique d'un noeud */
	if(nature == A_ENTIER || nature == A_REEL || nature == A_BOOLEEN)
		a->valeur = (float*) malloc(1 * sizeof(float));
	else
		a->valeur = valeur;
	a->nature = nature;
	a->frangin = a->fils = NULL; /* le noeud est pour l'instant une feuille sans fils ni frangin */
	return a;
}

void videArbre(arbre a)
{
	if(a!=NULL)
	{
		videArbre(a->fils); /* vide le fils */
		videArbre(a->frangin); /* puis vide le frangin */
		if(a->nature != A_IDF)
			free(a->valeur);
		free(a); /* et enfin vide a */
	}
}

arbre attache_papa_frangin(arbre papa, arbre frangin)
{
	papa->frangin = frangin;
	return papa;
}

arbre attache_papa_fils(arbre papa, arbre fils)
{
	papa->fils = fils;
	return papa;
}

void afficheArbre(arbre a, int espace)
{
	int i;
	for(i=0 ; i<espace ; i++) /* indentation */
		fprintf(fileToWrite, " ");
	if(a != NULL)
	{
		afficheArbreBis(a); /* affiche en lettre la nature du noeud (qui est un int) */
		afficheArbre(a->fils, espace+2); /* affichage du fils avec une plus grande identation */
		afficheArbre(a->frangin, espace); /* affichage du frangin avec une meme indentation pour donner l'impression d'un arbre en penchant la tete a gauche */
	}
	else
		fprintf(fileToWrite, "ø\n");
}

void afficheArbreBis(arbre a)
{
	switch(a->nature)
	{
    case 10: fprintf(fileToWrite, "IDF");               break;
    case 11: fprintf(fileToWrite, "ENTIER %d", (int)(*(a->valeur)));break;
    case 12: fprintf(fileToWrite, "REEL %f", *(a->valeur));break;
    case 13: fprintf(fileToWrite, "BOOLEEN, %d", (int)(*(a->valeur)));break;
    case 14: fprintf(fileToWrite, "SQRT");              break;
    case 15: fprintf(fileToWrite, "SIN");               break;
    case 16: fprintf(fileToWrite, "COS");               break;
    case 17: fprintf(fileToWrite, "TAN");               break;
    case 18: fprintf(fileToWrite, "ET");                break;
    case 19: fprintf(fileToWrite, "OU");                break;
    case 20: fprintf(fileToWrite, "NON");               break;
    case 21: fprintf(fileToWrite, "EGAL");              break;
    case 22: fprintf(fileToWrite, "DIFFERENT");         break;
    case 23: fprintf(fileToWrite, "SUPERIEUR_OU_EGAL"); break;
    case 24: fprintf(fileToWrite, "INFERIEUR_OU_EGAL"); break;
    case 25: fprintf(fileToWrite, "SUPERIEUR");         break;
    case 26: fprintf(fileToWrite, "INFERIEUR");         break;
    case 27: fprintf(fileToWrite, "PLUS");              break;
    case 28: fprintf(fileToWrite, "MOINS");             break;
    case 29: fprintf(fileToWrite, "MULTIPLIE_PAR");     break;
    case 30: fprintf(fileToWrite, "DIVISE_PAR");        break;
    case 31: fprintf(fileToWrite, "MODULO");            break;
    default: fprintf(fileToWrite, "noeud inconnu");
	}
	fprintf(fileToWrite, "\n");
}

float evalue_contrainte(arbre a)
{
	switch(a->nature)
	{
    case A_IDF:               return *(a->valeur);
    case A_ENTIER:            return *(a->valeur);
    case A_REEL:              return *(a->valeur);
    case A_BOOLEEN:           return *(a->valeur);
    case A_SQRT:              return sqrt(evalue_contrainte(a->fils));
    case A_SIN:               return sin(evalue_contrainte(a->fils));
    case A_COS:               return cos(evalue_contrainte(a->fils));
    case A_TAN:               return tan(evalue_contrainte(a->fils));
    case A_ET:                return (evalue_contrainte(a->fils) && evalue_contrainte(a->fils->frangin));
    case A_OU:                return (evalue_contrainte(a->fils) || evalue_contrainte(a->fils->frangin));
    case A_NON:               return (!(evalue_contrainte(a->fils)));
    case A_EGAL:              return (evalue_contrainte(a->fils) == evalue_contrainte(a->fils->frangin));
    case A_DIFFERENT:         return (evalue_contrainte(a->fils) != evalue_contrainte(a->fils->frangin));
    case A_SUPERIEUR_OU_EGAL: return (evalue_contrainte(a->fils) >= evalue_contrainte(a->fils->frangin));
    case A_INFERIEUR_OU_EGAL: return (evalue_contrainte(a->fils) <= evalue_contrainte(a->fils->frangin));
    case A_SUPERIEUR:         return (evalue_contrainte(a->fils) > evalue_contrainte(a->fils->frangin));
    case A_INFERIEUR:         return (evalue_contrainte(a->fils) < evalue_contrainte(a->fils->frangin));
    case A_PLUS:              return (evalue_contrainte(a->fils) + evalue_contrainte(a->fils->frangin));
    case A_MOINS:             return (evalue_contrainte(a->fils) - evalue_contrainte(a->fils->frangin));
    case A_MULTIPLIE_PAR:     return (evalue_contrainte(a->fils) * evalue_contrainte(a->fils->frangin));
    case A_DIVISE_PAR:        return (evalue_contrainte(a->fils) / evalue_contrainte(a->fils->frangin));
    case A_MODULO:            return (float)((int)evalue_contrainte(a->fils) % (int)evalue_contrainte(a->fils->frangin));
    default:                  return 0;
	}
}
