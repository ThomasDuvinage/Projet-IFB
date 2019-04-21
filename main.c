//
//  main.c
//  PROJECT
//
//  Created by Thomas Duvinage on 18/04/2019.
//  Copyright © 2019 Thomas Duvinage. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define true 1
#define false 0

char nom_pswd[10][45]= {"thomas","coucou","enzo","sacha"};
int nb_employe = 4;


//DECLARATIONS DES FONCTIONS
bool identification(char nom_pswd[10][45],int nb_employe);//on declare la fonction


// ****** MAIN ******
int main(int argc, const char * argv[]) {
    // insert code here...
    //printf("%lu",strlen(nom_pswd));
    
    if(identification(nom_pswd, nb_employe) == true){
        printf("BIENVENUE SUR NOTRE PLATFORME \n");
    }
    
    return 0;
}


// ********  BOUCLE IDENTIFICATION  **********

bool identification(char nom_pswd[10][45],int nb_employe){
    
    int i; //curseur pour la verification lors de l'autentification
    bool check = false; //on definit check comme false comme ca la boucle d'identification va se mettre en marche tant que la personne n'a pas donnee les bon identifiant et mot de passe
    
    //dans un premier temps nous demandons le nom et le mot de passe de la personne
    char nom_entre[10];//chaine de caractere qui correspond au nom de l'utilisateur
    char psw_entre[10];//chaine de caractere qui correpond au password de l'utilisateur
    
    
    do {
        //on fait l'affichage pour la connexion
        printf(" ==== IDENTIFICATION ==== \n");
        
        printf("NOM : ");
        //on remplie nom avec la chaine de caractere que l'utilisateur vient de rentrer
        scanf("%s",nom_entre);
        
        //printf("%s",nom_entre);
        
        printf("PASSWORD : ");
        //on remplie psw avec la chaine de caractere que l'utilisateur vient de rentrer
        getchar();//on est oblige de faire un getchar cela nous permet de mettre a jour l'adresse de la memoire
        scanf(" %s",psw_entre);
        
        
        //printf("%s", psw_entre);
        
        for(i = 0;i< nb_employe;i++){
            
            //printf("%d ",strcmp(nom_entre,nom_pswd[i])); //aide pour le debug
            //printf("%d \n",strcmp(nom_entre,nom_pswd[i+1])); //aide pour le debug
            if(strcmp(nom_entre,nom_pswd[i])==0 && strcmp(psw_entre, nom_pswd[i+1])==0){
                check = true;
            }
            i++;
        }
    }while (check != true);
    
    
    return true;
}

// ****** FIN DE LA BOUCLE IDENTIFICATION ******
