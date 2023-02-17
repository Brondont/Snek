#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "render.hpp"
#include "apple.hpp"
#include "player.hpp"

const int HEIGHT = 500, WIDTH = 500;

enum Direction {
        DOWN,
        UP,
        LEFT,
        RIGHT
    };
    int game = 0;
    enum GameStatus {
        RUNNING,
        PAUSED,
        OVER
    };

    int dir = 2;
    int fps = 25;
    int dt = 1000/fps;
const Uint8 *keyboard = SDL_GetKeyboardState(NULL);

int InitGame()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    return true;
}

bool gamerunning = InitGame();

RendererWindow window(WIDTH,HEIGHT,"Snek");

Snake snek(250,250,10,10);
Apple redApple("Red", (rand() % 40 + 1) * 10, (rand() % 40 + 1) * 10, 10, 10, 255, 0, 0);
Apple bigApple("Big", (rand()% 40 +1) * 10, (rand() % 40 * 1 * 10), 20, 20, 255, 0, 255);
bool bigAppleSpawned = false;

void mainGameLoop()
{
    if(rand()%100 == 1)
        bigAppleSpawned = true;

    if(keyboard[SDL_SCANCODE_A])    if(dir != RIGHT)   dir = LEFT;
    if(keyboard[SDL_SCANCODE_D])    if(dir != LEFT)    dir = RIGHT;
    if(keyboard[SDL_SCANCODE_W])    if(dir != DOWN)    dir = UP;
    if(keyboard[SDL_SCANCODE_S])    if(dir != UP)      dir = DOWN;

    switch(dir)
        {
            case LEFT:  snek.moveLeft();  break;
            case RIGHT: snek.moveRight(); break;
            case UP:    snek.moveUp();    break;
            case DOWN:  snek.moveDown();  break;
        }
    if(snek.Death())
            {
                game = 2;
            }
    window.drawBackGround();
    window.clearRenderer();
    snek.checkCollisionWith(&redApple,NULL);
    if(bigAppleSpawned)
        snek.checkCollisionWith(&bigApple, &bigAppleSpawned);
    snek.update();
    window.drawSnake(snek.getHead(), snek.getBody());
    window.drawApple(redApple.getRect(), redApple.getColor());
    if(bigAppleSpawned)
        window.drawApple(bigApple.getRect(), bigApple.getColor());
    // window.drawApple(poisonApple.getRect(), poisonApple.getColor());
    window.drawScore(snek.getSize());
    window.display();
}

void resetGame()
{
    snek.setx(250);
    snek.sety(250);
    snek.resetSize();
    dir = 2;
}

void pauseMenu()
{
    window.pauseMenu();
    window.display();
}

void gameOver()
{
    window.drawBackGround();
    window.clearRenderer();
    window.deathMenu();
    window.drawScore(snek.getSize());
    window.display();
    if(keyboard[SDL_SCANCODE_R])
    {
        resetGame();
        game = 0;
    }
}

int main(int argc, char *argv[])
{
    srand(time(nullptr));
    while(gamerunning)
    {   
        int startloop = SDL_GetTicks();

        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                gamerunning = false;
        }
        if(keyboard[SDL_SCANCODE_P] && game != 2)    
        {   
            SDL_Delay(100);
            game = window.pause();
        }
        if(game == 0)
            mainGameLoop();
        else if(game == 1)
            pauseMenu();
        else if(game == 2)
            gameOver();

        int delta = SDL_GetTicks() - startloop;
        if(delta < dt)
            SDL_Delay((dt - delta));
    }
    window.exit();
    SDL_Quit();
    return 0;
}

