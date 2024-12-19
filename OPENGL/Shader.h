#pragma once
#include <iostream>
#include <map>
#include "GL/glew.h"

class Shader
{
private:
	GLuint id = 0;
	GLenum type;
	std::string content;
	void readFile(std::string path);
public:
	Shader(std::string path, GLenum type);
	~Shader();

	GLuint getId() { return id;	}
	/*
	* Creates and compiles shader
	* 
	* Returns error code
	*/
	int createShader();

	std::string typeToString();
};

