#ifndef RENDER_RENDER_HPP
#define RENDER_RENDER_HPP

#include "editor/TextureLoader.h"
#include "Global.h"
#include "../stb_image.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

enum DrawMode
{
	SOLID_MODE = 0,
	WAREFRAME_MODE = 1,
};

class RenderObject
{
	unsigned int VBO, VAO;
public:
	RenderObject();
	~RenderObject();
	void InputVertex();
	void Draw(int);
	void BindVAO() {glBindVertexArray(VAO);}
};

RenderObject::RenderObject()
{
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
}
 
RenderObject::~RenderObject()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void RenderObject::InputVertex()
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

void RenderObject::Draw(int drawMode)
{
	switch (drawMode)
	{
		case SOLID_MODE: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
		case WAREFRAME_MODE: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
	}
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

#endif