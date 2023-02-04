#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

class RendererWindow
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;

public:
    RendererWindow(int Width, int Height, const char *title);
    void clearRenderer();
    void checkCollisionApple();
    void checkCollisionBody();
    void drawBackGround();
    void draw();
    void display();
    void moveLeft();
    void growBody();
    void update();
    void moveRight();
    void moveUp();
    void moveDown();
    void exit();
};