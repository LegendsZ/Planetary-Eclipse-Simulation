#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <vector>

class Window{
	private:
		static std::vector<Window*> windows;
		GLFWwindow* _glfwWindow;
		int _width;
		int _height;
	public:
		Window(const int& width, const int& height);
		Window(const Window&) = delete;
		Window& operator=(const Window&)=delete;
		
		void render() const;
		static void renderAll();

		void close();
		static void closeAll();

		static inline std::vector<Window*> getWindows();
		
		bool shouldClose() const;
		inline int getWidth() const;
		inline int getHeight() const;
};

#endif
