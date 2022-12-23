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

/**
 * @brief Compute the C vector (second member of the equation).
 * 
 * @param position Vector of the position.
 * @param mat Material.
 * @param bar Bar.
 * @param C Vector to fill.
 */
void makeC(const std::vector<double>& position, const Material& mat, const Bar& bar, std::vector<double>& C)
{
    C.clear();
    C.resize(position.size());
    for (size_t i = 0; i < position.size(); i++)
    {
        C[i] = 1 / (mat.getDensity() * mat.getSpecificHeatCapacity() * bar(position[i]));
    }
}

/**
 * @brief Compute the AdAhn matrix (first member of the equation).
 * 
 * @param bar Bar.
 * @param time Vector of the time.
 * @param position Vector of the position.
 * @param mat Material.
 * @param AdAhn Matrix to fill.
 */
void makeAdAhn(const Bar& bar, const std::vector<double> time, const std::vector<double> position, const Material& mat, std::vector<std::vector<double>>& AdAhn)
{
    double dt = time[1] - time[0];
    double h = position[1] - position[0];
    AdAhn.clear();
    AdAhn.resize(position.size());
    for (size_t i = 0; i < position.size(); i++)
    {
        AdAhn[i].resize(position.size());
        AdAhn[i][i] = 1;
    }
    const double coeff = mat.getThermalConductivity() / (mat.getDensity() * mat.getSpecificHeatCapacity()) * dt;
}

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

void Bar::solve(const std::vector<double>& time, const std::vector<double> position, std::vector<std::vector<double>>& sol) const
{
    const Material& mat = Material::materials[material];
    std::vector<std::vector<double>> AdAhn;
    std::thread adAhnThread(makeAdAhn, std::ref(*this), std::ref(time), std::ref(position), std::ref(mat), std::ref(AdAhn));
    std::vector<double> C;
    std::thread cThread(makeC, std::ref(position), std::ref(mat), std::ref(*this), std::ref(C));
    cThread.join();
    adAhnThread.join();

    sol.clear();
    sol.resize(time.size());
    for (size_t i = 0; i < time.size(); i++)
    {
        sol[i].resize(position.size());
    }
    sol[0] = std::vector<double>(position.size(), u0);
}