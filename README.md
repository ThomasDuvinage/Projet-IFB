# Projet-IFB

Ce projet est universitaire .

Notre projet consiste en une application qui va aider les agents de ménages dans l’organisation des taches. Celle-ci va permettre d’optimiser le nettoyage des salles en générant un planning de nettoyage chaque jour en fonction de l’occupation des salles pour chaque agent de ménage.
Par exemple l’agent de ménage rentre son identifiant et on lui génère la liste des salles qu'il doit nettoyer avec les horaires. Cela va non seulement optimiser le nettoyage mais aussi diminuer le temps de travail.


## Pour compiler: 
Pour compiler ce projet en ligne de commande vous devez taper :

** gcc -g main.c identification.c ... -o projet.app **

Les (...) correspondent à tous les autres fichiers .c de votre projet que vous avez besoins pour que le projet main.c fonctionne. 

Très important pour faire cela vous devez faire en sorte que le .h soit lu qu'une seule fois donc vous devez ajouter : (exemple avec identification.h)

````
///Tout en haut de votre .h
#ifndef IDENTIFICATION_H_INCLUDE
#define IDENTIFICATION_H_INCLUDE

....

#endif ///a la fin de votre .h

````

## IMPORTANT

- Sur Linux et MacOS : gcc -g ... -o projet.app

- Sur Windows : gcc -g ... -o projet.exe


