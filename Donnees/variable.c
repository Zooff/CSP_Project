#include "variable.h"

/* Fonction d'utilisation de la liste de variables */


variables creer_liste_var_vide(){

	return NULL;
}

variables ajouter_var(variables V, char* nom_var){


	variables new = (variables)xmalloc(1, sizeof(variable));
	new->id = -1;
	new->nom = nom_var;
	new->contraintes = creer_liste_contrainte();
	new->domaines = creer_pile_domaines();
	new->precedent = NULL;
	new->suivant = V;
	if (V != NULL)
		V->precedent = new;
	return new;

}

variables supprimer_variable(variables V, char* nom_var){

	variables courant = V;

	while(courant != NULL && strcmp(nom_var, courant->nom) != 0)
		courant = courant->suivant;

	if (courant == NULL){
		fprintf(fileToWrite, " Suppresion impossible\n");
		return V;
	}

	if(courant->suivant == NULL){
		courant->precedent->suivant = NULL;
	}

	else if (courant->precedent == NULL){
		courant->suivant->precedent = NULL;
	}

	else{
		courant->suivant->precedent = courant->precedent;
		courant->precedent->suivant = courant->suivant;
	}

	free(courant);
	return V;
}

void liberer_liste(variables V){
	variables courant;
	while (V != NULL){
		courant = V;
		V = V->suivant;
		vider_liste_contrainte(courant->contraintes);
		vider2_pile_domaines(courant->domaines);
		free(courant->nom);
		free(courant);
	}
}

variable* premiere_variable(variables V){
	while (V->precedent != NULL)
		V = V->precedent;
	return V;
}

variable* derniere_variable(variables V){
	while (V->suivant != NULL)
		V = V->suivant;
	return V;
}


int fin_de_liste(variables V){
	return (V == NULL);
}

/* -------------------------------------- */


/* Fonction de gestion des variables */

int affecter_valeur(variables V){
	domaine d = (V->domaines)->dom;
	while(d != NULL && V->valeur >= d->valeur){
		d = d->suivant;

	}
	if (d != NULL){
		V->valeur = d->valeur;
		return 1;
	}
	return 0;
}

variable* suivante(variable* var){
	return var->suivant;
}

variable* precedente(variable* var){
	var->valeur = (float)(var->domaines->dom->valeur - 1);
	if(forwardChecking){
		variables V = suivante(var);
		listeContrainte l;
		while( !fin_de_liste(V)){
			l = V->contraintes;
			while(l!= NULL){
				if(l->presenceVariable[var->id]=='1') {
					depiler(&(V->domaines));
				}
				l = l->suivant;
			}
		}
		V = suivante(V);
	}
	return var->precedent;
}




/* ------------------------------------------- */

/* Fonction d'affichage */


void afficher_liste(variables V){

	while(V != NULL){
		if ( V->precedent == NULL)
			fprintf(fileToWrite, "Debut \n");
		afficher_variable(*V);
		fprintf(fileToWrite, "Domaine: ");
		afficher_domaine(V->domaines->dom);
		afficher_liste_contrainte(V->contraintes);
		if (V->suivant == NULL)
			fprintf(fileToWrite, "Fin\n");
		V = V->suivant;
	}
}

void afficher_variable(variable var){

	fprintf(fileToWrite, "Nom : %s Valeur : %d, ID : %d\n", var.nom, (int)(var.valeur), var.id);


}

void affecterDommaineDansVariables(variables V, domaine d){
	while(V != NULL){
		empiler(&(V->domaines), d);
		V = V->suivant;
	}
}

void concat_variables(variables* v1, variables* v2){
	variables courant = *v1;
	if(*v1 == NULL) // si v1 est vide, la concatenantion de v1 avec v2 est v2
		*v1 = *v2;
	else if(*v2 != NULL){// si v2 n'est pas NULL, alors on change les pointeurs precedent du premier de v2 et suivant du dernier de v1
		while(courant->suivant != NULL) // cherche le dernier pointeur de v1
			courant = courant->suivant;
		courant->suivant = *v2; // change le dernier pointeur suivant de v1 pour pointer sur le premier element de v2
		(*v2)->precedent = courant; // change le premier pointeur precedent de v2 pour pointer sur le dernier element de v1
	} // sinon si v2 est NULL, la concatenation est de v1 avec v2 est v1 donc on change rien
}

