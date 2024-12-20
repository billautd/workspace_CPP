#include "Mesh.h"
#include "Logger.h"

Mesh::Mesh(const GLfloat* indices, const GLuint* vertices,
	const unsigned int vertexCount, const unsigned int indexCount) : ibo(0), vao(0), vbo(0), vertexCount(vertexCount), indexCount(indexCount) {
	create(indices, vertices, vertexCount, indexCount);
}

Mesh::~Mesh() {
	destroy();
}

void Mesh::create(const GLfloat* vertices, const GLuint* indices, 
		const unsigned int vertexCount, const unsigned int indexCount) {
	//Create & bind VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Create & bind IBO
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indexCount, indices, GL_STATIC_DRAW);

	//Create & bind VBO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertexCount, vertices, GL_STATIC_DRAW);
	//Create pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	//Unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::render() {
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::destroy() {
	if (ibo != 0) {
		glDeleteBuffers(1, &ibo);
		ibo = 0;
	}
	if (vbo != 0) {
		glDeleteBuffers(1, &vbo);
		vbo = 0;
	}
	if (vao != 0) {
		glDeleteBuffers(1, &vao);
		vao = 0;
	}
}