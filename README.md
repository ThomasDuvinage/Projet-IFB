# Projet-IFB

Ce projet est universitaire .

Notre projet consiste en une application qui va aider les agents de ménages dans l’organisation des taches. Celle-ci va permettre d’optimiser le nettoyage des salles en générant un planning de nettoyage chaque jour en fonction de l’occupation des salles pour chaque agent de ménage.
Par exemple l’agent de ménage rentre son identifiant et on lui génère la liste des salles qu'il doit nettoyer avec les horaires. Cela va non seulement optimiser le nettoyage mais aussi diminuer le temps de travail.

## Les fonctions : 
- Identification de l’agent :
    Dans un premier temps nous demandons à la personne son nom et son mot de passe. 

    Si la personne rentre les paramètres correspondant alors elle peut rentrer sur la plateforme dans le cas contraire on lui demande si elle veut réessayer ou si elle veut créer un compte. Si elle appuie sur « r » alors on lui redemande de rentrer son identifiant et son mot de passe. Dans le cas contraire si elle appuie sur « c » alors on lui demande un identifiant et un mot de passe qui lui permettront de se connecter. Ainsi ses nouveaux paramètres sont ajoutés sur le fichier des identifiants et on lui demande de se reconnecter pour qu’il accède à la plateforme.
    Cette fonction se nomme identification or elle ne peut fonctionner en autonomie, elle fait appel à la fonction création_agent et à la fonction de lecture_identifiant. La fonction de création d’agent permet de créer un agent dans le fichier des agents pour ensuite lui générer un emploi du temps. Pour la fonciton de lecture d’identifiants elle sert à lire tous les identifiants dans le fichier des identifiants et ensuite de remplir un tableau qui nous permet de stocker tous les agents lors de la génération ou même de l’identification.

    Pour appeler cette fonction, nous faisons : 
    
    ````
    bool identification();

    ````
    En sortie de la fonction identification nous avons un booléen celui-ci permet dans le main.c de mettre une condition qui permet de définir l’entrée dans la plate-forme.



## Pour compiler: 
Pour compiler ce projet en ligne de commande vous devez taper :

#### gcc -g src/main.c lib/identification/identification.c lib/personnel/agents_modif.c lib/personnel/ajout_tache.c lib/recherche_salle/recherche_salle.c lib/generate_timetable/generate_timetable.c lib/Validation/validation.c lib/Validation/change_value.c lib/Validation/reinitialisation.c  -o projet.app

Les (...) correspondent à tous les autres fichiers .c de votre projet dont vous avez besoin pour que le projet main.c fonctionne. 

Très important pour faire cela vous devez faire en sorte que le .h ne soit lu qu'une seule fois donc vous devez ajouter : (exemple avec identification.h)

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


## Doxygen

J'ai decouvert cette extension grace à Jules Topart :)

Celle-ci vous permet d'utiliser les commentaires que vous faites dans le code afin de générer une page html automatiquement cela peut donc être très utile pour faire des rapports de stage ou de la documentation ;) 

 - Pour cela vous devez aller sur le site de Doxygen <http://www.doxygen.nl/download.html> 

 Puis télécharger en fonction de votre OS le logiciel 

 - Ensuite dans Visual Code Studio Preférences/Extentions et tapez Doxygen Documentation 

 L'icône correspondante représente des lignes de code :)

Ensuite il ne vous reste plus qu'à commenter et ouvrir le logiciel suivre les instructions qui vous sont demandées et enjoy 



