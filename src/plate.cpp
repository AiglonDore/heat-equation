/**
 * @file plate.cpp
 * @author Thomas Roiseux
 * @brief Implements {@link plate.h}.
 * @version 0.1
 * @date 2022-12-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../header/plate.h"

Plate::Plate(double u0, double L, double tMax, double f, const std::string& material) : u0(u0), L(L), tMax(tMax), f(f), material(material)
{
    F = [tMax, f, L](double x, double y) -> double {
        if (L / 6 <= x && x <= 2 * L / 6 && L / 6 <= y && y <= 2 * L / 6)
            return tMax * f * f;
        else if (4 * L / 6 <= x && x <= 5 * L / 6 && L / 6 <= y && y <= 2 * L / 6)
            return tMax * f * f;
        else if (L / 6 <= x && x <= 2 * L / 6 && 4 * L / 6 <= y && y <= 5 * L / 6)
            return tMax * f * f;
        else if (4 * L / 6 <= x && x <= 5 * L / 6 && 4 * L / 6 <= y && y <= 5 * L / 6)
            return tMax * f * f;
        else
            return 0.0;
    };
}

Plate::~Plate()
{
}

void Plate::solve(const std::vector<double>& time, const std::vector<double>& positionX, const std::vector<double>& positionY, std::vector<std::vector<double>>& sol) const
{

}