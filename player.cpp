#include "player.hpp"
#include "algorithm"
#include <string>

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

void Snake::checkCollisionWith(Apple *apple)
{
    // head collision with apple
    if (Head.x == (*apple).getx() && Head.y == (*apple).gety())
    {
        size += 2;
        (*apple).setx((rand() % 40 + 1) * 10);
        (*apple).sety((rand() % 40 + 1) * 10);
    }
    std::for_each(Body.begin(), Body.end(), [&](SDL_Rect &cell)
                  {
        if(cell.x == (*apple).getx() && cell.y == (*apple).gety())
        {
            size += 2;
            (*apple).setx((rand()%40 + 1) * 10);
            (*apple).sety((rand()%40 + 1) * 10);
        } });
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
    for (int i = 1; i < Body.size(); i++)
    {
        if (Head.x == Body[i].x && Head.y == Body[i].y)
        {
            dead = true;
        }
    };
    return dead;
}