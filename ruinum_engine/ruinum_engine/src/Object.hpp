#ifndef OBJECT_SHADER
#define OBJECT_SHADER

#include "TextureLoader.h"
#include "Global.h"
#include "../stb_image.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum DrawMode
{
	SOLIDMODE = 0,
	WAREFRAMEMODE = 1,
};

class Object
{
	unsigned int VBO, VAO;
public:
	Object();
	~Object();
	void InputVertex();
	void Draw(int);
	void BindVAO() {glBindVertexArray(VAO);}
};

Object::Object()
{
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
}
 
Object::~Object()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Object::InputVertex()
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coords attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	LoadTexture("wall.jpg");

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Object::Draw(int drawMode)
{
	switch (drawMode)
	{
		case SOLIDMODE: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
		case WAREFRAMEMODE: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
	}
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

#endif