variable* retournerVariablePortantNom(variables V, char* nom, int* indiceVariable){
	int i=0;
	while(V != NULL && strcmp(V->nom, nom) != 0){
		V = V->suivant;
		i++;
	}
	if(V == NULL){
		fprintf(fileToWrite, "Erreur ligne %d, utilisation d'une variable '%s' sans la declarer auparavant en donnant son domaine, le programme quitte donc.\n", num_ligne, nom);
		exit(EXIT_FAILURE);
	}
	*indiceVariable = i;
	return V;
}

int verifier_les_contraintes(variable* variable){
	listeContrainte l = variable->contraintes;
	while(l != NULL){
		if(evalue_contrainte(l->a) == 0)
			return 0;
		l = l->suivant;
	}
	return 1;
}

void affecterContraintesDansVariables(variables V, listeContrainte* lc, int nombreVariable){
	int indiceVariable=0, indiceContrainte, i;
	listeContrainte contrainte;
	char* presenceVariable;
	while(V != NULL){ // pour chaque variable, on va chercher et lui ajouter des contraintes
		contrainte = *lc;
		indiceContrainte = 0;
		while(contrainte != NULL){ // pour chaque contrainte pas encore affectee (donc presente dans lc)
			presenceVariable = contrainte->presenceVariable;
			for(i=indiceVariable+1 ; i<nombreVariable ; i++) // on regarde la presence des variables d'indice plus grand dans la contrainte
				if(presenceVariable[i] == '1')
					break;
			if(presenceVariable[indiceVariable] == '1' && i == nombreVariable) // si cette contrainte fait intervenir cette variable et ne fait pas intervenir de variable d'indice plus grand
			{ // cela veut dire que on a eu aucun '1' entre (exclus) dans l'intervale d'indice ]indiceVariable, nombreVariable[  du tableau presenceVariable. donc que la contrainte ne fait intervenir aucune variable d'indice plus grand que la variable en cours. donc on enleve cette contrainte de lc et on la met dans la liste des contraintes de cette variable
				ajouter_contrainte(&(V->contraintes), contrainte->a, contrainte->presenceVariable);
				contrainte = contrainte->suivant; // on doit faire passer au suivant ici car on fait un free sur cette contrainte dans la fonction juste en dessous
				enlever_contrainte(lc, indiceContrainte);
				// comme on enleve la contrainte, l'indice de la prochaine ne change pas dans lc donc on ne change pas indiceContrainte
			}
			else{ // si on n'enleve pas la contrainte, l'indice de la prochaine est l'indice + 1
				indiceContrainte++;
				contrainte = contrainte->suivant;
			}
		}
		V = V->suivant;
		indiceVariable++;
	}
	vider_liste_contrainte(*lc);// arriver ici, si il reste des contraintes dans lc, elles ne font intervenir aucune variable donc des contraintes inutiles donnes par un utilisateur soucieux d'embeter le codeur de ce programme. cette derniere ligne lui est dedicacee.
}

void initialiserValeurVariables(variables V){
	while(V != NULL){
		V->valeur = (float)(V->domaines->dom->valeur - 1);
		V = V->suivant;
	}
}

void ajouterContraintesDifferent(char* nomVariable, variables variablesAlldiff, listeContrainte* contraintes, variables V, int nombreVariable)
{
	int indiceNouvelleVarDiff, indiceVariableDiff;
	variable* nouvelleVarDiff = retournerVariablePortantNom(V, nomVariable, &indiceNouvelleVarDiff);
	variable* variableDiff;
	char* presenceVariable;
	arbre a, fils1, fils2;
	while( !fin_de_liste(variablesAlldiff) )
	{
		presenceVariable = creerTableauPresenceVariable(nombreVariable);
		presenceVariable[indiceNouvelleVarDiff] = '1';
		variableDiff = retournerVariablePortantNom(V, variablesAlldiff->nom, &indiceVariableDiff);
		presenceVariable[indiceVariableDiff] = '1';
		a = cons_noeud(A_DIFFERENT, NULL);
		fils1 = cons_noeud(A_IDF, &(variableDiff->valeur));
		fils2 = cons_noeud(A_IDF, &(nouvelleVarDiff->valeur));
		fils1 = attache_papa_frangin(fils1, fils2);
		a = attache_papa_fils(a, fils1);
		ajouter_contrainte(contraintes, a, presenceVariable);
		variablesAlldiff = variablesAlldiff->suivant;
	}
}

