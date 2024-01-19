#include "Shader.h"
#include <iostream>

int success;
char infoLog[512];

bool CreateVertexShader(const char* vertexShaderSource, unsigned int* vertexShader)
{
	*vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(*vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(*vertexShader);
	glGetShaderiv(*vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(*vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

		return false;
	}

	return true;
}

bool CreateFragmentShader(const char* fragmentShaderSource, unsigned int* fragmentShader)
{
	*fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(*fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(*fragmentShader);
	glGetShaderiv(*fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(*fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}

	return true;
}

bool CreateShader(const char* vertexShaderSource, const char* fragmentShaderSource, unsigned int* shaderProgram)
{
	unsigned int vertexShader;
	unsigned int fragmentShader;

	if (!CreateVertexShader(vertexShaderSource, &vertexShader)) 
	{
		std::cout << "Error in compilation of vertex shader." << std::endl;
		return false;
	}
	
	if (!CreateFragmentShader(fragmentShaderSource, &fragmentShader) )
	{
		std::cout << "Error in compilation of fragment shader." << std::endl;
		return false;
	}

	*shaderProgram = glCreateProgram();
	glAttachShader(*shaderProgram, vertexShader);
	glAttachShader(*shaderProgram, fragmentShader);
	glLinkProgram(*shaderProgram);
	glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);
	
	if (!success)
	{
		glGetProgramInfoLog(*shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;

		return false;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return true;
}