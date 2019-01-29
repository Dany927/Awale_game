#include "awale.h"

void partie_graphique(int tableau[2][6], SDL_Surface* ecran, SDL_Surface* imageFond,int nb_tour,Joueur joueur[2])
{
    SDL_Surface *imagePlateau=NULL, *texte=NULL, *message=NULL, *txt_score=NULL;
    SDL_Rect positionPlateauJ1,positionPlateauJ2,positionImageFond;
    SDL_Rect positionTexte, positionMessage, positionScore;
    
    SDL_Color couleurNoire = {0, 0, 0}, couleurBlanche = {255, 255, 255};
    
    TTF_Font *police = NULL;
        
    positionTexte.x = 330;	positionTexte.y = 100;
    positionMessage.x = 50; positionMessage.y = 100;

    positionPlateauJ1.x=50;    positionPlateauJ1.y=200;
    positionPlateauJ2.x=50;    positionPlateauJ2.y=300;
    positionImageFond.x=0;     positionImageFond.y=0;

    positionScore.x=50;	positionScore.y = 450;

    TTF_Init();
    imagePlateau = IMG_Load("./rapport.png");

    police = TTF_OpenFont("./04B_30__.TTF", 28);

    SDL_FillRect(ecran, NULL, SDL_Swap32(SDL_MapRGB(ecran->format,255,255,255)));
    SDL_BlitSurface(imageFond, NULL, ecran, &positionImageFond);
    
    txt_score = TTF_RenderText_Shaded(police, "Score :", couleurBlanche, couleurNoire);
    message = TTF_RenderText_Shaded(police, "Au tour de :", couleurBlanche, couleurNoire);
    texte = TTF_RenderText_Shaded(police, joueur[nb_tour%2].pseudo, couleurBlanche, couleurNoire);
    
    SDL_BlitSurface(txt_score, NULL, ecran, &positionScore);
    SDL_BlitSurface(message, NULL, ecran, &positionMessage);
    SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
    SDL_BlitSurface(imagePlateau, NULL, ecran, &positionPlateauJ1);
    SDL_BlitSurface(imagePlateau, NULL, ecran, &positionPlateauJ2);
    
    placement_graine(ecran,tableau);
    TTF_Quit();
}

int deplacement_graine(SDL_Rect clic,int i)
{
    int j;
    
    if(i==0)
    {
        if ( (clic.y > 220 && clic.y < 290 ) && (clic.x > 66 && clic.x < 138))  j=0;
        else if ( (clic.y > 220 && clic.y < 290 ) && (clic.x > 144 && clic.x < 214))  j=1;
        else if ( (clic.y > 220 && clic.y < 290 ) && (clic.x > 218 && clic.x < 292))  j=2;
        else if ( (clic.y > 220 && clic.y < 290 ) && (clic.x > 296 && clic.x < 374))  j=3;
        else if ( (clic.y > 220 && clic.y < 290 ) && (clic.x > 378 && clic.x < 454))  j=4;
        else if ( (clic.y > 220 && clic.y < 290 ) && (clic.x > 458 && clic.x < 532))  j=5;
        else j=-1;
    }
    else
    {
        if ( (clic.y > 320 && clic.y < 390 ) && (clic.x > 66 && clic.x < 138))  j=0;
        else if ( (clic.y > 320 && clic.y < 390 ) && (clic.x > 144 && clic.x < 214))  j=1;
        else if ( (clic.y > 320 && clic.y < 390 ) && (clic.x > 218 && clic.x < 292))  j=2;
        else if ( (clic.y > 320 && clic.y < 390 ) && (clic.x > 296 && clic.x < 374))  j=3;
        else if ( (clic.y > 320 && clic.y < 390 ) && (clic.x > 378 && clic.x < 454))  j=4;
        else if ( (clic.y > 320 && clic.y < 390 ) && (clic.x > 458 && clic.x < 532))  j=5;
        else j=-1;
    }

    return j;
}

