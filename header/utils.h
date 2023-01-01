/**
 * @file utils.h
 * @author Thomas Roiseux
 * @brief Provides utility functions.
 * @version 0.1
 * @date 2023-01-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef UTILS_H
#define UTILS_H

#include <vector>

/**
 * @brief Adds v2 to v1.
 * 
 * @param v1 First vector.
 * @param v2 Second vector.
 * @throws Exn if v1 and v2 have different sizes.
 */
void addVector(std::vector<double>& v1, const std::vector<double>& v2);

/**
 * @brief Computes LU decomposition.
 * 
 * @param A Matrix.
 * @param L Lower triangular matrix.
 * @param U Upper triangular matrix.
 */
void luDecomp(const std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& L, std::vector<std::vector<double>>& U);

/**
 * @brief Solves a linear system.
 * 
 * @param L Lower triangular matrix.
 * @param U Upper triangular matrix.
 * @param b Right-hand side.
 * @param x Solution.
 */
void luSolve(const std::vector<std::vector<double>>& L, const std::vector<std::vector<double>>& U, const std::vector<double>& b, std::vector<double>& x);

#endif // UTILS_H