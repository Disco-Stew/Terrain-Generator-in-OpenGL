#pragma once
#include <glew.h>
#include <time.h>
#include <stdlib.h>

#include "Noise.h"
#include "helper.h"

class FractalNoise : public Noise
{
private:
	GLint iterations = 0;
	GLint variation = 0;

	GLfloat seed = 0;
	GLint arrayLength = 0;

	GLfloat rough;
	GLfloat roughness;

	GLint size;
	GLint divisions;
	GLfloat min, max;

	GLvoid makeTexture();
	GLvoid diamond(GLint x, GLint y, GLint side, GLfloat scale);
	GLvoid square(GLint x, GLint y, GLint side, GLfloat scale);

public:
	FractalNoise(GLint resolution, GLint seed, GLfloat roughness);
	~FractalNoise();

	GLfloat getAltitude(GLint x, GLint y);

	GLuint texture;

	// keeping it here for testing
	GLfloat** map;

};