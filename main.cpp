#include <iostream>

#include "include/SDL2/SDL.h"

using namespace std;

int main(int argc, char** argv)
{

    SDL_Event event;

    int continuer = 1;

    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        cout << "Something went wrong! " << SDL_GetError() << endl;
    }

    SDL_Window* window = SDL_CreateWindow("SDL_Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          1280, 720, SDL_WINDOW_OPENGL);
    if(window == nullptr) {
        cout << "Something also went wrong here" << endl;
    }

    while(continuer)
    {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT :
                    continuer = 0;
                    break;
            }
        }
    }
    SDL_Quit();
    return 0;
}