#include <GLFW/glfw3.h>

class _Window{
	private:
		static _Window* _window = nullptr;
	public:
		int _width;
		int _height;

		_Window(const int& _width, const int& _height);
};
