#pragma once
#include "info.h"
#include "ProceduralGrid.h"

/*
Class representing the water plane

Derived from ProceduralGrid, uses WaterTech for rendering.
*/
class Water : public ProceduralGrid
{
public:
	Water(char* imagePath);
	~Water(void);
	void Render(glm::mat4 view, glm::mat4 projection, float time);
	Shader* shaderProgram;
	GLuint textureID;

protected:
	//WaterTech m_Technique;
	GLuint m_hTex[1];
	
};
#pragma once
