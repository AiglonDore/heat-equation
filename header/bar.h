/**
 * @file bar.h
 * @author Thomas Roiseux
 * @brief Provides
 * @version 0.1
 * @date 2022-12-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef BAR_H
#define BAR_H

#include <functional>
#include <string>
#include <vector>

/**
 * @brief Class for the bar model.
 * 
 */
class Bar
{
private:
    std::function<double(double)> F;
    double u0;
    double L;
    double tMax;
    double f;
    std::string material;
public:
    /**
     * @brief Construct a new Bar object.
     * 
     * @param u0 Initial temperature.
     * @param L Length.
     * @param tMax Max time.
     * @param f Value for the source.
     * @param material Material.
     * @throws Exn If the material is not found.
     */
    explicit Bar(double u0, double L, double tMax, double f, const std::string& material);
    /**
     * @brief Destroy the Bar object.
     * 
     */
    ~Bar();

    /**
     * @brief Solve the bar model.
     * 
     * @param time Vector of time.
     * @param sol Vector of solution.
     */
    void solve(std::vector<double>& time, std::vector<double>& sol) const;
};

#endif // BAR_H