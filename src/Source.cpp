/*#ifdef _WIN32
#elif __APPLE__
#endif*/

#include "../include/Initializer.h"

void printHelp(){
    std::cout << "Usage:\n";
    std::cout<<"--width <int> : Set the width of the window\n";
    std::cout<<"--height <int> : Set the height of the window\n";
    std::cout<<"--fps <int> : Set the frames per second (must set vsync off too)\n";
    std::cout<<"--vsync <int> : Set the vsync (1=on/0=off)\n";
    std::cout<<"--help : Display this message\n";
}

int main(int argc, char* argv[]){
	//default values for args
	int width = -1;
	int height = -1;
	int fps = 60;
	int vsync = 1;

    //assists with parsing
    size_t pos;

	//Sets arguments from user
	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];
        try{
            if (arg == "--width" && i + 1 < argc) {
                width = std::stoi(argv[++i],&pos);
                if (pos != std::string(argv[i]).length()) {
                    l_log(2,"Invalid argument: " + std::string(argv[i]));
                    printHelp();
                    return 1;
                }
            } else if (arg == "--height" && i + 1 < argc) {
                height = std::stoi(argv[++i], &pos);
                if (pos != std::string(argv[i]).length()) {
                    l_log(2,"Invalid argument: " + std::string(argv[i]));
                    printHelp();
                    return 1;
                }
            } else if (arg == "--fps" && i + 1 < argc) {
                fps = std::stoi(argv[++i], &pos);
                if (pos != std::string(argv[i]).length()) {
                    l_log(2,"Invalid argument: " + std::string(argv[i]));
                    printHelp();
                    return 1;
                }
            } else if (arg == "--vsync" && i + 1 < argc) {
                vsync = std::stoi(argv[++i], &pos);
                if (pos != std::string(argv[i]).length()) {
                    l_log(2,"Invalid argument: " + std::string(argv[i]));
                    printHelp();
                    return 1;
                }
            }else if (arg == "--help"){
                printHelp();
                return 0;
            }
            else {
                l_log(2,"Invalid argument: " + arg);
                printHelp();
                return 1;
            }
        }catch (std::exception e){
            l_log(2,"Invalid argument: " + arg);
            printHelp();
            return 1;
        }
	}

	if (!Initializer::InitializeAll(width, height, fps, vsync)) {
		l_log(2,"Failed to initialize: \n" + Initializer::errorMessage);
		return 1;
	}

	while (Window::countRendering!= 0){
		//Poll for and process events #1#
		glfwPollEvents();
	};
	game::stopGame();

	l_log(0,"Goodbye!");
	return 0;
}
