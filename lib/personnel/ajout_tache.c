#include "agents_modif.h"
#include "../buffer.h"

/**
 * @brief Cette fonction permet d'ajouter des taches à l'agent 
 * 
 */
void ajout_tache(int numero_agent,char jour[8],int salle, int etage, int heure, int minute){
    char chemin_agent[50] = "csv_files/agents/";//cette variable est declarer en extren dans le fichier buffer.h

    FILE *f;

    char numero_agent_char[5] = "";
	
    sprintf(numero_agent_char, "%d",numero_agent);//on convertit l'entier numero salle en char dans la chaine de caracteres nb_salle
    strcat(chemin_agent,numero_agent_char);
	strcat(chemin_agent,"_");
	strcat(chemin_agent,namePassBuffer[numero_agent*2]);//nous multiplions par 2 afin de selectionner uniquement les noms des agents 
    strcat(chemin_agent,".csv"); //on ajoute la description du fichier
    printf("%s\n",chemin_agent);

    if ((minute == 0 || minute == 15 || minute == 30 || minute == 45) && (etage>=1 && etage<=3) && (heure>=8 && heure<=18)){
        /* open the CSV file */
        f = fopen(chemin_agent,"a");

        if( f == NULL)//si on arrive pas a ouvrir on affiche un message
        {
            printf("Impossible d'ouvrir le fichier '%s'\n",chemin_agent);
            //exit(1);
        }
		else{
				printf("Karma avant : %d",karma[numero_agent]);
				if(heure < 9 || heure > 17){
					karma[numero_agent] += 2;
				}
				else if ((heure > 11 && heure < 14))
				{
					karma[numero_agent] +=1;
				}

				printf("   Apres : %d\n",karma[numero_agent]);
				
				temps_travail[index_agent_temps_travail] += 15;

				fprintf(f,"Jour :%s Heure :%dh Minutes :%dmin Salle :%d Etage %d",jour,heure,minute,salle,etage);
            }
        /* close file */
        fclose(f);//femeture de la lecture du fichier

	}

}