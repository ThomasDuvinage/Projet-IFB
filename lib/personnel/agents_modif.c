#include "agents_modif.h"
#include "../buffer.h"

int karma[20] = {0};
int temps_travail[20] = {0};

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


    for(int i = 0; i<nombre_agent ; i++){
        agents_karma[i] = i;
        agents_travail[i] = i;

        printf("%d  ",agents_karma[i]);
        printf("%d  \n",agents_travail[i]);

    }
    printf("\n");

    //boucle de tri poir les karmas
    for(int k = 0; k < nombre_agent; k++){
        minimum_karma = karma[k];
        index_min = k;
        for(int n=k+1; n < nombre_agent;n++){
            if(minimum_karma > karma[n]){
                index_min = n;
            }
            agents_karma[k] = index_min;
        }

        for(int o = index_min; o<(nombre_agent-k);o++){
            karma[o] = karma[o+1];
        }
    }

    //boucle de tri pour les temps de travail
    for(int k = 0; k < nombre_agent; k++){
        minimum_travail = temps_travail[k];
        index_min = k;
        for(int n=k+1; n < nombre_agent;n++){
            if(minimum_travail> temps_travail[n]){
                index_min = n;
            }
            agents_travail[k] = index_min;
        }

        for(int o = index_min; o<(nombre_agent-k);o++){
            temps_travail[o] = temps_travail[o+1];
        }
    }

    for(int p = 0; p < nombre_agent; p++){
        printf("%d  ",agents_karma[p]);
        printf("%d  \n",agents_travail[p]);
    }
    
}