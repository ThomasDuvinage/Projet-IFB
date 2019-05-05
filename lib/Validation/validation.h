#ifndef VALIDATION_H_INCLUDE
#define VALIDATION_H_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BSIZE 80


/**
 * @brief Cette fonction permet de générer le chemin pour acceder au fichier csv recherché
 * 
 */
void 
generation_chemin();

/**
 * @brief Cette fonction permet de modifier l'état de salle. Cela consiste en la re-ecriture du fichier que la personne a donner
 * 
 * @return int 
 */
int 
modif_etat();



#endif

