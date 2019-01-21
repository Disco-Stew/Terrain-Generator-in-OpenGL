//#include "HeightGenerator.h"
//
//HeightGenerator::HeightGenerator(GLint seed, GLint amplitude, TerrainType terrainType)
//{
//	switch (terrainType)
//	{
//		//case TerrainType::RANDOM:
//		//	generateHeight = &HeightGenerator::randomNoise;
//		//	break;
//
//		//	case TerrainType::
//	}
//
//	this->seed = seed;
//	this->amplitude = amplitude;
//}
//
//
//HeightGenerator::~HeightGenerator()
//{
//}
//
//// Methods for generating height based on different noise types and interpolation
//GLfloat HeightGenerator::randomNoise(GLint x, GLint z)
//{
//	return getNoise(x, z) * amplitude;
//}
//
//GLfloat HeightGenerator::linearValueNoise(GLint x, GLint z)
//{
//	return linear(x, z) * amplitude;
//}
//
//GLfloat HeightGenerator::smoothValueNoise(GLint x, GLint z)
//{
//	return smooth((GLfloat)x/8.0f, (GLfloat)z/8.0f) * 550;
//}
//
//
///* 
// * Methods for generating the height values.
// */
//GLfloat HeightGenerator::linear(GLfloat x, GLfloat z)
//{
//	int intX = (int)x;
//	int intZ = (int)z;
//
//	float fracX = x - intX;
//	float fracZ = z - intZ;
//
//	GLfloat v1 = getNoise(intX - 128, intZ -128);
//	GLfloat v2 = getNoise(intX - 128, intZ + 128);
//	GLfloat v3 = getNoise(intX + 128, intZ + 128);
//	GLfloat v4 = getNoise(intX + 128, intZ - 128);
//
//	// linear interpolate on the x-axis followed by the z-axis
//	float i1 = linearInterpolate(v1, v2, fracX);
//	float i2 = linearInterpolate(v3, v4, fracX);
//	return (linearInterpolate(i1, i2, fracZ));
//}
//
//GLfloat HeightGenerator::smooth(GLfloat x, GLfloat z)
//{
//	int intX = (int)x;
//	int intZ = (int)z;
//
//	float fracX = x - intX;
//	float fracZ = z - intZ;
//
//	GLfloat v1 = getMeanNoise(intX, intZ);
//	GLfloat v2 = getMeanNoise(intX + 1, intZ);
//	GLfloat v3 = getMeanNoise(intX, intZ + 1);
//	GLfloat v4 = getMeanNoise(intX + 1, intZ + 1);
//
//	float i1 = cosInterpolate(v1, v2, fracX);
//	float i2 = cosInterpolate(v3, v4, fracX);
//	return (cosInterpolate(i1, i2, fracZ));
//}
//
//
///*
//* Methods for determining how the height values are interpolated
//* based on the values around it on the grid.
//*/
//GLfloat HeightGenerator::linearInterpolate(GLfloat value, GLfloat valueTwo, GLfloat weight)
//{
//	return (GLfloat)(weight * valueTwo + ((1 - weight) * value));
//}
//
//GLfloat HeightGenerator::cosInterpolate(GLfloat x, GLfloat z, GLfloat blend)
//{
//	GLdouble theta = blend * M_PI;
//	GLfloat f = (1.0f - (GLfloat)cos(theta)) * 0.5f;
//
//	return (GLfloat)(x * (1.0f - f) + z * f);
//}
//
//
///*
// * Generate noise based on pseudo-random number generation,
// * the same value in the grid will always produce the same height. 
// */
//GLfloat HeightGenerator::getNoise(GLint x, GLint z)
//{
//	srand(seed * x * z );
//
//	// Generate a number between 0 and 1
//	GLfloat randomValue = (GLfloat)rand() / (GLfloat)RAND_MAX;
//
//	// Make the range between - 1 and 1
//	randomValue *= 2;
//	randomValue -= 1;			
//
//	return randomValue;
//}
//
//// Returns the mean value of this points noise value and the points around it.
//GLfloat HeightGenerator::getMeanNoise(GLint x, GLint z)
//{
//	GLfloat bottomLeft = getNoise(x-1, z-1);
//	GLfloat bottomRight = getNoise(x+1, z-1);
//	GLfloat topLeft = getNoise(x-1, z+1);
//	GLfloat topRight = getNoise(x+1, z+1);
//
//	GLfloat leftSide = getNoise(x - 1, z);
//	GLfloat rightSide = getNoise(x + 1, z);
//	GLfloat top = getNoise(x, z + 1);
//	GLfloat bottom = getNoise(x, z - 1);
//
//	GLfloat corners = (bottomLeft + bottomRight + topLeft + topRight) / 16.0f;
//	GLfloat sides = (leftSide + rightSide + top + bottom) / 8.0f;
//
//	GLfloat center = getNoise(x, z) / 4.0f;
//
//	return center + sides + corners;
//}
