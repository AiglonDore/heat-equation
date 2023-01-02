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

#include "../header/bar.h"
#include "../header/exn.h"
#include "../header/materials.h"
#include "../header/utils.h"

#include <thread>
#include <map>
#include <iostream>

Bar::Bar(double u0, double L, double tMax, double f, const std::string &material) : u0(u0), L(L), tMax(tMax), f(f), material(material)
{
    if (!Material::isMaterial(material))
    {
        throw Exn("Material not found.");
    }
    F = [f, L, tMax](double x) -> double
    {
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

void Bar::solve(const std::vector<double> &time, const std::vector<double> &position, std::vector<std::vector<double>> &sol) const
{
    const Material &mat = Material::materials[material];
    sol.resize(time.size());
    for (size_t i = 0; i < time.size(); i++)
    {
        sol[i].resize(position.size());
        sol[0][i] = u0;
        sol[i][position.size() - 1] = u0;
    }
    const double dx = position[1] - position[0];
    
    const double dt = time[1] - time[0];
    const double a = - (2 * mat.getThermalConductivity() / (mat.getDensity() * mat.getSpecificHeatCapacity() * dx * dx) + 1 / dt);
    const double b = mat.getThermalConductivity() / (mat.getDensity() * mat.getSpecificHeatCapacity() * dx * dx);

    std::vector<std::vector<double>> A(position.size(), std::vector<double>(position.size(), 0.0));

    std::thread aThread([this, &a,&b, &A](){
        for (size_t i = 0; i < A.size(); i++)
        {
            A[i][i] = a;
            if (i > 0)
            {
                A[i][i - 1] = b;
            }
            if (i < A.size() - 1)
            {
                A[i][i + 1] = b;
            }
        }
    });
    std::vector<double> C(position.size(), 0.0);
    std::thread cThread([this, &mat, &C, &position](){
        for (size_t i = 0; i < C.size(); i++)
        {
            C[i] =  -1 / (mat.getDensity() * mat.getSpecificHeatCapacity()) * this->F(position[i]);
        }
    });
    

    std::vector<double> B(position.size(), 0.0);
    B[position.size() - 1] = - b * u0;
    B[0] = -b * u0;

    aThread.join();
    cThread.join();

    std::vector<std::vector<double>> l(time.size(),std::vector<double>(time.size(), 0.0)), u(time.size(),std::vector<double>(time.size(), 0.0));
    luDecomp(A, l, u);
    for (size_t i = 0; i < time.size() - 1; i++)
    {
        std::vector<double> values(sol[i]);
        std::vector<double> result(sol[i].size());
        for (size_t i = 0; i < values.size(); i++)
        {
            values[i] *= -1 / dt;
            values[i] += B[i] + C[i];
        }
        luSolve(l, u, values, result);
        sol[i + 1] = result;
    }
}