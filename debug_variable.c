#include "variable.h"



/*       Fichier de test des fonctions de la bibliotheque variable.h        */

/* Pour l'instant tout a l'air d'être correct même Valgrind ne râle pas */


int main(){


  variables liste_var = creer_liste_var_vide();      // <---- Instantiation de la liste
  pile_domaines *p1;
  domaine d = creer_domaine();

  ajouter_valeur(&d, 2);
  ajouter_valeur(&d, 3);
  ajouter_valeur(&d, 4);

  empiler(&p1,d);


  liste_var = ajouter_var(liste_var, "var", *p1, NULL);       // <---- Ajout d'element, pour l'instant la fonction retourne une liste,
  liste_var = ajouter_var(liste_var, "var2", *p1, NULL);     //         on pourrai aussi travailler sur un pointeur. A discuter
  liste_var = ajouter_var(liste_var, "var3", *p1, NULL);

  affecter_valeur(liste_var);

  afficher_liste(liste_var);                                    // <---- Affichage de la liste

  fprintf(stderr, "\n\n");

                                                                         // <---- Quelques fonctions de gestion de liste
  fprintf(stderr,"Premiere Variable -> ");
  afficher_variable(premiere_variable(liste_var));

  fprintf(stderr, "Derniere Variable -> ");
  afficher_variable(derniere_variable(liste_var));

  fprintf(stderr, "\n\n");

  fprintf(stderr, "Suppression d'element\n");
  supprimer_variable(liste_var, "var2");             // <---- Suppresion d'un element
  afficher_liste(liste_var);

  liberer_liste(liste_var);                                    // <---- Liberation de la mémoire

  return EXIT_SUCCESS;

}
