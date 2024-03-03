#ifndef SHADER_COMPONENT
#define SHADER_COMPONENT

#include "../../shader/Shader.hpp"

struct ShaderComponent
{
	Shader mShader;
	const char* FragmentPath;
	const char* VertexPath;

	const char* Diffuse = "";
	const char* Specular = "";

	ShaderComponent() {}
	ShaderComponent(const char* vertexPath, const char* fragmentPath)
	{		
		VertexPath = vertexPath;
		FragmentPath = fragmentPath;

		mShader = Shader{ VertexPath, FragmentPath };
	}
};

#endif