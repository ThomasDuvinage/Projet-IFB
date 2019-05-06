#ifndef GENERATION_TIMETABLE_H_INCLUDE
#define GENERATION_TIMETABLE_H_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


#define NB_SIZE 100

int DISPO_E1[NB_SIZE]={0},DISPO_E2[NB_SIZE]={0},DISPO_E3[NB_SIZE]={0};//variables correspondant a la dispo pour chaque 1/4 H

//nous definisons les fonctions
int 
recherche_salle(int etage,int numero_salle,char jour[],int heure,int minute);

/**
 * @brief Cette fonction permet de génerer l'emploi du temps de chaque personne 
 * 
 * @param nb_employe 
 * @param DISPO_E1 
 * @param DISPO_E2 
 * @param DISPO_E3 
 */
void 
generate(int nb_employe,int DISPO_E1[20],int DISPO_E2[20],int DISPO_E3[20]);

/**
 * @brief Cette fonction permet de savoir a quelle heure les salles sont le plus libre en fonction de l'heure cela permet de savoir le nombre moyens que nous devons mettre a chaque etage afin de mieux manager le tout 
 * 
 * @param DIPO_ETAGE 
 * @return float 
 */
float 
ecart_type(int DIPO_ETAGE[]);

/**
 * @brief permet d'avoir la longueur de la chaine 
 * 
 * @param chaine 
 * @return int 
 */
int 
long_DISPO_ETAGE(int chaine[]);


#endif
