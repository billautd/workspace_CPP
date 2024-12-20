#include "Window.h"
#include "Logger.h"

Window::Window():Window(800, 600) {
	//Nothing
}

Window::Window(int width, int height) : width(width), height(height), bufferWidth(0), bufferHeight(0), window(nullptr) {
	//Nothing
}

Window::~Window() {
	destroy();
}

int Window::init() {
	//Init GLFW
	const int glfwInitResult = glfwInit();
	if (glfwInitResult != GLFW_TRUE) {
		Logger::error("Error initializing GLFW");
		glfwTerminate();
		return 1;
	}

	//Setup GLFW properties
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(width, height, "", NULL, NULL);
	if (!window) {
		Logger::error("Error initializing GLFW window");
		glfwTerminate();
		return 2;
	}

	//Get buffer size information
	glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

	//Set context for GLEW
	glfwMakeContextCurrent(window);

	//Allow modern extension features
	glewExperimental = GL_TRUE;

	//Init GLEW
	const int glewInitResult = glewInit();
	if (glewInitResult != GLEW_OK) {
		Logger::error("Error initializing GLEW : \n");
		Logger::error(glewGetErrorString(glewInitResult));
		glfwDestroyWindow(window);
		glfwTerminate();
		return 3;
	}

	//Enable depth buffer
	glEnable(GL_DEPTH_TEST);

	//Setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	return 0;
}

void Window::destroy() {
	glfwDestroyWindow(window);
	glfwTerminate();
}