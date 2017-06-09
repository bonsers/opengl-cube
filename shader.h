#pragma once

#include <GL\glew.h>

class Shader
{
public:
	Shader(const GLchar* vShaderCode, const GLchar* fShaderCode);
	~Shader();
	GLuint Program;
	void Use();
};

