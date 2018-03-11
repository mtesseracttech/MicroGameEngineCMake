#include <iostream>

#include "mge/core/AbstractGame.hpp"
#include "mge/MGEDemo.hpp"

/**
 * Main entry point for the Micro Engine.

 * Design goals:
 * - correct division of OpenGL into appropriate wrapper classes
 * - simple design
 * - each class should know as little as possible about other classes and non related parts of OpenGL
 * - the engine must allow different objects with different transforms, meshes, materials (shaders) etc
 * - consistent coding conventions
 * - reusable and extendable core set of classes which should require no modification
 *   (in other words it is possible to have a working "empty" example)
 *
 * All documentation is contained within the HEADER files, not the CPP files in possible.
 *
 */
int main()
{
    std::cout << "Starting Game" << std::endl;

    AbstractGame* game = nullptr;
    try
    {
        game = new MGEDemo();
        game->initialize();
        game->run();
    }
    catch (std::runtime_error& err)
    {
        std::cout << "An exception was thrown: " << std::endl << err.what() << std::endl;
    }

    delete game;

    return 0;
}