void afficherResultat(variables V){
	switch(typeCSP){
	case 1 :
		afficher_liste(V);
		break;
	case 2 :
		fprintf(fileToWrite, "SUDOKU\n");
		break;
	default :
		fprintf(fileToWrite, "Seulement 2 types\n");
	}
}

void tri_liste_variable()
{
    if(nombreVariable == 1)// cas ou il n'y a que une variable
    {
         listeVariables->id = 0 ;
         return;
    }
        
    int i;
    int* tab_nbr_apparition_variable = (int*) malloc(nombreVariable * sizeof(int)); // nombreVariable var global donné par le yacc
    char* tab; // stocke le tableau presence variable d'une contrainte
    listeContrainte newContrainte; // liste des contraintes d'une variabl
    int fini = -1;
    variables news = listeVariables, tampon , precedent, suivant;

    for(i =0 ; i<nombreVariable ; i++) // initialisation du tableau a 0
    {
        tab_nbr_apparition_variable[i] = 0;
    }

    while( !(fin_de_liste(news)) ) // boucle remplissant le tableau avec les nbr d'aparition des variables dans les contraintes
    {
        newContrainte = news->contraintes;
        while(newContrainte != NULL)
        {
            tab =newContrainte->presenceVariable ;
            for(i =0 ; i<nombreVariable ; i++)
            {
                if(tab[i] == '1')
                {
                    tab_nbr_apparition_variable[i]++;
                }
            }
            newContrainte = newContrainte->suivant;
        }
        news = news->suivant;
    }

    news = listeVariables;
    i = 0;

    while( !(fin_de_liste(news)) )
    { // boucle affectant les id des dans les variables: nombre d'apparition contrainte divise par taille domaine
        news->id = tab_nbr_apparition_variable[i++] / (float)taille(news->domaines->dom);
        news = news->suivant;
    }

    while(fini != 1) // tri a bulle de la liste doublement chainée
    {
        fini = 1;
        precedent = listeVariables;
        news = precedent->suivant;
        suivant = news->suivant;
        tampon = precedent->precedent;

        if(precedent->id < news->id) // cas particulier pour savoir si le pointeur en debut de liste doit changer
        {
            fini = 0;
            precedent->suivant = suivant;
            precedent->precedent = news;
            news->suivant = precedent;
            news->precedent = tampon;
            if(suivant != NULL)
                suivant->precedent = precedent;
            tampon = precedent;
            precedent = news;
            news = tampon;

            listeVariables = precedent;
        }
        tampon = precedent;
        precedent = news;
        news = suivant;
        if(suivant != NULL)
            suivant = suivant->suivant;
        
        while( ! fin_de_liste(news))
        {
            if(precedent->id < news->id)
            {
                fini = 0;
                precedent->suivant = suivant;
                precedent->precedent = news;
                news->suivant = precedent;
                news->precedent = tampon;
                tampon->suivant = news;
                
                if(suivant != NULL)
                    suivant->precedent = precedent;
                
                tampon = precedent;
                precedent = news;
                news = tampon;
            }
            tampon = precedent;
            precedent = news;
            news = suivant;
            
            if(suivant != NULL)
                suivant = suivant->suivant;
        }
    }
        // maintenant que les variables sont triées on leurs affectent un id correspondant de 0 a nombreVariable-1
    news = listeVariables;
    i=0;
    while (! fin_de_liste(news) )
    {
        news->id = i++;
        news = news->suivant;
    }
    free(tab_nbr_apparition_variable);
}

int est_initialise(variables V){
  return (V->valeur == (V->domaines->dom->valeur -1));
}

int longueur(variables V){
  variable* Xi = premiere_variable(V);
  int i=0;
  while( !fin_de_liste(Xi) ){
    i++;
    Xi = suivante(Xi);
  }
  return i;
}
