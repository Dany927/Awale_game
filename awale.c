#include "awale.h"

int main()
{
    int **plateau=NULL, indL, indC;
    
    init_plateau(&plateau);
    while(1)
    {
        affichage_debug(plateau);
        printf("Ligne Colonne : ");
        scanf(" %d %d",&indL,&indC);
        deplacement(plateau, indL, indC);
    }

    return 0;
}

void init_plateau(int ***plateau)
{
    int i,j;
    *plateau=(int**)malloc(sizeof(int*)*NB_LIGNE);
    for(i=0;i<NB_LIGNE;i++)
    {
        (*plateau)[i]=(int*)malloc(sizeof(int)*NB_COLONNE);
    }
    for(i=0;i<NB_LIGNE;i++)
    {
        for(j=0;j<NB_COLONNE;j++)
        {
            (*plateau)[i][j]=3;
        }
    }
}

void affichage_debug(int **plateau)
{
    int i,j;
    for(i=0;i<NB_LIGNE;i++)
    {
        for(j=0;j<NB_COLONNE;j++)
        {
            printf("%2.d",plateau[i][j]);
        }
        printf("\n");
    }
}

void deplacement(int **plateau, int indL, int indC)
{
    int i;
    int decalageD=0,decalageG=0;
    decalageD=plateau[indL][indC];
    plateau[indL][indC]=0;
    for(i=1;i<=decalageD;i++)
    {
        if(indC+i>NB_COLONNE-1 && indL==1)
        {
            indL-=1;
            plateau[indL][indC+(i-1-decalageG)]++;
            decalageG=i;
        }
        else if(indC+(decalageG-i)<0 && indL==0)
        {
            indL+=1;
            plateau[indL][indC+(decalageG-(i-1))]++;
            decalageG=i;
        }
        else if(indL==0)
        {
            plateau[indL][indC+(decalageG-i)]++;
        }
        else if(indL==1)
        {
            plateau[indL][indC+(i-decalageG)]++;
        }
    }
}
