#include "Orientation.h"
#include <iostream>

Orientation::Orientation()
{
	mPosition = glm::vec3(0, 0, 0);
	mScale = glm::vec3(0, 0, 0);

	mPositionMatrix = glm::mat4(1);
	mScaleMatrix = glm::mat4(1);
	mTempMatrix = glm::mat4(0);
	mModelMatrix = glm::mat4(1);
	mRotationMatrix = glm::mat4(1);

	mRotationAxis = glm::vec3(1, 0, 0);
	mRotationAngle = 0.0f;

	mRight = glm::vec3(0, 0, 1);
	mUp = glm::vec3(0, 1, 0);
	mForward = glm::vec3(1, 0, 0);
}
void Orientation::setModelMatrix(glm::mat4 matrix)
{
	this->mModelMatrix = matrix;

}
void Orientation::setPositionMatrix(glm::vec3 position)
{
	mPositionMatrix = glm::mat4(1);
	mPositionMatrix = glm::translate(mPositionMatrix, position);
}

void Orientation::setScaleMatrix(glm::vec3 scale)
{
	mScaleMatrix = glm::mat4(1);
	mScaleMatrix = glm::scale(mScaleMatrix, scale);
}

void Orientation::addPosition(glm::vec3 vector)
{
	mPosition += vector;
	setPositionMatrix(mPosition);
	updateModelMatrix();
}

void Orientation::setPosition(glm::vec3 vector)
{
	mPosition = vector;
	setPositionMatrix(mPosition);
	updateModelMatrix();
}

void Orientation::setPositionX(GLfloat x)
{
	mPosition.x = x;
	setPositionMatrix(mPosition);
	updateModelMatrix();
}

void Orientation::setPositionY(GLfloat y)
{
	mPosition.y = y;
	setPositionMatrix(mPosition);
	updateModelMatrix();
}

void Orientation::setPositionZ(GLfloat z)
{
	mPosition.z = z;
	setPositionMatrix(mPosition);
	updateModelMatrix();
}

void Orientation::setScale(glm::vec3 vector)
{
	mScale = vector;
	setScaleMatrix(mScale);
	updateModelMatrix();
}

void Orientation::setScaleX(GLfloat x)
{
	mScale.x = x;
	setScaleMatrix(mScale);
	updateModelMatrix();
}

void Orientation::setScaleY(GLfloat y)
{
	mScale.y = y;
	setScaleMatrix(mScale);
	updateModelMatrix();
}

void Orientation::setScaleZ(GLfloat z)
{
	mScale.z = z;
	setScaleMatrix(mScale);
	updateModelMatrix();
}


void Orientation::setRotationAxis(glm::vec3 vector)
{
	mRotationAxis = vector;
}

void Orientation::addRotation(GLfloat angleIncrementDegrees)
{
	mRotationAngle += angleIncrementDegrees;
	mRotationMatrix = glm::rotate(mRotationMatrix, glm::radians(mRotationAngle), mRotationAxis);
	updateLocalAxis();
	updateModelMatrix();
}

void Orientation::setRotationAngle(GLfloat angleDegrees)
{
	mRotationAngle = angleDegrees;
	mRotationMatrix = glm::rotate(mRotationMatrix, glm::radians(angleDegrees), mRotationAxis);
	updateLocalAxis();
	updateModelMatrix();
}


void Orientation::updateLocalAxis()
{

	//Recalculate local axis
	mRight = glm::vec3(0, 0, 1);
	mUp = glm::vec3(0, 1, 0);
	mForward = glm::vec3(1, 0, 0);

	mRight = rotateVector(mRight, mRotationAxis, mRotationAngle);
	mUp = rotateVector(mUp, mRotationAxis, mRotationAngle);
	mForward = rotateVector(mForward, mRotationAxis, mRotationAngle);


}

glm::vec3 Orientation::rotateVector(glm::vec3 vectorToRotate, glm::vec3 axis, GLfloat theta)
{
	float u, v, w;

	u = axis.x;
	v = axis.y;
	w = axis.z;
	double xPrime = u * (u * vectorToRotate.x + v * vectorToRotate.y + w * vectorToRotate.z) * (1.0 - glm::cos(theta))
		+ vectorToRotate.x * glm::cos(theta)
		+ (-w * vectorToRotate.y + v * vectorToRotate.z) * glm::sin(theta);
	double yPrime = v * (u * vectorToRotate.x + v * vectorToRotate.y + w * vectorToRotate.z) * (1.0 - glm::cos(theta))
		+ vectorToRotate.y * glm::cos(theta)
		+ (w * vectorToRotate.x - u * vectorToRotate.z) * glm::sin(theta);
	double zPrime = w * (u * vectorToRotate.x + v * vectorToRotate.y + w * vectorToRotate.z) * (1.0 - glm::cos(theta))
		+ vectorToRotate.z * glm::cos(theta)
		+ (-v * vectorToRotate.x + u * vectorToRotate.y) * glm::sin(theta);
	return glm::vec3((float)xPrime, (float)yPrime, (float)zPrime);

}

glm::mat4 Orientation::updateModelMatrix()
{
	//Matrices are applied in the order: Scale, Rotation, Translation
	mTempMatrix = mPositionMatrix * mRotationMatrix;
	mModelMatrix = mTempMatrix * mScaleMatrix;
	return mModelMatrix;
}

glm::vec3 Orientation::getPosition()
{
	return mPosition;
}

GLfloat Orientation::getRotationAngle()
{
	return mRotationAngle;
}

glm::vec3 Orientation::getUpVector()
{
	return mUp;
}

glm::vec3 Orientation::getRightVector()
{
	return mRight;
}

glm::vec3 Orientation::getForwardVector()
{
	return mForward;
}


glm::mat4 Orientation::getModelMatrix()
{
	return mModelMatrix;
}

void Orientation::printMat4(glm::mat4 mat4Object)
{
	std::cout << "Object: \n";
	std::cout << mat4Object[0].x << "\t" << mat4Object[0].y << "\t" <<  mat4Object[0].z << "\t" << mat4Object[0].w << "\n";
	std::cout << mat4Object[1].x << "\t" << mat4Object[1].y << "\t" << mat4Object[1].z << "\t" << mat4Object[1].w << "\n";
	std::cout << mat4Object[2].x << "\t" << mat4Object[2].y << "\t" << mat4Object[2].z << "\t" << mat4Object[2].w << "\n";
	std::cout << mat4Object[3].x << "\t" << mat4Object[3].y << "\t" << mat4Object[3].z << "\t" << mat4Object[3].w << "\n";
}

void Orientation::printVec3(glm::vec3 vec3Object)
{
	std::cout << "Vector: \n";
	std::cout << "X is: "<<vec3Object.x << "\nY is:" << vec3Object.y << "\nZ is: " << vec3Object.z;
}
