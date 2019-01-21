// GLM Mathemtics

#include <iostream>
#include <string>
#include "GameObject.h"

GameObject::~GameObject() {}
GameObject::GameObject()
	:GameObject("", "")
{
}
GameObject::GameObject(const GLchar* vertexShader, const GLchar* fragmentShader)
{
	shaderProgram = new Shader(vertexShader, fragmentShader);
	orientation = new Orientation();

}

glm::vec3 GameObject::getPosition(void)
{
	return orientation->getPosition();
}

void GameObject::setPosition(glm::vec3 newPosition)
{
	orientation->setPosition(newPosition);
}

void GameObject::setScale(glm::vec3 newScale)
{
	orientation->setScale(newScale);
}

GameObject::GameObject(const GameObject &obj)
{
	shaderProgram = new Shader("", "");
	*shaderProgram = *obj.shaderProgram;
	orientation = new Orientation();
	*orientation = *obj.orientation;
}

GLfloat GameObject::distanceFromOtherGameObject(GameObject otherGameObject)
{
	return std::fabsf(glm::distance(getPosition(), otherGameObject.getPosition()));
}




	