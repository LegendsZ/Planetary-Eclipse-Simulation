cmake_minimum_required(VERSION 3.24)
project(Planetary-Simulation)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find the OPENGL code on the system, will define path variables
find_package(GLAD REQUIRED)
find_package(GLFW REQUIRED)

# Specify include directories and libraries to be linked that apply to all targets

# List of source files to compile to objects 
set(OBJECT_SOURCES )

# Loop over `OBJECT_SOURCES` and compile each one, keeping track of the
# generated object files in `_OBJECTS_` (underscores used because `OBJECT` and
# `OBJECTS` are keywords)
foreach(_OBJECT_ ${OBJECT_SOURCES})

	# Declare a new object that should be built ...
	add_library(${_OBJECT_} OBJECT "${CMAKE_SOURCE_DIR}/src/${_OBJECT_}.cpp")
	target_include_directories(${_OBJECT_} PUBLIC "${CMAKE_SOURCE_DIR}/include"
		$<TARGET_PROPERTY:GLAD::GLAD,INTERFACE_INCLUDE_DIRECTORIES>
		$<TARGET_PROPERTY:GLFW::GLFW,INTERFACE_INCLUDE_DIRECTORIES>)
	target_link_libraries(${_OBJECT_} GLAD::GLAD GLFW::GLFW)
	# ... add the output object to `OBJECTS` list
	list(APPEND _OBJECTS_ $<TARGET_OBJECTS:${_OBJECT_}>)

endforeach()

# Compile the complete executable against all objects and OPENGL libraries
add_executable(PlanetarySimulation "${CMAKE_SOURCE_DIR}/src/Source.cpp")

target_include_directories(PlanetarySimulation PUBLIC "${CMAKE_SOURCE_DIR}/include"
	$<TARGET_PROPERTY:GLAD::GLAD,INTERFACE_INCLUDE_DIRECTORIES>
	$<TARGET_PROPERTY:GLFW::GLFW,INTERFACE_INCLUDE_DIRECTORIES>)
target_link_libraries(MafiaGangs ${_OBJECTS_} GLAD::GLAD GLFW::GLFW)
