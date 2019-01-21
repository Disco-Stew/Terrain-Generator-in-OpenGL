#pragma once
#include <glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SOIL.h>

#include "Shader.h"
#include "info.h"

class SkyBox
{
private:
	GLuint vertexArray;
	GLuint vertexBuffer;
	GLuint textureBuffer;

	Shader shader;

	GLuint numOfVertices;
	GLsizei sizeOfVertices;

	GLuint texture;
	std::vector<const GLchar*> faces;


public:
	SkyBox::SkyBox();
	~SkyBox();

	GLuint getTexture();

	void draw(glm::mat4 mvp);
};