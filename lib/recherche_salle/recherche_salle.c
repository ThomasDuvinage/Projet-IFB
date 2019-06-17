#include "recherche_salle.h"
#include "../buffer.h"

char nom_salle[50] = "csv_files/etage_";//cette variable est declarer en extren dans le fichier buffer.h

int recherche_salle(int etage,int numero_salle,char jour[],int heure,int minute){//les minutes --> 0, 15, 30, 45
    char nom_salle[50] = "csv_files/etage_";//cette variable est declarer en extren dans le fichier buffer.h

    char buffer[BSIZE];
    FILE *f;
    char *field;
    int DISPO0 = 0,DISPO15 = 0,DISPO30 = 0,DISPO45 = 0, index = 0;

    int DISPO_J[40]; //tableau qui permet d'acceuillir toutes les valeurs que nous lisons du fichier
    //cela permet de pouvoir modifier le tableau puis de le l'ecrire par la suite dans le fichier

    //int n = 8;//curseur permettant d'afficher l'heure dans l'affichage
    int i = 0; //curseur permettant de remplir le tableau des dispos_j
    int ligne = 0;
 
    char nb_salle[12]; // on creer une chaine de caracteres qui va permettre de recevoir le numero de la salle en caracteres
    char numero_etage[5] = "";
    sprintf(numero_etage, "%d",etage);//on convertit l'entier numero salle en char dans la chaine de caracteres nb_salle
    strcat(nom_salle,&numero_etage[0]);
    strcat(nom_salle,"/");
    //printf("jour = %s\n",jour);
    strcat(nom_salle,jour);
    strcat(nom_salle,"/");
    strcat(nom_salle,"p");

    sprintf(nb_salle, "%d", numero_salle);//on convertit l'entier numero salle en char dans la chaine de caracteres nb_salle
    strcat(nom_salle,nb_salle); //on concatene les deux chaines de caracteres
    strcat(nom_salle,".csv"); //on ajoute la description du fichier
    //printf("salle = %s\n",nom_salle);

    int etat_return;//cette variable permet de retourner l'etat de la salle ou -1 si les parametres ne sont pas bon

    if ((minute == 0 || minute == 15 || minute == 30 || minute == 45) && (etage>=1 && etage<=3) && (heure>=8 && heure<=18)){
        /* open the CSV file */
        f = fopen(nom_salle,"r");

        if( f == NULL)//si on arrive pas a ouvrir on affiche un message
        {
            printf("Impossible d'ouvrir le fichier '%s'\n",nom_salle);
            //exit(1);
        }
		else{
			while(fgets(buffer,BSIZE,f) && ligne!=12)
			{
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

                ligne++;
            }

        }

            /* close file */
            fclose(f);//femeture de la lecture du fichier


            int index = ((heure-8)*4)+(minute/15);

        	//printf("%d \n",index);
            //printf("%d \n",DISPO_J[index]);
			etat_return = DISPO_J[index];

	}
	else
	{
		etat_return = -1;
	}
	
    return(etat_return);
}