#ifndef EDITOR_UTILITIES
#define EDITOR_UTILITIES

#include <iostream>
#include <cstring>

char* CopyCatChars(const char* firstWord, const char* secondWord);

char* GetResourcePath();
char* GetShaderPath();
char* GetTexturePath();

char* GetShader(const char* shaderName);
char* GetTexture(const char* textureName);

#endif