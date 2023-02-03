#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>



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
                if(event.key.keysym.sym == SDLK_d) {if(dir != LEFT) dir = RIGHT;}
                if(event.key.keysym.sym == SDLK_a) {if(dir != RIGHT) dir = LEFT;}
                if(event.key.keysym.sym == SDLK_w) {if (dir != DOWN) dir = UP;}
                if(event.key.keysym.sym == SDLK_s) {if (dir != UP) dir = DOWN;}
            }
        }
        switch(dir)
            {
                case RIGHT: if(dir != LEFT) window.moveRight(); break;
                case LEFT: if(dir != RIGHT) window.moveLeft(); break;
                case UP: if (dir != DOWN) window.moveUp(); break;
                case DOWN: if (dir != UP) window.moveDown(); break;
            }
        
        window.drawBackGround();
        window.clearRenderer();
        window.drawHead();
        window.drawApple();
        window.checkCollisionApple();
        window.checkCollisionBody();
        window.growBody();
        window.update();
        window.display();
        SDL_Delay(40);
    }
    window.exit();
    SDL_Quit();
    return 0;
}
