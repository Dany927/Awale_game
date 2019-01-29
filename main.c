#include "awale.h"

int main(int argc, char* argv[])
{

    int fleches=0;
    int gagnant=0,continuer=1,position_preced;

    Joueur joueur[2];
    
    SDL_Surface *ecran=NULL, *imageFond=NULL, *curseur=NULL;
    SDL_Event event;
    SDL_Rect positionImageFond, positionCurseur;
    SDL_Rect choix[3];
    
    FMOD_SYSTEM *system;
    FMOD_SOUND *Curseur;
    FMOD_SOUND *Choix;
    FMOD_RESULT resultat;
    FMOD_CHANNEL *channel;
    
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);
    resultat = FMOD_System_CreateSound(system, "./Curseur.wav", FMOD_CREATESAMPLE, 0, &Curseur);
    resultat = FMOD_System_CreateSound(system, "./Choix.wav", FMOD_CREATESAMPLE, 0, &Choix);
    
    positionImageFond.x=0;  positionImageFond.y=0;
    
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(600, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
    SDL_WM_SetCaption("Jeu Awale", NULL);
    imageFond=IMG_Load("./menu_awale.png");
    SDL_BlitSurface(imageFond, NULL, ecran, &positionImageFond);
    p = MENU;
    curseur = SDL_LoadBMP("./curseur.bmp");
    SDL_SetColorKey(curseur, SDL_SRCCOLORKEY, SDL_MapRGB(curseur->format, 0, 0, 255));
    positionCurseur.y = 285;    positionCurseur.x = 180;
    SDL_BlitSurface(curseur, NULL, ecran, &positionCurseur);
    
    placement_choix(choix);

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
                /* Croix de la fenêtre pour quitter le jeu */
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    /* Appuie sur echap pour quitter le fullscreen*/
                    case SDLK_ESCAPE:
                        continuer=0;
                        break;
                    case SDLK_UP:
                        fleches--;
                        if(fleches<0)
                            fleches = 2;
                        positionCurseur.x = choix[fleches].x;
                        positionCurseur.y = choix[fleches].y;
                        /* Son du curseur qui se deplace dans le menu principal */
                        FMOD_System_GetChannel(system,9,&channel);
                        FMOD_System_PlaySound(system, Curseur, 0, 0, &channel);
                         SDL_BlitSurface(imageFond, NULL, ecran, &positionImageFond);
                        SDL_BlitSurface(curseur, NULL, ecran, &positionCurseur);
                        break;
                        
                    case SDLK_DOWN:
                        fleches++;
                        if(fleches > 2)
                            fleches = 0;
                        positionCurseur.x = choix[fleches].x;
                        positionCurseur.y = choix[fleches].y;
                        /* Son du curseur qui se deplace dans le menu principal */
                        FMOD_System_GetChannel(system,9,&channel);
                        FMOD_System_PlaySound(system, Curseur, 0, 0, &channel);
                        SDL_BlitSurface(imageFond, NULL, ecran, &positionImageFond);
                        SDL_BlitSurface(curseur, NULL, ecran, &positionCurseur);
                        break;
                        
                        /*Appuie sur entree pour valider ton choix && pour revenir au menu
                         * 0 : jouer, 1 : scores, 2 : options, 3 : crédits, 4 : quitter */
                    case SDLK_RETURN:
                        /* Valider choix du menu
                         * Utilisation du son choix */
                        FMOD_System_GetChannel(system,9,&channel);
                        FMOD_System_PlaySound(system, Choix, 0, 0, &channel);
                        
                        /* Si tu valides le choix sur jouer */
                        if((positionCurseur.x == choix[0].x && positionCurseur.y == choix[0].y))
                        {
                            if(p==MENU)
                            {
                                imageFond=IMG_Load("./Choix_jeu.png");
                                SDL_BlitSurface(imageFond, NULL, ecran, &positionImageFond);
                                SDL_BlitSurface(curseur, NULL, ecran, &positionCurseur);
                            }
                            
                            if(p==MENU2)
                            {
                                jouer_J1_J2(ecran, imageFond, positionImageFond, joueur);
                            }
                            p=MENU2;
                        }
                        /* Entrer dans le sous menu score */
                        /*else if( (positionCurseur.x == choix[1].x && positionCurseur.y == choix[1].y))
                        {
                            imageDeFond = IMG_Load("./Images/pic_menu/scores.bmp");
                            p = SCORE;
                        }*/
                        /* quitter avec le menu */
                        else    continuer = 0;
                    default:;
                }
                break;
            case SDL_MOUSEMOTION:
                if(p==MENU || p==MENU2)
                {
                    position_preced=positionCurseur.y;
                    if((event.motion.x>200 && event.motion.x<400) && (event.motion.y>270 && event.motion.y<326))
                    {
                        positionCurseur.y = choix[0].y; positionCurseur.x = choix[0].x;
                    }
                    else if((event.motion.x>200 && event.motion.x<400) && (event.motion.y>345 && event.motion.y<400))
                    {
                        positionCurseur.y = choix[1].y; positionCurseur.x = choix[1].x;
                    }
                    else if((event.motion.x>200 && event.motion.x<400) && (event.motion.y>425 && event.motion.y<480))
                    {
                        positionCurseur.y = choix[2].y; positionCurseur.x = choix[2].x;
                    }
                    if(positionCurseur.y!=position_preced)
                    {
                        FMOD_System_GetChannel(system,9,&channel);
                        FMOD_System_PlaySound(system, Curseur, 0, 0, &channel);
                        SDL_BlitSurface(imageFond, NULL, ecran, &positionImageFond);
                        SDL_BlitSurface(curseur, NULL, ecran, &positionCurseur);
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    /* Si tu valides le choix sur jouer */
                    if((positionCurseur.x == choix[0].x && positionCurseur.y == choix[0].y))
                    {
                        if(p==MENU)
                        {
                            imageFond=IMG_Load("./Choix_jeu.png");
                            SDL_BlitSurface(imageFond, NULL, ecran, &positionImageFond);
                            SDL_BlitSurface(curseur, NULL, ecran, &positionCurseur);
                        }
                        
                        if(p==MENU2)
                        {
                            jouer_J1_J2(ecran, imageFond, positionImageFond, joueur);
                        }
                        p=MENU2;
                    }
                    else continuer = 0;
                }
                
                break;
            default:;
        }
        SDL_Flip(ecran);


    }
    
    SDL_FreeSurface(ecran);
    SDL_Quit();
    FMOD_Sound_Release(Curseur);
    FMOD_Sound_Release(Choix);
    FMOD_System_Close(system);
    FMOD_System_Release(system);
    
    return EXIT_SUCCESS;
}



