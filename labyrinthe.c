//
// Created by Kilian on 22/03/2016.
//

#include "labyrinthe.h"

SDL_Texture *load_texture(char path[100] , SDL_Renderer *renderer)
{
    SDL_Texture *newTexture = NULL;
    SDL_Surface *image = SDL_LoadBMP(path);
    newTexture = SDL_CreateTextureFromSurface(renderer , image);
    SDL_FreeSurface(image);

    return newTexture;
}

void afficher_labyrinthe(Labyrinthe *labyrinthe , SDL_Renderer *renderer
        , int indiceI , int indiceJ) {
    if(indiceJ == labyrinthe->hauteur)
        return;
    if(indiceI == labyrinthe->longueur){
        indiceJ++;
        indiceI = 0;
        afficher_labyrinthe(labyrinthe , renderer , indiceI , indiceJ);
    }
    else {
        /*MUR OUEST*/
        labyrinthe->posMur.x = indiceI * 32;
        labyrinthe->posMur.y = indiceJ * 32;
        labyrinthe->posMur.w = 6;
        labyrinthe->posMur.h = 32;
        if (labyrinthe->cellule[indiceJ][indiceI].contenu[MUR_OUEST])
            SDL_RenderCopy(renderer, labyrinthe->Mur[IMG_MUR_V], NULL, &labyrinthe->posMur);
        /*MUR EST*/
        labyrinthe->posMur.x = (indiceI + 1) * 32;
        labyrinthe->posMur.y = indiceJ * 32;
        if (labyrinthe->cellule[indiceJ][indiceI].contenu[MUR_EST])
            SDL_RenderCopy(renderer, labyrinthe->Mur[IMG_MUR_V], NULL, &labyrinthe->posMur);
        /*MUR NORD*/
        labyrinthe->posMur.x = indiceI * 32;
        labyrinthe->posMur.y = indiceJ * 32;
        labyrinthe->posMur.w = 32;
        labyrinthe->posMur.h = 6;
        if (labyrinthe->cellule[indiceJ][indiceI].contenu[MUR_NORD])
            SDL_RenderCopy(renderer, labyrinthe->Mur[IMG_MUR_H], NULL, &labyrinthe->posMur);
        /*MUR_SUD*/
        labyrinthe->posMur.x = indiceI * 32;
        labyrinthe->posMur.y = (indiceJ + 1) * 32;
        if (labyrinthe->cellule[indiceJ][indiceI].contenu[MUR_SUD])
            SDL_RenderCopy(renderer, labyrinthe->Mur[IMG_MUR_H], NULL, &labyrinthe->posMur);
        afficher_labyrinthe(labyrinthe, renderer, indiceI + 1, indiceJ);
    }
}
void correction_affichage_labyrinthe(Labyrinthe *labyrinthe , SDL_Renderer *renderer)
{
    labyrinthe->posMur.x = labyrinthe->longueur * 32;
    labyrinthe->posMur.y = labyrinthe->hauteur * 32;
    labyrinthe->posMur.w = 6;
    labyrinthe->posMur.h = 32;
    SDL_RenderCopy(renderer, labyrinthe->Mur[IMG_MUR_V], NULL, &labyrinthe->posMur);
    /*MUR NORD*/
    labyrinthe->posMur.w = 32;
    labyrinthe->posMur.h = 6;
    SDL_RenderCopy(renderer, labyrinthe->Mur[IMG_MUR_H], NULL, &labyrinthe->posMur);

}

