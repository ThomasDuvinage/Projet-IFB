#include "../lib/identification/identification.h"
#include "../lib/recherche_salle/recherche_salle.h"
#include "../lib/generate_timetable/generation_timetable.h"
#include "../lib/Validation/validation.h"
#include "../lib/buffer.h"


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

char nom_agent[20];
// ****** MAIN ******
 
int main() {
	system("clear");//permet d'effacer toutes les infos du terminal
	if (identification()) {
		system("clear");
		printf("\nBIENVENUE SUR NOTRE PLATFORME\n\n\n");
		printf("Cette application vous permet de faire de la gestion d'emploie du temps pour des agents de menage\n\n");
		printf("Realized by Sacha Manet, Enzo Lanzarini, Thomas Duvinage\n");

		clock_t start,end;
		start=clock();
		while(((end=clock())-start)<=((2000*CLOCKS_PER_SEC)/1000));

		char day[128];//cette chaine permet d'acceullir le nom du jour de la semaine
		time_t temps; //on initialise la librairie time a ce moment 
		struct tm date;//cela permet de faire appel a un dictionnaire deja present dans la librairie
		time_t secondes;
		struct tm instant;

		// On récupère la date et l'heure actuelles.
		time(&temps);
		date=*localtime(&temps);

		// On remplit la chaîne avec le format choisi, puis on l'affiche.
		strftime(day, 128, "%A", &date);//%A permet de renvoyer exclusivement le jour (Monday,..)

		time(&secondes);
        instant = *localtime(&secondes);

        int heure = instant.tm_hour;

		if(strcmp(day,"Monday") == 0 && strcmp(nom_agent,"thomas") == 0 && heure < 9){
			reinitialisation();
			generate();
		}
	}

	char choice;

	do{
		do
		{	
			system("clear");//si voulez faire la meme chose sur window --> system("cls");
			printf("Que souhaitez-vous faire ? \n");
			printf("1. VALIDER UNE SALLE\n");
			printf("2. GENERER LES EMPLOIS DU TEMPS \n");
			printf("3. QUITTER L'APPLICATION\n");
			printf("Votre choix : ");
			scanf(" %c",&choice);
			//printf("%d",choice);
			printf("\n");
			/* code */
		} while ((int)choice != 49 &&  (int)choice != 50 && (int)choice != 51);

		if(choice == 49){
			//faire la validation 
			system("clear");
			validation(); //quand la personne valide son action nous devonsnous regenerer afin de verifier 
			//si la salle n'a pas ete nettoye alors regenerons l'emplois du temps pour que la salle soit nettoyee
		}

		else if (choice == 50)
		{
			system("clear");
			generate();
		}

	
	}while (choice != 51);
	system("clear");

	return 0;
}

