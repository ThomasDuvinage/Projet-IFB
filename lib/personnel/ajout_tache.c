#include "agents_modif.h"

/**
 * @brief Cette fonction permet d'ajouter des taches à l'agent 
 * 
 */
void ajout_tache(int numero_agent,int salle){
    char chemin_agent[50] = "csv_files/agents/";//cette variable est declarer en extren dans le fichier buffer.h

    char buffer[BSIZE];
    FILE *f;
    char *field;

    char numero_agent_char[5];
    sprintf(numero_agent_char, "%d",numero_agent);//on convertit l'entier numero salle en char dans la chaine de caracteres nb_salle
    strcat(chemin_agent,numero_agent_char);
    strcat(chemin_agent,".csv"); //on ajoute la description du fichier
    //printf("%s\n",nom_salle);

    if ((minute == 0 || minute == 15 || minute == 30 || minute == 45) && (etage>=1 && etage<=3) && (heure>=8 && heure<=18)){
        /* open the CSV file */
        f = fopen(chemin_agent,"r");

        if( f == NULL)//si on arrive pas a ouvrir on affiche un message
        {
            printf("Impossible d'ouvrir le fichier '%s'\n",nom_salle);
            //exit(1);
        }
		else{
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
    
}