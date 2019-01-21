#pragma once
#include "ProceduralGrid.h"

class Terrain : public ProceduralGrid
{
public:
	Terrain();
	~Terrain(void);
	void Render(glm::mat4 view, glm::mat4 projection);
	GLvoid Terrain::reset();
	GLvoid bindTextures(GLuint program);
	GLvoid createTextures();
	Shader* shaderProgram;
protected:
	GLuint snowTexture, sandTexture, grassTexture, rockTexture;
	GLuint m_hTex[4];
	glm::vec4 SunLight_Ambient;
	glm::vec4 SunLight_Diffuse;
	glm::vec4 SunLight_Specular;
	glm::vec4 SunLight_Position;
};
