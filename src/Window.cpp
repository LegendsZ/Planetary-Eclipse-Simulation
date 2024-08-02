#include "../include/Window.h"

Window* Window::window = nullptr;

Window::Window(const int& width, const int& height){
	this->_width = width;
	this->_height = height;
	Window::window = this;
}
