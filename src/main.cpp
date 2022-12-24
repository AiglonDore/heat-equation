/**
 * @file main.cpp
 * @author Thomas Roiseux
 * @brief Main file.
 * @version 0.1
 * @date 2022-12-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include "../header/exn.h"
#include "../header/materials.h"
#include "../header/bar.h"
#include "../header/computation.h"

using namespace std;

/**
 * @brief Print help.
 * @param arg Name of the program. Should be argv[0].
 */
void printHelp(const char *arg)
{
    cout << "Usage: " << arg << "[OPTIONS] <material> <u0> <tMax> <f> <L>" << endl;
    cout << "OPTIONS:" << endl;
    cout << "  -h, --help\t\tDisplay this help message." << endl;
    cout << "  -v, --version\t\tDisplay version information." << endl;
    cout << "  -m, --material\tNew material to add." << endl;
    cout << "  -p, --plate\t\tPlate to use. If this option is used, then <W> is mandatory." << endl;
    cout << "  -f, --file\t\tOutput will also be written in the given file, using CSV notation." << endl;
    cout << "  -n, --no-gui\t\tNo GUI will be displayed. Output will be in stdout." << endl;
}

/**
 * @brief Parse arguments.
 *
 * @param argc Number of arguments.
 * @param argv Arguments.
 * @param u0 Initial temperature.
 * @param L Length
 * @param tMax Maximum time.
 * @param f Temperature of the source.
 * @param material Material
 * @param plate If the plate is used.
 * @param filename File to write output.
 * @param nogui If the GUI is used.
 * @throws Exn If not enough arguments for material creation.
 */
void parseArguments(int argc, char *argv[], double &u0, double &L, double &tMax, double &f, string &material, bool &plate, string &filename, bool &nogui)
{
    if (argc == 1)
    {
        printHelp(argv[0]);
        exit(0);
    }
    if (argc < 6)
    {
        throw Exn("Not enough arguments.");
    }
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            printHelp(argv[0]);
            exit(0);
        }
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0)
        {
            cout << "Version 1.0" << endl;
            exit(0);
        }
        if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--plate") == 0)
        {
            plate = true;
        }
        if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--material") == 0)
        {
            string name = argv[i + 1];
            double lambda;
            if (!sscanf(argv[i + 2], "%lf", &lambda) || lambda < 0)
                throw Exn("Invalid lambda value.");
            double rho;
            if (!sscanf(argv[i + 3], "%lf", &rho) || rho < 0)
                throw Exn("Invalid rho value.");
            double cp;
            if (!sscanf(argv[i + 4], "%lf", &cp) || cp < 0)
                throw Exn("Invalid cp value.");

            Material::materials[name] = Material(lambda, rho, cp);

            cout << "Material \"" << name << "\" created." << endl;
            i += 4;
        }
        else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0)
        {
            if (argc == i + 1)
                throw Exn("Not enough arguments.");
            filename = argv[i + 1];
            i++;
            cout << "Output will also be written in \"" << filename << "\"." << endl;
        }
        else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--no-gui") == 0)
        {
            nogui = true;
        }
        else if (material == "")
        {
            material = argv[i];
        }
        else if (u0 < 0)
        {
            if (!sscanf(argv[i], "%lf", &u0) || u0 < 0)
                throw Exn("Invalid u0 value.");
        }
        else if (tMax < 0)
        {
            if (!sscanf(argv[i], "%lf", &tMax) || tMax < 0)
                throw Exn("Invalid tMax value.");
        }
        else if (f < 0)
        {
            if (!sscanf(argv[i], "%lf", &f))
                throw Exn("Invalid f value.");
        }
        else if (L < 0)
        {
            if (!sscanf(argv[i], "%lf", &L) || L < 0)
                throw Exn("Invalid L value.");
        }
    }
}

/**
 * @brief Main function.
 *
 * @param argc Number of arguments.
 * @param argv Arguments.
 * @return int Exit code.
 */
int main(int argc, char *argv[])
{
    cout << "\t\t----- Heat Equation Solver -----" << endl;
    double u0 = -1, L = -1, tMax = -1, f = -1;
    string material = "", filename = "";
    bool plate = false;
    bool nogui = false;
    try
    {
        parseArguments(argc, argv, u0, L, tMax, f, material, plate, filename, nogui);
        if (!plate)
        {
            Bar bar(u0, L, tMax, f, material);
            solveBar(bar, filename, nogui);
        }
        else
        {
            Plate plate(u0, L, tMax, f, material);
            solvePlate(plate, filename, nogui);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}