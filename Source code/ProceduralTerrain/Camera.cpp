#include "Camera.h"

//camera class used to draw all of the objects in the program
Camera::Camera()
{
	staticCamera = false;
	cameraPosition = glm::vec3(0.0f, 1000.0f, 0.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
	upVector = glm::vec3(0.0f, 1.0f, 0.0f);
	worldUp = upVector;

	viewMatrix = glm::lookAt(
		cameraPosition,
		cameraPosition + cameraFront,
		upVector);

	projectionMatrix = glm::perspective(
		glm::radians(45.0f), (GLfloat)WIDTH / (GLfloat)HEIGHT, 1.0f, 10000.0f);

	projectionViewMatrix = projectionMatrix * viewMatrix;
}

Camera::Camera(glm::vec3 newCameraPosition, glm::vec3 newCameraTarget)
{
	staticCamera = true;
	cameraPosition = newCameraPosition;
	cameraTarget = newCameraTarget;
	upVector = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::~Camera()
{

}

void Camera::calculateLookAt()
{
	viewMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraFront, upVector);
	projectionViewMatrix = projectionMatrix * viewMatrix;
}

// getters
glm::vec3 Camera::getCameraPosition()
{
	return cameraPosition;
}

glm::mat4 Camera::getView()
{
	return viewMatrix;
}

glm::mat4 Camera::getProjection()
{
	return projectionMatrix;
}

glm::mat4 Camera::getProjectionViewMatrix()
{
	return projectionViewMatrix;
}

// Mutators
void Camera::setKey(GLint key, GLboolean value)
{
	keys[key] = value;
}

void Camera::addCameraSpeed(GLint speed)
{
	cameraSpeed += speed;
}

//controls for the movement of the camera using the keyboard
void Camera::move(GLfloat deltaTime)
{
	GLfloat speed = cameraSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		cameraPosition += speed * cameraFront;
	}
	if (keys[GLFW_KEY_S])
		cameraPosition -= speed * cameraFront;

	if (keys[GLFW_KEY_A])
		cameraPosition -= glm::normalize(glm::cross(cameraFront, upVector)) * speed;

	if (keys[GLFW_KEY_D])
		cameraPosition += glm::normalize(glm::cross(cameraFront, upVector)) * speed;

	calculateLookAt();
}

//update where the camera should be facing so that the lookAt can be calculated
void Camera::updateFront(GLfloat xPosition, GLfloat yPosition)
{
	if (firstMouseInWindow)
	{
		lastXPosition = xPosition;
		lastYPosition = yPosition;
		firstMouseInWindow = false;
	}

	GLfloat deltaX = xPosition - lastXPosition;
	GLfloat deltaY = yPosition - lastYPosition;

	deltaY = -deltaY;

	lastXPosition = xPosition;
	lastYPosition = yPosition;

	yaw += (deltaX * sensitivity);
	pitch += (deltaY * sensitivity);

	// gimble lock check
	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	cameraFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront.y = sin(glm::radians(pitch));
	cameraFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	// Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	cameraFront = glm::normalize(cameraFront);
	rightVector = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f,1.0f,0.0f)));  
	upVector = glm::normalize(glm::cross(rightVector, cameraFront));

	calculateLookAt();
}

/*Set camera position of a static camera - one that is not updated by mouse and keyboard movements*/
void Camera::setCameraPosition(glm::vec3 newCameraPosition)
{
	cameraPosition = newCameraPosition;
	calculateFrontVectorForStaticCamera();
	calculateLookAtForStaticCamera();
}
/*Set camera target position of a static camera - one that is not updated by mouse and keyboard movements*/
void Camera::setCameraTarget(glm::vec3 newCameraTarget)
{
	cameraTarget = newCameraTarget;
	calculateFrontVectorForStaticCamera();
	calculateLookAtForStaticCamera();
}

void Camera::calculateFrontVectorForStaticCamera()
{
	glm::vec3 addedVector = cameraTarget - cameraPosition;
	printf("Front is: X %f, Y %f Z %f", addedVector.x, addedVector.y, addedVector.z);
	cameraFront = glm::normalize(addedVector);
}

void Camera::calculateLookAtForStaticCamera()
{
	viewMatrix = glm::lookAt(cameraPosition, cameraTarget, upVector);
	projectionViewMatrix = projectionMatrix * viewMatrix;
}

glm::vec3 Camera::getCameraFront()
{
	return cameraFront;
}
