#include "generation_timetable.h"
#include "../recherche_salle/recherche_salle.h"
#include"../buffer.h"

void generate(int nb_employe,int DISPO_E1[],int DISPO_E2[],int DISPO_E3[]){
	char buffer[BSIZE];
	FILE *f;
	char *field;

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

	int etage_1[100]={0}, etage_2[100]= {0},etage_3[100]={0};
	int index_etage1 = 0, index_etage2 = 0, index_etage3 = 0;
	int nb_tache1 = 0,nb_tache2 = 0, nb_tache3 = 0;
	int heure,minute,etage,numero_salle;
    
	for(heure = 8; heure <= 18;heure++)//pour chaque heure de la journee nous remplisons les salles disponibles
	{
		for(minute = 0; minute <= 45; minute = minute + 15)
		{
			for (etage = 0; etage < 3; etage++)//pour chaque etage nous balayons les salles dispo
			{
				//la boucle qui va suivre va permettre de remplir les dispo de l'etage 1
				for (numero_salle = 119; numero_salle <= 120; numero_salle++)
				{
					int salle = numero_salle+(100*etage);//nous somme oblige de faire cela car numero salle varie de 100 a 120 
					//or dans les etages nous modifions le numero de salle de 100 en 100 donc si nous passons a l'etage 2 soit etage = 1 dans le programme alors on aura numero salle = 220 par exemple
					if(recherche_salle(etage+1,salle,day,heure,minute) != -1){
						printf("heure :%d minute : %d etage : %d salle : %d  etat : %d \n\n",heure,minute,etage+1,salle,recherche_salle(etage+1,salle,day,heure,minute));

						if(etage+1 == 1){
							//rechercher la dispo de toutes les salles pour l'etage 1
							if(recherche_salle(etage+1,numero_salle,day,heure,minute) == 0){
								etage_1[index_etage1] = numero_salle; //nous somme oblige de faire cela car numero salle varie de 100 a 120 
								//or dans les etages nous modifions le numero de salle de 100 en 100 donc si nous passons a l'etage 2 soit etage = 1 dans le programme alors 
								index_etage1++;		
							}					
						}

						if(etage+1 == 2){
							//rechercher la dispo de toutes les salles pour l'etage 2
							if(recherche_salle(etage,numero_salle,day,heure,minute) == 0){
								etage_2[index_etage2] = numero_salle;	
								index_etage2++;	
							}		
						}

						if(etage+1 == 3){
							//recherche la dispo de toutes les salles de l'etage 3
							if(recherche_salle(etage,numero_salle,day,heure,minute) == 0){
								etage_3[index_etage3] = numero_salle;	
								index_etage3++;		
							}				
						}
					}
				}
			}
		}
	}

	//en sortie de cette boucle on a par exemple etage_1 = [0,0,121,0]
	//nous devons maintenant definir pour quel etage est ce qu'il a le plus de salle a nettoyer
}


// ********** ECART TYPE *********
//cette fonction permet de calculer en fonction de chaque etage l'heure pour laquelle il y le plus besoins de personnel 
//pour cela nous devons calculer la moyenne et ensuite lire la valeur retourne du fichier pour chaque 1/4h
float ecart_type(int DISPO_ETAGE[]){
	int nombre_interation = long_DISPO_ETAGE(DISPO_ETAGE)/2;//cela permet de dire que le nombre d'itterations correspond au nombre de 1/4h pour une demi journee (/2)
	int sum = 0; //cela permet de calculer la somme des termes afin de faire la moyenne
	float ecart_type = 0;

	//le for qui sui permet de calculer la somme afin de faire le calcul de la moyenne
	for (int itterations = 0; itterations < nombre_interation; itterations++)
	{
		sum += DISPO_ETAGE[itterations];
	}

	float moyenne = sum / nombre_interation;//on calcul la moyenne

	//le for qui va suivre permet de faire le calcul de l'ecart type
	for (int itterations = 0; itterations < nombre_interation; itterations++)
	{
		ecart_type += pow(fabsf(DISPO_ETAGE[itterations] - moyenne),2);
	}

	ecart_type = sqrt(ecart_type);

	return ecart_type;
}


/**
 * @brief Cette fonction permet de connnaitre la longueur de la chaine
 * 
 * @param chaine 
 * @return int 
 */
int long_DISPO_ETAGE(int chaine[]){
    int n = 0;
    while(chaine[n] != '\0'){
        n++;
    }
    n=n-1;
    return n;
}


