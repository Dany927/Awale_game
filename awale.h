#ifndef AWALE_H
    #define AWALE_H

    #include <stdlib.h>
    #include <stdio.h>
    #include <SDL/SDL.h>
    #include <SDL/SDL_image.h>
    #include <SDL/SDL_ttf.h>
    #include "fmod.h"

    #define NB_LIGNE 2
    #define NB_COLONNE 6
    #define VRAI 1
    #define FAUX 0

    enum picture {MENU,SCORE,MENU2} p;

    typedef struct
    {
        char pseudo[30];
        int score;
        
    }Joueur;

    void placement_graine(SDL_Surface *ecran, int tableau[2][6]);
    void partie_graphique(int tableau[2][6], SDL_Surface* ecran, SDL_Surface* imageFond,int nb_tour,Joueur joueur[2]);
    int deplacement_graine(SDL_Rect clic, int i);
    void saisi_pseudo(SDL_Surface *ecran,char Pseudo[12]);
    void placement_choix(SDL_Rect choix[3]);
    void jouer_J1_J2(SDL_Surface *ecran, SDL_Surface *imageFond, SDL_Rect positionImageFond, Joueur joueur[2]);
    int victoire(int tableau[2][6], Joueur joueur[2], int nb_tour_sans_recolte, int nb_tour);
#endif
