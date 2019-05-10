#include "agents_modif.h"
#include "../buffer.h"

int karma[20] = {0,10,3,4,8,9,2,7};
int temps_travail[20] = {0,10,3,4,8,9,2,7};

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

    }

    int i,j,c;
    for(i=0;i<nombre_agent-1;i++){
        for(j=i+1;j<nombre_agent;j++){
            if ( karma[i] > karma[j] ) {
                c = karma[i];
                karma[i] = karma[j];
                karma[j] = c;
            }
        }
        for(int p = 0; p < nombre_agent; p++){
            printf("%d    ",karma[p]);
            printf("%d \n",agents_karma[p]);
        }

        printf("k = %d\n",i);
        printf("\n");  
    }
    
}