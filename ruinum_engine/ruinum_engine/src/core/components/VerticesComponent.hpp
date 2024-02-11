#ifndef VERTICES_COMPONENT
#define VERTICES_COMPONENT

struct VerticesComponent
{
	unsigned int VBO, VAO;
	float *Vertices;
	VerticesComponent(){}
	VerticesComponent(float vertices[])
	{
		Vertices = vertices;
	}
};

#endif