#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

class Window{
	private:
		static Window* window;
		GLFWwindow* glfwWindow;
		int _width;
		int _height;
		Window(const int& width, const int& height);
	public:
		Window(const Window&) = delete;
		Window& operator=(const Window&)=delete;

		static Window* createWindow(const int& width, const int& height);
		
		static inline Window* getWindow();
		inline int getWidth() const;
		inline int getHeight() const;
};

#endif
