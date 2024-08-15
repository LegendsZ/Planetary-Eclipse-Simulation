#include "../include/Window.h"

bool Window::initialized=false;
std::vector<Window*> Window::windows;
int Window::countRendering = 0;

Window::Window(const int& width, const int& height, const char* vertex, const char* fragment, bool visible, double cfps, int vsync):
	_width(width), _height(height),_visible(visible), _cFps(cfps), _frameTime(1.0/cfps), _vsync(vsync), _rendering(false), _frameBufferWidth(0), _frameBufferHeight(0)
{
	if (!initialized) {
		return;
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

	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //problematic?
#endif

	_glfwWindow = glfwCreateWindow(_width, _height, "PlanetarySimulation", NULL, NULL);
	if (!_glfwWindow){
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(_glfwWindow);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	_shader = loadShader(vertex, fragment);
	if (_shader == -1) {
		logger::l_log(3, "Failed to load shader!");
	}

	//glfwGetFramebufferSize(_glfwWindow, &_frameBufferWidth, &_frameBufferHeight);
	//std::cout << _frameBufferWidth << " " << _frameBufferHeight << "\n";
	//glViewport(0,0,_frameBufferWidth,_frameBufferHeight);
	windows.push_back(this);
}

bool Window::initGLFW() {
	if (!glfwInit()) { //initialize glfw
		return false;
	}
	Window::initialized=true;
	return true;
}


void Window::makeContextCurrent() const{
	glfwMakeContextCurrent(_glfwWindow);
}

Window* Window::findWindow(GLFWwindow* window) {
	for (Window* w : windows){
		if (w->_glfwWindow == window) {
			return w;
		}
	}
	return nullptr;
}

void Window::render() const{
	if (!_visible) {
		return;
	}
	/* Render here */
	glfwMakeContextCurrent(_glfwWindow);
	/* Clear the screen */
	glClearColor(.2f,.2f,.6f,0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//use shader
	glUseProgram(_shader);
	//draw models
	draw(_drawDetails);
	/* Swap front and back buffers */
	glfwSwapBuffers(_glfwWindow);
	//glFlush();
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
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		Window::countRendering--;
		return;
	}
	glfwSwapInterval(window->_vsync); //enables/disables vsync based off user input

	window->_rendering=true;
	while (window->_rendering) {
		if(glfwWindowShouldClose(window->_glfwWindow)) break;
		// Calculate the time taken for one frame for the current window
		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		window->render();

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
	_rendering=false;
	glfwSetWindowShouldClose(_glfwWindow, GLFW_TRUE);
	glfwDestroyWindow(_glfwWindow);
	if (windows.size() == 1) {
		glfwTerminate();
	}
	auto it = std::remove(windows.begin(), windows.end(), this);
	if (it != windows.end()) {
		windows.erase(it, windows.end());
	}
}

void Window::closeAll(){
	std::vector<Window*> windowsDupe;
	windowsDupe.assign(windows.begin(), windows.end());
	for (Window* window : windowsDupe) {
		window->close();
	}
	glfwTerminate();
	windows.clear();
}

bool Window::shouldClose() const {
	return glfwWindowShouldClose(_glfwWindow);
}