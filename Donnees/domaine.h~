#ifndef __DOM
#define __DOM

#include <stdio.h>
#include <stdlib.h>

    struct s_element{
      int valeur; //Un élément du domaine possède une valeur, ici un entier

      struct s_element* suivant; //Un pointeur sur l'élément suivant
      struct s_element* precedent; //Et un autre sur l'élément précédent
    };

    typedef struct s_element* domaine;

    domaine creer_domaine(); //Met à nul le domaine
    int est_vide(domaine); //Renvoie 1 si le domaine est vide (comprendre est NULL) 0 sinon
    int taille(domaine); //Renvoie la taille du domaine passé en argument
    int deja_presente(domaine , int); //Renvoie 1 si l'entier est déjà dans le domaine 0 sinon
    int ajouter_valeur(domaine* , int); //Renvoie 1 si la valeur a été ajoutée 0 sinon
    int obtenir_valeur(domaine, int); //Renvoie la valeur située à indice dans le domaine d
    void afficher_domaine(domaine); //Affiche le domaine passé en argument avec un valeur par ligne
    domaine dupliquer_domaine(domaine); //Duplique le domaine passer en argument
    domaine initialiser(int borne_inf, int borne_sup); //Renvoie un domaine contenant toutes les valeurs entre borne_inf et borne_sup incluses
    domaine union_domaine(domaine d1, domaine d2); //Renvoie l'union des domaines d1 et d2
    domaine intersection(domaine d1, domaine d2); //Renvoie l'intersection des domaines d1 et d2
    void vider_domaine(domaine d); // Vide recursivement d

#endif
