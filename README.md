*Planetary-Simulation*
Created by: *LegendsZ*

*Description*:
This project aims to provide a visual simulation (using OpenGL) of planets using primarily Newtonian physics.

*Instructions to build*:
From the root directory of this project, execute:
1. cd (mkdir first if nonexistent) into debug/release
If *debug*:
2. cmake -DCMAKE_BUILD_TYPE=Debug ..
If *release*:
2. cmake -DCMAKE_BUILD_TYPE=Release ..
3. make
*Individual targets for make*:
a. make PlanetarySimulation : Build the main executable
b. make copy_shaders : Copy the shaders to the build directory

*Instructions to run*:
From the root directory of this project, execute:
./PlanetarySimulation

*Optional arguments*:

--width <int> : Set the width of the window
--height <int> : Set the height of the window
--fps <int> : Set the frames per second (must set vsync off too)
--vsync <int> : Set the vsync (1=on/0=off)
--help : Display this message

Enjoy!
