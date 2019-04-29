#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BSIZE 80

int recherche_salle();

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
        recherche_salle(nom_salle);// puis on utilise le nom de la salle dans la fonction
    }

}


int recherche_salle(char nom_salle[10]){
	char buffer[BSIZE];
	FILE *f;
	char *field;
	int DISPO0,DISPO15,DISPO30,DISPO45;

    int n = 8;

	/* open the CSV file */
	f = fopen(nom_salle,"r");
	if( f == NULL)
	{
		printf("Unable to open file '%s'\n",nom_salle);
		exit(1);
	}

	while(fgets(buffer,BSIZE,f))
	{
		/* get year */
		field=strtok(buffer,",");
		DISPO0=atoi(field);

		field=strtok(NULL,",");
		DISPO15=atoi(field);

		field=strtok(NULL,",");
		DISPO30=atoi(field);

        field=strtok(NULL,",");
		DISPO45=atoi(field);


		/* display the result in the proper format */
		printf("Pour %dh les dispos sont %d -- %d -- %d -- %d\n",n,DISPO0,DISPO15,DISPO30,DISPO45);

        n++;
	}

	/* close file */
	fclose(f);

	return(0);
}