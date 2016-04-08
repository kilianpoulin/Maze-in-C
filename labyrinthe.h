//
// Created by Kilian on 22/03/2016.
//

#ifndef SDL_TEST_LABYRINTHE_H
#define SDL_TEST_LABYRINTHE_H

#define HAUTEUR_LAB 15
#define LONGUEUR_LAB 20

typedef struct Cellule
{
    unsigned char contenu[5];
}Cellule;

typedef struct Labyrinthe
{
    int hauteur;
    int longueur;
    int compteur;
    Cellule **cellule;
    SDL_Texture *Mur[2];
    SDL_Rect posMur;
    int direction[4]; /*Pour tester les 4 directions lors de la génération*/
    int xprec;
    int yprec;/*Pour mémoriser les cordonnées (backtracking)*/
} Labyrinthe;

void afficher(Labyrinthe *labyrinthe , SDL_Renderer *renderer);
void afficher_labyrinthe(Labyrinthe *labyrinthe , SDL_Renderer *renderer
        , int indiceI , int indiceJ);
void correction_affichage_labyrinthe(Labyrinthe *labyrinthe , SDL_Renderer *renderer);
void init_labyrinthe(Labyrinthe *labyrinthe , SDL_Renderer *renderer);
SDL_Texture *load_texture(char path[100] , SDL_Renderer *renderer);

int generer_labyrinthe(Labyrinthe *labyrinthe, int colonneActuel, int ligneActuel, int *colonneSuivante, int *ligneSuivante);

int tirer_direction(Labyrinthe *labyrinthe, const int xActuel, const int yActuel, int *xSuiv, int *ySuiv, int nb);
int tirer_direction_backtracking(Labyrinthe *labyrinthe, int xActuel, int yActuel, int *xSuiv, int *ySuiv, int nb);
void melange(int *direction , int taille);

enum{VISITE , MUR_NORD , MUR_SUD , MUR_EST , MUR_OUEST};
enum{IMG_MUR_H , IMG_MUR_V};
enum{NORD,EST,SUD,OUEST};

#endif //SDL_TEST_LABYRINTHE_H
