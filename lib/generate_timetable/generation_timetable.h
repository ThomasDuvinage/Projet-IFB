#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


#define BSIZE 80
#define NB_SIZE 100

int DISPO_E1[NB_SIZE]={0},DISPO_E2[NB_SIZE]={0},DISPO_E3[NB_SIZE]={0};//variables correspondant a la dispo pour chaque 1/4 H

//nous definisons les fonctions
int recherche_salle(int etage,int numero_salle,char jour[],int heure,int minute);
void generate(int nb_employe,int DISPO_E1[20],int DISPO_E2[20],int DISPO_E3[20]);

//declaration de la fonction pour le calcul de l'ecart type 
float ecart_type(int DIPO_ETAGE[]);
int long_DISPO_ETAGE(int chaine[]);

