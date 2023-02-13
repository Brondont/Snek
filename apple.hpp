#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>


class Apple{
    private:
        SDL_Rect appleRect;
        std::vector<Uint8> color;
        std::string type;
    public:
    Apple(std::string Type, int xpos, int ypos, int width, int height, Uint8 R, Uint8 G, Uint8 B);
    Apple() = default;
    int getx();
    int gety();
    std::string getType();
    std::vector<Uint8> getColor();
    void setx(int x);
    void sety(int y);
    int getw();
    int geth();
    SDL_Rect *getRect();
};