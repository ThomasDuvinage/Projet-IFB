#include "validation.h"
#include "../buffer.h"
#include "../generate_timetable/generation_timetable.h"
#include "../recherche_salle/recherche_salle.h"


int reinitialisation(){
    char week[15][20] = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};//permet de stocker tous les jours de la semaine 

	int jour,heure,minute,etage,numero_salle,salle;
	char get_jour[15];
	int index; //cette variable permet de connaitre l'index ou mettre l'etat de l'agent dans le tableau
	
	
	for(jour = 0; jour<5; jour++)
	{
		for(heure = 8; heure <= 18;heure++)//pour chaque heure de la journee nous remplisons les salles disponibles
		{
			for(minute = 0; minute <= 45; minute += 15)
			{
				for (etage = 0; etage < 3; etage++)//pour chaque etage nous balayons les salles dispo
				{
					//la boucle qui va suivre va permettre de remplir les dispo de l'etage 1
					for (numero_salle = MIN_SALLE; numero_salle <= MAX_SALLE; numero_salle++)
					{
						salle = numero_salle+(100*etage); //comme nous faisons varier les etages de 0 a 2 nous sommes obligé de faire une incrementation des salles
						index = ((heure-8)*4)+(minute/15); //cet index permet d'aller lire d'inserer dans l'emploi du temps provisoir de l'agent son etat

						//printf("salle number = %d\n",salle);

						for(int k = 0; k< 15;k++)
                        {//cette boucle permet de vider la variable get_jour afin de pouvoir ecrire un nouveau jour
							strcpy(&get_jour[k],"\0");//permet de mettre a jour la variable de get_jour 
						}
						strncpy(get_jour,week[jour],strlen(week[jour]));//permet de coller le jour dans une variable car sinon beug

						if(recherche_salle(etage+1,salle,get_jour,heure,minute) == 3 || recherche_salle(etage+1,salle,get_jour,heure,minute) == 2)
                        {
                            change_value(0,etage+1,salle,get_jour,heure,minute);
						}
					}
				}
			}
		}
	}

    return(0);
}