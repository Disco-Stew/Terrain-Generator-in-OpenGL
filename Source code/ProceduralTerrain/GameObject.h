#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Orientation.h"

#include "info.h"

typedef struct
{
	GLfloat modelHeight;
	GLfloat modelWidth;
	GLfloat modelDepth;
	GLfloat largestWidth;
	GLfloat largestHeight;
	glm::vec3 centrePoint;
}boundingBox2D;

class GameObject
{
public:

	Shader*   shaderProgram;
	Orientation* orientation;

	GLfloat frames = 100.0f;
	GLboolean moving = false;
	GLboolean movingX = false;
	GLboolean movingY = false;
	GLboolean movingZ = false;
	GLboolean dropping = false;
	int collisionOccurred = 1;
	glm::vec3 moveToPosition;


public:
	GameObject(const GLchar* vertexShader, const GLchar* fragmentShader);
	GameObject::~GameObject();
	GameObject::GameObject(const GameObject &obj);
	GameObject::GameObject();
	glm::vec3 getPosition(void);
	void setPosition(glm::vec3 newPosition);
	void setScale(glm::vec3 setScale);
	virtual int draw()
	{
		return 0;
	}
	virtual float getRadius()
	{
		return 1.0f;
	}
	GLfloat GameObject::distanceFromOtherGameObject(GameObject otherGameObject);
};