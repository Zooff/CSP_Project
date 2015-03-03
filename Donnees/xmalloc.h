#ifndef XMAL
#define XMAL

/* Header de xmalloc 
Auteur : Dimitri Escalle
Date : 19/02/2014 
*/
#include <stdio.h>
#include <stdlib.h>
// Fonction d'allocation mémoire vérifiant que celle ci a été bien aloué
void* xmalloc(size_t nbbloc, size_t tailleob);

#endif
