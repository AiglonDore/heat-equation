/**
 * @file material.cpp
 * @author Thomas Roiseux
 * @brief Implements material data.
 * @version 0.1
 * @date 2022-12-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../header/materials.h"

std::map<std::string, Material> Material::materials = {
    {"cuivre", Material(389, 8940, 380)},
    {"fer", Material(80.2, 7874, 440)},
    {"verre", Material(1.2, 2530, 840)},
    {"polystyrene", Material(0.1, 1040, 1200)}
};

Material::Material() : lambda(0), rho(0), cp(0)
{
}

Material::Material(double lambda, double rho, double cp) : lambda(lambda), rho(rho), cp(cp)
{
}

Material::~Material()
{
}