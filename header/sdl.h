/**
 * @file sdl.h
 * @author Thomas Roiseux
 * @brief Provides an interface to use the SDL library.
 * @version 0.1
 * @date 2022-12-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SDL_H
#define SDL_H

#include <SDL2/SDL.h>
#include <vector>
#include "bar.h"
#include "plate.h"


/**
 * @brief Class for the SDL library.
 * 
 */
class Sdl
{
private:
    /* data */
public:
    /**
     * @brief Construct a new Sdl object.
     * 
     */
    Sdl(/* args */);
    /**
     * @brief Destroy the Sdl object.
     * 
     */
    ~Sdl();
    /**
     * @brief Run the SDL window.
     * @throws Exn if the window cannot be created.
     * @param bar Bar.
     * @param time Time values.
     * @param position Position values.
     * @param sol Solution.
     */
    static void SdlBarRunWindow(const Bar& bar, const std::vector<double>& time, const std::vector<double>& position, std::vector<std::vector<double>>& sol);
    ~Sdl();
    /**
     * @brief Run the SDL window.
     * @throws Exn if the window cannot be created.
     * @param plate Plate.
     * @param time Time values.
     * @param positionX Position values along x.
     * @param positionY Position values along y.
     * @param sol Solution.
     */
    static void SdlBarRunWindow(const Plate& plate, const std::vector<double>& time, const std::vector<double>& positionX, const std::vector<double>& positionY, std::vector<std::vector<std::vector<double>>>& sol);
};

#endif // SDL_H