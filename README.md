## CMake based version of the MicroGameEngine (MGE)

MGE is a barebones game engine written for the Game Technology course on Saxion University of Applied Sciences.

I wanted to make the engine build using CMake, so here it is.

Dependencies:
-  SFML, used for context management, audio and texture loading (has some other nifty things too that are not utilized in the base engine)
-  GLM, OpenGL Mathematics Library, for linear algebra and related objects, in a GLSL-like style
-  GLEW, OpenGL extension wrangler

Installation Instructions on Windows:
-  Install MSYS2 (Package manager for Windows)
-  Start MSYS2 and enter the following commands to install the dependencies:
```bash
pacman -Su //Updates
pacman -S mingw-w64-x86_64-toolchain //Installs the C/C++ toolchain
pacman -S mingw-w64-x86_64-sfml
pacman -S mingw-w64-x86_64-glm
pacman -S mingw-w64-x86_64-glew
```
-  If you use CLion as you idea (which I did), in settings > Build, Settings & Deployment > Toolchains, set the environment to the mingw64 folder inside of the msys2 install (e.g. C:\msys64\mingw64)