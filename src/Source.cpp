/*#ifdef _WIN32
#elif __APPLE__
#endif*/

#include "../include/Initializer.h"

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

	if (!Initializer::InitializeAll(width, height, fps, vsync)) {
		logger::l_log(2,"Failed to initialize: \n" + Initializer::errorMessage);
		return 1;
	}

	while (Window::countRendering!= 0){
		//Poll for and process events #1#
		glfwPollEvents();
	};
	game::stopGame();

	logger::l_log(0,"Goodbye!");
	return 0;
}