void init_labyrinthe(Labyrinthe *labyrinthe , SDL_Renderer *renderer)
{
    int i = 0 , j = 0;
    labyrinthe->hauteur = HAUTEUR_LAB;
    labyrinthe->longueur = LONGUEUR_LAB;
    labyrinthe->compteur = labyrinthe->hauteur * labyrinthe->longueur;
    labyrinthe->Mur[IMG_MUR_H] = load_texture("C:/Users/Kilian/ClionProjects/THE_LABYRINTHE/MurH.bmp" , renderer);
    if(!labyrinthe->Mur[IMG_MUR_H])
        printf("Erreur mur horizontale");
    labyrinthe->Mur[IMG_MUR_V] = load_texture("C:/Users/Kilian/ClionProjects/THE_LABYRINTHE/MurV.bmp" , renderer);
    if(!labyrinthe->Mur[IMG_MUR_V])
        printf("Erreur mur horizontale");

    labyrinthe->cellule = malloc(labyrinthe->hauteur * sizeof(*labyrinthe->cellule));
    if(labyrinthe->cellule == NULL)
        printf("Erreur avec l'allocation du labyrinthe\n");
    for(i = 0 ; i < labyrinthe->hauteur ; i++)
    {
        labyrinthe->cellule[i] = malloc( labyrinthe->longueur * sizeof(**labyrinthe->cellule));
        if(labyrinthe->cellule[i] == NULL)
            printf("Erreur avec l'allocation du labyrinthe\n");
    }

    for(j = 0 ; j < labyrinthe->hauteur ; j++) {
        for (i = 0; i < labyrinthe->longueur; i++) {

            labyrinthe->cellule[j][i].contenu[VISITE] = 0;/*On n'a encore visité aucune cases au début*/
            labyrinthe->cellule[j][i].contenu[MUR_NORD] = 1;
            labyrinthe->cellule[j][i].contenu[MUR_SUD] = 1;
            labyrinthe->cellule[j][i].contenu[MUR_EST] = 1;
            labyrinthe->cellule[j][i].contenu[MUR_OUEST] = 1;
        }
    }
    labyrinthe->direction[0] = 0;
    labyrinthe->direction[1] = 1;
    labyrinthe->direction[2] = 2;
    labyrinthe->direction[3] = 3;

}

