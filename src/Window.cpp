#include "../include/Window.h"

Window* Window::window = nullptr;


Window::Window(const int& width, const int& height):
	_width(width), _height(height)
{
	if (!glfwInit()){
		return;
		//std::cout / write to error buffer/handler?
	}
	glfwWindow = glfwCreateWindow(_width, _height, "PlanetarySimulation", NULL, NULL);
	if (!glfwWindow){
		glfwTerminate();
		return;
		//std::cout / write to error buffer/handler?
	}
	glfwMakeContextCurrent(glfwWindow);
	
	//RENDER LOOP
	while (!glfwWindowShouldClose(glfwWindow))
    	{
        	/* Render here */
        	glClear(GL_COLOR_BUFFER_BIT);

        	/* Swap front and back buffers */
        	glfwSwapBuffers(glfwWindow);

        	/* Poll for and process events */
        	glfwPollEvents();
    	}
	glfwDestroyWindow(glfwWindow);
    	glfwTerminate();

	Window::window = this;
}

Window* Window::createWindow(const int& width, const int& height){
	if (window == nullptr){
		window = new Window(width, height);
		return window;
	}else{
		return nullptr;
	}
}

Window* Window::getWindow(){
	return window;
}

int Window::getWidth() const {
	return _width;
}

int Window::getHeight() const {
	return _height;
}
