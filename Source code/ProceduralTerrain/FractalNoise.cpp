#include "FractalNoise.h"
#include "info.h"

FractalNoise::FractalNoise(GLint iterations, GLint seed, GLfloat roughness)
	: Noise()
{
	srand(seed);
	if (iterations < 1 || roughness < 0)
	{
		// handle error
	}


	this->iterations = iterations;

	// (2 to the power n) + 1
	divisions = 1 << iterations;
	size = (1 << iterations) + 1;

	rough = 0.9;
	this->roughness = roughness;

	min = 0;
	max = 0;

	map = (GLfloat **)calloc(size * size, sizeof(GLfloat));

	makeTexture();

}

FractalNoise::~FractalNoise()
{

}

GLvoid FractalNoise::diamond(GLint x, GLint y, GLint side, GLfloat scale)
{
	if (side > 1)
	{
		int half = side / 2;
		double average = (map[x][y] + map[x + side][y] + map[x + side][y + side] + map[x][y + side]) * 0.25;
		GLfloat random = (GLfloat)rand() / (GLfloat)RAND_MAX;
		random *= 2;
		random -= 1;
		map[x + half][y + half] = average + random  * scale;
	}
}

GLvoid FractalNoise::square(GLint x, GLint y, GLint side, GLfloat scale)
{
	int half = side / 2;
	double average = 0.0, sum = 0.0;
	if (x >= 0)
	{
		average += map[x][y + half]; 
		sum += 1.0;
	}
	if (y >= 0)
	{
		average += map[x + half][y];
		sum += 1.0;
	}
	if (x + side <= divisions)
	{
		average += map[x + side][y + half];
		sum += 1.0;
	}

	if (y + side <= divisions)
	{
		average += map[x + half][y + side];
		sum += 1.0;
	}

	GLfloat random = (GLfloat)rand() / (GLfloat)RAND_MAX;
	random *= 2;
	random -= 1;
	map[x + half][y + half] = (average /  sum) + random * scale;

}

GLvoid FractalNoise::makeTexture()
{
	for (GLint i = 0; i < size; i++)
	{
		map[i] = (GLfloat *)calloc(size, sizeof(GLfloat));
	}

	GLint maxIndex = size-1;
	arrayLength = maxIndex;

	 //seed corners
	map[0][0] = 0.2;
	map[0][maxIndex] = 0.4;
	map[maxIndex][0] = 0.25;
	map[maxIndex][maxIndex] = 0.152;

	for (GLint i = 0; i < iterations; ++i)
	{
		GLint q = 1 << i;
		GLint r = 1 << (iterations - i);
		GLint s = r >> 1;

		for (GLint j = 0; j < divisions; j += r)
		{
			for (GLint k = 0; k < divisions; k += r)
			{
				diamond(j, k, r, rough);
			}

		}
			
		if (s > 0)
		{
			for (GLint j = 0; j <= divisions; j += s)
			{

				for (GLint k = (j + s) % r; k <= divisions; k += r)
				{
					square(j - s, k - s, r, rough);
				}
			}

		}

		rough *= roughness;

	}

	for (int i = 0; i <= divisions; ++i)
	{
		for (int j = 0; j <= divisions; ++j)
		{
			if (map[i][j] < min)
			{
				min = map[i][j];
			}
			else if (map[i][j] > max)
			{
				max = map[i][j];
			}
		}
	}
}

GLfloat FractalNoise::getAltitude(GLint x, GLint y)
{
	GLfloat value = 0;
	GLfloat altitude = map[y][x];
	value = (altitude - min) / (max - min);
	return value;
}