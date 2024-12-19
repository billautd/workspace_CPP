#include "Shader.h"
#include "Logger.hpp"
#include <fstream>
#include <iostream>
#include <string>

Shader::Shader(std::string path, GLenum type):type(type) {
	readFile(path);
}

Shader::~Shader() {
	//Nothing
}

void Shader::readFile(std::string path) {
	std::ifstream fileStream(path, std::ios::in);

	if (!fileStream.is_open()) {
		Logger::get().error("Cannot open file at " + path);
		return;
	}

	std::string line;
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + '\n');
	}
	fileStream.close();

	Logger::get().info("Read file at " + path);
}

int Shader::createShader() {
	this->type = type;
	//Create
	id = glCreateShader(type);

	//Pointer to code
	const GLchar* code[1];
	code[0] = content.c_str();

	//Pointer to code length
	GLint codeLength[1];
	codeLength[0] = strlen(content.c_str());

	//Compile
	glShaderSource(id, 1, code, codeLength);
	glCompileShader(id);

	GLint result;
	GLchar log[1024];

	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE) {
		glGetShaderInfoLog(id, sizeof(log), NULL, log);
		Logger::get().error("Error compiling " + typeToString() + " shader : \n" + log);
		return 1;
	}

	Logger::get().info("Created " + typeToString() + " shader");
	Logger::get().debug("Content : \n" + content);
	return 0;
}

std::string Shader::typeToString() {
	switch(type){
	case GL_VERTEX_SHADER:
		return "vertex";
	case GL_FRAGMENT_SHADER:
		return "fragment";
	default:
		return std::to_string(type);
	}
}