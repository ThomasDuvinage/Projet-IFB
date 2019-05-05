#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


#define BSIZE 80


extern char namePassBuffer[45][20];

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
lecture_identifiant		(int* nb_employe);

int  
creation_agent			(int* nb_employe);
