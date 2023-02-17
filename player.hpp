#pragma once


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <algorithm>
#include <deque>
#include "apple.hpp"

class Snake{
private:
    SDL_Rect Head;
    std::deque<SDL_Rect> Body = {};
    int speed = 10;
    int size = 0;   
public:
    Snake(int xpos, int ypos, int width, int height);
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    bool Death();
    void checkCollisionWith(Apple *apple, bool *bigAppleTrue);
    void update();
    void resetSize();
    SDL_Rect *getHead();
    std::deque<SDL_Rect> *getBody();
    int getSize();
    void setx(int x);
    void sety(int y);
};