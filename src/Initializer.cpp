#include "../include/Initializer.h"

namespace Initializer {
	std::string readFile(const std::string& filePath){
        std::ifstream fileStream(filePath);
        if (!fileStream.is_open()) {
            std::cerr << "Failed to open file: " << filePath << std::endl;
            return "";
        }
        std::stringstream buffer;
        buffer << fileStream.rdbuf();
        return buffer.str();
    }

    void printGLInfo(){
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        const GLubyte* vendor = glGetString(GL_VENDOR);
        const GLubyte* renderer = glGetString(GL_RENDERER);
        const GLubyte* version = glGetString(GL_VERSION);
        GLint major, minor;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);
        const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
        l_log(0, "OpenGL Vendor: " + std::string((const char*)vendor));
        l_log(0, "OpenGL Renderer: " + std::string((const char*)renderer));
        l_log(0, "OpenGL Version: " + std::string((const char*)version));
        l_log(0, "OpenGL Version (integer): " + std::to_string(major) + "." + std::to_string(minor));
        l_log(0, "GLSL Version: " + std::string((const char*)glslVersion));
    }

	bool initOpenGL(Window* window) {
		try {
            /* DEPRECATED WAY TO LOAD MODEL
			std::vector<vertex> obj_parts;
			obj_parts.emplace_back(.5f, -.5f,0.f);
			obj_parts.emplace_back(-.5f, -.5f,0.f);
			obj_parts.emplace_back(0.f, .5f,0.f);
			std::vector<uint32_t> elem = {0,1,2};
			//move models to window
			window->_drawDetails.push_back(uploadMesh(obj_parts, elem));*/


            GLfloat vertices[] = {
                0.5f, -0.5f, 0.0f,
                -0.5f, -0.5f, 0.0f,
                0.0f, 0.5f, 0.0f
            };
            GLfloat colours[] = {
                1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f
            };
            GLuint elements[] = {
                0, 1, 2
            };
            window->_drawDetails.push_back(uploadMesh(vertices, colours, sizeof(vertices)/sizeof(vertices[0]), elements, sizeof(elements)/sizeof(elements[0])));

        }catch (std::exception e) {
            return false;
        }
		return true;
	}

	bool setCallbackFunctions(GLFWwindow* window) {
		try {
			glfwSetFramebufferSizeCallback(window, callbackFunctions::reshape);
			glfwSetMouseButtonCallback(window, callbackFunctions::mouse);
			glfwSetCursorPosCallback(window, callbackFunctions::mouseMotionHandler);
			glfwSetKeyCallback(window, callbackFunctions::keyHandler);
			glfwSetWindowCloseCallback(window, callbackFunctions::windowCloseHandler);

			signal(SIGINT, callbackFunctions::signalWindowCloseHandler);
		}catch (std::exception e) {
			return false;
		}
		return true;
	}

	bool initializeGameObjects()
	{
		//example room objects
		/*for (int i = 0; i < 100; i++)
		{
			game::gameObjects.push_back((GameObject*)new Cube({ float((i % 100) - 50) * 2, float((i % 100) % 10) * 2 ,float((i / 100) - 50) * 2}, {0.1,0.1,0.1}, 1.0, 0, 0, 0, 0));
			game::gameObjects[i]->physics.init(&(game::gameObjects[i]->Position));
			game::gameObjects[i]->physics.gravityEnabled = true;
			//game::gameObjects[i]->Write("gobj\\object" + std::to_string(i) + ".bin");
			//game::gameObjects.push_back((GameObject*) new Cube("gobj\\object" + std::to_string(i) + ".bin"));
		}

		//NEWLY commented out portion
		VECTOR3D origin = VECTOR3D(-16.0f, 0.0f, 16.0f);
		callbackFunctions::roomMesh = new RoomMesh(16, 32.0);
		callbackFunctions::roomMesh->InitMesh(16, origin, 32.0, 32.0);
		origin = VECTOR3D(5.0f, 5.0f, 5.0f);


		VECTOR3D ambient = VECTOR3D(0.0f, 0.05f, 0.0f);
		VECTOR3D diffuse = VECTOR3D(0.4f, 0.8f, 0.4f);
		VECTOR3D specular = VECTOR3D(0.04f, 0.04f, 0.04f);


		float shininess = 0.2;
		Cube* sample = new Cube(4.0, 8.0);
		sample->InitMesh(4, origin, 8.0, 8.0, 8.0);
		sample->SetMaterial(ambient, diffuse, specular, shininess);
		game::gameObjects.push_back((GameObject*)sample);


		VECTOR3D ambient = VECTOR3D(0.0f, 0.05f, 0.0f);
		VECTOR3D diffuse = VECTOR3D(0.4f, 0.8f, 0.4f);
		VECTOR3D specular = VECTOR3D(0.04f, 0.04f, 0.04f);
		float shininess = 0.2;
		callbackFunctions::roomMesh->SetMaterial(ambient, diffuse, specular, shininess);

		Camera::makeCamera();
		game::gameObjects.push_back((GameObject*)Camera::camera);

		//make gui elements
		GUIElements::GUIElement* picbox = (GUIElements::GUIElement*)new GUIElements::PictureBox("", { Camera::camera->eye->x, Camera::camera->eye->y }, 5.0, 5.0);
		Camera::camera->GUIElements.push_back(picbox);
		*/
		return true;
	}

	bool InitializeAll(int width, int height, int fps, int vsync) {
		glfwSetErrorCallback(callbackFunctions::errorHandler); // glfw error redirection
        l_log(0, "Initializing...");
        if (!Window::initGLFW()) {
            errorMessage = "Failed to initialize GLFW!";
            return false;
        }

        std::string vertexShader = readFile("shaders/vertex.vert");
        std::string fragmentShader = readFile("shaders/fragment.frag");
        if (vertexShader=="" || fragmentShader=="") {
            errorMessage = "Failed to read shaders:\nVertex Shader="+std::to_string(vertexShader!="")+"\nFragment Shader="+std::to_string(fragmentShader!="");
            return false;
        }
        Window* window = new Window(width,height,vertexShader.c_str(), fragmentShader.c_str(),true,fps,vsync);
        if (!window->_glfwWindow) {
            errorMessage = "Failed to create window!";
            return false;
        }

        printGLInfo();

		if (!Initializer::setCallbackFunctions(window->_glfwWindow)) {
			errorMessage="Failed to set callback functions!";
			return false;
		}
		if (!Initializer::initOpenGL(window)) {
			errorMessage="Failed to initialize OpenGL!";
			return false;
		}
		if (!Initializer::initializeGameObjects()) {
			errorMessage="Failed to initialize game objects!";
			return false;
		}

		try {
			game::startGame();
		}
		catch (std::exception e) {
			errorMessage=e.what();
			return false;
		}

		try {
			Window::startAllRenderLoop(); //multi-threaded
		}
		catch (std::exception e) {
			errorMessage=e.what();
			return false;
		}
		l_log(0,"Done initializing!");
		return true;
	}
}