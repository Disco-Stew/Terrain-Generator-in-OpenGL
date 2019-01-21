#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

#include "info.h"
#include "Shader.h"
#include "FractalNoise.h"

struct Vertex
{
	glm::vec3 Pos, Norm;
	glm::vec2 Tex;
};

/*
Procedural grid class

Create the grid for the terrain.
Uses a grid of square cells made up of two triangles. Tesselates using diamond patterns for smoother terrain.
Calculates the normals and fault lines for the grid.
*/
class ProceduralGrid
{
public:
	ProceduralGrid();
	~ProceduralGrid(void);
	
	void Smooth(GLuint iterations, GLuint centerweight);
	void RandomNoise(float magnitude);
	void Fault(GLuint iterations, float initdisplacement, float dampening);
	

protected:
	enum VertexAttribute { POSITION, NORMAL, TEXCOORDINATE };
	
	glm::vec3 ProceduralGrid::generateNormal(glm::vec3 trianglePoint1, glm::vec3 trianglePoint2, glm::vec3 trianglePoint3);
	Noise* noise;
	
	void CalculateMedianHeight(void);
	GLvoid ProceduralGrid::init();
	GLvoid ProceduralGrid::createBuffers();
	GLvoid ProceduralGrid::deleteBuffers();
	GLvoid ProceduralGrid::setBuffers();
	GLuint m_iWidth, m_iHeight, m_uiNumVertices, m_hVBOVertexBuffer, m_hVBOIndexBuffer;
	GLfloat m_fHsize, m_fVsize, m_fMedianHeight, m_fTileSize;
	GLuint m_uiNumSubsets;
	GLuint * pIndices;
	GLuint NumTriangles;
	
	GLuint vertexBuffer;
	GLuint indexBuffer;
	GLuint textureBuffer;
	GLuint normalBuffer;

	GLfloat *vertices;
	GLfloat *normals;
	GLfloat *textureCoords;
	GLuint *indices;
	GLfloat size;
	GLint seed;
	GLint amplitude;
	glm::vec3 *normalVectors;

	GLuint vertexCount;
	GLuint count;
	GLuint verticesCount;
	GLuint textureCoordsCount;
	GLuint indicesCount;
	GLuint noOfTriangles;

	GLuint vbo;
	GLuint vao;
	GLuint ibo;
	glm::mat4 model;
};
