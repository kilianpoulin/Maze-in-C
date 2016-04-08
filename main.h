#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include "include/SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "labyrinthe.c"


void afficher(Labyrinthe *labyrinthe , SDL_Renderer *renderer);
void liberation(SDL_Window *window , SDL_Renderer *renderer);
int aleatoire(int max);
void melange(int *direction , int taille);

#endif // MAIN_H_INCLUDED
