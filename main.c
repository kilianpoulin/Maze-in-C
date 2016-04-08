#include "main.h"

int main(int argc, char** argv) {

    int i = 0;
    srand(time(NULL));
    int continuer = 1  ,  aleatoireLigne = 0 , aleatoireColonne = 0;
    SDL_Event event;
    SDL_Renderer *renderer = NULL;
    Labyrinthe labyrinthe;

    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        printf("Initialisation de la SDL");
    }

    SDL_Window *window = SDL_CreateWindow("Labyrinthe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              646, 486, SDL_WINDOW_OPENGL);
    if(window == NULL) {
        printf("Erreur window");
    }
    renderer = SDL_CreateRenderer(window, -1 , SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) {
        printf("Erreur Renderer ");
    }


    init_labyrinthe(&labyrinthe , renderer);
    aleatoireLigne = aleatoire(labyrinthe.hauteur);/*Case actuel*/
    aleatoireColonne = aleatoire(labyrinthe.longueur);
    labyrinthe.cellule[aleatoireLigne][aleatoireColonne].contenu[VISITE] = 1;/*On a visité la première case*/

    int xSuiv = 0, ySuiv = 0;
    melange(labyrinthe.direction , 4);
    for(i = 0 ; i < 4 ; i ++)
    {
        printf("Tab : %d\n" , labyrinthe.direction[i]);
    }

    if(tirer_direction(&labyrinthe, aleatoireColonne, aleatoireLigne, &xSuiv, &ySuiv, 0) == 1)/*On trouve la case suivante*/
        generer_labyrinthe(&labyrinthe, aleatoireColonne , aleatoireLigne, &xSuiv , &ySuiv);/*On génère le labyrinthe*/

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

        SDL_SetRenderDrawColor(renderer , 255, 255 , 255 ,0);

        SDL_RenderClear(renderer);

        afficher(&labyrinthe , renderer);

        SDL_RenderPresent(renderer);/*On met à jour*/
    }
    free(labyrinthe.cellule);
    SDL_DestroyTexture(labyrinthe.Mur[IMG_MUR_H]);/*Libération des textures*/
    SDL_DestroyTexture(labyrinthe.Mur[IMG_MUR_V]);

    liberation(window , renderer);

    return 0;
}

void afficher(Labyrinthe *labyrinthe , SDL_Renderer *renderer){

    afficher_labyrinthe(labyrinthe , renderer , 0 , 0);
    correction_affichage_labyrinthe(labyrinthe , renderer);
}

void liberation(SDL_Window *window , SDL_Renderer *renderer) {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
int aleatoire(int max)
{
    srand(time(NULL));
    return rand()%max;
}

void melange(int *direction , int taille)
{
    if(taille - 1 == 0)
    {
        return;
    }
    else
    {
        int nbAlea = rand() % (taille);
        int temp = direction[taille - 1];
        direction[taille - 1] = direction[nbAlea];
        direction[nbAlea] = temp;
        melange(direction , taille - 1);
    }
}
