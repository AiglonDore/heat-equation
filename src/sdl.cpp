/**
 * @file sdl.cpp
 * @author Thomas Roiseux
 * @brief Implements {@link sdl.h}.
 * @version 0.1
 * @date 2022-12-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../header/sdl.h"
#include "../header/exn.h"

Sdl::Sdl(/* args */)
{
}

Sdl::~Sdl()
{
}

void Sdl::SdlBarRunWindow(const Bar& bar, const std::vector<double>& time, const std::vector<double>& position, std::vector<std::vector<double>>& sol)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        throw Exn((std::string("SDL_Init Error: ") + SDL_GetError()).c_str());
    }
    SDL_Window* window = SDL_CreateWindow("Heat equation solution for a bar", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event event;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, 0, 240, 640, 240);
        SDL_RenderDrawLine(renderer, 320, 0, 320, 480);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}