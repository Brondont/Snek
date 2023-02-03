#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class RendererWindow
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;

public:
    RendererWindow(int Width, int Height, const char *title);
    void clearRenderer();
    void drawHead();
    void checkCollisionApple();
    void checkCollisionBody();
    void drawBackGround();
    void display();
    void moveLeft();
    void growBody();
    void drawApple();
    void update();
    void moveRight();
    void moveUp();
    void moveDown();
    void exit();
};