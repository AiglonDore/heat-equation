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
     * @brief Get the U0 object.
     * 
     * @return double 
     */
    double getU0() const { return u0; };

    /**
     * @brief Get the L object.
     * 
     * @return double 
     */
    double getL() const { return L; };

    /**
     * @brief Get the TMax object.
     * 
     * @return double 
     */
    double getTMax() const { return tMax; };

    /**
     * @brief Get the F object.
     * 
     * @return double 
     */
    double getF() const { return f; };
    /**
     * @brief Get the value of the source.
     * 
     * @param x Position.
     * @return double 
     */
    double operator()(double x) const { return this->F(x); };

    /**
     * @brief Solve the bar model.
     * 
     * @param time Vector of time.
     * @param position Vector of position.
     * @param sol Vector of solution.
     */
    void solve(const std::vector<double>& time, const std::vector<double> position, std::vector<std::vector<double>>& sol) const;
};

#endif // BAR_H