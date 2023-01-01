/**
 * @file utils.cpp
 * @author Thomas Roiseux
 * @brief Implements {@link utils.h}.
 * @version 0.1
 * @date 2023-01-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../header/utils.h"
#include "../header/exn.h"

void addVector(std::vector<double>& v1, const std::vector<double>& v2)
{
    if (v1.size() != v2.size())
    {
        throw Exn("Vectors have different sizes.");
    }
    for (size_t i = 0; i < v1.size(); i++)
    {
        v1[i] += v2[i];
    }
}

void luDecomp(const std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& L, std::vector<std::vector<double>>& U)
{
    size_t n = A.size();
    for (size_t i = 0; i < n; i++)
    {
        L[i][i] = 1.0;
    }
    for (size_t i = 0; i < n - 1; i++)
    {
        for (size_t j = i; j < n; j++)
        {
            double tmp = 0.0;

            if (i != 0)
            {
                for (size_t k = 0; k < i - 1; k++)
                {
                    tmp += L[i][k] * U[k][j];
                }
            }
            
            U[i][j] = (A[i][j]) - tmp;
        }
        for (size_t j = i + 1; j < n; j++)
        {
            double tmp = 0.0;
            if (i != 0)
            {
                for (size_t k = 0; k < i - 1; k++)
                {
                    tmp += L[j][k] * U[k][i];
                }
            }
            L[j][i] = (A[j][i] - tmp) / U[i][i];
        }
    }
    U[n - 1][n - 1] = A[n - 1][n - 1];
    for (size_t k = 0; k < n - 1; k++)
    {
        U[n - 1][n - 1] -= L[n - 1][k] * U[k][n - 1];
    }
}

void luSolve(const std::vector<std::vector<double>>& L, const std::vector<std::vector<double>>& U, const std::vector<double>& b, std::vector<double>& x)
{
    if (U.size() != b.size())
    {
        throw Exn("Matrix and vector sizes do not match.");
    }

    std::vector<double> y(b.size(), 0);

    for (size_t i = 0; i < U.size(); i++)
    {
        double tmp = 0.0;
        for (size_t j = 0; j < i; j++)
        {
            tmp += L[i][j] * y[j];
        }
        y[i] = b[i] - tmp;
    }

    for (size_t i = U.size(); i >= 1; i--)
    {
        double tmp = 0.0;
        for (size_t j = i; j < U.size() - 1; j++)
        {
            tmp += U[i - 1][j] * x[j];
        }
        x[i - 1] = (y[i - 1] - tmp) / U[i - 1][i - 1];
    }
}