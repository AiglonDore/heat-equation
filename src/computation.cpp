/**
 * @file computation.cpp
 * @author Thomas Roiseux
 * @brief  Implements {@link computation.h}.
 * @version 0.1
 * @date 2022-12-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../header/computation.h"
#include "../header/sdl.h"
#include "../header/exn.h"

#include <map>
#include <thread>
#include <iostream>
#include <fstream>

void solveBar(const Bar &bar, const std::string& filename, bool nogui)
{
    double tMax = bar.getTMax();
    double L = bar.getL();
    
    std::vector<double> time;
    std::vector<double> position;
    std::vector<std::vector<double>> sol;

    double dt = tMax / 1000;
    std::thread timeThread([&time, tMax, dt]()
    {
        for (double t = 0; t <= tMax; t += dt)
        {
            time.push_back(t);
        }
    });
    std::thread positionThread([&position, L]()
    {
        for (double x = 0; x <= L; x += L / 1000)
        {
            position.push_back(x);
        }
    });
    timeThread.join();
    positionThread.join();

    bar.solve(time, position, sol);

    std::cout << "Solution computed." << std::endl;
    if (filename != "")
    {
        std::ofstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Unable to open file " + filename);
        }

        for (size_t i = 0; i < position.size(); i++)
        {
            file << position[i] << ",";
        }
        file << std::endl;
        
        for (size_t i = 0; i < time.size(); i++)
        {
            file << time[i] << ",";
            for (size_t j = 0; j < position.size(); j++)
            {
                file << sol[i][j] << ",";
            }
            file << std::endl;
        }
        file.close();
        std::cout << "Solution saved in " << filename << std::endl;
    }

    if (!nogui)
    {
        std::cout << "Displaying solution in GUI..." << std::endl;
        std::cout << "Initializing SDL..." << std::endl;
        Sdl::SdlBarRunWindow(bar, time, position, sol);
    }
    else
    {
        std::cout << "Displaying solution in console..." << std::endl;
        for (size_t i = 0; i < position.size(); i++)
        {
            std::cout << position[i] << ",";
        }
        std::cout << std::endl;
        
        for (size_t i = 0; i < time.size(); i++)
        {
            std::cout << time[i] << ",";
            for (size_t j = 0; j < position.size(); j++)
            {
                std::cout << sol[i][j] << ",";
            }
            std::cout << std::endl;
        }
    }
}

void solvePlate(const Plate &plate, const std::string& filename, bool nogui)
{
    double tMax = plate.getTMax();
    double L = plate.getL();
    
    std::vector<double> time;
    std::vector<double> positionX;
    std::vector<double> positionY;
    std::vector<std::vector<double>> sol;

    double dt = tMax / 1000;
    std::thread timeThread([&time, tMax, dt]()
    {
        for (double t = 0; t <= tMax; t += dt)
        {
            time.push_back(t);
        }
    });
    std::thread positionXThread([&positionX, L]()
    {
        for (double x = 0; x <= L; x += L / 1000)
        {
            positionX.push_back(x);
        }
    });
    std::thread positionYThread([&positionY, L]()
    {
        for (double y = 0; y <= L; y += L / 1000)
        {
            positionY.push_back(y);
        }
    });
    timeThread.join();
    positionXThread.join();
    positionYThread.join();

    plate.solve(time, positionX, positionY, sol);

    std::cout << "Solution computed." << std::endl;
    if (filename != "")
    {
        std::ofstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Unable to open file " + filename);
        }

        for (size_t i = 0; i < positionX.size(); i++)
        {
            file << positionX[i] << ",";
        }
        file << std::endl;
        
        for (size_t i = 0; i < positionY.size(); i++)
        {
            file << positionY[i] << ",";
        }
        file << std::endl;
        
        for (size_t i = 0; i < time.size(); i++)
        {
            file << time[i] << ",";
            for (size_t j = 0; j < positionX.size(); j++)
            {
                for (size_t k = 0; k < positionY.size(); k++)
                {
                    file << sol[i][j * positionY.size() + k] << ",";
                }
            }
            file << std::endl;
        }
        file.close();
        std::cout << "Solution saved in " << filename << std::endl;
    }
    if (!nogui)
    {
        std::cout << "Displaying solution in GUI..." << std::endl;
        std::cout << "Initializing SDL..." << std::endl;
        std::vector<std::vector<std::vector<double>>> solForSDL;
        for (size_t i = 0; i < time.size(); i++)
        {
            std::vector<std::vector<double>> solForSDLi;
            for (size_t j = 0; j < positionX.size(); j++)
            {
                std::vector<double> solForSDLij;
                for (size_t k = 0; k < positionY.size(); k++)
                {
                    solForSDLij.push_back(sol[i][j * positionY.size() + k]);
                }
                solForSDLi.push_back(solForSDLij);
            }
            solForSDL.push_back(solForSDLi);
        }
        Sdl::SdlBarRunWindow(plate, time, positionX, positionY, solForSDL);
    }
    else
    {
        std::cout << "Displaying solution in console..." << std::endl;
        for (size_t i = 0; i < positionX.size(); i++)
        {
            std::cout << positionX[i] << ",";
        }
        std::cout << std::endl;
        
        for (size_t i = 0; i < positionY.size(); i++)
        {
            std::cout << positionY[i] << ",";
        }
        std::cout << std::endl;
        
        for (size_t i = 0; i < time.size(); i++)
        {
            std::cout << time[i] << ",";
            for (size_t j = 0; j < positionX.size(); j++)
            {
                for (size_t k = 0; k < positionY.size(); k++)
                {
                    std::cout << sol[i][j * positionY.size() + k] << ",";
                }
            }
            std::cout << std::endl;
        }
    }
}
