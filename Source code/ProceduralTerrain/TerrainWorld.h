#pragma once

#include "GameWorld.h"
#include "info.h"
#include "Shader.h"

#include "Camera.h"
#include "SkyBox.h"
#include "Terrain.h"
//#include "TerrainGenerator.h"
#include "Water.h"


class TerrainWorld : public GameWorld
{
private:
	Camera camera;
	SkyBox skyBox;
	//TerrainGenerator* terrainGenerator;
	Water* water;
	Terrain* terrain;
	GLboolean lines = false;

	GLuint size = 3200;
	GLuint vertexCount = 4;

public:
	TerrainWorld();
	~TerrainWorld();

	GLvoid update(GLfloat deltaTime);
	GLvoid draw(GLfloat deltaTime);

	GLvoid input(GLFWwindow* window, int key, int scancode, int action, int mode);
	GLvoid mouseButton(GLFWwindow* window, int button, int action, int mods);
	GLvoid mouseInput(GLFWwindow* window, double xPosition, double yPosition);
	GLvoid scrollInput(GLFWwindow* window, double xScroll, double yScroll);
};

