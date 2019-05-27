#ifndef VALIDATION_H_INCLUDE
#define VALIDATION_H_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BSIZE 80


int validation();


/**
 * @brief Cette fonction permet de changer un parametre dans un tableau csv
 * 
 * @param value 
 * @param etage 
 * @param numero_salle 
 * @param jour 
 * @param heure 
 * @param minute 
 */
int change_value(int value,int etage,int numero_salle,char jour[10],int heure,int minute);

int reinitialisation();


#endif

