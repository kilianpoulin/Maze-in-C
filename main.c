#include "main.h"

void init_labyrinthe(Labyrinthe *labyrinthe)
{
    labyrinthe->hauteur = HAUTEUR_LAB;
    labyrinthe->longueur = LONGUEUR_LAB;
    labyrinthe->compteur = labyrinthe->hauteur * labyrinthe->longueur;

    labyrinthe->cellule = malloc(labyrinthe->hauteur * labyrinthe->longueur * sizeof(Cellule));
    /* if(labyrinthe->cellule == NULL)
         exit*/
    labyrinthe->cellule[0][0].contenu[VISITE] = 1;
    labyrinthe->cellule[0][0].contenu[MUR_NORD] = 1;
    labyrinthe->cellule[0][0].contenu[MUR_SUD] = 1;
    labyrinthe->cellule[0][0].contenu[MUR_EST] = 1;
    labyrinthe->cellule[0][0].contenu[MUR_OUEST] = 1;
}

void liberation(void) {
    SDL_Quit();
}

void sdl_init(SDL_Window *window) {

    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        //printf
    }

    window = SDL_CreateWindow("SDL_Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              640, 480, SDL_WINDOW_OPENGL);
    if(window == NULL) {
        //printfreturn 0;
    }
}

void init(SDL_Window *window , Labyrinthe *labyrinthe) {
    sdl_init(window);

    init_labyrinthe(labyrinthe);
}

int main(int argc, char** argv) {
    Labyrinthe labyrinthe;
    int continuer = 1;
    SDL_Event event;//pour les evenements
    SDL_Window *window = NULL;
    init(window , &labyrinthe);
    while(continuer)//boucle principale du programme
    {
        while (SDL_PollEvent(&event))//tant qu'il y a un evenement
             {
            switch (event.type) //de quel type devenement il s'agit
            {
                case SDL_QUIT ://si on appui sur echap
                    continuer = 0;
                    break;
            }
        }
    }
    liberation();

    return 0;
}