#include "identification.h"
#include "../Validation/validation.h"
#include "../generate_timetable/generation_timetable.h"
#include "../buffer.h"

/**
 * @brief Cette chaine de caractere permet d'acceuilir les ID et PWD de tous les agents. Nous ne la mettons pas en parametres des fonctions car nous l'avons declarer comme extern dans buffer.h
 * 
 */
char namePassBuffer[45][20];
int nombre_agent;//cette variable est utilisée dans la fonction de lecture agent et de ajout_tache
char nom_agent[20];
// ********  BOUCLE IDENTIFICATION  **********
bool identification(){
    int i; //curseur pour la verification lors de l'autentification
    bool check = false; //on definit check comme false comme ca la boucle d'identification va se mettre en marche tant que la personne n'a pas donnee les bon identifiant et mot de passe
    char ask_retry = 'r';//on definit le retry comme au debut cela permet de rentrer dans la fonction 

    int nb_employe = 0;

    int create_info = 0;//cette variable permet de savoir si la personne a creer un compte dans ce cas on lui demande directement de s'identifier
    
    do {
        if(ask_retry == 'r'){

            lecture_identifiant(&nb_employe);//dans cette fonction nous remplissons le tableau nom_pswd de tous les ID et PWD puis nous mettons a jour la valeur du nombre d'emploie a l'aide des pointeurs

            //on fait l'affichage pour la connexion
            printf(" ==== IDENTIFICATION ==== \n");

            //dans un premier temps nous demandons le nom et le mot de passe de la personne
            char nom_entre[20];//chaine de caractere qui correspond au nom de l'utilisateur
            char psw_entre[20];//chaine de caractere qui correpond au password de l'utilisateur
            
            printf("NOM : ");
            //on remplie nom avec la chaine de caractere que l'utilisateur vient de rentrer
            scanf(" %s",nom_entre);
            strcpy(nom_agent,nom_entre);
            
            //printf("%d \n",strncmp(nom_entre,nom_pswd[0],strlen(nom_entre)));
            //printf("%s \n",nom_entre);
            
            printf("PASSWORD : ");
            //on remplie psw avec la chaine de caractere que l'utilisateur vient de rentrer
            getchar();//on est oblige de faire un getchar cela nous permet de mettre a jour l'adresse de la memoire
            scanf(" %s",psw_entre);
        
            //printf("%d \n",strncmp(psw_entre,nom_pswd[1],strlen(psw_entre)));
            //printf("%s \n", psw_entre);
            
            for(i = 0;i< nb_employe;i=i+2){
                //printf("%d ",strncmp(nom_entre,nom_pswd[i],strlen(nom_entre))); //aide pour le debug
                //printf("%d \n",strncmp(psw_entre,nom_pswd[i+1],strlen(psw_entre))); //aide pour le debug
                //printf("%s %s \n",nom_pswd[i],nom_pswd[i+1]);

                //strncmp permet de comparer pour un certain nombre de caractere soit la longueur du nom ou du pwd donné 
                if(strncmp(nom_entre, namePassBuffer[i],strlen(nom_entre))==0 && strncmp(psw_entre, namePassBuffer[i+1],strlen(psw_entre))==0){
                    check = true;
                }
            }

            if(create_info == 1){
                reinitialisation();
                generate();
            }
            
            create_info = 0;
        }

        if(ask_retry == 'c' && create_info == 0)
        {
            creation_agent(&nb_employe);
            create_info = 1;
            ask_retry = 'r';

        }
        
        if (check == false && create_info == 0)
        {
            do
            {
                printf("Si vous voulez reesayer appuyer sur r et si vous souhaitez creer un compte appuyé sur c \n");
                scanf(" %c",&ask_retry);
            } while (ask_retry != 'r' && ask_retry != 'c');
            system("clear");
        }
        
    }while (check != true);

    
    
    return true;
}

// ****** FIN DE LA BOUCLE IDENTIFICATION ******

// ******* DEBUT FONCTION DE LECTURE FICHIER *********
void lecture_identifiant(int* nb_employe){
    char buffer[BSIZE];
	FILE *f;
	char *field;
	char nom[20],pwd[20];

    nombre_agent = 0;

	int i = 0; //curseur permettant de remplir le tableau des dispos_j

	/* open the CSV file */
	f = fopen("csv_files/ID.csv","r");

	if( f == NULL)//si on arrive pas a ouvrir on affiche un message 
	{
		printf("Impossible d'ouvrir le fichier ID.csv \n");
		exit(1);
	}

	while(fgets(buffer,BSIZE,f))
	{
		field=strtok(buffer,",");//on separe le fichier en chaine de caractere entre chaque (,) 
		strcpy(nom,field);//on associe a la variable la valeur en entier de la chaine de caractere de la valeur lue precedement --> fonction atoi()
        //printf("%s \n",nom);

		field=strtok(NULL,",");
		strcpy(pwd,field);
        //printf("%s",pwd);

		//les 2 lignes suivantes permettent de remplir le tableau des valeurs lues
		strncpy(namePassBuffer[i],nom,strlen(nom));
		strncpy(namePassBuffer[i+1],pwd,strlen(pwd));

		i=i+2;//on incremente le cursueur 
        nombre_agent++;

	}

    *nb_employe = i;
	/* close file */
	fclose(f);//femeture de la lecture du fichier
}


//cette fonction me permet de creer un agent en l'ajoutant dans le fichier 
int creation_agent(int* nb_employe){
    FILE *f;
    char nom[20];
    char pwd[20];
    int create_info = 0;

    printf("==== CREATION DE COMPTE ==== \n");
    printf("Nom = ");
    scanf("%s",nom);

    printf("Mot de passe = ");
    scanf("%s",pwd);
    printf("\n");

    /**
     * @brief Construct a new strncpy object permet de coper pour un certain nombre de caracteres une chaine de caracteres dans une autre
     * 
     */
    strncpy(namePassBuffer[*nb_employe],nom,strlen(nom));
    strncpy(namePassBuffer[*nb_employe+1],pwd,strlen(pwd));
    //strcat(namePassBuffer[*nb_employe+1],"\n");

    //on passe en mode ecriture de fichier, cela permet de remplacer les valeurs dans le tableau et apres de les inseres dans le fichier
	f = fopen("csv_files/ID.csv","w");

	//on fait une boucle pour remplir le fichier 
	for(int i = 0; i < *nb_employe; i=i+2)
	{
		fprintf(f,"%s,%s", namePassBuffer[i], namePassBuffer[i+1]);//on ecrit dans le fichier les valeurs du tableau que nous avons modofié ou non 
    }

    fprintf(f,"\n%s,%s", namePassBuffer[*nb_employe], namePassBuffer[*nb_employe+1]);
	
	fclose(f);

    return 0;
}