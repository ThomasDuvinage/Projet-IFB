#include "agents_modif.h"
#include "../buffer.h"

int karma[20] = {0,1,3,4,8,9,2,7};
int temps_travail[20] = {7,19,3,4,88,9,2,7};

/**
 * @brief Cette fonciton va permettre de retourner l'index de l'agent qui a le plus petit karma
 * 
 * @param numero_agent 
 */
void choix_agent(){
    //agent karma correspond au index des agents apres le tri 
    int minimum_karma = karma[0] , index_min;
    int minimum_travail = temps_travail[0];
    int value_to_return;

    int agents_karma[20] = {0};
    int agents_travail[20] = {0};

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

    for(int n = 0; n < nombre_agent; n++){
        sum = 0;
        for(int i = 0; i < nombre_agent;i++){
        
            if (agents_karma[n] != agents_travail[i])
            {
                sum++;
            }

            if(agents_karma[n] == agents_travail[i])
            {
                i = nombre_agent;
            }

        }
        printf("%d\n",sum);
        score[n] = sum;
    }

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
    printf("\n");
    for(int p = 0; p < nombre_agent; p++){
        printf("score = %d    ",score[p]);
        printf("agent = %d    ",agents_karma[p]);
            
        printf("%d\n",p);
    }
    
}