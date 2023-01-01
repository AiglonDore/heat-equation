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
    std::vector<double> C(position.size());
    sol.resize(time.size());

    for (size_t i = 0; i < sol.size(); i++)
    {
        sol[0][i] = u0;
        sol[i][sol[i].size() - 1] = u0;
        sol[i][0] = u0;
    }

    std::thread cThread([this, &time, &position, &C, &mat](){
        for (size_t i = 0; i < position.size(); i++)
        {
            C[i] = (time[1] - time[0]) * this->F(position[i]) / (mat.getDensity() * mat.getSpecificHeatCapacity());
        };
    });

    std::vector<std::vector<double>> A(position.size(), std::vector<double>(position.size(), 0));

    std::thread aThread([this, &time, &A, &mat](){
        const double dt = time[1] - time[0];
        const double coef = mat.getThermalConductivity() / (mat.getDensity() * mat.getSpecificHeatCapacity());
        for (size_t i = 0; i < A.size(); i++)
        {
            A[i][i] = 1 + 2 * dt * coef;
            if (i > 0)
            {
                A[i][i - 1] = -dt * coef;
            }
            if (i < A.size() - 1)
            {
                A[i][i + 1] = -dt * coef;
            }
        }        
    });

    cThread.join();
    aThread.join();

    std::vector<std::vector<double>> L(A.size(), std::vector<double>(A.size(), 0));
    std::vector<std::vector<double>> U(A.size(), std::vector<double>(A.size(), 0));
    luDecomp(A, L, U);
    for (size_t i = 0; i < time.size() - 1; i++)
    {
        std::vector<double> values(sol[i]);
        addVector(values, C);
        luSolve(L, U, values, values);
        values[values.size() - 1] = u0;
        sol[i + 1] = values;
    }
}