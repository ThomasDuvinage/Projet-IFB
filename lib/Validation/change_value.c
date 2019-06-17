#include "validation.h"
#include "../buffer.h"

char path_to_csv[50] = "csv_files/etage_";

int change_value(int value,int etage,int numero_salle,char jour[10],int heure,int minute){
/* open the CSV file */
    char path_to_csv[50] = "csv_files/etage_";//cette variable est declarer en extren dans le fichier buffer.h

    char buffer[BSIZE];
    FILE *f;
    char *field;
    int DISPO0 = 0,DISPO15 = 0,DISPO30 = 0,DISPO45 = 0;

    int DISPO_J[40]; //tableau qui permet d'acceuillir toutes les valeurs que nous lisons du fichier
    //cela permet de pouvoir modifier le tableau puis de le l'ecrire par la suite dans le fichier

    //int n = 8;//curseur permettant d'afficher l'heure dans l'affichage
    int i = 0; //curseur permettant de remplir le tableau des dispos_j
    int ligne = 0;
 
    char nb_salle[12]; // on creer une chaine de caracteres qui va permettre de recevoir le numero de la salle en caracteres
    char numero_etage[5] = "";
    sprintf(numero_etage, "%d",etage);//on convertit l'entier numero salle en char dans la chaine de caracteres nb_salle
    strcat(path_to_csv,&numero_etage[0]);
    strcat(path_to_csv,"/");
    //printf("etage %s\n",numero_etage);
    strcat(path_to_csv,jour);
    strcat(path_to_csv,"/");
    strcat(path_to_csv,"p");

    sprintf(nb_salle, "%d", numero_salle);//on convertit l'entier numero salle en char dans la chaine de caracteres nb_salle
    strcat(path_to_csv,nb_salle); //on concatene les deux chaines de caracteres
    strcat(path_to_csv,".csv"); //on ajoute la description du fichier

	f = fopen(path_to_csv,"r");

	//puts(path_to_csv);

	if( f == NULL)//si on arrive pas a ouvrir on affiche un message 
	{
		printf("Impossible d'ouvrir le fichier dans change value'%s'\n",chemin_fichier);
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

    int index = ((heure-8)*4)+(minute/15);

	DISPO_J[index] = value;

    //on passe en mode ecriture de fichier, cela permet de remplacer les valeurs dans le tableau et apres de les inseres dans le fichier
	f = fopen(path_to_csv,"w");

	//on fait une boucle pour remplir le fichier 
	for(int i = 0; i < 40; i=i+4)//40 correspond au nombre de valeur car on fait de 8h a 18h donc 4*10 valeurs 
	{
		fprintf(f, "%d,%d,%d,%d\n",DISPO_J[i],DISPO_J[i+1],DISPO_J[i+2],DISPO_J[i+3]);//on ecrit dans le fichier les valeurs du tableau que nous avons modofié ou non 
	}
	
	fclose(f);

	return(0);
}