/*But : génerer la case suivante*/
int tirer_direction(Labyrinthe *labyrinthe, const int xActuel, const int yActuel, int *xSuiv, int *ySuiv, int nb)
{
    if(nb == 4)
        return 0;

   if ((labyrinthe->direction[nb] == NORD) && (yActuel - 1 >= 0)){
     if(labyrinthe->cellule[yActuel - 1][xActuel].contenu[VISITE] == 0){
           *xSuiv = xActuel;
           *ySuiv = yActuel - 1;
           return 1;
       }
    }
        //OUEST
    else if ((labyrinthe->direction[nb] == OUEST) && (xActuel - 1 >= 0)){
        if(labyrinthe->cellule[yActuel][xActuel - 1].contenu[VISITE] == 0) {
        *xSuiv = xActuel - 1;
        *ySuiv = yActuel;
        return 1;
       }
   }
        //SUD
    else if ((labyrinthe->direction[nb] == SUD) && (yActuel + 1 < 15)) {
       if ((labyrinthe->cellule[yActuel + 1][xActuel].contenu[VISITE] == 0)) {
           *xSuiv = xActuel;
           *ySuiv = yActuel + 1;
           return 1;
       }
   }
        //EST
    else if ((labyrinthe->direction[nb] == EST) && (xActuel + 1 < 20)){
             if(labyrinthe->cellule[yActuel][xActuel + 1].contenu[VISITE] == 0){
        *xSuiv = xActuel + 1;
        *ySuiv = yActuel;
        return 1;
       }
    }

    return tirer_direction(labyrinthe, xActuel, yActuel, xSuiv, ySuiv, nb + 1);
}
int tirer_direction_backtracking(Labyrinthe *labyrinthe, int xActuel, int yActuel, int *xSuiv, int *ySuiv, int nb)
{
    if(nb == 4)
        return 0;

    //NORD
   if ((labyrinthe->direction[nb] == NORD) && (yActuel - 1 >= 0)) {

       if (labyrinthe->cellule[yActuel][xActuel].contenu[MUR_NORD] == 0){

           if(labyrinthe->cellule[yActuel - 1][xActuel].contenu[VISITE] != 2) {

               *xSuiv = xActuel;
               *ySuiv = yActuel - 1;
               return 1;
           }
       }
   }
        //OUEST
    else if ((labyrinthe->direction[nb] == OUEST) && (xActuel - 1 >= 0)){

        if(labyrinthe->cellule[yActuel][xActuel].contenu[MUR_OUEST] == 0)
        {

             if(labyrinthe->cellule[yActuel][xActuel - 1].contenu[VISITE] != 2) {

                 *xSuiv = xActuel - 1;
                 *ySuiv = yActuel;
                 return 1;
             }
        }
    }
        //SUD
    else if ((labyrinthe->direction[nb] == SUD) && (yActuel + 1 < 15)) {
        if (labyrinthe->cellule[yActuel][xActuel].contenu[MUR_SUD] == 0)
        {
            if(labyrinthe->cellule[yActuel + 1][xActuel].contenu[VISITE] != 2) {
                *xSuiv = xActuel;
                *ySuiv = yActuel + 1;
                return 1;
            }
        }
    }
        //EST
    else if ((labyrinthe->direction[nb] == EST) && (xActuel + 1 < 20)){

        if (labyrinthe->cellule[yActuel][xActuel].contenu[MUR_EST] == 0)
        {

           if(labyrinthe->cellule[yActuel][xActuel + 1].contenu[VISITE] != 2){
                *xSuiv = xActuel + 1;
                *ySuiv = yActuel;
                return 1;
            }
        }
    }
    return tirer_direction_backtracking(labyrinthe, xActuel, yActuel, xSuiv, ySuiv, nb + 1);
}
int generer_labyrinthe(Labyrinthe *labyrinthe, int colonneActuel, int ligneActuel, int *colonneSuivante, int *ligneSuivante) {

   printf("Actu->ligne : %d", ligneActuel);
    printf("\nActu->colonne : %d", colonneActuel);
    printf("\nSuiv->ligne : %d", *ligneSuivante);
    printf("\nSuiv->colonne : %d", *colonneSuivante);
    printf("\ncompteur : %d", labyrinthe->compteur);
    printf("\n\n\n");
    if (labyrinthe->compteur == 0)
        return 0;

    /* On indique que la case est visitée */
    if(labyrinthe->cellule[*ligneSuivante][*colonneSuivante].contenu[VISITE] == 0)
    {
        labyrinthe->cellule[*ligneSuivante][*colonneSuivante].contenu[VISITE] = 1;
    }
    /* on casse les murs */
    if (*ligneSuivante - ligneActuel == -1) {// on va vers le nord
        labyrinthe->cellule[ligneActuel][colonneActuel].contenu[MUR_NORD] = 0;
        labyrinthe->cellule[*ligneSuivante][*colonneSuivante].contenu[MUR_SUD] = 0;
    }
    else if (*colonneSuivante - colonneActuel == -1) { // on va vers l'ouest
        labyrinthe->cellule[ligneActuel][colonneActuel].contenu[MUR_OUEST] = 0;
        labyrinthe->cellule[*ligneSuivante][*colonneSuivante].contenu[MUR_EST] = 0;
    }
    else if (*colonneSuivante - colonneActuel == 1) { // on va vers l'est
        labyrinthe->cellule[ligneActuel][colonneActuel].contenu[MUR_EST] = 0;
        labyrinthe->cellule[*ligneSuivante][*colonneSuivante].contenu[MUR_OUEST] = 0;

    }
    else if (*ligneSuivante - ligneActuel == 1) { // on va vers le SUD
        labyrinthe->cellule[ligneActuel][colonneActuel].contenu[MUR_SUD] = 0;
        labyrinthe->cellule[*ligneSuivante][*colonneSuivante].contenu[MUR_NORD] = 0;
    }
    labyrinthe->xprec = colonneActuel;
    labyrinthe->yprec = ligneActuel;

    colonneActuel = *colonneSuivante;
    ligneActuel = *ligneSuivante;

    melange(labyrinthe->direction , 4);/*On mélange le tableau pour tirer une direction*/

    if(tirer_direction(labyrinthe , colonneActuel , ligneActuel ,colonneSuivante , ligneSuivante , 0) == 1)
        generer_labyrinthe(labyrinthe, colonneActuel, ligneActuel, colonneSuivante, ligneSuivante);
    else {
        if(labyrinthe->cellule[ligneActuel][colonneActuel].contenu[VISITE] == 1) {
            labyrinthe->cellule[ligneActuel][colonneActuel].contenu[VISITE] = 2;
        }
        labyrinthe->compteur--;

        melange(labyrinthe->direction , 4);
        if(tirer_direction_backtracking(labyrinthe , colonneActuel , ligneActuel , colonneSuivante , ligneSuivante , 0) == 1) {
            generer_labyrinthe(labyrinthe, colonneActuel, ligneActuel, colonneSuivante, ligneSuivante);
        }
    }
    return 0;
}