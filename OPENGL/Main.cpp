#include <iostream>
#include <vector>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Constants.h"
#include "Logger.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Window.h"

const float toRadians = 3.14159265f / 180.0f;
std::vector<Mesh*> meshList;

void createObjects() {
	const GLuint indices[] = {
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
	const unsigned int indexCount = sizeof(indices) / sizeof(indices[0]);


	const GLfloat vertices[] = {
		-1.0f,1.0f,-1.0f,//Top Front Left
		1.0f,1.0f,-1.0f,//Top Front Right
		-1.0f,1.0f,1.0f,//Top Back Left
		1.0f,1.0f,1.0f,//Top Back Right
		-1.0f,-1.0f,-1.0f,//Bottom Front Left
		1.0f,-1.0f,-1.0f,//Bottom Front Right
		-1.0f,-1.0f,1.0f,//Bottom Back Left
		1.0f,-1.0f,1.0f//Bottom Back Right
	};
	const unsigned int vertexCount = sizeof(vertices) / sizeof(vertices[0]);

	Mesh* cube1 = new Mesh(vertices, indices, vertexCount, indexCount);
	Mesh* cube2 = new Mesh(vertices, indices, vertexCount, indexCount);

	meshList.push_back(cube1);
	meshList.push_back(cube2);
}

int main(int argc, char** argv) {
	Window window = Window(1920, 1080);
	window.init();

	ShaderProgram program = ShaderProgram("shader.vert", "shader.frag");
	//Create model matrix
	program.createUniform("model");
	program.createUniform("projection");
	program.createUniform("view");

	//Projection
	glm::mat4 projection = glm::perspective(45.0f, window.getAspectRatio(), 0.1f, 100.0f);
	//View
	glm::mat4 view(1.0f);

	createObjects();

	float angle = 0.0f;

	//Loop until window closed
	while (!window.shouldClose()) {
		//Update offset
		angle += 0.5f;

		//Get user inputs
		glfwPollEvents();

		//Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Draw triangle
		program.use();

		//Projection
		glUniformMatrix4fv(program.getUniform(ShaderProgram::PROJECTION_NAME), 1, GL_FALSE, glm::value_ptr(projection));
		//View
		glUniformMatrix4fv(program.getUniform(ShaderProgram::VIEW_NAME), 1, GL_FALSE, glm::value_ptr(view));

		//Model
		glm::mat4 model(1.0f);
		//Move away cube from us to see after projection
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, -2.5f));
		model = glm::rotate(model, angle * toRadians, glm::vec3(0.4f, 1.0f, 0.2f));
		model = glm::scale(model, glm::vec3(0.5f));
		glUniformMatrix4fv(program.getUniform(ShaderProgram::MODEL_NAME), 1, GL_FALSE, glm::value_ptr(model));
		meshList[0]->render();

		model = glm::mat4(1.0f);
		//Move away cube from us to see after projection
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -2.5f));
		model = glm::rotate(model, angle * toRadians, glm::vec3(0.4f, 1.0f, 0.2f));
		model = glm::scale(model, glm::vec3(0.5f));
		glUniformMatrix4fv(program.getUniform(ShaderProgram::MODEL_NAME), 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->render();

		program.reset();

		window.swapBuffers();
	}

	return 0;
}
