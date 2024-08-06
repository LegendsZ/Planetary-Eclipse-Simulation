#include "../include/Window.h"

std::vector<Window*> Window::windows;
int Window::countRendering = 0;

Window::Window(const int& width, const int& height, bool visible, double cfps, int vsync):
	_width(width), _height(height), _visible(visible), _cFps(cfps), _frameTime(1.0/cfps), _vsync(vsync)
{
	if (!glfwInit()){
		return;
		//std::cout / write to error buffer/handler?
	}

	//Set width/height to max if specified
	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
	if (_width == -1) {
		_width = mode->width;
	}
	if (_height == -1) {
		_height = mode->height;
	}

	_glfwWindow = glfwCreateWindow(_width, _height, "PlanetarySimulation", NULL, NULL);
	if (!_glfwWindow){
		glfwTerminate();
		return;
		//std::cout / write to error buffer/handler?
	}
	windows.push_back(this);
}

void Window::makeContextCurrent() const{
	glfwMakeContextCurrent(_glfwWindow);
}


void Window::render() const{
	if (!_visible) {
		return;
	}
	/* Render here */
	//glfwMakeContextCurrent(_glfwWindow);
	/* Clear the screen */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/* Swap front and back buffers */
	glfwSwapBuffers(_glfwWindow);
}

void Window::renderAll(){
	for (Window* w : windows){
		w->render();
	}
}

void Window::startRenderLoop() {
	_thread = new std::thread(Window::renderLoop, this);
	Window::countRendering++;
}

void Window::stopRenderLoop() {
	_rendering=false;
	_thread->join();
	delete _thread;
}


void Window::startAllRenderLoop() {
	for (Window* w : windows){
		if (!w->_rendering) {
			w->startRenderLoop();
		}
	}
}

void Window::stopAllRenderLoop() {
	for (Window* w : windows){
		if (w->_rendering) {
			w->stopRenderLoop();
		}
	}
}

void Window::renderLoop(Window* window) {
	//vars for tracking fps
	double lastTime = glfwGetTime();
	double fpsTime = lastTime;
	double currentTime;
	double deltaTime;

	glfwMakeContextCurrent(window->_glfwWindow);
	glfwSwapInterval(window->_vsync); //enables/disables vsync based off user input

	window->_rendering=true;
	while (window->_rendering) {
		if(glfwWindowShouldClose(window->_glfwWindow)) break;
		// Calculate the time taken for one frame for the current window
		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		//glfwMakeContextCurrent(_glfwWindow);
		window->render();
		glfwSwapBuffers(window->_glfwWindow);


		// Increment FPS counter
		window->_cFps++;

		if (currentTime - fpsTime >= 1.0) {
			std::cout << "FPS: " << window->_cFps << "\n";
			window->_cFps = 0;
			fpsTime = currentTime;
		}
		//Delays till next frame accordingly with vsync setting
		if (window->_vsync == 0 && deltaTime < window->_frameTime) {
			std::this_thread::sleep_for(std::chrono::duration<double>(window->_frameTime - deltaTime));
		}
	}
	window->_rendering=false;
	Window::countRendering--;
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

bool Window::shouldClose() const {
	return glfwWindowShouldClose(_glfwWindow);
}