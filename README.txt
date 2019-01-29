//    README
//    MOURAO DANY
//    ROUMEC BRYAN
//    ROUSSEL QUENTIN
//    TERUEL RAPHAEL
//    HAMMAR MERIEM

Pour installer la bibliothèque graphique SDL 1.2, vous pouvez l'installer grâce à ces commandes :

sudo apt-get install libsdl1.2-dev

//bibliotheque pour les images
sudo apt-get install libsdl-image1.2 libsdl-image1.2-dev

//bibliotheque pour le texte
sudo apt-get install libsdl-ttf2.0-0 libsdl-ttf2.0-dev
				
ligne de compilation pour le jeu awale :

gcc -Wall graphique_awale.c main.c -o Awale -lSDL -lSDL_ttf -lfmod -lSDL_image -lm

