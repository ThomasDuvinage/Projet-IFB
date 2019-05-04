#ifndef IDENTIFICATION_H_
#define IDENTIFICATION_H_


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


#define BSIZE 80


//DECLARATIONS DES FONCTIONS

/**
 * @brief Cette fonction me fait chier
 * 
 * @param nom_pswd 
 * @return true 
 * @return false 
 */

bool
identification();

void 
lecture_identifiant	(char(*nom_pswd)[20][45],	int* nb_employe);

int  
creation_agent			(char(*nom_pswd)[20][45],	int* nb_employe);

#endif