#include "../include/Window.h"

std::vector<Window*> Window::windows;


Window::Window(const int& width, const int& height):
	_width(width), _height(height)
{
	if (!glfwInit()){
		return;
		//std::cout / write to error buffer/handler?
	}
	_glfwWindow = glfwCreateWindow(_width, _height, "PlanetarySimulation", NULL, NULL);
	if (!_glfwWindow){
		glfwTerminate();
		return;
		//std::cout / write to error buffer/handler?
	}
	glfwMakeContextCurrent(_glfwWindow);	
}

void Window::render() const{
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(_glfwWindow);

        /* Poll for and process events */
        glfwPollEvents();
}

void Window::renderAll(){
	for (Window* w : windows){
		w->render();
	}
}

void Window::close(){
	glfwDestroyWindow(_glfwWindow);
	glfwTerminate(); //in the case of multiple closures, should this be moved?
}

void Window::closeAll(){
	for (Window* w : windows){
		w->close();
	}
	//glfwTerminate(); ???
}

std::vector<Window*> Window::getWindows(){
	return windows;
}

bool Window::shouldClose() const {
	return glfwWindowShouldClose(_glfwWindow);
}

int Window::getWidth() const {
	return _width;
}

int Window::getHeight() const {
	return _height;
}
