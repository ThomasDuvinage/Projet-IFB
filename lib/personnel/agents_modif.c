#include "agents_modif.h"
#include "../buffer.h"

int karma[20] = {0};
int temps_travail[20] = {0};

int agents_karma[20] = {0};
int agents_travail[20] = {0};

int index_agent_temps_travail;

/**
 * @brief Cette fonciton va permettre de retourner l'index de l'agent qui a le plus petit karma
 * 
 * @param numero_agent 
 */
int choix_agent(){
    //agent karma correspond au index des agents apres le tri 
    int minimum_karma = karma[0] , index_min;
    int minimum_travail = temps_travail[0];
    int value_to_return;

    

    //on genere les tableaux pour les agents
    for(int i = 0; i<nombre_agent ; i++){
        agents_karma[i] = i;
        agents_travail[i] = i;

    }

    //on tri les karmas du plus petit au plus grand
    for(int i=0;i<nombre_agent-1;i++){
        for(int j=i+1;j<nombre_agent;j++){
            if ( karma[i] > karma[j] ) {
                int tampon_tri = karma[i];
                int tampon_agent = agents_karma[i];

                agents_karma[i] = agents_karma[j];
                karma[i] = karma[j];

                agents_karma[j] = tampon_agent;
                karma[j] = tampon_tri;
            }
        } 
    }

    //on tri les temps de travail du plus petit au plus grand 
    for(int i=0;i<nombre_agent-1;i++){
        for(int j=i+1;j<nombre_agent;j++){
            if ( temps_travail[i] > temps_travail[j] ) {
                int tampon_tri = temps_travail[i];
                int tampon_agent = agents_travail[i];

                agents_travail[i] = agents_travail[j];
                temps_travail[i] = temps_travail[j];

                agents_travail[j] = tampon_agent;
                temps_travail[j] = tampon_tri;
            }
        }
    }

    //permet d'afficher tous les parametres que nous avons trié
    for(int p = 0; p < nombre_agent; p++){
        printf("karma = %d    ",karma[p]);
        printf("agent = %d    ",agents_karma[p]);

        printf("travail = %d    ",temps_travail[p]);
        printf("agent   = %d    ",agents_travail[p]);
            
        printf("%d\n",p);
    }

    int score[20] = {0};//cette variable permet de stocker toutes les
    int sum;

    //nous trions les scores du plus petit au plus grand afin de determiner le bon agent 
    for(int n = 0; n < nombre_agent; n++){
        sum = 0;
        for(int i = 0; i < nombre_agent;i++){
        
            if(agents_karma[n] == agents_travail[i] )
            { 
                sum = karma[n] + temps_travail[i];
                i = nombre_agent;
            }

        }
        score[n] = sum;
    }
    //comme nous lisons le tableau agent karma suivant n, ce tableau nous sert de reference pour les scores en therme d'indice 

    //pour la boucle qui suit nous reutilisons le tableau de agent_karma afin de faire ne pas recreer un tableau 
    //on tri les karmas du plus petit au plus grand
    for(int i=0;i<nombre_agent-1;i++){
        for(int j=i+1;j<nombre_agent;j++){
            if ( score[i] > score[j] ) {
                int tampon_tri = score[i];
                int tampon_agent = agents_karma[i];

                agents_karma[i] = agents_karma[j];
                score[i] = score[j];

                agents_karma[j] = tampon_agent;
                score[j] = tampon_tri;
            }
        } 
    }

    //permet d'afficher tous les parametres que nous avons trié
    // printf("\n");
    // for(int p = 0; p < nombre_agent; p++){
    //     printf("score = %d    ",score[p]);
    //     printf("agent = %d    ",agents_karma[p]);
            
    //     printf("%d\n",p);
    // }
    //le premier indice de du tableau agent_karma permet de connaitre l'agent qui doit faire la tache car il possedre le plus petit karma et le plus petit temps de travail.
    //seulement si plusieurs personne on le meme score alors nous devons choisir de maniere aleatoire afin que ce ne soit pas tout le temps la meme personne qui se retrouve choisi

    int repetition = 0;
    for(int i = 0;i<nombre_agent;i++){
        if(score[0] == score[i])
        {
            repetition++;
        }
        else
        {
            i = nombre_agent;
        }
        
    }

    srand(time(0));
    int choix_personnel;
    if(repetition != 0){
        choix_personnel = agents_karma[rand()%(repetition-1)];
    }
    else{
        choix_personnel = agents_karma[0];
    }

    //la boucle qui suit permet de savoir la position de l'agent dans le tableau des temps de travail afin d'ajouter le temps de travail dans la bonne case du tableau
    index_agent_temps_travail = 0;
    for(int i = 0;i < nombre_agent;i++){
        if(choix_personnel != agents_travail[i]){
            index_agent_temps_travail++;
        }
        else
        {
            i = nombre_agent;
        }
        
    }

    printf("index travail : %d\n",index_agent_temps_travail);
    //printf("CHOIX = %d\n",choix_personnel);

    return choix_personnel;
}