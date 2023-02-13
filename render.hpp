#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <deque>

class RendererWindow
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;

public:
    RendererWindow(int Width, int Height, const char *title);
    void clearRenderer();
    void drawBackGround();
    void drawSnake(SDL_Rect *head, std::deque<SDL_Rect> *body);
    void drawApple(SDL_Rect *apple, std::vector<Uint8> RGB);
    void drawScore(int gameScore);
    void display();
    bool pause();
    void pauseMenu();
    void deathMenu();
    void exit();
};