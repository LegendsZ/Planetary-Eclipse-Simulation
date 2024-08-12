cmake_minimum_required(VERSION 3.24)
project(Planetary-Simulation)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find the GLFW3 package
find_package(GLFW3 REQUIRED)

find_package(OpenGL REQUIRED)

# Compile the complete executable against all objects and GLFW libraries
add_executable(PlanetarySimulation)

# Silence deprecation warnings
add_definitions(-DGL_SILENCE_DEPRECATION)

target_sources(PlanetarySimulation PRIVATE
  ${CMAKE_SOURCE_DIR}/src/Source.cpp
  ${CMAKE_SOURCE_DIR}/src/Window.cpp
  ${CMAKE_SOURCE_DIR}/src/Initializer.cpp
  ${CMAKE_SOURCE_DIR}/src/Game.cpp
  ${CMAKE_SOURCE_DIR}/src/callbackFunctions.cpp
  ${CMAKE_SOURCE_DIR}/src/glad.c
)

# Include directories for the executable
target_include_directories(PlanetarySimulation PRIVATE "${CMAKE_SOURCE_DIR}/include")

# Link libraries for the executable
target_link_libraries(PlanetarySimulation glfw "-framework OpenGL" OpenGL::GL)
