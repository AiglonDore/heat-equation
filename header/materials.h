/**
 * @file materials.h
 * @author Thomas Roiseux
 * @brief Provides material data.
 * @version 0.1
 * @date 2022-12-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef MATERIALS_H
#define MATERIALS_H

#include <string>
#include <map>

/**
 * @brief Material class.
 *
 */
class Material
{
private:
    double lambda; // W/mK
    double rho;    // kg/m3
    double cp;     // J/kgK
public:
    /**
     * @brief Map of materials.
     *
     */
    static std::map<std::string, Material> materials;
    /**
     * @brief Construct a new Material object.
     *
     */
    Material(/* args */);
    /**
     * @brief Construct a new Material object.
     *
     * @param lambda Thermal conductivity.
     * @param rho Density.
     * @param cp Specific heat capacity.
     */
    Material(double lambda, double rho, double cp);
    /**
     * @brief Destroy the Material object.
     *
     */
    ~Material();

    /**
     * @brief Get the Thermal Conductivity object.
     *
     * @return double Thermal conductivity.
     */
    double getThermalConductivity() const { return lambda; };
    /**
     * @brief Get the Density object.
     *
     * @return double Density.
     */
    double getDensity() const { return rho; };
    /**
     * @brief Get the Specific Heat Capacity object.
     *
     * @return double Specific heat capacity.
     */
    double getSpecificHeatCapacity() const { return cp; };

    /**
     * @brief Check if a material exists.
     *
     * @param name Name of the material.
     * @return true Material exists.
     * @return false Material does not exist.
     */
    static bool isMaterial(const std::string& name) { return materials.find(name) != materials.end(); };
};

#endif // MATERIALS_H