#include "validation.h"
#include "../generate_timetable/generation_timetable.h"
#include "../recherche_salle/recherche_salle.h"
#include "../buffer.h"

char chemin_fichier[50] = "csv_files/etage_";//aller voir buffer.h pour la declaration de la variable
int numero_salle,etage;// declaration des variables

int validation(){
    char buffer[BSIZE];
    FILE *f;
    char *field;
    int DISPO0,DISPO15,DISPO30,DISPO45;//variables correspondant a la dispo pour chaque 1/4 H

    int DISPO_J[40]={0};//tableau qui permet d'acceuillir toutes les valeurs que nous lisons du fichier
    //cela permet de pouvoir modifier le tableau puis de le l'ecrire par la suite dans le fichier

    int n = 8;//curseur permettant d'afficher l'heure dans l'affichage
    int i = 0; //curseur permettant de remplir le tableau des dispos_j

    char rep;
    do{
    printf("Avez vous nettoyez la salle? (y/n) \n"); //on demande à l'agent si il a realisé une action
    scanf(" %c",&rep);
    }while(rep != 'y' && rep !='n' );

    if (rep == 'n')
    {
        printf("Aucune salle est nettoyée \n");
        generate();
    }
    else  // si oui on recupere jour,l'heure, minutes
    {

        int numero_salle = 0, etage = 0;
        printf("Quelle salle voulez-vous valider ? \n");
        scanf("%d",&numero_salle);

        //les deux lignes qui suivent devront etre suprimer afin que la personne donne juste la salle et on calcul l'etage
        printf("A quel étage etes vous ?\n");
        scanf("%d",&etage);

        time_t secondes;
        struct tm instant;
        time(&secondes);
        instant = *localtime(&secondes);

        
        time_t temps;
        struct tm date;
        char jour[30];
        time(&temps);
        date=*localtime(&temps);

        // On remplit la chaîne avec le format choisi, puis on l'affiche.
        strftime(jour, 30, "%A", &date); 
        int heure = instant.tm_hour;
        int minute = instant.tm_min;

        if (recherche_salle(etage,numero_salle,jour,heure,minute) == 0) //on vérifie que la salle était a faire
        {
            if (minute>45)   // dans cette étape on attribue au minute pas fixe (autre que 0,15,30,45) le quart d'heure d'après
            {
                minute=60;
            }
            else if (45>=minute && minute>30)
            {
                minute=45;
            }
            else if (30>=minute && minute>15)
            {
                minute=30;
            }
            else if (15>=minute && minute>0)
            {
                minute=15;
            }
        }
        else if (recherche_salle(etage,numero_salle,jour,heure,minute) == 3)
        {
            printf("La salle n'etait pas a faire\n");
        }

        change_value(2,etage,numero_salle,jour,heure,minute);
    }

 return(0);
}

