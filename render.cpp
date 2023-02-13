#include <vector>
#include <algorithm>
#include <deque>
#include <string>
#include <ctime>

#include "render.hpp"
#include "apple.hpp"

SDL_Rect head{250, 250, 10, 10};
std::deque<SDL_Rect> body = {};

SDL_Rect PauseRect{110,180, 300,100};
SDL_Rect scoreRect{0, 0, 100, 20};
SDL_Rect endScreen{50, 70, 400, 200};
SDL_Rect endScreenContinue{50, 280, 400, 100};

bool bigAppleRen = false;
bool smallAppleRen = false;
bool paused = false;

int speed = 10;
int bodySize = 0;

RendererWindow::RendererWindow(int Width, int Height, const char *title)
{
    TTF_Init();
    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        Width,
        Height,
        SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cout << "Window was not created. " << SDL_GetError() << std::endl;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
    {
        std::cout << "Renderer was not created. " << SDL_GetError() << std::endl;
    }
}

void RendererWindow::exit()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

void RendererWindow::clearRenderer()
{
    SDL_RenderClear(renderer);
}

void RendererWindow::display()
{
    SDL_RenderPresent(renderer);
}

void RendererWindow::drawBackGround()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void RendererWindow::drawScore(int gameScore)
{
    TTF_Font *font = TTF_OpenFont("font/bit5x3.ttf",12);
    SDL_Color textColor = {255, 255, 255};
    const char *sscore = ("score: " + std::to_string(gameScore *10)).c_str();
    SDL_Surface *tempsurf = TTF_RenderText_Solid(font, sscore, textColor);
    SDL_Texture *scoretext = SDL_CreateTextureFromSurface(renderer, tempsurf);
    SDL_RenderCopy(renderer, scoretext, NULL, &scoreRect);
    SDL_DestroyTexture(scoretext);
    SDL_FreeSurface(tempsurf);
}

void RendererWindow::drawSnake(SDL_Rect *head, std::deque<SDL_Rect> *body)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer,head);
    for_each((*body).begin(), (*body).end(), [&](SDL_Rect &cell)
    {
        SDL_RenderFillRect(renderer,&cell);
    });
}

void RendererWindow::drawApple(SDL_Rect *apple, std::vector<Uint8> RGB)
{
    SDL_SetRenderDrawColor(renderer, RGB[0], RGB[1], RGB[2], 255);
    SDL_RenderFillRect(renderer, apple);
}

// void RendererWindow::update()
// {
//     body.push_front(head);
//     while (body.size() > bodySize)
//         body.pop_back();
// }

// void RendererWindow::checkCollisionApple()
// {
//     if (redApple.getx() == head.x && redApple.gety() == head.y)
//     {
//         bodySize += 2;
//         redApple.setx((rand() % 40 + 1) * 10);
//         redApple.sety((rand() % 40 + 1) * 10);
//     }
//     std::for_each(body.begin(), body.end(), [&](SDL_Rect &cell)
//     {
//         if(cell.x == redApple.getx() && cell.y == redApple.gety())
//         {
//             bodySize+= 2;
//             redApple.setx((rand() % 40 + 1) * 10);
//             redApple.sety((rand() % 40 + 1) * 10);
//         }
//     });
// }

// void RendererWindow::checkCollisionBigApple()
// {
//     if(bigApple.getx() + bigApple.getw()/2 >= head.x && bigApple.getx() <= head.x + head.w
//     && bigApple.gety() + bigApple.geth()/2 >= head.y && bigApple.gety() <= head.y + head.h && bigAppleRen)
//     {
//         bodySize += 8;
//         bigApple.setx((rand() % 40 + 1) *10);
//         bigApple.sety((rand() % 40 + 1) *10);
//         bigAppleRen = false;
//     }
// }

bool RendererWindow::pause()
{
    paused = paused == true ? false : true;   
    if(paused)
        return 1;
    else
        return 0;
}

void RendererWindow::pauseMenu()
{
    TTF_Font *font = TTF_OpenFont("font/bit5x3.ttf",12);
    SDL_Color textColor = {255, 255, 255};
    SDL_Surface *tempsurf = TTF_RenderText_Solid(font,"Paused",textColor);
    SDL_Texture *pause = SDL_CreateTextureFromSurface(renderer,tempsurf);
    SDL_RenderCopy(renderer, pause, NULL, &PauseRect);
    SDL_FreeSurface(tempsurf);
    SDL_DestroyTexture(pause);
}

void RendererWindow::deathMenu()
{
    TTF_Font *font = TTF_OpenFont("font/bit5x3.ttf",12);
    SDL_Color textColor = {255, 255, 255};
    SDL_Surface *tmpsurf = TTF_RenderText_Solid(font, "Game Over", textColor);
    SDL_Surface *tmpsurf2 = TTF_RenderText_Solid(font, "Press R to Restart..", textColor);
    SDL_Texture *end = SDL_CreateTextureFromSurface(renderer, tmpsurf);
    SDL_Texture *endContinue = SDL_CreateTextureFromSurface(renderer, tmpsurf2);
    SDL_RenderCopy(renderer, end, NULL, &endScreen);
    SDL_RenderCopy(renderer, endContinue, NULL, &endScreenContinue);
    SDL_FreeSurface(tmpsurf);
    SDL_FreeSurface(tmpsurf2);
    SDL_DestroyTexture(end);
    SDL_DestroyTexture(endContinue);
}