void placement_graine(SDL_Surface *ecran,int tableau[2][6])
{
    int i,j,pos_plateau=0;
    SDL_Surface *imageGraines=NULL;
    SDL_Rect positionGraines;
    imageGraines=IMG_Load("./pilule.png");
    positionGraines.x=78;   positionGraines.y=244;
    
    SDL_Color couleurNoire = {0, 0, 0}, couleurBlanche = {255, 255, 255};
    
    TTF_Font *police = NULL;
    SDL_Surface* texte=NULL;
    char num;

    TTF_Init();
    police = TTF_OpenFont("./04B_30__.TTF", 15);
    
    for(i=0;i<6;i++)
    {
        if(tableau[pos_plateau][i]<7)
        {
            for(j=0;j<tableau[pos_plateau][i];j++)
            {
                SDL_BlitSurface(imageGraines, NULL, ecran, &positionGraines);
                SDL_Flip(ecran);
                if(j==2)   {positionGraines.x=78+78*i;  positionGraines.y=260;}
                positionGraines.x+=15;
            }
            positionGraines.y=244;
            if(tableau[pos_plateau][i]>0) positionGraines.x+=60;
            else    positionGraines.x+=78;
        }
        else
        {
            num=tableau[pos_plateau][i];
            texte = TTF_RenderText_Blended(police, &num, couleurNoire);
            positionGraines.x=78+78*i;   positionGraines.y=244;
            SDL_BlitSurface(texte, NULL, ecran, &positionGraines);
        }
    }
    positionGraines.x=78;   positionGraines.y=344;
    pos_plateau=1;
    for(i=0;i<6;i++)
    {
        if(tableau[pos_plateau][i]<7)
        {
            for(j=0;j<tableau[pos_plateau][i];j++)
            {
                SDL_BlitSurface(imageGraines, NULL, ecran, &positionGraines);
                SDL_Flip(ecran);
                if(j==2)   {positionGraines.x=78+78*i;  positionGraines.y=360;}
                positionGraines.x+=15;
            }
             positionGraines.y=344;
            if(tableau[pos_plateau][i]>0) positionGraines.x+=60;
            else    positionGraines.x+=78;
        }
        else
        {
            num=tableau[pos_plateau][i];
            texte = TTF_RenderText_Blended(police, &num, couleurNoire);
            positionGraines.x=78+78*i;   positionGraines.y=344;
            SDL_BlitSurface(texte, NULL, ecran, &positionGraines);
        }
    }
    TTF_Quit();
}


void saisi_pseudo(SDL_Surface *ecran,char Pseudo[12])
{
    SDL_Color couleurNoire = {0, 0, 0}, couleurBlanche = {255, 255, 255};
    TTF_Font *police = NULL;
    SDL_Event event;
    /* tableau pour contenir "PSEUDO : <pseudo a rentrer> "*/
    char phrase_pseudo[255];
    /* variable qui contient le pseudo */
    SDL_Surface* texte;
    /* variable qui contient  l'image ou l'on va rentrer le pseudo */
    SDL_Surface *image_pseudo = NULL;
    /* variable des positions images et pseudo */
    SDL_Rect position_image_pseudo;
    SDL_Rect positionTexte;
    
    /* Utilisation de la boucle pause en attendant la saisie et la validation du pseudo */
    int pause = VRAI;
    int pos=0,unicode;
    int nbr_max=12;
    /* Chargement de l'image saisie pseudo */
    image_pseudo = IMG_Load("./saisie_pseudo.png");
    position_image_pseudo.x = 150;
    position_image_pseudo.y = 200;
    positionTexte.x = 175;
    positionTexte.y = 250;
    TTF_Init();
    police = TTF_OpenFont("./04B_30__.TTF", 15);
    SDL_EnableUNICODE(1);
    /* Boucle pause */
    while(pause)
    {
        /* On affiche l'image pour saisir le pseudo */
        SDL_BlitSurface(image_pseudo, NULL, ecran, &position_image_pseudo);
        sprintf(phrase_pseudo, "Pseudo : %s", Pseudo);
        texte = TTF_RenderText_Shaded(police, phrase_pseudo, couleurBlanche, couleurNoire);
        /* On affiche chaque caractere que l'on tape */
        SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
        SDL_Flip(ecran);
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
            {
                    /* ENTREE, on sort de la boucle car on valide */
                case SDLK_RETURN:
                    pause=FAUX;
                    break;
                    /* On efface un caractere */
                case SDLK_BACKSPACE:
                    if(pos>0)
                        pos--;
                    Pseudo[pos] = '\0';
                    break;
                    /* On ajoute un caractere au tableau */
                default:
                    unicode = event.key.keysym.unicode;
                    if (unicode >= 32 && unicode <= 127 && pos < nbr_max)
                    {
                        Pseudo[pos] = (char)unicode;
                        pos++;
                        Pseudo[pos] = '\0';
                    }
                    break;
            }
                break;
        }
    }
    SDL_EnableUNICODE(0);
    SDL_FreeSurface(image_pseudo);
    TTF_Quit();
    return;
}
