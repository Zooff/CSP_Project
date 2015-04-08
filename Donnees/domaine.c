
    #include "domaine.h"


    domaine creer_domaine(){
      return NULL;
    }

    int est_vide(domaine d){
      return (d == NULL);
    }

    int taille(domaine d){
      domaine courant = d;
      int taille = 0;

      while(courant != NULL){
        taille++;
        courant = courant->suivant;
      }

      return taille;
    }

    int deja_presente(domaine d, int value){
      domaine courant = d;

      while(courant != NULL){
        if(courant->valeur == value)
          return 1;

        courant = courant->suivant;
      }
      return 0;
    }

    int ajouter_valeur(domaine* d, int value){
  //Fonction qui ajoute la valeur "au bon endroit" afin d'obtenir des domaines triés
  domaine courant = *d;
  domaine precedent;

  if(est_vide(*d)){
    //Si le domaine pointe sur NULL on l'initalise comm il faut et lui affecte value
    (*d) = malloc(sizeof(struct s_element));

    (*d)->suivant = NULL;
    (*d)->precedent = NULL;
    (*d)->valeur = value;

    return 1;
  }

  domaine maillon = malloc(sizeof(struct s_element));
  maillon->valeur = value;

  if(!(deja_presente(*d, value))){
    //On exécutera le reste uniquement si la valeur n'est pas présente dans le domaine
    if((*d)->valeur > value){
      /* Si la valeur à ajouter est inférieure à la première valeur du domaine alors
       * on fait pointer le précédent du domaine sur l'élément à ajouter
       * et on fait commencer le domaine au nouvel élément
       */
      (*d)->precedent = maillon;
      maillon->suivant = *d;

      *d = maillon;

      return 1;
    }

    //Pour les cas où on ajoute au milieu et à la fin
    while(courant->suivant != NULL){
      precedent = courant->precedent;
      if(value < courant->valeur){
        /* La valeur à ajouter est inférieure à la valeur de courant alors
         * le suivant de l'élément à ajouter va pointer sur courant
         * on fait pointer le précédent de courant sur l'élément à ajouter
         * le précédent de l'élément à ajouter va pointer sur précédent
         * on fait pointer le suivant de précédent sur l'élément à ajouter
         */
        maillon->suivant = courant;
        courant->precedent = maillon;
        maillon->precedent = precedent;
        if (precedent != NULL)
        {
          precedent->suivant = maillon;
        }

        return 1;
      }
      //On fait avancer les itérateurs
      courant = courant->suivant;
    }

    if(courant->suivant == NULL){
      /*On a parcouru tout le domaine sans insérer d'élément
       * c'est donc que sa valeur est supérieure à toutes les autres valeurs du domaine
       * on fait donc pointer le suivant de précédent sur l'élément à ajouter
       * on met le suivant de l'élément à ajouter à NULL puisqu'il est le dernier élément du domaine
       */

       if (courant->valeur > value)
       {
         courant->precedent->suivant = maillon;
         maillon->precedent = courant->precedent;
         courant->precedent = maillon;
         maillon->suivant = courant;

         return 1;
       }

      courant->suivant = maillon;
      maillon->precedent = courant;
      maillon->suivant = NULL;

      return 1;
    }
  }
  return 0;
}

