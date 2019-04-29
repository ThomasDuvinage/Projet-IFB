#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BSIZE 80

int modif_etat();

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

        modif_etat(nom_salle);// puis on utilise le nom de la salle dans la fonction
    }
}


int modif_etat(char nom_salle[10]){
	char buffer[BSIZE];
	FILE *f;
	char *field;
	int DISPO0,DISPO15,DISPO30,DISPO45;//variables correspondant a la dispo pour chaque 1/4 H

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
	fclose(f);//on ferme la boucle de lecture de fichier 

	//il faut remplacer à cette endroit les valeurs du tableau afin de les remettre dans le fichier 

	

	//on passe en mode ecriture de fichier, cela permet de remplacer les valeurs dans le tableau et apres de les inseres dans le fichier
	f = fopen(nom_salle,"w");

	//on fait une boucle pour remplir le fichier 
	for(int i = 0; i < 40; i=i+4)//40 correspond au nombre de valeur car on fait de 8h a 18h donc 4*10 valeurs 
	{
		fprintf(f, "%d,%d,%d,%d\n",DISPO_J[i],DISPO_J[i+1],DISPO_J[i+2],DISPO_J[i+3]);//on ecrit dans le fichier les valeurs du tableau que nous avons modofié ou non 
	}
	
	fclose(f);

	return(0);
}
