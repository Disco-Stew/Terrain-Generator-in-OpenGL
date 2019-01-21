//#pragma once
//#include <iostream>
//#include <map>
//#include <thread>
//#include <functional>
//
//#include <glew.h>
//#include <glfw3.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "NoiseType.h"
//#include "Terrain.h"
//#include "Mountain.h"
//#include "Camera.h"
//#include "info.h"
//
///*
// * Class used to generate terrrain throughout the game world.
//*/
//class TerrainGenerator
//{
//private:
//	Noise* defaultNoise;
//
//
//	std::vector<Mountain*> mountains;
//	std::vector<Terrain*> smoothTerrain;
//	std::vector<Terrain*> mixedTerrain;
//
//	std::vector<Terrain*> terrains;
//	std::map<Terrain, GLint> terrainMap;
//	std::map<GLint, Terrain*> seedMap;
//	std::map<GLint, Mountain*> mountainSeedMap;
//
//	//std::vector<GrassSystem*> grassSystem;
//
//	GLint vertexCount = 0;
//	GLint size = 0;
//	GLint numTerrains = 0;
//	GLint numMountains = 0;
//	GLfloat exponent = 1.0f;
//	bool change;
//
//	glm::vec3 defaultPosition;
//
//	volatile bool finished = false;
//	volatile bool mountainFinished = false;
//
//	/*std::thread* threadOne = nullptr;
//	std::thread* mountainThread = nullptr;
//*/
//	GLvoid makeNewTerrain(GLint seed, GLint mark);
//	GLvoid makeNewMountain(GLint seed, GLint mark);
//
//	// tester method for calling a method through a seperate method
//	GLvoid method(GLint seed);
//
//public:
//	Terrain* terrain;
//	TerrainGenerator::TerrainGenerator();
//	TerrainGenerator::TerrainGenerator(glm::vec3 positions, GLint seed, GLint amplitude, GLuint vertexCount, GLuint size);
//	TerrainGenerator::~TerrainGenerator();
//
//	GLvoid init(glm::vec3 positions, GLint seed, GLint amplitude, GLuint vertexCount, GLuint size);
//	//GLvoid setHeights();
//
//	GLvoid redoPosition(glm::vec3 positions);
//	GLvoid redoAmplitude(GLuint amplitude);
//	GLvoid redoVertexCount(GLuint vertexCount);
//	GLvoid redoSize(GLuint size);
//	GLvoid redoExponent();
//	GLvoid redo(glm::vec3 positions, GLint seed, GLint amplitude, GLuint vertexCount, GLuint size, GLfloat exp);
//	GLvoid addExponent(GLfloat exp);
//
//	GLvoid update(GLfloat deltaTime, Camera camera);
//	GLvoid draw(glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPos);
//	GLvoid TerrainGenerator::draw(glm::mat4 view, glm::mat4 projection);
//	//GLvoid draw(glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPosition);
//};