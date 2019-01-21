#pragma once
#include <stdlib.h>
#include <glew.h> 
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "info.h"
#include "Shader.h"

#include "Camera.h"
#include "SkyBox.h"

/*
 * This class provides a way for creating different game world instances
*/
class GameWorld
{
public:
	virtual GLvoid update(GLfloat deltaTime) = 0;
	virtual GLvoid draw(GLfloat deltaTime) = 0;

	virtual GLvoid input(GLFWwindow* window, int key, int scancode, int action, int mode) = 0;
	virtual GLvoid mouseButton(GLFWwindow* window, int button, int action, int mods) = 0;
	virtual GLvoid mouseInput(GLFWwindow* window, double xPosition, double yPosition) = 0;
	virtual GLvoid scrollInput(GLFWwindow* window, double xScroll, double yScroll) = 0;
	
};

