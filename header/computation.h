/**
 * @file computation.h
 * @author Thomas Roiseux
 * @brief Provides an interfce for the computation of the solution.
 * @version 0.1
 * @date 2022-12-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef COMPUTATION_H
#define COMPUTATION_H

#include <vector>
#include "bar.h"
#include "plate.h"

/**
 * @brief Solve the bar.
 * 
 * @param bar Bar to solve.
 * @param filename File to write output.
 * @param nogui If the GUI is used.
 */
void solveBar(const Bar &bar, const std::string& filename, bool nogui);

/**
 * @brief Solve the plate.
 * 
 * @param plate Plate to solve.
 * @param filename File to write output.
 * @param nogui  If the GUI is used.
 */
void solvePlate(const Plate &plate, const std::string& filename, bool nogui);

#endif // COMPUTATION_H