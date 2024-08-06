#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <vector>
#include <chrono>
#include <thread>
#include <iostream> //for printing fps

class Window{
	public:
		static std::vector<Window*> windows;
		static int countRendering;
		GLFWwindow* _glfwWindow;
		int _width;
		int _height;
		bool _visible;
		int _fps;
		int _cFps;
		bool _rendering;
		int _vsync;
		double _frameTime;
		std::thread* _thread;

		Window(const int& width, const int& height, bool visible, double cfps,int vsync);
		Window(const Window&) = delete;
		Window& operator=(const Window&)=delete;

		void makeContextCurrent() const;

		void render() const;
		static void renderAll();
		void startRenderLoop();
		void stopRenderLoop();
		static void startAllRenderLoop();
		static void stopAllRenderLoop();
		static void renderLoop(Window* window);

		void close();
		static void closeAll();

		bool shouldClose() const;
};

#endif
