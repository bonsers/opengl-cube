#include "shader.h"
#include <iostream>



Shader::Shader(const GLchar* vShaderCode, const GLchar* fShaderCode)
{
	// COMPILE SHADERS
	GLuint vertex;
	GLuint fragment;
	GLchar infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);
	GLint success;
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		std::cout << "ERROR VERTEX SHADER COMPILATION FAILED: " << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		std::cout << "ERROR FRAGMENT SHADER COMPILATION FAILED: " << infoLog << std::endl;
	}

	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glLinkProgram(this->Program);

	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->Program, 512, nullptr, infoLog);
		std::cout << "ERROR LINKING FAILED: " << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


Shader::~Shader()
{
}

void Shader::Use()
{
	glUseProgram(this->Program);
}