#pragma once
#include <glew.h>
#include <iostream>
#include <String.h>
#include <sstream>
#include <vector>
#include <fstream> 

class Shader
{
private:
	GLuint program;
	GLchar* shaderName = "";
public:

	Shader::Shader(const GLchar* vertexFilePath, const GLchar* fragmentFilePath);
	Shader::Shader(GLchar* shaderName, const GLchar* vertexFilePath, const GLchar* fragmentFilePath);
	GLuint getProgram();

	void useProgram();


};