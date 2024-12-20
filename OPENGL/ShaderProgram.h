#pragma once
#include <map>
#include "GL/glew.h"
#include "Shader.h"

class ShaderProgram
{
private:
	GLuint id = 0;
	std::map<GLenum, Shader*> shaders;
	std::map<std::string, GLint> uniforms;

	/*
	* Create program
	* 
	* Returns error code
	*/
	const int create(std::string vertShaderPath, std::string fragShaderPath);

	/*
	* Add shader to this program
	* 
	* Returns error code
	*/
	const int addShader(std::string path, GLenum shaderType);
public:
	ShaderProgram(std::string vertShaderPath, std::string fragShaderPath);
	~ShaderProgram();

	const static std::string MODEL_NAME;
	const static std::string PROJECTION_NAME;
	const static std::string VIEW_NAME;

	GLuint getId() { return id; }
	Shader& getShader(GLenum type) { return *shaders[type]; }
	GLint getUniform(std::string name) { return uniforms[name]; }

	/*
	* Creates uniform variable
	*
	* Returns id
	*/
	GLint createUniform(std::string name);

	/*
	* Use this program
	*/
	void use() { glUseProgram(id); }

	/*
	* Reset program use
	*/
	void reset() { glUseProgram(0); }




};

