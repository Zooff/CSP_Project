#ifndef _ARBRE
#define _ARBRE

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define A_IDF 10
#define A_ENTIER 11
#define A_REEL 12
#define A_BOOLEEN 13
#define A_SQRT 14
#define A_SIN 15
#define A_COS 16
#define A_TAN 17
#define A_ET 18
#define A_OU 19
#define A_NON 20 
#define A_EGAL 21
#define A_DIFFERENT 22
#define A_SUPERIEUR_OU_EGAL 23
#define A_INFERIEUR_OU_EGAL 24
#define A_SUPERIEUR 25
#define A_INFERIEUR 26
#define A_PLUS 27
#define A_MOINS 28
#define A_MULTIPLIE_PAR 29
#define A_DIVISE_PAR 30
#define A_MODULO 31

typedef struct noeud
{
  int nature; /* prend la valeur d'une des constantes ci dessus */
  float* valeur; // on y stocke soit un reel, soit un entier, soit 0 ou 1
  struct noeud* fils; /* pointeur sur le fils */
  struct noeud* frangin; /* pointeur sur le frangin */
}noeud;
typedef noeud* arbre;

arbre cons_noeud(int nature, float* valeur);
/* alloue un noeud, en y stockant sa nature.
   son fils et frangin sont NULL */

void videArbre(arbre a);
/* vide a en entamant par sa famille */

arbre attache_papa_frangin(arbre papa, arbre frangin);
/* met dans *papa.frangin le pointeur frangin */

arbre attache_papa_fils(arbre papa, arbre fils);
/* met dans *papa.fils le pointeur fils */

void afficheArbre(arbre a, int espace);
/* affiche recursivement l'arbre */

void afficheArbreBis(arbre a);
/* affiche en lettre la nature d'un noeud de l'arbre */

float evalue_contrainte(arbre a);
/* retourne le resultat de l'expression que contient l'arbre a */

#endif
