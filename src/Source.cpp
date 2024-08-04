#include <iostream>

#include "../include/Window.h"

//silence warnings
#define GL_SILENCE_DEPRECATION

int main(int argc, char* argv[]){
	std::cout << "Starting PlanetarySimulation...";
	std::cout << "OK!\n";

	Window* window = new Window(500,500);

	while (!window->shouldClose()){
		window->render();
	}

	std::cout << "Goodbye!\n";
	return 0;
}