int victoire(int tableau[2][6], Joueur joueur[2], int nb_tour_sans_recolte, int nb_tour)
{
    int i=0, test_joueur=0,test1=0;
    while(tableau[(nb_tour+1)&0b1][i]==0 && i<=5)// test si la zone de jeu de l'adversaire est vide
    {
        test_joueur++;
        i++;
    }

    test1= (joueur[(nb_tour&0b1)].score>=19) ? (nb_tour&0b1)+1 : 0;// test le nombre de point du joueur

    test1=(nb_tour_sans_recolte>=20 && joueur[0].score==joueur[1].score) ? 3: 0;// si personne n'a reussi a prendre de graine pendant 20 tours celui qui a le plus de graine gagne
    test1=(nb_tour_sans_recolte>=20 && joueur[1].score>joueur[0].score) ?  2: 0;
    test1=(nb_tour_sans_recolte>=20 && joueur[0].score>joueur[1].score) ?  1: 0;

    test1=(test_joueur==6) ?  (nb_tour&0b1)+1: 0; // si  l'adversaire n'a plus de graine dans sa zone de jeu le joueur courant gagne

   return (test1!=0) ? test1: 0;

}


void placement_choix(SDL_Rect choix[3])
{
    choix[0].x = 180;   choix[0].y = 285;
    
    choix[1].x = 180;   choix[1].y = 360;
    
    choix[2].x = 180;   choix[2].y = 438;

}



void jouer_J1_J2(SDL_Surface *ecran, SDL_Surface *imageFond, SDL_Rect positionImageFond, Joueur joueur[2])
{
    SDL_Event event;
    SDL_Rect clic;
    int tableau[2][6] = {{3,3,3,3,3,3},{3,3,3,3,3,3}};
    int valeur, nb_tour=0,incrementation;
    int gagnant=0,continuer=1;
    int nb_tour_sans_recolte=20;
    joueur[0].score=0;
    joueur[1].score=0;
    int i, j;
    
    imageFond=IMG_Load("./fond_noir.png");
    SDL_BlitSurface(imageFond, NULL, ecran, &positionImageFond);
    
    saisi_pseudo(ecran,joueur[1].pseudo);
    saisi_pseudo(ecran,joueur[0].pseudo);
    /* Lancer la partie */
    do
    {
        if(nb_tour<=1 || j>-1)   {nb_tour++; partie_graphique(tableau,ecran,imageFond,nb_tour,joueur);}
        
        SDL_WaitEvent(&event);
        switch(event.type)
        {
                /* Croix de la fenêtre pour quitter le jeu */
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    clic.x=event.button.x;
                    clic.y=event.button.y;
                }
                break;
            default:;
        }
        
        i=nb_tour&0b1;
        j=deplacement_graine(clic,i);
        
        if(j>-1)
        {
            valeur = tableau[i][j];
            tableau[i][j]=0;
            incrementation=0;
            
            while(incrementation<valeur)
            {
                incrementation++;
                
                j=(j==0 && i==0)? -1:j;// en cas i=0 j=0 on passe a la case i=1 j=0
                i=(j==-1 && i==0)? 1:i;
                
                
                j=(j==5 && i==1)? 6:j;// en cas i=1 j=5 on passe a la case i=0 j=5
                i=(j==6 && i==1)? 0:i;
                
                
                j+=(i==0 )? -1 : 0; // = si i=0 j--
                j+=(i==1 )? 1 : 0;  // = si i=1 j++
                j+=(i==0 && incrementation==12)? -1 : 0;// on ne doit pas poser de graine sur la case de depard
                j+=(i==1 && incrementation==12)?  1 : 0;
                
                tableau[i][j]++;
            }
            
            if(tableau[i][j]<=3 && tableau[i][j]>1 && i!=(nb_tour&0b1))
            {
                joueur[nb_tour%2].score+=tableau[i][j];
                tableau[i][j]=0;
                //if(j==0 && i==0){i=1;j=0;}
                //else if(j==5 && i==1){i=0;j=5;}
                if(i==0){j++;}
                else if(i==1){j--;}
                if(tableau[i][j]<=3 && tableau[i][j]>1)
                {
                    joueur[nb_tour%2].score+=tableau[i][j];
                    tableau[i][j]=0;
                }
                nb_tour_sans_recolte=0;
            }
            else{nb_tour_sans_recolte++;}
            
            gagnant=victoire(tableau,joueur,nb_tour_sans_recolte,nb_tour);
        }
    }while (gagnant==0 && continuer);
}
