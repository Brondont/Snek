#include "render.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <deque>
#include <string>

SDL_Rect head{250, 250, 10, 10};
SDL_Rect apple{(rand() % 40 + 1)*10, (rand() % 40 + 1)*10, 10, 10};
SDL_Rect score{0, 0, 100, 20};
int speed = 10;
std::deque<SDL_Rect> body ={}; 

int bodySize = 1;
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

void RendererWindow::moveDown()
{
    if (head.y >= 500)
        head.y = 0;
    head.y += speed;
}

void RendererWindow::moveUp()
{
    if (head.y <= 0)
        head.y = 500;
    head.y -= speed;
}

void RendererWindow::moveLeft()
{
    if (head.x <= 0)
        head.x = 500;
    head.x -= speed;
}

void RendererWindow::moveRight()
{
    if (head.x >= 500)
        head.x = 0;
    head.x += speed;
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

void RendererWindow::draw()
{
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &apple);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &head);
    if(bodySize > 1)
    {
    std::for_each(body.begin(), body.end(), [&](SDL_Rect &cell){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &cell);
    });}
    TTF_Font *textfont = TTF_OpenFont("font/bit5x3.ttf", 12);
    SDL_Color textColor = {255, 255, 255};
    const char *sscore = ("score: " + std::to_string(bodySize*10)).c_str();
    SDL_Surface *tempsurf = TTF_RenderText_Solid(textfont, sscore, textColor);
    SDL_Texture *scoretext = SDL_CreateTextureFromSurface(renderer, tempsurf);
    SDL_RenderCopy(renderer, scoretext, NULL, &score);
    SDL_DestroyTexture(scoretext);
    SDL_FreeSurface(tempsurf);
}
void RendererWindow::update()
{
    srand(time(nullptr));
    //grow body
    if(bodySize < 2) return;
    body.push_front(head);
    while(body.size() > bodySize)
        body.pop_back();
}

void RendererWindow::checkCollisionApple()
{
    if (apple.x == head.x && apple.y == head.y)
    {
        bodySize++;
        apple.x = (rand() % 40 + 1)*10;
        apple.y = (rand() % 40 + 1)*10;
    }
}


void RendererWindow::checkCollisionBody()
{
    std::for_each(body.begin(), body.end(), [&](SDL_Rect &cell){
        if(head.x == cell.x && head.y == cell.y)
        {
            bodySize =1;
            
        }
        
    });
}