#pragma once
#include <glew.h>

/*
 * Abstract class Noise
*/
class Noise
{
private:

protected:
	GLint seed;

public:
	virtual GLfloat getAltitude(GLint x, GLint z) = 0;
};