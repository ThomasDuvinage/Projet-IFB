#include "generation_timetable.h"
#include "../identification/identification.h"
#include "../recherche_salle/recherche_salle.h"
#include"../buffer.h"
#include "../personnel/agents_modif.h"

void generate(){
	char week[15][20] = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};//permet de stocker tous les jours de la semaine 

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
	
	int index_jour = get_nday(day,week);
	/**
	 * @brief ces tableaux d'entier permettent de stocker les salles qui doivent etre nettoyer
	 * 
	 */
	int etage_1[200]={0}, etage_2[200]= {0},etage_3[200]={0};
	int salle_nettoyer[7][500] = {0};
	int nb_salle_nettoyer = 0;
	int index_etage1 = 0, index_etage2 = 0, index_etage3 = 0;
	int nb_tache1 = 0,nb_tache2 = 0, nb_tache3 = 0;
	int jour,heure,minute,etage,numero_salle,salle;
	char get_jour[15];

	//cette partie permet de remettre les fichiers des agents a zero afin de les remplir correctement
	for(jour = index_jour; jour<5; jour++)
	{
		nb_salle_nettoyer = 0;
		for(heure = 8; heure <= 18;heure++)//pour chaque heure de la journee nous remplisons les salles disponibles
		{
			for(minute = 0; minute <= 45; minute += 15)
			{
				for (etage = 0; etage < 3; etage++)//pour chaque etage nous balayons les salles dispo
				{
					//la boucle qui va suivre va permettre de remplir les dispo de l'etage 1
					for (numero_salle = MIN_SALLE; numero_salle <= MAX_SALLE; numero_salle++)
					{
						salle = numero_salle+(100*etage); 

						for(int k = 0; k< 15;k++){//cette boucle permet de vider la variable get_jour afin de pouvoir ecrire un nouveau jour
							strcpy(&get_jour[k],"\0");//permet de mettre a jour la variable de get_jour 
						}

						strncpy(get_jour,week[jour],strlen(week[jour]));//permet de coller le jour dans une variable car sinon beug
						//printf("je suis celui que tu cherches %s de longueur : %lu\n",get_jour,strlen(week[6]));

						printf("heure :%d minute : %d etage : %d salle : %d etat : %d jour: %d\n\n",heure,minute,etage+1,salle,recherche_salle(etage+1,salle,get_jour,heure,minute),jour);
						//nous somme oblige de faire cela car numero salle varie de 100 a 120 
						//or dans les etages nous modifions le numero de salle de 100 en 100 donc si nous passons a l'etage 2 soit etage = 1 dans le programme alors on aura numero salle = 220 par exemple
				
						if(recherche_salle(etage+1,salle,get_jour,heure,minute) == 0){
							int indice_validation = 0;//cet indice permet de savoir si la salle a deja ete nettoyer
							for(int i = 0 ; i < 500;i++){//200 correspond à la dimension du tableau
								if(salle_nettoyer[jour][i] == salle){//si il y a une appartenant alors nous ne nettoyons pas la salle
									indice_validation = 1;
									i = 200;//permet de stopper la boucle
								}
							}

							if(indice_validation == 0){//or si celle-ci n'appartient pas encore au tableau alors nous la nettoyons
								ajout_tache(choix_agent(),get_jour,salle,etage,heure,minute);
								salle_nettoyer[jour][nb_salle_nettoyer] = salle;
							}
						}
						
					}
				}
			}
		}
	}
	//cette boucle permet d'afficher toutes les salles disponibles chaque 1/4h
	// for (int i = 0; i < 200; i++)
	// {
	// 	/* code */
	// 	printf("salle a nettoyer ETAGE 1: %d   ",etage_1[i]);
	// 	printf("salle a nettoyer ETAGE 2: %d  ",etage_2[i]);
	// 	printf("salle a nettoyer ETAGE 3: %d \n",etage_3[i]);
	// }

	//printf("L'agent choisi est le : %d\n",choix_agent());

}


/**
 * @brief Get the nday object cette fonction permet de connaitre l'index du jour actuelle dans la semaine afin de calculer uniquement pour les jours dans la fin de semaine qui nous interesse
 * 
 * @param day 
 * @param week 
 * @return int 
 */
int get_nday(char day[128],char week[8][20]){
	int i = 0;
	//printf("%d",strncmp(day,week[3],strlen(week[3])));
	while (strncmp(day, week[i],strlen(week[i])) != 0)
	{
		i++;
	} 

	return i;
}