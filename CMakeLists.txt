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

# Define DEBUG only if CMAKE_BUILD_TYPE is Debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()

target_sources(PlanetarySimulation PRIVATE
        ${CMAKE_SOURCE_DIR}/src/Source.cpp
        ${CMAKE_SOURCE_DIR}/src/Window.cpp
        ${CMAKE_SOURCE_DIR}/src/Initializer.cpp
        ${CMAKE_SOURCE_DIR}/src/Game.cpp
        ${CMAKE_SOURCE_DIR}/src/callbackFunctions.cpp
        ${CMAKE_SOURCE_DIR}/src/Logger.cpp
        ${CMAKE_SOURCE_DIR}/src/glad.c
)

# Include directories for the executable
target_include_directories(PlanetarySimulation PRIVATE "${CMAKE_SOURCE_DIR}/include")

# Link libraries for the executable
target_link_libraries(PlanetarySimulation glfw "-framework OpenGL" "-Wextra-qualification" OpenGL::GL)

# Define the source and destination directories for shaders
set(SHADERS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/shaders")
set(SHADERS_DEST_DIR "${CMAKE_BINARY_DIR}/shaders")

# Add a custom command to delete the shaders directory in the build folder

# Add a custom command to copy the shaders directory to the build folder
add_custom_command( # doesnt overwrite correctly...
        OUTPUT ${SHADERS_DEST_DIR}
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${SHADERS_DEST_DIR}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${SHADERS_DEST_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${SHADERS_SOURCE_DIR} ${SHADERS_DEST_DIR}
        COMMENT "Copying shaders directory to build folder"
)

# Ensure the custom command is executed
#add_custom_target(delete_shaders ALL DEPENDS ${SHADERS_DEST_DIR})
add_custom_target(copy_shaders ALL DEPENDS ${SHADERS_DEST_DIR})