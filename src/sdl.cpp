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

double max(const std::vector<double> &v)
{
    double max = v[0];
    for (size_t i = 1; i < v.size(); i++)
    {
        if (v[i] > max)
        {
            max = v[i];
        }
    }
    return max;
}

void Sdl::SdlBarRunWindow(const Bar &bar, const std::vector<double> &time, const std::vector<double> &position, std::vector<std::vector<double>> &sol)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        throw Exn((std::string("SDL_Init Error: ") + SDL_GetError()).c_str());
    }
    SDL_Window *window = SDL_CreateWindow("Heat equation solution for a bar", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event event;
    bool quit = false;
    bool plot = false;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (!plot)
            {
                for (size_t i = 0; i < time.size(); i += 10)
                {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderClear(renderer);
                    double maxItem = max(sol[i]);
                    for (size_t j = 0; j < position.size() - 1; j++)
                    {
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderDrawLine(renderer, position[j] * 1280 / bar.getL(), sol[i][j] * 720 / maxItem, position[j + 1] * 1280 / bar.getL(), sol[i][j + 1] * 720 / maxItem);
                        SDL_RenderPresent(renderer);
                    }
                }
                plot = true;
            }
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Sdl::SdlBarRunWindow(const Plate &plate, const std::vector<double> &time, const std::vector<double> &positionX, const std::vector<double> &positionY, std::vector<std::vector<std::vector<double>>> &sol)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        throw Exn((std::string("SDL_Init Error: ") + SDL_GetError()).c_str());
    }
}