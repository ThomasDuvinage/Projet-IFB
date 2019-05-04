#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define true 1
#define false 0

#define BSIZE 80
char nom_pswd[20][45];//cette chaine de caractere permet de contenir le nom et pwd

//DECLARATIONS DES FONCTIONS

/**
 * @brief Cette fonction me fait chier
 * 
 * @param nom_pswd 
 * @return true 
 * @return false 
 */
bool identification(char nom_pswd[20][45]);//on declare la fonction
void lecture_identifiant(char nom_pswd[20][45],int* nb_employe);
int creation_agent(char nom_pswd[20][45], int* nb_employe);