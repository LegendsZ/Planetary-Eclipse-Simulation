#include <iostream>

#include "../include/Window.h"

#define GL_SILENCE_DEPRECATION // silence warnings

int main(int argc, char* argv[]){
	std::cout << "Starting PlanetarySimulation...";
	std::cout << "OK!\n";

	Window* window = Window::createWindow(500,500);

	std::cout << "Goodbye!\n";
	return 0;
}
