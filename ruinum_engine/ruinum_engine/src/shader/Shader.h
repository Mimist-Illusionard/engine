#ifndef SHADER
#include <glad/glad.h>
#include <GLFW/glfw3.h>

bool CreateVertexShader(const char* vertexShaderSource, unsigned int* vertexShader);
bool CreateFragmentShader(const char* fragmentShaderSource, unsigned int* fragmentShader);

bool CreateShader(const char* vertexShaderSource, const char* fragmentShaderSource, unsigned int* shaderProgram);
#endif