int retirer_valeur(domaine* d, int value)
{
	//Fonction qui retire la valeur donnée en argument au domaine.
	if (!deja_presente(*d, value))
	{
		//Si la valeur est pas présente dans le domaine, on va même pas plus loin.
		return 0;
	}

	if ((*d)->valeur == value)
	{
		//Si la valeur est la première de la liste, on l'enlève et change la liste pour qu'elle pointe sur la seconde.
		domaine del = *d;
		*d = (*d)->suivant;
		free(del);
		if (*d != NULL)
		{
			(*d)->precedent = NULL;
		}
		return 1;
	}

	domaine courant = *d;

	while(courant != NULL)
	{
		//Dans les autres cas, recherche classique dans le domaine
		if (courant->valeur == value)
		{
			if (courant->precedent == NULL)
			{
				fprintf(stderr, "Probleme! La valeur %d n'a pas de précédent alors qu'on est sensé être au milieu de la liste!\n", courant->valeur);
			}
			courant->precedent->suivant = courant->suivant;
			if (courant->suivant != NULL)
			{
				//vérif si le suivant existe
				courant->suivant->precedent = courant->precedent;
			}
			free(courant);
			return 1;
		}

		courant = courant->suivant;
	}

	return 0;
}

    int obtenir_valeur(domaine d, int indice){
      /*
       * Attention cette fonction fonctionne comme un tableau
       * ainsi obtenir_valeur(d, 0) renverra la première valeur
       * et obtenir_valeur(d, taille(d) - 1) la dernière
       */
      domaine courant = d;
      int longueur = taille(d);

      if (indice < 0 || indice > longueur){
        fprintf(fileToWrite, "Le domaine d a pour taille %d et votre indice est %d\n", longueur, indice);
      }

      while(indice != 0){
        courant = courant->suivant;
        indice--;
      }

      return courant->valeur;
    }

    void afficher_domaine(domaine d){
      domaine courant = d;

      if(est_vide(d))
        fprintf(fileToWrite, "le domaine est vide\n");

      while(courant != NULL){
        fprintf(fileToWrite, "%d ", courant->valeur);
        courant = courant->suivant;
      }
    }

    domaine initialiser(int borne_inf, int borne_sup){
      int i;
      domaine new_d = NULL;

      if(borne_sup < borne_inf){
        fprintf(fileToWrite, "La borne supérieure est inférieure à la borne inférieure : %d < %d\n", borne_sup, borne_inf);
        //Dans ce cas le domaine renvoyé sera vide
      }

      for(i = borne_inf; i <= borne_sup; i++)
        ajouter_valeur(&new_d, i);

      return new_d;
    }

    domaine union_domaine(domaine d1, domaine d2){
      domaine courant_d1;
      domaine courant_d2;

      domaine new_d = NULL;

      if(est_vide(d1))
        return d2;

      if(est_vide(d2))
        return d1;

      courant_d1 = d1;
      courant_d2 = d2;

      if(taille(d1) > taille(d2)){
        //On parcourt les listes jusqu'à la fin de la plus petite
        while(courant_d2 != NULL){
          ajouter_valeur(&new_d, courant_d1->valeur);
          ajouter_valeur(&new_d, courant_d2->valeur);

          courant_d1 = courant_d1->suivant;
          courant_d2 = courant_d2->suivant;
        }

        //Puis on termine le parcours de la plus grande
        while(courant_d1 != NULL){
          ajouter_valeur(&new_d, courant_d1->valeur);

          courant_d1 = courant_d1->suivant;
        }
      }
      else{
        while(courant_d1 != NULL){
          ajouter_valeur(&new_d, courant_d1->valeur);
          ajouter_valeur(&new_d, courant_d2->valeur);

          courant_d1 = courant_d1->suivant;
          courant_d2 = courant_d2->suivant;
        }

        while(courant_d2 != NULL){
          ajouter_valeur(&new_d, courant_d2->valeur);

          courant_d2 = courant_d2->suivant;
        }
      }

      return new_d;
    }

    domaine intersection(domaine d1, domaine d2){
      domaine courant_d1;
      domaine courant_d2;

      domaine new_d = NULL;

      if(est_vide(d1) || est_vide(d2))
        return NULL;

      courant_d1 = d1;
      courant_d2 = d2;

      if(taille(d1) > taille(d2)){
        while(courant_d2 != NULL){
          //On ajoute uniquement si la valeur courante est aussi dans l'autre domaine
          if(deja_presente(d1, courant_d2->valeur))
            ajouter_valeur(&new_d, courant_d2->valeur);

          courant_d1 = courant_d1->suivant;
          courant_d2 = courant_d2->suivant;
        }

        while(courant_d1 != NULL){
          if(deja_presente(d2, courant_d1->valeur))
            ajouter_valeur(&new_d, courant_d1->valeur);

          courant_d1 = courant_d1->suivant;
        }
      }
      else{
        while(courant_d1 != NULL){
          if(deja_presente(d2, courant_d1->valeur))
            ajouter_valeur(&new_d, courant_d1->valeur);

          courant_d1 = courant_d1->suivant;
          courant_d2 = courant_d2->suivant;
        }

        while(courant_d2 != NULL){
          if(deja_presente(d1, courant_d2->valeur))
            ajouter_valeur(&new_d, courant_d2->valeur);

          courant_d2 = courant_d2->suivant;
        }
      }

      return new_d;
    }

    domaine dupliquer_domaine(domaine d){
      domaine new_d = NULL;
      domaine courant = d;

      while(courant != NULL){
        //Pour chaque valeur du domaine d on l'ajoutera au nouveau domaine
        ajouter_valeur(&new_d, courant->valeur);
        courant = courant->suivant;
      }
      return new_d;
    }

    void vider_domaine(domaine d){
        if(d != NULL){
           vider_domaine(d->suivant);
           free(d);
      }
    }
