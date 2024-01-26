#ifndef EDITOR_UTILITIES_H
#define EDITOR_UTILITIES_H

#include <iostream>
#include <cstring>

char* CopyCatChars(const char* firstWord, const char* secondWord);

char* GetResourcePath();
char* GetShaderPath();
char* GetTexturePath();

char* GetShader(const char* shaderName);
char* GetTexture(const char* textureName);

#endif