/**
 * @file plate.h
 * @author Thomas Roiseux
 * @brief Provides the {@link Plate} class.
 * @version 0.1
 * @date 2022-12-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef PLATE_H
#define PLATE_H

#include <functional>
#include <string>
#include <vector>

/**
 * @brief Class representing a plate.
 * 
 */
class Plate
{
private:
    std::function<double(double, double)> F;
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
     * @param L Length and width of the plate.
     * @param tMax Max time.
     * @param f Value for the source.
     * @param material Material.
     * @throws Exn If the material is not found.
     */
    explicit Plate(double u0, double L, double tMax, double f, const std::string& material);
    /**
     * @brief Destroy the Bar object.
     * 
     */
    ~Plate();

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
    double operator()(double x, double y) const { return this->F(x,y); };

    /**
     * @brief Solve the bar model, using a finite differences method.
     * 
     * @param time Vector of time.
     * @param positionX Vector of position along x.
     * @param positionY Vector of position along y.
     * @param sol Vector of solution.
     */
    void solve(const std::vector<double>& time, const std::vector<double>& positionX, const std::vector<double>& positionY, std::vector<std::vector<double>>& sol) const;
};


#endif // PLATE_H