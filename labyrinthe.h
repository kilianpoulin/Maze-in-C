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
} Labyrinthe;

void init_labyrinthe(Labyrinthe *labyrinthe);

enum{VISITE , MUR_NORD , MUR_SUD , MUR_EST , MUR_OUEST};

#endif //SDL_TEST_LABYRINTHE_H
