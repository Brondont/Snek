#include "player.hpp"
#include "algorithm"
#include <string>
#include <SDL2/SDL_mixer.h>

Snake::Snake(int xpos, int ypos, int width, int height)
{
    Head.x = xpos;
    Head.y = ypos;
    Head.w = width;
    Head.h = height;
}

void Snake::moveUp()
{
    if (Head.y <= 0)
        Head.y = 500;
    Head.y -= speed;
}

void Snake::moveDown()
{
    if (Head.y >= 490)
        Head.y = -10;
    Head.y += speed;
}

void Snake::moveLeft()
{
    if (Head.x <= 0)
        Head.x = 500;
    Head.x -= speed;
}

void Snake::moveRight()
{
    if (Head.x >= 490)
        Head.x = -10;
    Head.x += speed;
}

SDL_Rect *Snake::getHead()
{
    return &Head;
}

std::deque<SDL_Rect> *Snake::getBody()
{
    return &Body;
}

int Snake::getSize()
{
    return size;
}

void Snake::setx(int x)
{
    Head.x = x;
}

void Snake::sety(int y)
{
    Head.y = y;
}

void Snake::resetSize()
{
    size = 0;
}

void Snake::checkCollisionWith(Apple *apple, bool *bigAppleTrue)
{
    // head collision with apple
    if(apple->getType() == "Red")
    {
        Mix_Chunk *redAppleSound = Mix_LoadWAV("sounds/redApple.wav");

        if (Head.x == apple->getx() && Head.y == apple->gety())
        {
            Mix_PlayChannel(-1, redAppleSound, 0);
            size += 2;
            apple->setx((rand()%40 + 1) * 10);
            apple->sety((rand()%40 + 1) * 10);
        }
        std::for_each(Body.begin(), Body.end(), [&](SDL_Rect &cell)
                    {
                        if(cell.x == apple->getx() && cell.y == apple->gety())
                        {
                            Mix_PlayChannel(-1, redAppleSound, 0);
                            size += 2;
                            apple->setx((rand()%40 + 1) * 10);
                            apple->sety((rand()%40 + 1) * 10);
                        } 
            });
    }else
    {
        Mix_Chunk *bigAppleSound = Mix_LoadWAV("sounds/bigApple.wav");

        if (Head.x <= apple->getx() + apple->getw()/2 && Head.x >= apple->getx()
        && Head.y <= apple->gety() + apple->getw()/2 && Head.y >= apple->gety())
        {
            Mix_PlayChannel(-1, bigAppleSound, 0);
            size += 8;
            *bigAppleTrue = false;
            apple->setx((rand()%40 + 1) * 10);
            apple->sety((rand()%40 + 1) * 10);
        }
        std::for_each(Body.begin(), Body.end(), [&](SDL_Rect &cell)
                    {
                        if (cell.x <= apple->getx() + apple->getw()/2 && cell.x >= apple->getx()
                        && cell.y <= apple->gety() + apple->getw()/2 && cell.y >= apple->gety())
                        {
                            Mix_PlayChannel(-1, bigAppleSound, 0);
                            size += 8;
                            *bigAppleTrue = false;
                            apple->setx((rand()%40 + 1) * 10);
                            apple->sety((rand()%40 + 1) * 10);
                        } 
            });
    }
}

void Snake::update()
{
    Body.push_front(Head);
    while (Body.size() > size)
        Body.pop_back();
}

bool Snake::Death()
{
    bool dead = false;
    Mix_Chunk *deathSound = Mix_LoadWAV("sounds/death.wav");
    for (int i = 1; i < Body.size(); i++)
    {
        if (Head.x == Body[i].x && Head.y == Body[i].y)
        {
            Mix_PlayChannel(-1, deathSound, 0);
            dead = true;
        }
    };
    return dead;
}