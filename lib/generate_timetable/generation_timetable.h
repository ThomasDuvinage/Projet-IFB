#ifndef GENERATION_TIMETABLE_H_INCLUDE
#define GENERATION_TIMETABLE_H_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


#define NB_SIZE 100

#define MIN_SALLE 119
#define MAX_SALLE 120

#define NOMBRE_SALLE MIN_SALLE-MAX_SALLE


/**
 * @brief Get the nday object
 * 
 * @param day 
 * @param week 
 * @return int 
 */

int 
get_nday(char day[128],char week[8][20]);


/**
 * @brief Cette fonction permet de génerer l'emploi du temps de chaque personne 
 * 
 * @param nb_employe 
 * @param DISPO_E1 
 * @param DISPO_E2 
 * @param DISPO_E3 
 */
void 
generate();



#endif
