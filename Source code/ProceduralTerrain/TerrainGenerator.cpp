//#include "TerrainGenerator.h"
//
//
//TerrainGenerator::TerrainGenerator()
//{
//	defaultPosition = glm::vec3(0, 0, 0);
//}
//
//TerrainGenerator::TerrainGenerator(glm::vec3 positions, GLint seed, GLint amplitude, GLuint vertexCount, GLuint size)
//{
//	this->vertexCount = vertexCount;
//	this->size = size;
//	defaultNoise = new FractalNoise(log2(vertexCount), seed, 0.50);
//	terrain = new Terrain(positions, seed, amplitude, vertexCount, size, defaultNoise, exponent);
//	terrain->createAndFillVertexArrayObject();
//	terrain->createTextures();
//	
//
//	//GLfloat test = terrain->getHeight(0, 0);
//	//grassSystem.push_back(new GrassSystem(positions, size, size));
//	
//	Mountain* mountain = new Mountain(glm::vec3(positions.x + size, positions.y, positions.z), seed + 1);
//	
//	mountains.push_back(mountain);
//	mountain->createAndFillVertexArrayObject();
//
//	numTerrains++;
//	numMountains++;
//	seedMap[0] = terrain;
//	mountainSeedMap[0] = mountain;
//
//	// Grass system
//	/*setHeights();
//	grassSystem.at(0)->update();*/
//
//}
//
//TerrainGenerator::~TerrainGenerator()
//{
//
//}
//
//GLvoid TerrainGenerator::init(glm::vec3 positions, GLint seed, GLint amplitude, GLuint vertexCount, GLuint size)
//{
//}
//
////GLvoid TerrainGenerator::setHeights()
////{
////	std::vector<glm::mat4>* matrices = grassSystem.at(0)->getObjectPositions();
////	for (GLuint i = 0; i < matrices->size(); i++)
////	{
////		//matrices->at(i) = (glm::translate(matrices->at(i), glm::vec3(matrices->at(i)[3][0], 5000, matrices->at(i)[3][2])));
////		matrices->at(i) = (glm::translate(matrices->at(i), glm::vec3(0.0f, terrains.at(0)->getHeight(matrices->at(i)[3][0], matrices->at(i)[3][2]), 0.0f)));
////	}
////}
//
//GLvoid TerrainGenerator::redoPosition(glm::vec3 positions)
//{
//	GLuint seed = terrain->getSeed();
//	GLuint amplitude = terrain->getAmplitude();
//	GLuint vertexCount = terrain->getVertexCount();
//	GLuint size = terrain->getSize();
//	GLfloat exp = terrain->getExponent();
//	delete(terrain);
//	terrain = new Terrain(positions, seed, amplitude, vertexCount, size, defaultNoise, exp);
//}
//
//GLvoid TerrainGenerator::redoAmplitude(GLuint amplitude)
//{
//	glm::vec3 positions = terrain->getPosition();
//	GLuint seed = terrain->getSeed();
//	GLuint vertexCount = terrain->getVertexCount();
//	GLuint size = terrain->getSize();
//	GLfloat exp = terrain->getExponent();
//	delete(terrain);
//	terrain = new Terrain(positions, seed, amplitude, vertexCount, size, defaultNoise, exp);
//}
//
//GLvoid TerrainGenerator::redoVertexCount(GLuint vertexCount)
//{
//	glm::vec3 positions = terrain->getPosition();
//	GLuint seed = terrain->getSeed();
//	GLuint amplitude = terrain->getAmplitude();
//	GLuint size = terrain->getSize();
//	GLfloat exp = terrain->getExponent();
//	delete(terrain);
//	terrain = new Terrain(positions, seed, amplitude, vertexCount, size, defaultNoise, exp);
//}
//
//GLvoid TerrainGenerator::redoSize(GLuint size)
//{
//	glm::vec3 positions = terrain->getPosition();
//	GLuint seed = terrain->getSeed();
//	GLuint amplitude = terrain->getAmplitude();
//	GLuint vertexCount = terrain->getVertexCount();
//	GLfloat exp = terrain->getExponent();
//	delete(terrain);
//	terrain = new Terrain(positions, seed, amplitude, vertexCount, size, defaultNoise, exp);
//}
//GLvoid TerrainGenerator::redoExponent()
//{
//	glm::vec3 positions = terrain->getPosition();
//	GLuint seed = terrain->getSeed();
//	GLuint amplitude = terrain->getAmplitude();
//	GLuint vertexCount = terrain->getVertexCount();
//	GLuint size = terrain->getSize();
//	delete(terrain);
//	terrain = new Terrain(positions, seed, amplitude, vertexCount, size, defaultNoise, exponent);
//}
//
//GLvoid TerrainGenerator::redo(glm::vec3 positions, GLint seed, GLint amplitude, GLuint vertexCount, GLuint size, GLfloat exp)
//{
//	delete(terrain);
//	terrain = new Terrain(positions, seed, amplitude, vertexCount, size, defaultNoise, exp);
//}
//
//GLvoid TerrainGenerator::addExponent(GLfloat exp)
//{
//	exponent += exp;
//	if (exponent < 0.0f) {
//		exponent = 0.0f;
//	}
//	else if (exponent > 10.0f) {
//		exponent = 10.0f;
//	}
//	change = true;
//}
//GLvoid TerrainGenerator::method(GLint seed)
//{
//	for (GLint i = 0; i < 10; i++)
//	{
//		std::cout << "Printing in seperate thread" << std::endl;
//	}
//}
//
//GLvoid TerrainGenerator::makeNewTerrain(GLint numTerrains, GLint  seed)
//{
//	std::cout << "Generating new terrain: " << std::endl;
//	glm::vec3 position = terrains.at(0)->getPosition();
//	Terrain* temp = nullptr;	
//	
//	FractalNoise* noise = new FractalNoise(log2(vertexCount), seed, 0.50);
//	temp = new Terrain(glm::vec3(position.x, position.y, (seed) * size), numTerrains, 700, (GLint)257, size, noise, 1.0);
//	
//	terrains.push_back(temp);
//	seedMap[seed] = terrains.at(numTerrains);
//	finished = true;
//	std::cout << "z position: " << position.z << std::endl;
//}
//
//GLvoid TerrainGenerator::makeNewMountain(GLint numTerrains, GLint  seed)
//{
//	std::cout << "Generating new terrain: " << std::endl;
//	glm::vec3 position = mountains.at(numMountains - 1)->getPosition();
//	Mountain* temp = nullptr;
//
//	temp = new Mountain(glm::vec3(position.x, position.y, (seed)* size), seed);
//
//	mountains.push_back(temp);
//	mountainSeedMap[seed] = mountains.at(numMountains);
//	mountainFinished = true;
//}
//
//GLvoid TerrainGenerator::update(GLfloat deltaTime, Camera camera)
//{
//	GLint zPosition = camera.getCameraPosition().z;
//
//	GLint zPos = (zPosition);
//	GLint xPos = (camera.getCameraPosition().x);
//
//	GLint seed = (zPos ) / size;
//	
//	/*if (seedMap.find(seed) == seedMap.end() || finished)
//	{
//		if (finished)
//		{
//			threadOne->join();
//			numTerrains++;
//			terrains.at(numTerrains - 1)->createAndFillVertexArrayObject();
//			delete(threadOne);
//			threadOne = nullptr;
//			finished = false;
//			std::cout << terrains.size() << std::endl;
//		}else if (threadOne == nullptr && !finished)
//		{
//			std::cout << " new thread" << std::endl;
//			threadOne = new std::thread(&TerrainGenerator::makeNewTerrain, this, seed, seed);
//		}
//	}
//	if (change) {
//		redoExponent();
//		change = false;
//	}*/
//
//	//if (mountainSeedMap.find(seed) == mountainSeedMap.end() || mountainFinished)
//	//{
//	//	if (mountainFinished)
//	//	{
//	//		mountainThread->join();
//	//		numMountains++;
//	//		mountains.at(numMountains - 1)->createAndFillVertexArrayObject();
//	//		delete(mountainThread);
//	//		mountainThread = nullptr;
//	//		mountainFinished = false;
//	//	}
//
//	//	else if (mountainThread == nullptr && !mountainFinished)
//	//	{
//	//		mountainThread = new std::thread(&TerrainGenerator::makeNewMountain, this, seed, seed);
//	//	}
//	//}
////}
//
////GLvoid TerrainGenerator::draw(glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPosition)
////{
////
////	/*for (GLuint i = 0; i < grassSystem.size(); i++)
////	{
////		grassSystem[i]->draw(view, projection, cameraPosition);
////	}*/
////
////	for (GLuint i = 0; i < numTerrains; i++)
////	{
////		terrains.at(i)->draw(view, projection);
////	}
////
////	//for (GLuint i = 0; i < numMountains; i++)
////	//{
////	//	mountains.at(i)->draw(view, projection);
////	//}
////}
//
////GLvoid TerrainGenerator::draw(glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPos)
////{
////	terrain->draw(view, projection, cameraPos);
//	/*for (GLuint i = 0; i < numTerrains; i++)
//	{
//		terrains.at(i)->draw(view, projection, cameraPos);
//	}
//
//	for (GLuint i = 0; i < numMountains; i++)
//	{
//		mountains.at(i)->draw(view, projection);
//	}*/
//}