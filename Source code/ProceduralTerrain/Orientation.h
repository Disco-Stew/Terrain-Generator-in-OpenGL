#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glew.h>
class Orientation {
private:
	int moveTurn = 1;		 // a turn int
	GLfloat difference;		 // difference for gradual movement
	GLfloat deltaPosition;	 // update used to update position
	glm::vec3 startingPosition;//used for velocity
	glm::vec3 mPosition;     // Object position
	glm::vec3 mScale;        // Scalar value
	glm::vec3 mForward;      // Local x
	glm::vec3 mRight;        // Local z
	glm::vec3 mUp;           // Local y
	glm::vec3 mRotationAxis; // Axis about which rotations occur
	GLfloat mRotationAngle;
	//Transformation matrices
	glm::mat4 mPositionMatrix;
	glm::mat4 mRotationMatrix;
	glm::mat4 mScaleMatrix;
	glm::mat4 mTempMatrix;
	glm::mat4 mModelMatrix;
	void setPositionMatrix(glm::vec3 position);
	void setScaleMatrix(glm::vec3 scale);
	void updateLocalAxis();
	glm::mat4 updateModelMatrix();
	glm::vec3 rotateVector(glm::vec3 vectorToRotate, glm::vec3 axis, GLfloat theta);


public:
	Orientation();
	void setModelMatrix(glm::mat4 matrix);
	void addPosition(glm::vec3 vector);
	void setPosition(glm::vec3 vector);
	void setPositionX(GLfloat x);
	void setPositionY(GLfloat y);
	void setPositionZ(GLfloat z);
	void setScale(glm::vec3 vector);
	void setScaleX(GLfloat x);
	void setScaleY(GLfloat y);
	void setScaleZ(GLfloat z);
	void setRotationAxis(glm::vec3 vector);
	void addRotation(GLfloat angleIncrementDegrees);
	void setRotationAngle(GLfloat angleDegrees);
	glm::vec3 getPosition();
	GLfloat getRotationAngle();
	glm::vec3 getUpVector();
	glm::vec3 getRightVector();
	glm::vec3 getForwardVector();
	glm::mat4 getModelMatrix();
	void printMat4(glm::mat4 mat4Object);
	void printVec3(glm::vec3 vec3Object);

};