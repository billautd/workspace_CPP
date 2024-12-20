#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Window
{
private:
	GLFWwindow* window;
	int width;
	int height;
	int bufferWidth;
	int bufferHeight;

public:
	Window();
	Window(int width, int height);
	~Window();

	/*
	* Initialize window, OpenGL parameters and context 
	*/
	int init();

	float getAspectRatio() { return (float)bufferWidth / (float)bufferHeight; }

	void swapBuffers() { glfwSwapBuffers(window); };

	bool shouldClose() { return glfwWindowShouldClose(window);	}

	void destroy();
};

