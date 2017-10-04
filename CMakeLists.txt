#Sets the minimum version of CMake
cmake_minimum_required(VERSION 3.8)

#Sets the project name
project(MicroGameEngine)

#Sets what version of C++ is compiled (C++11 by default)

set(CMAKE_CXX_STANDARD 11)

#List containing all files to be compiled

add_executable(MicroGameEngine
        src/mge/behaviours/AbstractBehaviour.cpp
        src/mge/behaviours/AbstractBehaviour.hpp
        src/mge/behaviours/KeysBehaviour.cpp
        src/mge/behaviours/KeysBehaviour.hpp
        src/mge/behaviours/LookAt.cpp
        src/mge/behaviours/LookAt.hpp
        src/mge/behaviours/RotatingBehaviour.cpp
        src/mge/behaviours/RotatingBehaviour.hpp
        src/mge/core/AbstractGame.cpp
        src/mge/core/AbstractGame.hpp
        src/mge/core/Camera.cpp
        src/mge/core/Camera.hpp
        src/mge/core/GameObject.cpp
        src/mge/core/GameObject.hpp
        src/mge/core/Mesh.cpp
        src/mge/core/Mesh.hpp
        src/mge/core/Renderer.cpp
        src/mge/core/Renderer.hpp
        src/mge/core/ShaderProgram.cpp
        src/mge/core/ShaderProgram.hpp
        src/mge/core/Texture.cpp
        src/mge/core/Texture.hpp
        src/mge/core/World.cpp
        src/mge/core/World.hpp
        src/mge/materials/AbstractMaterial.cpp
        src/mge/materials/AbstractMaterial.hpp
        src/mge/materials/ColorMaterial.cpp
        src/mge/materials/ColorMaterial.hpp
        src/mge/materials/TextureMaterial.cpp
        src/mge/materials/TextureMaterial.hpp
        src/mge/util/DebugHud.cpp
        src/mge/util/DebugHud.hpp
        src/mge/config.hpp
        src/mge/MGEDemo.cpp
        src/mge/MGEDemo.hpp
        src/glm.hpp
        src/main.cpp)

#Sets a base path for the includes so that they can be used in the same way as in Visual Studio/Codeblocks
set(BASEPATH "${CMAKE_SOURCE_DIR}/src")
include_directories("${BASEPATH}")

#Lets CMake search in {Project Directory}/cmake/modules for Find*.cmake files
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

#Finds and Links SFML
find_package(SFML 2.4 COMPONENTS system window graphics audio REQUIRED)
if(SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIR})
        target_link_libraries(MicroGameEngine ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif (SFML_FOUND)


#Finds and Links OpenGL
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
        include_directories(${OPENGL_INCLUDE_DIR})
        target_link_libraries(MicroGameEngine ${OPENGL_LIBRARIES})
endif(OPENGL_FOUND)


#Finds and Links GLEW
find_package(GLEW REQUIRED)
if(GLEW_FOUND)
        include_directories(${GLEW_INCLUDE_DIRS})
        target_link_libraries(MicroGameEngine ${GLEW_LIBRARIES})
endif(GLEW_FOUND)

#CMake is already packaged with versions of Find*.cmake files (OpenGL and GLEW are 2 examples of that here)
#Often libraries are also packaged with a Find*.cmake file of itself (SFML being an example when installed though MSYS2)
#If neither is the case, a quick google search for the file often turns up with something