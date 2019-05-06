#include "generation_timetable.h"
#include "../recherche_salle/recherche_salle.h"
#include"../buffer.h"

void generate(){
	int i = 0;//nous creons un curseur qui va nous servir d'index pour remplie les dispo_etage

    char day[128];//cette chaine permet d'acceullir le nom du jour de la semaine
    time_t temps; //on initialise la librairie time a ce moment 
    struct tm date;//cela permet de faire appel a un dictionnaire deja present dans la librairie

    // On récupère la date et l'heure actuelles.
    time(&temps);
    date=*localtime(&temps);

    // On remplit la chaîne avec le format choisi, puis on l'affiche.
    strftime(day, 128, "%A", &date);//%A permet de renvoyer exclusivement le jour (Monday,..)
    //puts(day);//permet d'afficher le jour que nous sommes
	
	/**
	 * @brief ces tableaux d'entier permettent de stocker les salles qui doivent etre nettoyer
	 * 
	 */
	int etage_1[100]={0}, etage_2[100]= {0},etage_3[100]={0};
	int index_etage1 = 0, index_etage2 = 0, index_etage3 = 0;
	int nb_tache1 = 0,nb_tache2 = 0, nb_tache3 = 0;
	int heure,minute,etage,numero_salle,salle;


	for(heure = 8; heure <= 18;heure++)//pour chaque heure de la journee nous remplisons les salles disponibles
	{
		for(minute = 0; minute <= 45; minute += 15)
		{
			for (etage = 0; etage < 3; etage++)//pour chaque etage nous balayons les salles dispo
			{
				//la boucle qui va suivre va permettre de remplir les dispo de l'etage 1
				for (numero_salle = 119; numero_salle <= 120; numero_salle++)
				{
					salle = numero_salle+(100*etage); 
					printf("heure :%d minute : %d etage : %d salle : %d etat : %d \n\n",heure,minute,etage+1,salle,recherche_salle(etage+1,salle,day,heure,minute));
					//nous somme oblige de faire cela car numero salle varie de 100 a 120 
					//or dans les etages nous modifions le numero de salle de 100 en 100 donc si nous passons a l'etage 2 soit etage = 1 dans le programme alors on aura numero salle = 220 par exemple
			
					if(recherche_salle(etage+1,salle,day,heure,minute) != -1){
						if(etage+1 == 1){
							//rechercher la dispo de toutes les salles pour l'etage 1
							if(recherche_salle(etage+1,salle,day,heure,minute) == 0){
								etage_1[index_etage1] = salle; //nous somme oblige de faire cela car numero salle varie de 100 a 120 
								//or dans les etages nous modifions le numero de salle de 100 en 100 donc si nous passons a l'etage 2 soit etage = 1 dans le programme alors 
								index_etage1++;	//de base nous avons rempli le tableau etage_1 de 0 donc on rempli avec la salle si la condition est verifiee
							}
							else
							{
								index_etage1++;//cela permet de sauter un champ de la sorte nous pourrons savoir a la salle, l'heure, la minute d'une paire de coups
							}					
						}

						if(etage+1 == 2){
							//rechercher la dispo de toutes les salles pour l'etage 2
							if(recherche_salle(etage+1,salle,day,heure,minute) == 0){
								etage_2[index_etage2] = salle;	
								index_etage2++;	
							}
							else
							{
								index_etage2++;
							}	
						}

						if(etage+1 == 3){
							//recherche la dispo de toutes les salles de l'etage 3
							if(recherche_salle(etage+1,salle,day,heure,minute) == 0){
								etage_3[index_etage3] = salle;	
								index_etage3++;		
							}	
							else
							{
								index_etage3++;
							}			
						}
					}
					else
					{
					printf("il y a un probleme dans la declaration des parametres dans code\n");
					exit(1);
					}
				}
			}
		}
	}

	//en sortie de cette boucle on a par exemple etage_1 = [0,0,121,0]
	//nous devons maintenant definir pour quel etage est ce qu'il a le plus de salle a nettoyer
}




