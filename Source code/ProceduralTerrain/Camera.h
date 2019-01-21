#pragma once
#include <iostream>

#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "info.h"

/*
 * This class defines a camera within the game world.
*/
class Camera
{

protected:
	// state of keys
	GLboolean keys[1024] = { false };

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 projectionViewMatrix;

	glm::vec3 cameraPosition;
	glm::vec3 cameraTarget;
	glm::vec3 cameraFront;
	glm::vec3 upVector;
	glm::vec3 rightVector;
	glm::vec3 worldUp;

	GLfloat pitch = 0.0f;
	GLfloat yaw = -90.0f;

	GLfloat lastXPosition = WIDTH / 2;
	GLfloat lastYPosition = HEIGHT / 2;

	GLboolean firstMouseInWindow = true;

	GLfloat sensitivity = 0.05f;
	GLfloat cameraSpeed = 500.0f;
	GLfloat zoom = 45.0f;

	bool staticCamera;

	void Camera::calculateLookAtForStaticCamera();
	void Camera::calculateFrontVectorForStaticCamera();

	void calculateLookAt();

public:
	Camera();
	Camera(glm::vec3 newCameraPosition, glm::vec3 newCameraTarget);
	~Camera();

	glm::vec3 getCameraPosition();
	glm::mat4 getView();
	glm::mat4 getProjection();
	glm::mat4 getProjectionViewMatrix();

	void setKey(GLint key, GLboolean value);
	void addCameraSpeed(GLint speed);
	void move(GLfloat deltaTime);
	void updateFront(GLfloat xPosition, GLfloat yPosition);
	void setCameraPosition(glm::vec3 newCameraPosition);
	void setCameraTarget(glm::vec3 newCameraTarget);
	glm::vec3 getCameraFront();



};

