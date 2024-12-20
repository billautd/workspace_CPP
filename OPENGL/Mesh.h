#pragma once
#include "GL/glew.h"



class Mesh
{
private:
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	unsigned int vertexCount;
	unsigned int indexCount;
public:
	Mesh(const GLfloat* vertices, const GLuint* indices,
		const unsigned int vertexCount, const unsigned int indexCount);
	~Mesh();

	/*
	* Creates mesh
	* We have to pass counts for arrays because arrays passed as parameters are size 0
	*/
	void create(const GLfloat* vertices, const GLuint* indices,
			const unsigned int vertexCount, const unsigned int indexCount);
	void render();
	void destroy();
};

