#include "render.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <deque>

SDL_Rect head{250, 250, 10, 10};
SDL_Rect apple{(rand() % 40 + 1)*10, (rand() % 40 + 1)*10, 10, 10};
std::deque<SDL_Rect> body ={}; 

int bodySize = 1;
RendererWindow::RendererWindow(int Width, int Height, const char *title)
{
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
    head.y += 10;
}
void RendererWindow::moveUp()
{
    if (head.y <= 0)
        head.y = 500;
    head.y -= 10;
}
void RendererWindow::moveLeft()
{
    if (head.x <= 0)
        head.x = 500;
    head.x -= 10;
}
void RendererWindow::moveRight()
{
    if (head.x >= 500)
        head.x = 0;
    head.x += 10;
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
void RendererWindow::drawHead()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &head);
}
void RendererWindow::update()
{
    srand(time(nullptr));
    int i=10;
    if(bodySize > 1)
    {
    std::for_each(body.begin(), body.end(), [&](SDL_Rect &cell){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &cell);
    });}
}
void RendererWindow::drawApple()
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &apple);
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
void RendererWindow::growBody()
{
    if(bodySize < 2) return;
    body.push_front(head);
    while(body.size() > bodySize)
        body.pop_back();
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