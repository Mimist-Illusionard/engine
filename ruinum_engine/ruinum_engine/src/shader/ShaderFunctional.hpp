#ifndef SHADERFUNCTIONAL
#include "Shader.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum DrawMode
{
	SOLIDMODE = 0,
	WAREFRAMEMODE = 1,
};

class ShaderFunctional
{
	unsigned int shaderProgram;
	unsigned int VBO, VAO, EBO;
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";
public:
	ShaderFunctional();
	~ShaderFunctional();
	void InputVertex();
	void Draw(int);
};

ShaderFunctional::ShaderFunctional()
{
	if (!CreateProgramShader(vertexShaderSource, fragmentShaderSource, &shaderProgram))
	{
		std::cout << "Error in creating shader. See other errors." << std::endl;
	}

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
}
 
ShaderFunctional::~ShaderFunctional()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
}

void ShaderFunctional::InputVertex()
{
	float vertices[] =
	{
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	unsigned int indices[] =
	{
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void ShaderFunctional::Draw(int drawMode)
{
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	switch (drawMode)
	{
		case SOLIDMODE: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
		case WAREFRAMEMODE: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
	}
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

#endif