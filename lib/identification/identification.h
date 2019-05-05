#ifndef IDENTIFICATION_H_INCLUDE
#define IDENTIFICATION_H_INCLUDE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


//DECLARATIONS DES FONCTIONS

/**
 * @brief Cette fonction permet de savoir si la personne peut rentrer dans la platforme 
 * 
 * @return true 
 * @return false 
 */

bool
identification();

/**
 * @brief Cette fonction permet de lire les identifiants dans le fichier csv et ainsi de remplir le tableau qui correspond à ça
 * 
 * @param nb_employe 
 */
void 
lecture_identifiant		(int* nb_employe);

/**
 * @brief Cette fonction permet de creer un agent dans la base de données pour ensuite l'ajouter dans le tableau que vous avons lu grâce à la fonction lecture_identifiant
 * 
 * @param nb_employe 
 * @return int 
 */
int  
creation_agent			(int* nb_employe);

#endif
