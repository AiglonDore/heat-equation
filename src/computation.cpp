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

#include <thread>
#include <iostream>
#include <fstream>

void solveBar(const Bar &bar, const std::string& filename, bool nogui)
{
    double tMax = bar.getTMax();
    std::vector<double> time;
    double dt = tMax / 1000;
    for (double t = 0; t <= tMax; t += dt)
    {
        time.push_back(t);
    }

    unsigned int nbThreadsAvailable = std::thread::hardware_concurrency();
    std::cout << "Computing solution using " << nbThreadsAvailable << " threads." << std::endl;
    std::vector<std::thread> threads(nbThreadsAvailable);

    

    for (unsigned int i = 0; i < nbThreadsAvailable; i++)
    {
        threads[i].join();
    }

    std::cout << "Solution computed." << std::endl;
    if (filename != "")
    {
        std::ofstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Unable to open file " + filename);
        }
        file.close();
        std::cout << "Solution saved in " << filename << std::endl;
    }
}