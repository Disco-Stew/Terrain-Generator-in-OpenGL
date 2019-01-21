#include "Helper.h"

// Constructor and destructor do not need to initialise anything
Helper::Helper()
{
}


Helper::~Helper()
{
}

// For this method the vertexArray must be passed by reference
void Helper::createVertexArray(GLuint& vertexArray)
{
	// Generate Vertex Array object and vertex buffer
	glGenVertexArrays(1, &vertexArray);
}


void Helper::fillVertexArrayWithVertices(GLuint vertexArray, GLuint& vertexBuffer, GLfloat vertices[], GLint length, GLuint index)
{
	glGenBuffers(1, &vertexBuffer);
	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, length, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Helper::positionInstance(GLuint vertexArray, GLuint& instanceVBO, glm::vec3 objPos[], GLint length, GLuint index, GLint divisor)
{
	glBindVertexArray(vertexArray);
	glGenBuffers(1, &instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * length, &objPos[0], GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	glVertexAttribDivisor(index, divisor); // Tell OpenGL this is an instanced vertex attribute.

	glBindVertexArray(0);
}

void Helper::createEmptyVBO(GLuint& vbo, GLuint maxFloats) {
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, maxFloats * 4, NULL, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Helper::addInstancedAttrib(GLuint vao, GLuint vbo, GLint attribute, GLint size, GLint dataLength, GLint offset)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray(vao);
	glVertexAttribPointer(attribute, size, GL_FLOAT, GL_FALSE, dataLength * 4, (GLvoid*)(offset * 4));
	glVertexAttribDivisor(attribute, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void Helper::instancing(GLuint vertexArray, GLuint& instanceVBO, glm::mat4  matrices[], GLint length, GLuint index, GLint divisor)
{
	glBindVertexArray(vertexArray);
	glGenBuffers(1, &instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * length, matrices, GL_DYNAMIC_DRAW);

	//4 vertexAttributes are setUp because each has a max size of vec 4, a matrix is 4 time this
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (GLvoid*)0);
	glEnableVertexAttribArray(index + 1);//the rest of the matrix automatically goes to the next attribute
	glVertexAttribPointer(index + 1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (GLvoid*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(index + 2);
	glVertexAttribPointer(index + 2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (GLvoid*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(index + 3);
	glVertexAttribPointer(index + 3, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (GLvoid*)(3 * sizeof(glm::vec4)));

	// Tell OpenGL these are instanced vertex attributes.
	glVertexAttribDivisor(index, divisor);
	glVertexAttribDivisor(index+1, divisor);
	glVertexAttribDivisor(index+2, divisor);
	glVertexAttribDivisor(index+3, divisor);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Helper::refreshBuffer(GLuint& instanceVBO, glm::mat4  modelMatrices[], GLint length)
{
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * length, &modelMatrices[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Helper::fillVertexArrayWithIndices(GLuint vertexArray, GLuint& indexBuffer, GLuint indices[], GLuint length)
{
	glGenBuffers(1, &indexBuffer);
	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, length, indices, GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void Helper::fillVertexArrayWithNormals(GLuint vertexArray, GLuint& normalBuffer, GLfloat normals[], GLint length, GLuint index)
{
	glGenBuffers(1, &normalBuffer);
	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, length, normals, GL_STATIC_DRAW);
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid *)0);
	glEnableVertexAttribArray(index);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Helper::fillVertexArrayWithTextureCoords(GLuint vertexArray, GLuint& textureCoordsBuffer, GLfloat textureCoords[], GLint length, GLuint index)
{
	glGenBuffers(1, &textureCoordsBuffer);
	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, textureCoordsBuffer);
	glBufferData(GL_ARRAY_BUFFER, length, textureCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (GLvoid *)0);
	glEnableVertexAttribArray(index);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Helper::texture2DSetRepeatAndLinear(GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Helper::textureSetWrap(GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Helper::loadTextureWithImage2D(GLuint texture, char* imagePath, GLuint textureSampler)
{
	glActiveTexture(GL_TEXTURE0 + textureSampler);
	glBindTexture(GL_TEXTURE_2D, texture);
	int width, height;
	unsigned char* image = SOIL_load_image(imagePath, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);

}

/*std::vector<PointLight> Helper::calculateClosestLightsToObject(GameObject gameObject, std::vector<PointLight> &objectList, int numberOfObjectsToReturn)
{
	int distanceFromObject = -1;
	int indexOfFurthestNearObject = -1;
	if (objectList.size() <= numberOfObjectsToReturn)
	{
		std::cout << "You have not passed a long enough to need to sort";
		return objectList;
	}

	std::vector<PointLight> nearObjects;
	for (int objectInPassedList = 0; objectInPassedList < objectList.size(); objectInPassedList++)
	{
		if (nearObjects.size() < numberOfObjectsToReturn)
		{
			nearObjects.push_back(objectList.at(objectInPassedList));
		}
		else
		{
			indexOfFurthestNearObject = -1;

			distanceFromObject = std::fabsf(glm::distance(gameObject.getPosition(), objectList.at(objectInPassedList).getPosition()));
			for (int nearObject = 0; nearObject < nearObjects.size(); nearObject++)
			{
				//If we find an object further away in our nearest list
				if (distanceFromObject < gameObject.distanceFromOtherGameObject(nearObjects.at(nearObject).getGameObject()))
				{
					//Record it's index if index is -1
					if (indexOfFurthestNearObject == -1)
					{
						indexOfFurthestNearObject = nearObject;
					}
					//Record it's index if this is the new max distance in our nearest list
					else if (gameObject.distanceFromOtherGameObject(nearObjects.at(nearObject).getGameObject())
				> gameObject.distanceFromOtherGameObject(nearObjects.at(indexOfFurthestNearObject).getGameObject()))
					{
						indexOfFurthestNearObject = nearObject;
					}
				}
			}
			if (indexOfFurthestNearObject != -1)
			{
				nearObjects.at(indexOfFurthestNearObject) = objectList.at(objectInPassedList);
			}
		}

	}
	return nearObjects;
}*/
