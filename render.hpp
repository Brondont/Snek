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
    void drawBackGround();
    void display();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void exit();
};