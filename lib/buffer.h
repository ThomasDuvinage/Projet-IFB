#ifndef BUFFER_H_INCLUDE
#define BUFFER_H_INCLUDE

#define BSIZE 80

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

/**
 * @brief cette declaration extern permet d'avoir accès à namePassBuffer dans toutes les fonctions <https://docs.microsoft.com/fr-fr/cpp/cpp/extern-cpp?view=vs-2019>
 * 
 */
extern char namePassBuffer[45][20];//utilisée dans tous les fichiers identifications 
extern int nombre_agent;
extern char nom_agent[20];
//RECHERCHER SALLE
extern char nom_salle[50]; //utilisée dans la fonction de recherche de salle 

//VALIDATION
extern char chemin_fichier[50];// utilisée dans la fonction de validation
int numero_salle,etage;// declaration des variables 
//initialisation
extern char path_to_csv[50];


#endif
