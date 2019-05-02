#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BSIZE 80

//nous definisons les fonctions
int recherche_salle(int etage,char nom_salle[10],char jour[10],int heure,int minute);
void generate(int nb_employe,int DISPO_E1[20],int DISPO_E2[20],int DISPO_E3[20]);


int DISPO_E1[20]={0},DISPO_E2[20]={0},DISPO_E3[20]={0};//variables correspondant a la dispo pour chaque 1/4 H


int main()
{

}


void generate(int nb_employe,int DISPO_E1[20],int DISPO_E2[20],int DISPO_E3[20]){
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
    
	for(int heure = 8; heure <= 18;heure++)//pour chaque heure de la journee nous remplisons les salles disponibles
	{
		for(int minute = 0; minute <=45; minute = minute + 15)
		{
			for (int etage = 0; etage < 3; i++)//pour chaque etage nous balayons les salles dispo
			{
				//la boucle qui va suivre va permettre de remplir les dispo de l'etage 1
				for (int numero_salle = 100; numero_salle < 120; numero_salle++)
				{
					numero_salle = numero_salle+(100*etage);//nous somme oblige de faire cela car numero salle varie de 100 a 120 
					//or dans les etages nous modifions le numero de salle de 100 en 100 donc si nous passons a l'etage 2 soit etage = 1 dans le programme alors on aura numero salle = 220 par exemple
					switch (etage)
					{
					case 1:
						//rechercher la dispo de toutes les salles pour l'etage 1
						if(recherche_salle(etage+1,numero_salle,day,heure,minute) == 0){
							etage_1[index_etage1] = numero_salle; //nous somme oblige de faire cela car numero salle varie de 100 a 120 
							//or dans les etages nous modifions le numero de salle de 100 en 100 donc si nous passons a l'etage 2 soit etage = 1 dans le programme alors 
							nb_tache1++;	
						}		
						index_etage1++;				
						break;

					case 2:
						//rechercher la dispo de toutes les salles pour l'etage 2
						if(recherche_salle(etage,numero_salle,day,heure,minute) == 0){
							etage_2[index_etage2] = numero_salle;	
							nb_tache2;	
						}		
						index_etage2++;				
						break;

					case 3:
						//recherche la dispo de toutes les salles de l'etage 3
						if(recherche_salle(etage,numero_salle,day,heure,minute) == 0){
							etage_3[index_etage3] = numero_salle;	
							nb_tache3;	
						}		
						index_etage3++;				
						break;
					
					default:
						break;
					}  
				}
			}
		}
	}

	//en sortie de cette boucle on a par exemple etage_1 = [0,0,121,0]
	//nous devons maintenant definir pour quel etage est ce qu'il a le plus de salle a nettoyer



}

double ecart_type(int DISPO_ETAGE[20]){
	
}



int recherche_salle(int etage,char nom_salle[10],char jour[10],int heure,int minute){//les minutes --> 0, 15, 30, 45
	char buffer[BSIZE];
	FILE *f;
	char *field;
	int DISPO0,DISPO15,DISPO30,DISPO45;

	int DISPO_J[40]={0};//tableau qui permet d'acceuillir toutes les valeurs que nous lisons du fichier
	//cela permet de pouvoir modifier le tableau puis de le l'ecrire par la suite dans le fichier

    int n = 8;//curseur permettant d'afficher l'heure dans l'affichage
	int i = 0; //curseur permettant de remplir le tableau des dispos_j

	/* open the CSV file */
	f = fopen(nom_salle,"r");

	if( f == NULL)//si on arrive pas a ouvrir on affiche un message
	{
		printf("Impossible d'ouvrir le fichier '%s'\n",nom_salle);
		exit(1);
	}

	while(fgets(buffer,BSIZE,f))
	{
		/* get year */
		field=strtok(buffer,",");//on separe le fichier en chaine de caractere entre chaque (,)
		DISPO0=atoi(field);//on associe a la variable la valeur en entier de la chaine de caractere de la valeur lue precedement --> fonction atoi()

		field=strtok(NULL,",");
		DISPO15=atoi(field);

		field=strtok(NULL,",");
		DISPO30=atoi(field);

        field=strtok(NULL,",");
		//fputs("n", f);
		DISPO45=atoi(field);

		/* display the result in the proper format */
		//printf("Pour %dh les dispos sont %d -- %d -- %d -- %d\n",n,DISPO0,DISPO15,DISPO30,DISPO45);

		//les 4 lignes suivantes permettent de remplir le tableau des valeurs lues
		DISPO_J[i]=DISPO0;
		DISPO_J[i+1] = DISPO15;
		DISPO_J[i+2] = DISPO30;
		DISPO_J[i+3] = DISPO45;

		i=i+4;//on incremente le cursueur de 4 en 4
        //n++; //utile pour l'affichage de l'heure
	}
	/* close file */
	fclose(f);//femeture de la lecture du fichier

	int index = ((heure-8)*4)+(minute/15);

	//printf("%d \n",index);
	//printf("%d \n",DISPO_J[index]);

	return(DISPO_J[index]);
}
