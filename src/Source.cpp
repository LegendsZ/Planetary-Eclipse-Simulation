/*#ifdef _WIN32
#elif __APPLE__
#endif*/

#include <iostream>

#include "../include/VECTOR3D.h"
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

	std::cout << "Starting PlanetarySimulation...\n";
	if (!Window::initGLFW()) {
		std::cerr << "Failed to start PlanetarySimulation!\n";
		return 1;
	}
	if (!((new Window(width,height,true,fps,vsync))->_glfwWindow)) {
		std::cerr << "Failed to start PlanetarySimulation!\n";
		return 1;
	}
	std::cout << "Started PlanetarySimulation!\n";
	Window::startAllRenderLoop();
	//glutMainLoop();


	while (Window::countRendering!= 0){
		//Poll for and process events #1#
		glfwPollEvents();
	};
	std::cout << "Goodbye!\n";
	return 0;
}
