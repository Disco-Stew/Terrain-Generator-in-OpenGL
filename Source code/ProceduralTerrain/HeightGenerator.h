/#pragma once
//#include <glew.h>
//
//#include <random>
//#include <iostream>
//
//#define _USE_MATH_DEFINES
//#include <math.h>
//
//#include "TerrainType.h"
//
//class HeightGenerator
//{
//
//private:
//	GLfloat linear(GLfloat x, GLfloat z);
//	GLfloat smooth(GLfloat x, GLfloat z);
//
//	GLfloat linearInterpolate(GLfloat x, GLfloat z, GLfloat weight);
//	GLfloat cosInterpolate(GLfloat x, GLfloat z, GLfloat blend);
//
//	GLfloat getNoise(GLint x, GLint z);
//	GLfloat getMeanNoise(GLint x, GLint z);
//
//	GLint seed;
//	GLint amplitude;
//
//public:
//	HeightGenerator(GLint seed, GLint amplitude, TerrainType typeOfTerrain);
//	~HeightGenerator();
//
//	GLfloat (HeightGenerator::*generateHeight)(GLint x,  GLint z);
//
//	GLfloat randomNoise(GLint x, GLint z);
//	GLfloat linearValueNoise(GLint x, GLint z);
//	GLfloat smoothValueNoise(GLint x, GLint z);
//};
//
