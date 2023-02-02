#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "render.hpp"

const int HEIGHT = 500, WIDTH = 500;
bool gamerunning = false;

int main(int argc, char *argv[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING) > 0)
    {
        std::cout << "SDL elemetns did not intialzie" << std::endl;
        return -1;
    }

    RendererWindow window = RendererWindow(WIDTH,HEIGHT,"Game");
    gamerunning = true;
    SDL_Event event;

    enum Direction {
        DOWN,
        UP,
        LEFT,
        RIGHT
    };
    int dir = 0;
    while(gamerunning)
    {   
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT) {gamerunning = false;}
            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_d) {dir = RIGHT;}
                if(event.key.keysym.sym == SDLK_a) {dir = LEFT;}
                if(event.key.keysym.sym == SDLK_w) {dir = UP;}
                if(event.key.keysym.sym == SDLK_s) {dir = DOWN;}
            }
        }
        switch(dir)
            {
                case RIGHT: window.moveRight(); break;
                case LEFT: window.moveLeft(); break;
                case UP: window.moveUp(); break;
                case DOWN: window.moveDown(); break;
            }
        
        window.drawBackGround();
        window.clearRenderer();
        window.drawHead();
        window.display();
        SDL_Delay(25);
    }
    window.exit();
    SDL_Quit();
    return 0;
}
