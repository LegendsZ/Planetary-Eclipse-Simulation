#include "../include/Initializer.h"

namespace Initializer {
	/*bool initGlut(int argc, char** argv, const int& vWidth, const int& vHeight) {
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutInitWindowSize(vWidth, vHeight);
		glutInitWindowPosition(200, 30);
		glutCreateWindow("3D Room");
		return true;
	}*/

	bool initOpenGL(Window* window) {
		try {
			//load models!
			std::vector<vertex> obj_parts;
			obj_parts.emplace_back(.5f, -.5f,0.f);
			obj_parts.emplace_back(-.5f, -.5f,0.f);
			obj_parts.emplace_back(0.f, .5f,0.f);
			std::vector<uint32_t> elem = {0,1,2};
			//move movels to window
			window->_drawDetails.push_back(uploadMesh(obj_parts, elem));
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
		logger::l_log(0, "Initializing...");
		if (!Window::initGLFW()) {
			errorMessage = "Failed to initialize GLFW!";
			return false;
		}

		const char* vertexShader = "#version 330 core\n"
				"layout (location = 0) in vec3 aPos;\n"
				"void main()\n"
				"{\n"
				"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
				"}\0";

		const char* fragmentShader = "#version 330 core\n"
				"out vec4 FragColor;\n"
				"void main()\n"
				"{\n"
				"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
				"}\n\0";

		Window* window = new Window(width,height,vertexShader, fragmentShader,true,fps,vsync);
		if (!window->_glfwWindow) {
			errorMessage = "Failed to create window!";
			return false;
		}

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
		logger::l_log(0,"Done initializing!");
		return true;
	}
}