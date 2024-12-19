#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Constants.h"
#include "Logger.hpp"
#include "ShaderProgram.h"

static GLFWwindow* window = nullptr;
const float toRadians = 3.14159265f / 180.0f;

int init() {
	//Init GLFW
	const int glfwInitResult = glfwInit();
	if (glfwInitResult != GLFW_TRUE) {
		Logger::get().error("Error initializing GLFW");
		glfwTerminate();
		return 1;
	}

	//Setup GLFW properties
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "", NULL, NULL);
	if (!window) {
		Logger::get().error("Error initializing GLFW window");
		glfwTerminate();
		return 2;
	}

	//Get buffer size information
	int bufferWidth = 0;
	int bufferHeight = 0;
	glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

	//Set context for GLEW
	glfwMakeContextCurrent(window);

	//Allow modern extension features
	glewExperimental = GL_TRUE;

	//Init GLEW
	const int glewInitResult = glewInit();
	if (glewInitResult != GLEW_OK) {
		Logger::get().error("Error initializing GLEW : \n");
		Logger::get().error(glewGetErrorString(glewInitResult));
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

GLuint vao, vbo, ibo;
const GLuint vertexIndices[] = {
	0,1,4, //Front face
	1,4,5,
	0,1,2,//Top face
	1,2,3,
	2,3,6,//Back face
	3,6,7,
	4,5,6,//Bottom face
	5,6,7,
	0,2,4,//Left face
	2,4,6,
	1,3,5,//Right face
	3,5,7
};

const GLfloat cubeVertices[] = {
	-1.0f,1.0f,-1.0f,//Top Front Left
	1.0f,1.0f,-1.0f,//Top Front Right
	-1.0f,1.0f,1.0f,//Top Back Left
	1.0f,1.0f,1.0f,//Top Back Right
	-1.0f,-1.0f,-1.0f,//Bottom Front Left
	1.0f,-1.0f,-1.0f,//Bottom Front Right
	-1.0f,-1.0f,1.0f,//Bottom Back Left
	1.0f,-1.0f,1.0f//Bottom Back Right
};


void createCube() {
	//Create & bind VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Create & bind IBO
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices, GL_STATIC_DRAW);

	//Create & bind VBO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	//Create pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	//Unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


int main(int argc, char** argv) {
	int initResult = init();

	ShaderProgram program = ShaderProgram("shader.vert", "shader.frag");
	//Create model matrix
	program.createUniform("model");

	createCube();

	float angle = 0.0f;

	//Loop until window closed
	while (!glfwWindowShouldClose(window)) {
		//Update offset
		angle += 0.5f;

		//Get user inputs
		glfwPollEvents();

		//Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Draw triangle
		glUseProgram(program.getId());

		glm::mat4 model(1.0f);
		model = glm::rotate(model, angle * toRadians, glm::vec3(0.4f, 1.0f, 0.2f));
		model = glm::scale(model, glm::vec3(0.4f));
		glUniformMatrix4fv(program.getUniform("model"), 1, GL_FALSE, glm::value_ptr(model));

		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		glDrawElements(GL_TRIANGLES, sizeof(vertexIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glUseProgram(0);

		glfwSwapBuffers(window);
	}

	return 0;
}
