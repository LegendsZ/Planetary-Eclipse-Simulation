#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <vector>
#include <chrono>
#include <thread>

class Window{
	public:
		static std::vector<Window*> windows;
		GLFWwindow* _glfwWindow;
		int _width;
		int _height;
		bool _visible;
		int _fps;
		int _cFps;
		bool _rendering;
		int _vsync;
		double _frameTime;

		Window(const int& width, const int& height, bool visible, double cfps,int vsync);
		Window(const Window&) = delete;
		Window& operator=(const Window&)=delete;

		void makeContextCurrent() const;

		void render() const;
		static void renderAll();
		void startRenderLoop();
		static void startAllRenderLoop();

		void close();
		static void closeAll();

		bool shouldClose() const;
};

#endif
