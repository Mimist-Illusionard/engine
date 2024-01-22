#include "TextureLoader.h"
#include <iostream>
#include <cstring>
#include <string.h>

char* CopyCatChars(const char* firstWord, const char* secondWord)
{
	char* result = new char[strlen(firstWord) + strlen(secondWord) + 1];

	strcpy_s(result, strlen(firstWord) + strlen(secondWord) + 1, firstWord);
	strcat_s(result, strlen(firstWord) + strlen(secondWord) + 1, secondWord);

	return result;
}

char* GetResourcePath()
{
	return CopyCatChars("D:/GitHub/engine/ruinum_engine/", "resources/");
}

char* GetShaderPath()
{
	return CopyCatChars(GetResourcePath(), "shaders/");
}

char* GetTexturePath()
{
	return CopyCatChars(GetResourcePath(), "textures/");
}

char* GetShader(const char* shaderName)
{
	return CopyCatChars(GetShaderPath(), shaderName);
}

char* GetTexture(const char* textureName)
{
	return CopyCatChars(GetTexturePath(), textureName);
}