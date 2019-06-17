#include "generation_timetable.h"
#include "../Validation/validation.h"
#include "../identification/identification.h"
#include "../recherche_salle/recherche_salle.h"
#include"../buffer.h"
#include "../personnel/agents_modif.h"

int nombre_agent;
char namePassBuffer[45][20]; 

int agents_karma[20] ;
int agents_travail[20] ;

void generate(){
	reinitialisation();
	char week[15][20] = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};//permet de stocker tous les jours de la semaine 

	//on genere les tableaux pour les agents
	for(int i = 0; i<nombre_agent ; i++){
		agents_karma[i] = i;
		agents_travail[i] = i;

	}
	//cette partie permet de remettre a zero tous les emplois du temps deja generer auparavant 
	//pour cela nous creons des fichiers vides
	for(int i = 0;i<nombre_agent;i++){
		char chemin_agent[50] = "csv_files/agents/";//cette variable est declarer en extren dans le fichier buffer.h

		FILE *reecriture_fichier;

		char numero_agent_char[5] = "";
		
		sprintf(numero_agent_char, "%d",i);//on convertit l'entier numero salle en char dans la chaine de caracteres nb_salle
		strcat(chemin_agent,numero_agent_char);
		strcat(chemin_agent,"_");
		strcat(chemin_agent,namePassBuffer[i*2]);//nous multiplions par 2 afin de selectionner uniquement les noms des agents 
		strcat(chemin_agent,".csv"); //on ajoute la description du fichier
		//printf("%s\n",chemin_agent);

		reecriture_fichier = fopen(chemin_agent,"w");

		fclose(reecriture_fichier);
	}


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
	int salle_nettoyer[7][50] = {0};
	int nb_salle_nettoyer = 0;

	int jour,heure,minute,etage,numero_salle,salle;
	char get_jour[15];
	int agent_check_disponibility[20][50] = {0}; //cette variable permet de savoir si la personne a deja une salle a nettoyer a l'heure selectionner
	//cette partie permet de remettre les fichiers des agents a zero afin de les remplir correctement
	int index; //cette variable permet de connaitre l'index ou mettre l'etat de l'agent dans le tableau
	
	
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
						salle = numero_salle+(100*etage); //comme nous faisons varier les etages de 0 a 2 nous sommes obligé de faire une incrementation des salles
						index = ((heure-8)*4)+(minute/15); //cet index permet d'aller lire d'inserer dans l'emploi du temps provisoir de l'agent son etat

						for(int k = 0; k< 15;k++){//cette boucle permet de vider la variable get_jour afin de pouvoir ecrire un nouveau jour
							strcpy(&get_jour[k],"\0");//permet de mettre a jour la variable de get_jour 
						}

						strncpy(get_jour,week[jour],strlen(week[jour]));//permet de coller le jour dans une variable car sinon beug
						//printf("je suis celui que tu cherches %s de longueur : %lu\n",get_jour,strlen(week[6]));

						//printf("heure :%d minute : %d etage : %d salle : %d etat : %d jour: %d\n\n",heure,minute,etage+1,salle,recherche_salle(etage+1,salle,get_jour,heure,minute),jour);
						//nous somme oblige de faire cela car numero salle varie de 100 a 120 
						//or dans les etages nous modifions le numero de salle de 100 en 100 donc si nous passons a l'etage 2 soit etage = 1 dans le programme alors on aura numero salle = 220 par exemple
				
						if(recherche_salle(etage+1,salle,get_jour,heure,minute) == 0 || recherche_salle(etage+1,salle,get_jour,heure,minute) == 3){
							int indice_validation = 0;//cet indice permet de savoir si la salle a deja ete nettoyer
							for(int i = 0 ; i < 50;i++){//200 correspond à la dimension du tableau
								if(salle_nettoyer[jour][i] == salle){//si il y a une appartenant alors nous ne nettoyons pas la salle
									indice_validation = 1;//permet de savoir si une salle a deja été nettoyer
									i = 200;//permet de stopper la boucle
								}
							}

							if(indice_validation == 0){//or si celle-ci n'appartient pas encore au tableau alors nous la nettoyons
								int agent_choisi = choix_agent();//cette variable me permet de stocker le numero de l'agent car en comme j'utilise la fonction rand je ne peux pas l'appeller a chaque fois 
								int loop_stop = 0;//cette variable me permet de savoir combien de fois j'ai essaye de nettoyer une salle afin de ne pas essayer à l'infini

								//si vous arrivez pas a trouver facilement alors vous devez augmenter le nombre de boucle afin que le rand tombe sur le bon agent 
								while(agent_check_disponibility[agent_choisi][index] != 0 && loop_stop < 10){//cette boucle me permet de trouver le bon agent qui est disponible pour realiser la tache a faire
									agent_choisi = choix_agent();//si les parametres ne correspondent pas alors je regenere un agent
									loop_stop++;
								}

								if(loop_stop != 10){//si nous avons pas atteint le seuil de loop max alors cela signifie que nous avons trouver le bon agent
									ajout_tache(agent_choisi,get_jour,salle,etage,heure,minute);
									change_value(3,etage+1,salle,get_jour,heure,minute);
									salle_nettoyer[jour][nb_salle_nettoyer] = salle;//on ajoute la salle a l'index qui nous interresse
									nb_salle_nettoyer++;//permet de deplacer le curseur afin d'ajouter la salle suivante au bon index dans le tableau
									agent_check_disponibility[agent_choisi][index] = 1;
								}
								// else{
								// 	printf("Nous n'avons pas pu trouver de disponibilité d'agent pour le nettoyage de la salle : %d\n",numero_salle);
								// }
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

	// for(int i = 0;i<nombre_agent;i++){
	// 	for(int k = 0; k<50;k++){
	// 		printf("disponibilté de l'agent %d =  %d\n",i,agent_check_disponibility[i][k]);
	// 	}
	// }

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