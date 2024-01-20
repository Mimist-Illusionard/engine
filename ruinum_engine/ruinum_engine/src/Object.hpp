#ifndef SHADERFUNCTIONAL
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../stb_image.h"
#include "TextureLoader.h"

enum DrawMode
{
	SOLIDMODE = 0,
	WAREFRAMEMODE = 1,
};

class Object
{
	unsigned int VBO, VAO, EBO;
public:
	Object();
	~Object();
	void InputVertex();
	void Draw(int);
};

Object::Object()
{
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
}
 
Object::~Object()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Object::InputVertex()
{
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
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

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	LoadTexture("D:/GitHub/engine/ruinum_engine/resources/textures/wall.jpg");

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Object::Draw(int drawMode)
{
	glBindVertexArray(VAO);
	switch (drawMode)
	{
		case SOLIDMODE: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
		case WAREFRAMEMODE: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
	}
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

#endif