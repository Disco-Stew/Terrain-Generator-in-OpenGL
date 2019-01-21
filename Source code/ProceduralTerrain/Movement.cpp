#include "Movement.h"
#include <iostream>

Movement::Movement(Orientation* ori)
{
	orientation = ori;
}

void Movement::drop(GLfloat deltaTime)
{
	if (bouncing == true)
	{
		//reset startingDrop so it can go back down after its bounced up
		if (startingDrop != 1)
		{
			startingDrop = 1;
		}
		acceleration = gravity;
	}
	else
	{
		acceleration = gravity *-1.0f;
	}
		
		if (startingDrop == 1)
		{
			startingPositionDrop = orientation->getPosition().y;
			startingDrop--;
		}

		// use v = u + at to work out v
		glm::vec3 newVelocity = glm::vec3(getVelocity().x, (getVelocity().y + (acceleration* deltaTime)), getVelocity().z);

		// then sub v into v^2 = u^2 + 2as (s = (v^2 - u^2)/2a )
		newPosition = ((newVelocity.y * newVelocity.y) - (getVelocity().y * getVelocity().y)) / (2.0f * gravity);

		//setting the new position
		orientation->setPosition(glm::vec3(orientation->getPosition().x, orientation->getPosition().y + newPosition, orientation->getPosition().z));
		//updating the velocity value
		setVelocity(newVelocity);
		if (getVelocity().y < 0.1f)
		{
			bouncing = false;
		}
	
}

void Movement::bounce(GLfloat deltaTime)
{
	// use v = u + at to work out v
	glm::vec3 newVelocity = glm::vec3(getVelocity().x, (getVelocity().y + (gravity * deltaTime)), getVelocity().z);

	// then sub v into v^2 = u^2 + 2as (s = (v^2 - u^2)/2a )
	newPosition = ((newVelocity.y * newVelocity.y) - (getVelocity().y * getVelocity().y)) / (2.0f * gravity);
	//new u for next calculation
	printf("Velocity: %f\n", velocity.y);
	//setting the new position
	orientation->setPosition(glm::vec3(orientation->getPosition().x, orientation->getPosition().y + newPosition, orientation->getPosition().z));
	//updating the velocity value
	setVelocity(newVelocity);

}

GLboolean Movement::moveToPosition(glm::vec3 newPosition, glm::vec3 initialVelocity, GLfloat deltaTime)
{
	if (moveTurn == 1)
	{
		startingPosition = orientation->getPosition();
		initialVelocity = getVelocity();
	}
	GLboolean newPos = newPosition.x > 0.0f;
	GLboolean oldPos = startingPosition.x > 0.0f;

	//IF STARTING AND ENDING POSITIONS ARE POSITIVE
	if (newPos == true && oldPos == true)
	{
		//IF YOU ARE MOVING BACKWARDS
		if (startingPosition.x > newPosition.x)
		{
			if (moveTurn == 1)
			{
				difference = startingPosition.x - newPosition.x;
				deltaPosition = -1.0f * ((startingPosition.x - newPosition.x) / initialVelocity.x);
				moveTurn--;
			}
			difference += deltaPosition;
		}
		//IF YOU ARE MOVING FORWARDS
		else
		{
			if (moveTurn == 1)
			{
				difference = -1.0f * (startingPosition.x - newPosition.x);
				deltaPosition = (startingPosition.x - newPosition.x) / initialVelocity.x;
				moveTurn--;
			}
			difference += deltaPosition;
		}
	}
	//IF STARTING AND ENDING POSITIONS ARE NEGATIVE
	else if (newPos == false && oldPos == false)
	{
		//IF STARTING POSITION IS HIGHER THAN END POSITION
		if (startingPosition.x > newPosition.x)
		{
			if (moveTurn == 1)
			{
				difference = (startingPosition.x - newPosition.x);
				moveTurn--;
			}
			deltaPosition = -1.0f * ((startingPosition.x - newPosition.x) / initialVelocity.x);
			difference += deltaPosition;
		}
		else
		{
			if (moveTurn == 1)
			{
				difference = -1.0f * (startingPosition.x - newPosition.x);
				moveTurn--;
			}
			deltaPosition = -1.0f * (startingPosition.x - newPosition.x) / initialVelocity.x;
			difference -= deltaPosition;
		}
	}
	//OTHER COMBINATIONS
	else
	{
		//IF END POSITION IS POSITIVE AND START POSITION IS NEGATIVE
		if (newPos == true)
		{
			if (moveTurn == 1)
			{
				difference = -1.0f * (startingPosition.x - newPosition.x);
				moveTurn--;
			}
			deltaPosition = -1.0f * (startingPosition.x - newPosition.x) / initialVelocity.x;
			difference -= deltaPosition;
		}
		//IF START POSITION IS POSITIVE AND END POSITION IS NEGATIVE
		else
		{
			if (moveTurn == 1)
			{
				difference = (startingPosition.x - newPosition.x);
				moveTurn--;
			}
			deltaPosition = -1.0f * (startingPosition.x - newPosition.x) / initialVelocity.x;
			difference += deltaPosition;
		}
	}

	//updating x, y, z variables
	glm::vec3 move;
	move.x = orientation->getPosition().x + deltaPosition;
	move.y = orientation->getPosition().y + (newPosition.y - orientation->getPosition().y) / initialVelocity.y;
	move.z = orientation->getPosition().z + (newPosition.z - orientation->getPosition().z) / initialVelocity.z;

	if (difference > 0.0f)
	{
		orientation->setPosition(move);
		return true;
	}
	else
	{
		moveTurn = 1;
		return false;
	}
}

void Movement::moveX(glm::vec3 newVelocity, GLfloat deltaTime)
{
	glm::vec3 move;
	move.x = orientation->getPosition().x + (newVelocity.x * deltaTime);
	move.y = orientation->getPosition().y;
	move.z = orientation->getPosition().z;
	orientation->setPosition(move);
}

void Movement::moveY(glm::vec3 newVelocity, GLfloat deltaTime)
{
	glm::vec3 move;
	move.x = orientation->getPosition().x;
	move.y = orientation->getPosition().y + (newVelocity.y * deltaTime);
	move.z = orientation->getPosition().z;
	orientation->setPosition(move);
}

void Movement::moveZ(glm::vec3 newVelocity, GLfloat deltaTime)
{
	glm::vec3 move;
	move.x = orientation->getPosition().x;
	move.y = orientation->getPosition().y;
	move.z = orientation->getPosition().z + (newVelocity.z * deltaTime);
	orientation->setPosition(move);

}

void Movement::setVelocity(glm::vec3 newVelocity)
{
	velocity = newVelocity;
}

glm::vec3 Movement::getVelocity()
{
	return velocity;
}