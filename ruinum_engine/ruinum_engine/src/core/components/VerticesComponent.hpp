#ifndef VERTICES_COMPONENT
#define VERTICES_COMPONENT

struct VerticesComponent
{
	unsigned int VBO, VAO;
	float *Vertices;
	int Size;
	VerticesComponent(){}
	VerticesComponent(float vertices[])
	{
		Vertices = vertices;
		Size = sizeof(vertices) * 144;
	}
};

#endif