#include "ShaderProgram.h"
#include "Logger.hpp"

#include <iostream>

ShaderProgram::ShaderProgram(std::string vertShaderPath, std::string fragShaderPath) {
	create(vertShaderPath, fragShaderPath);
}

ShaderProgram::~ShaderProgram() {
	//Nothing
}

const int ShaderProgram::create(std::string vertShaderPath, std::string fragShaderPath)
{
	id = glCreateProgram();
	if (id == 0) {
		Logger::get().error("Error creating shader program");
		return 1;
	}

	addShader(vertShaderPath, GL_VERTEX_SHADER);
	addShader(fragShaderPath, GL_FRAGMENT_SHADER);

	GLint result;
	GLchar log[1024];

	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &result);
	if (result != GL_TRUE) {
		glGetProgramInfoLog(id, sizeof(log), NULL, log);
		Logger::get().error("Error linking program : \n" + std::string(log));
		return 2;
	}

	glValidateProgram(id);
	glGetProgramiv(id, GL_VALIDATE_STATUS, &result);
	if (result != GL_TRUE) {
		glGetProgramInfoLog(id, sizeof(log), NULL, log);
		Logger::get().error("Error validating program : \n" + std::string(log));
		return 3;
	}
	Logger::get().info("Created program with id " + std::to_string(id) + " and " + std::to_string(shaders.size()) + " shaders");
	return 0;
}

const int ShaderProgram::addShader(std::string path, GLenum shaderType) {
	Shader* shader = new Shader(path, shaderType);
	const int result = shader->createShader();
	if (result != 0) {
		Logger::get().error("Error creating " + shader->typeToString() + " shader");
		return result;
	}
	this->shaders.emplace(shaderType, shader);
	glAttachShader(id, shader->getId());
	Logger::get().info("Added " + shader->typeToString() + " to program " + std::to_string(id));
	return 0;
}

GLint ShaderProgram::createUniform(std::string name) {
	GLint uniform = glGetUniformLocation(id, name.c_str());
	if (uniform == -1) {
		Logger::get().error("Cannot create uniform " + name + " for program " + std::to_string(id));
		return -1;
	}
	uniforms.emplace(name, uniform);
	Logger::get().info("Created uniform " + name + " at id " + std::to_string(uniform));
	return uniform;
}
