#pragma once
#include <glew.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include "GameObject.h"
//#include "PointLight.h"

#include "SOIL.h"

/*
 * This class is used to provide an easy access to methods that are used over and over
 * by many objects in the codebase. 
 * Some exmaples are setting up vertex array objects, buffers and the loading of textures. 
*/
class Helper
{

private:

public:
	Helper();
	~Helper();

	// Buffer methods
	void createVertexArray(GLuint& vertexArray);
	void createEmptyVBO(GLuint& vbo, GLuint maxFloats);
	void fillVertexArrayWithVertices(GLuint vertexArray, GLuint& vertexBuffer, GLfloat vertices[], GLint length, GLuint index);
	void fillVertexArrayWithIndices(GLuint vertexArray, GLuint& indexBuffer, GLuint indices[], GLuint length);
	void fillVertexArrayWithNormals(GLuint vertexArray, GLuint& normalBuffer, GLfloat vertices[], GLint length, GLuint index);
	void fillVertexArrayWithTextureCoords(GLuint vertexArray, GLuint& textureBuffer, GLfloat vertices[], GLint length, GLuint index);

	//Instancing Methods
	void positionInstance(GLuint vertexArray, GLuint& instanceVBO, glm::vec3  positions[], GLint length, GLuint index,GLint divisor);
	void addInstancedAttrib(GLuint vao, GLuint vbo, GLint attribute, GLint size, GLint dataLength, GLint offset);
	void instancing(GLuint vertexArray, GLuint& instanceVBO, glm::mat4  matrices[], GLint length, GLuint index, GLint divisor);
	void refreshBuffer(GLuint& instanceVBO, glm::mat4  modelMatrices[], GLint length);

	// Texture methods
	void texture2DSetRepeatAndLinear(GLuint texture);
	void textureSetWrap(GLuint texture);
	void loadTextureWithImage2D(GLuint texture, char* imagePath, GLuint textureSampler);

	//Calculate closest pointlights
	//std::vector<PointLight> Helper::calculateClosestLightsToObject(GameObject gameObject, std::vector<PointLight> &objectList, int numberOfObjectsToReturn);


};

