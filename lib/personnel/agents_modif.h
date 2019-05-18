#ifndef AGENTS_MODIF_H_INCLUDE
#define AGENTS_MODIF_H_INCLUDE

extern int karma[20];
extern int temps_travail[20];

int agents_karma[20];
int agents_travail[20];

extern int index_agent_temps_travail;

int choix_agent();

void ajout_tache(int numero_agent,char jour[8],int salle,int etage, int heure, int minute);


#endif