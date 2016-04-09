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
} Labyrinthe;

void afficher(Labyrinthe *labyrinthe , SDL_Renderer *renderer);
void afficher_labyrinthe(Labyrinthe *labyrinthe , SDL_Renderer *renderer
        , int indiceI , int indiceJ);
void correction_affichage_labyrinthe(Labyrinthe *labyrinthe , SDL_Renderer *renderer);
void init_labyrinthe(Labyrinthe *labyrinthe , SDL_Renderer *renderer);
SDL_Texture *load_texture(char path[100] , SDL_Renderer *renderer);

int generer_labyrinthe(Labyrinthe *labyrinthe, int colonneActuel, int ligneActuel, int *colonneSuivante, int *ligneSuivante);


int tirer_direction(Labyrinthe *labyrinthe, const int xActuel, const int yActuel, int *xSuiv, int *ySuiv, int nb); // Fonction qui génère la case suivante
int tirer_direction_backtracking(Labyrinthe *labyrinthe, int xActuel, int yActuel, int *xSuiv, int *ySuiv, int nb); //Fonction qui réalise le backtracking
void melange(int *direction , int taille); // melange aléatoirement les directions dans un tableau

enum{VISITE , MUR_NORD , MUR_SUD , MUR_EST , MUR_OUEST}; // Informations sur les cases
enum{IMG_MUR_H , IMG_MUR_V};    // Images des murs (barre horizontale et barre verticale
enum{NORD,EST,SUD,OUEST};   // Directions

#endif //SDL_TEST_LABYRINTHE_H
