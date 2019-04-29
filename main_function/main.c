//
//  main.c
//  PROJECT
//
//  Created by Thomas Duvinage on 18/04/2019.
//  Copyright © 2019 Thomas Duvinage. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define true 1
#define false 0

#define BSIZE 80
char nom_pswd[20][45];


//DECLARATIONS DES FONCTIONS
bool identification(char nom_pswd[20][45]);//on declare la fonction
void lecture_identifiant(char nom_pswd[20][45],int* nb_employe);



// ****** MAIN ******
int main(int argc, const char * argv[]) {
    // insert code here...
    //printf("%lu",strlen(nom_pswd));
    
    if(identification(nom_pswd) == true){
        printf("BIENVENUE SUR NOTRE PLATFORME \n");
    }
    
    return 0;
}


// ********  BOUCLE IDENTIFICATION  **********

bool identification(char nom_pswd[20][45]){
    
    int i; //curseur pour la verification lors de l'autentification
    bool check = false; //on definit check comme false comme ca la boucle d'identification va se mettre en marche tant que la personne n'a pas donnee les bon identifiant et mot de passe
    char ask_retry = 'r';//on definit le retry comme au debut cela permet de rentrer dans la fonction 

    //dans un premier temps nous demandons le nom et le mot de passe de la personne
    char nom_entre[10];//chaine de caractere qui correspond au nom de l'utilisateur
    char psw_entre[10];//chaine de caractere qui correpond au password de l'utilisateur
    
    int nb_employe = 0;

    int create_info = 0;//cette variable permet de savoir si la personne a creer un compte dans ce cas on lui demande directement de s'identifier
    
    lecture_identifiant(nom_pswd,&nb_employe);

    do {
        if(ask_retry == 'r'){
            //on fait l'affichage pour la connexion
            printf(" ==== IDENTIFICATION ==== \n");
            
            printf("NOM : ");
            //on remplie nom avec la chaine de caractere que l'utilisateur vient de rentrer
            scanf("%s",nom_entre);
            
            printf("%d \n",strcmp(nom_entre,nom_pswd[0]));
            printf("%s \n",nom_entre);
            
            printf("PASSWORD : ");
            //on remplie psw avec la chaine de caractere que l'utilisateur vient de rentrer
            getchar();//on est oblige de faire un getchar cela nous permet de mettre a jour l'adresse de la memoire
            scanf(" %s",psw_entre);

            
            
            printf("%d \n",strcmp(psw_entre,nom_pswd[1]));
            printf("%s \n", psw_entre);
            
            for(i = 0;i< nb_employe;i=i+2){
                
                printf("%d ",strcmp(nom_entre,nom_pswd[i])); //aide pour le debug
                printf("%d \n",strcmp(nom_entre,nom_pswd[i+1])); //aide pour le debug
                printf("%s %s \n",nom_pswd[i],nom_pswd[i+1]);
                if(strcmp(nom_entre,nom_pswd[i])==0 && strcmp(psw_entre, nom_pswd[i+1])==0){
                    check = true;
                }
            }
        }

        else
        {
            char nom[20];
            char pwd[20];
            int create_info = 0;

            printf("==== CREATION DE COMPTE ==== \n");
            printf("Nom = ");
            getchar();
            scanf(" %s",nom);

            printf("\nMot de passe = ");
            getchar();
            scanf(" %s",pwd);
            printf("\n");

            create_info = 1;
            nb_employe = nb_employe + 2;
        }
        
        if (check == false && create_info == 0)
        {
            do
            {
                printf("Si vous voulez reesayer appuyer sur r et si vous souhaitez creer un compte appuyé sur c \n");
                scanf(" %c",&ask_retry);
            } while (ask_retry != 'r' && ask_retry != 'c');
        }
        
    }while (check != true);
    
    
    return true;
}

// ****** FIN DE LA BOUCLE IDENTIFICATION ******


// ******* DEBUT FONCTION DE LECTURE FICHIER *********
void lecture_identifiant(char nom_pswd[20][45], int* nb_employe){
    char buffer[BSIZE];
	FILE *f;
	char *field;
	char nom[20],pwd[20];


	int i = 0; //curseur permettant de remplir le tableau des dispos_j

	/* open the CSV file */
	f = fopen("identifiants.csv","r");

	if( f == NULL)//si on arrive pas a ouvrir on affiche un message 
	{
		printf("Impossible d'ouvrir le fichier identifiants.csv \n ");
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
		strcpy(nom_pswd[i],nom);
		strcpy(nom_pswd[i+1],pwd);

		i=i+2;//on incremente le cursueur 

	}

    *nb_employe = i;
	/* close file */
	fclose(f);//femeture de la lecture du fichier
}

