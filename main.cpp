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
    int fps = 25;
    int dt = 1000/fps;
    while(gamerunning)
    {   
        int startloop = SDL_GetTicks();
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
        window.checkCollisionBody();
        window.checkCollisionApple();
        window.checkCollisionBigApple();
        window.update();
        window.clearRenderer();
        window.draw();
        window.display();
        int delta = SDL_GetTicks() - startloop;
        if(delta < dt)
            SDL_Delay((dt - delta));
    }
    window.exit();
    SDL_Quit();
    return 0;
}
