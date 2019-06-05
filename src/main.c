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
	}

	int choice;

	do{
		do
		{
			system("clear");//si voulez faire la meme chose sur window --> system("cls");
			printf("Que souhaitez-vous faire ? \n");
			printf("1. VALIDER UNE SALLE\n");
			printf("2. GENERER LES EMPLOIS DU TEMPS \n");
			printf("3. REINITIALISER LES EMPLOIS DU TEMPS (à faire tous les lundi)\n");
			printf("4. QUITTER L'APPLICATION\n");
			printf("Votre choix : ");
			scanf("%d",&choice);
			printf("\n");
			/* code */
		} while (choice != 1 && choice != 2 && choice !=3 && choice != 4);

		if(choice == 1){
			//faire la validation 
			system("clear");
			validation(); //quand la personne valide son action nous devonsnous regenerer afin de verifier 
			//si la salle n'a pas ete nettoye alors regenerons l'emplois du temps pour que la salle soit nettoyee
		}

		else if (choice == 2)
		{
			system("clear");
			generate();
		}

		else if (choice == 3)
		{
			system("clear");
			reinitialisation();
		}
		

	}while (choice != 4);
	system("clear");

	return 0;
}

