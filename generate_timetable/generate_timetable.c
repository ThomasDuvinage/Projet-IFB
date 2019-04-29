#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BSIZE 80

int recherche_salle();

void generate();

int main()
{

    for(int i = 219; i<221;i++){
        char nom_salle[10] = "p"; //on definit le nom de base soit p
        char nb_salle[12]; // on creer une chaine de caracteres qui va permettre de recevoir le numero de la salle en caracteres
    
        int numero_salle = i; // numero de la salle que nous recherchons 
        sprintf(nb_salle, "%d", numero_salle);//on convertit l'entier numero salle en char dans la chaine de caracteres nb_salle
        strcat(nom_salle,nb_salle); //on concatene les deux chaines de caracteres
        strcat(nom_salle,".csv"); //on ajoute la description du fichier 
        printf("%s\n",nom_salle);
        printf("%d \n",recherche_salle(nom_salle,9,0));

    }
}


void generate(){
	char buffer[BSIZE];
	FILE *f;
	char *field;
	int DISPO_E1[20]={0},DISPO_E2[20]={0},DISPO_E3[20]={0};//variables correspondant a la dispo pour chaque 1/4 H

    char day[128];
    time_t temps;
    struct tm date;

    // On récupère la date et l'heure actuelles.
    time(&temps);
    date=*localtime(&temps);

    // On remplit la chaîne avec le format choisi, puis on l'affiche.
    strftime(day, 128, "%A", &date);//%A permet de renvoyer exclusivement le jour (Monday,..)
    //puts(format);
    
    
	
	

}



int recherche_salle(char nom_salle[10],int heure,int minute){//les minutes --> 0, 15, 30, 45
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