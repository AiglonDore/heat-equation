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
 * @param time Vector of the time.
 * @param position Vector of the position.
 * @param mat Material.
 * @param AdAhn Matrix to fill.
 */
void makeAdAhn(const std::vector<double> time, const std::vector<double> position, const Material& mat, std::vector<std::vector<double>>& AdAhn)
{
    double dt = time[1] - time[0];
    double h = position[1] - position[0];
    AdAhn.clear();
    AdAhn.resize(position.size());
    const double coeff = mat.getThermalConductivity() / (mat.getDensity() * mat.getSpecificHeatCapacity()) * dt;
    for (size_t i = 0; i < position.size(); i++)
    {
        AdAhn[i].resize(position.size());
        AdAhn[i][i] = 1.0 + 2.0 * coeff / (h * h);
        if (i > 0)
        {
            AdAhn[i][i - 1] = -coeff / (h * h);
        }
        if (i < position.size() - 1)
        {
            AdAhn[i][i + 1] = -coeff / (h * h);
        }
    }
    // Inverting matrix
    
}

/**
 * @brief Compute the solution of the equation.
 * 
 * @param mat Matrix of the equation.
 * @param vec Vector of the equation.
 * @param sol Vector to fill.
 */
void computeTermSol(const std::vector<std::vector<double>>& mat, const std::vector<double>& vec, std::vector<double>& sol)
{
    sol.clear();
    sol.resize(vec.size());
    for (size_t i = 0; i < vec.size(); i++)
    {
        sol[i] = 0.0;
        for (size_t j = 0; j < vec.size(); j++)
        {
            sol[i] += mat[i][j] * vec[j];
        }
    }
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

void Bar::solve(const std::vector<double>& time, const std::vector<double>& position, std::vector<std::vector<double>>& sol) const
{
    const Material& mat = Material::materials[material];
    std::vector<std::vector<double>> AdAhn;
    std::thread adAhnThread(makeAdAhn, std::ref(time), std::ref(position), std::ref(mat), std::ref(AdAhn));
    std::vector<double> C;
    std::thread cThread(makeC, std::ref(position), std::ref(mat), std::ref(*this), std::ref(C));

    sol.clear();
    sol.resize(time.size());
    for (size_t i = 0; i < time.size(); i++)
    {
        sol[i].resize(position.size());
    }
    sol[0] = std::vector<double>(position.size(), u0);
    cThread.join();
    adAhnThread.join();
    std::vector<std::vector<double>> AdAhn2 = AdAhn;
    for (size_t i = 1; i < time.size(); i++)
    {
        AdAhn2[i][i] *= (time[1] - time[0]);
        if (i > 1)
        {
            AdAhn2[i][i - 1] *= (time[1] - time[0]);
        }
        if (i < time.size() - 1)
        {
            AdAhn2[i][i + 1] *= (time[1] - time[0]);
        }
    }
    for (size_t i = 1; i < time.size(); i++)
    {
        std::vector<double> termSol1;
        std::vector<double> termSol2;

        std::thread termSol1Thread(computeTermSol, std::ref(AdAhn), std::ref(sol[i - 1]), std::ref(termSol1));
        std::thread termSol2Thread(computeTermSol, std::ref(AdAhn2), std::ref(C), std::ref(termSol2));

        termSol1Thread.join();
        termSol2Thread.join();

        for (size_t j = 0; j < position.size(); j++)
        {
            sol[i][j] = termSol1[j] + termSol2[j];
        }
        sol[i][0] = 0;
        sol[i][position.size() - 1] = u0;
    }
}