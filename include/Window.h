#ifndef WINDOW_H
#define WINDOW_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include <Vertex.h>

#include "OpenGLDraw.h"

class Window{
	public:
		static bool initialized;
		static std::vector<Window*> windows;
		static int countRendering;
		GLFWwindow* _glfwWindow;
		GLuint _shader;
		std::vector<drawDetails> _drawDetails;
		int _width;
		int _height;
		int _frameBufferWidth;
		int _frameBufferHeight;
		bool _visible;
		int _fps;
		int _cFps;
		bool _rendering;
		int _vsync;
		double _frameTime;
		std::thread* _thread;

		Window(const int& width, const int& height, const char* vertex, const char* fragment, bool visible, double cfps,int vsync);
		Window(const Window&) = delete;
		Window& operator=(const Window&)=delete;

		static bool initGLFW();

		static Window* findWindow(GLFWwindow* window);

		inline void makeContextCurrent() const;

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
