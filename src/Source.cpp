#include <iostream>

//Needed for render loop
#include <thread>
#include <chrono>

#include "../include/Window.h"

//silence warnings
#define GL_SILENCE_DEPRECATION

int main(int argc, char* argv[]){
	//default values for args
	int width = -1;
	int height = -1;
	int fps = 60;
	int vsync = 1;

	//Sets arguments from user
	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];
		if (arg == "--width" && i + 1 < argc) {
			width = std::stoi(argv[++i]);
		} else if (arg == "--height" && i + 1 < argc) {
			height = std::stoi(argv[++i]);
		} else if (arg == "--fps" && i + 1 < argc) {
			fps = std::stoi(argv[++i]);
		} else if (arg == "--vsync" && i + 1 < argc) {
			vsync = std::stoi(argv[++i]);
		}
	}

	std::cout << "Starting PlanetarySimulation...";
	new Window(width,height,true,fps,vsync);
	std::cout << "OK!\n";
	Window::startAllRenderLoop();

	std::cout << "Goodbye!\n";
	return 0;
}
