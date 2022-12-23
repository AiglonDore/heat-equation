/**
 * @file bar.cpp
 * @author Thomas Roiseux
 * @brief Implements {@link bar.h}.
 * @version 0.1
 * @date 2022-12-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
 * @brief Number of points for the solution.
*/
#define N 1001

#include "../header/bar.h"
#include "../header/exn.h"
#include "../header/materials.h"

#include <thread>

Bar::Bar(double u0, double L, double tMax, double f, const std::string& material) : u0(u0), L(L), tMax(tMax), f(f), material(material)
{
    if (!Material::isMaterial(material))
    {
        throw Exn("Material not found.");
    }
    F = [f, L, tMax](double x) -> double {
        if (x >= L / 10 && x <= 2 * L / 10)
        {
            return tMax * f * f;
        }
        else if (x >= 5 * L / 10 && x <= 6 * L / 10)
        {
            return 0.75 * tMax * f * f;
        }
        else
        {
            return 0.0;
        }
    };
}

Bar::~Bar()
{
}

void Bar::solve(const std::vector<double>& time, const std::vector<double> position, std::vector<std::vector<double>>& sol, size_t index) const
{
    const Material& mat = Material::materials[material];
}

void Bar::solveBar(const Bar& bar, const std::vector<double>& time, const std::vector<double> position, std::vector<std::vector<double>>& sol, size_t index)
{
    for (size_t i = index; i < time.size(); i += std::thread::hardware_concurrency())
    {
        bar.solve(time, position, sol, i);
    }
}