#include "validation.h"
#include "../buffer.h"

char chemin_fichier[50] = "csv_files/etage_";//aller voir buffer.h pour la declaration de la variable
int numero_salle,etage;// declaration des variables 
char nom_agent[20];

int validation(int agent,int etage,int numero_salle,char jour[10],int heure,int minute){
	generation_chemin();//on appelle la fonction de generation de chemin voir plus bas dans le code 

	char buffer[BSIZE];
	FILE *f;
	char *field;
	int DISPO0,DISPO15,DISPO30,DISPO45;//variables correspondant a la dispo pour chaque 1/4 H

	int DISPO_J[40]={0};//tableau qui permet d'acceuillir toutes les valeurs que nous lisons du fichier 
	//cela permet de pouvoir modifier le tableau puis de le l'ecrire par la suite dans le fichier

    int n = 8;//curseur permettant d'afficher l'heure dans l'affichage
	int i = 0; //curseur permettant de remplir le tableau des dispos_j

	

	/* open the CSV file */
	f = fopen(chemin_fichier,"r");

	if( f == NULL)//si on arrive pas a ouvrir on affiche un message 
	{
		printf("Impossible d'ouvrir le fichier '%s'\n",chemin_fichier);
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


	int index_agent;

	for(int i = 0; i<nombre_agent; i+=2){
		if(namePassBuffer[i] != nom_agent){
			index_agent+=2;
		}
	}

	char chemin_agent[50] = "csv_files/agents/";//cette variable est declarer en extren dans le fichier buffer.h

    FILE *fichier_agent;
	char buffer_agent[BSIZE];
	char* field_agent;

    char numero_agent_char[5] = "";
    sprintf(numero_agent_char, "%d",index_agent);//on convertit l'entier numero salle en char dans la chaine de caracteres nb_salle
    strcat(chemin_agent,numero_agent_char);
	strcat(chemin_agent,"_");
	strcat(chemin_agent,namePassBuffer[index_agent]);//nous multiplions par 2 afin de selectionner uniquement les noms des agents 
    strcat(chemin_agent,".csv"); //on ajoute la description du fichier
    printf("%s\n",chemin_agent);

	fichier_agent = fopen(chemin_agent,"r");

	if(fichier_agent == NULL){
		printf("Nous ne pouvons pas ouvrir le fichier pour verifier les taches de l'agent\n");
	}
	while (fgets())
	{
		
	}

	

	//TODO il faut remplacer à cette endroit les valeurs du tableau afin de les remettre dans le fichier 
	int index = ((heure-8)*4)+(minute/15);

	DISPO_J[index] = 2;

	//on passe en mode ecriture de fichier, cela permet de remplacer les valeurs dans le tableau et apres de les inseres dans le fichier
	f = fopen(chemin_fichier,"w");

	//on fait une boucle pour remplir le fichier 
	for(int i = 0; i < 40; i=i+4)//40 correspond au nombre de valeur car on fait de 8h a 18h donc 4*10 valeurs 
	{
		fprintf(f, "%d,%d,%d,%d\n",DISPO_J[i],DISPO_J[i+1],DISPO_J[i+2],DISPO_J[i+3]);//on ecrit dans le fichier les valeurs du tableau que nous avons modofié ou non 
	}
	
	fclose(f);

	return(0);
}


void generation_chemin(){// voir le fichier validation.h pour les explications de la fonction
	char chemin_fichier[50] = "csv_files/etage_";
	char nb_salle[12]; // on creer une chaine de caracteres qui va permettre de recevoir le numero de la salle en caracteres
    char numero_etage[5];// permet d'acceuilir la convertion de int vers char de numero etage 
	
    // ****************** Utilisation du temps (voir time_example)
	char jour[128];//declaration de la chaine de caractere qui permet d'acceuillir le jour (Monday,..)  
    time_t temps;
    struct tm date;

    // On récupère la date et l'heure actuelles.
    time(&temps);
    date=*localtime(&temps);

    // On remplit la chaîne avec le format choisi, puis on l'affiche.
    strftime(jour, 128, "%A", &date);//le %A permet d'avoir le jour sous le format Monday,...
	//*******************

	printf("Quelle salle voulez-vous valider ? \n");
	scanf("%d",&numero_salle);

	//les deux lignes qui suivent devront etre suprimer afin que la personne donne juste la salle et on calcul l'etage 
	printf("A quel étage etes vous ?\n");
	scanf("%d",&etage);

	sprintf(numero_etage, "%d",etage);//on convertit l'entier numero salle en char dans la chaine de caracteres nb_salle
    strcat(chemin_fichier,numero_etage );
    strcat(chemin_fichier,"/");
    strcat(chemin_fichier,jour);
    strcat(chemin_fichier,"/");
    strcat(chemin_fichier,"p");

    sprintf(nb_salle, "%d", numero_salle);//on convertit l'entier numero salle en char dans la chaine de caracteres nb_salle
    strcat(chemin_fichier,nb_salle); //on concatene les deux chaines de caracteres
    strcat(chemin_fichier,".csv"); //on ajoute la description du fichier

}