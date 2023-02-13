#include "apple.hpp"


Apple::Apple(std::string Type,int xpos, int ypos, int width, int height, Uint8 R, Uint8 G, Uint8 B)
{
    appleRect.x = xpos;
    appleRect.y = ypos;
    appleRect.h = height;
    appleRect.w = width;
    color.push_back(R);
    color.push_back(G);
    color.push_back(B);
    type = Type;
}

int Apple::getx()
{
    return appleRect.x;
}
   
int Apple::gety()
{
    return appleRect.y;
}

int Apple::getw()
{
    return appleRect.w;
}

int Apple::geth()
{
    return appleRect.h;
}

SDL_Rect *Apple::getRect()
{
    return &appleRect;
}

void Apple::setx(int x)
{
    appleRect.x = x;
}
   
void Apple::sety(int y)
{
    appleRect.y = y;
}

std::vector<Uint8> Apple::getColor()
{
    return color;
}

std::string Apple::getType()
{
    return type;
}