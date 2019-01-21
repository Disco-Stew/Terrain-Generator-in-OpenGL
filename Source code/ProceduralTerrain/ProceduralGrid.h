/*
Procedural grid class

The real heart of the terrain generator: allows the creation of a grid of square cells each made up of two triangles,
taking care to tesellate using diamond patterns for nicer looking terrain when undulated, as well as of calculating normals.
The class implements a number of terrain generation techniques (to be called at runtime after instantiation), which can be combined
to generate more complex terrains.
*/

#pragma once
#include "info.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "FractalNoise.h"
#include <cmath>

//#include "BaseGeometry.h"
//struct Material
//{
//	Material(void) { GLuint i; for (i = 0; i<4; i++) { Specular[i] = 0.0f; Emissive[i] = 0.0f; Diffuse[i] = 0.0f; Ambient[i] = 0.0f; } Shininess[0] = 1.0f; }
//	GLfloat Specular[4];
//	GLfloat Emissive[4];
//	GLfloat Diffuse[4];
//	GLfloat Ambient[4];
//	GLfloat Shininess[1];
//};
struct Vertex
{
	glm::vec3 Pos, Norm;
	glm::vec2 Tex;
};
class ProceduralGrid
{
public:
	ProceduralGrid();
	~ProceduralGrid(void);
	//Material material;
	//glm::vec3 GetGridSize(void) const;
	//float GetMedianHeight(void) const;
	//float GetPointHeight(float xpos, float zpos) const;
	//glm::vec3 GetPointNormal(float xpos, float zpos) const;
	//void Reset(float height = 0.0f);
	void Smooth(GLuint iterations, GLuint centerweight);
	void RandomNoise(float magnitude);
	void Fault(GLuint iterations, float initdisplacement, float dampening);
	

protected:
	enum VertexAttribute { POSITION, NORMAL, TEXCOORDINATE };
	//bool GetVertexAttrib(VertexAttribute attr, GLuint column, GLuint row, glm::vec3 &output) const;
	//GLvoid ProceduralGrid::addVertexArrayAttrib(GLuint vao, GLuint vbo, GLint attribute, GLint size, GLint dataLength, GLint offset);
	glm::vec3 ProceduralGrid::generateNormal(glm::vec3 trianglePoint1, glm::vec3 trianglePoint2, glm::vec3 trianglePoint3);
	Noise* noise;
	//void GenerateVertexBuffer(void);
	//void GenerateIndicesBuffer(void);
	//void NormalGen(void);
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
