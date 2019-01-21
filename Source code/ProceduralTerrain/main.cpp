#define GLEW_STATIC
/*
Terrain is defined by a square array of dimension (2^n + 1)^2
This value will be passed to the terrain generator and used as the n value.
(1-> 3x3, 2-> 5x5, 10-> 1025x1025)
Note, 12 seems to be the highest we can fit into an array at the moment, (make points array [size][3]?).
*/


#include <stdlib.h>

#include <glew.h> 
#include <glfw3.h>

#include "GameWorld.h"
#include "TerrainWorld.h"

GLFWwindow* window;

GLvoid update(GLfloat deltaTime);
GLvoid input(GLFWwindow* window, int key, int scancode, int action, int mode);
GLvoid mouseButton(GLFWwindow* window, int button, int action, int mods);
GLvoid mouseInput(GLFWwindow* window, double xPosition, double yPosition);
GLvoid scrollInput(GLFWwindow* window, double xScroll, double yScroll);


GLint initialiseContext();
GLdouble timeOfLastUpdate = 0.0f;
static GLdouble scroll = 0.0f;

GameWorld *currentWorld;

GLint main()
{

	GLint success = initialiseContext();
	if (success == 1)
	{
		return 1;
	}

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	
	GLfloat deltaTime = 0.0f;
	GLfloat previousTime = glfwGetTime();
	
	
	currentWorld = new TerrainWorld();

	//main game loop
	GLenum err;
	
	while (!glfwWindowShouldClose(window))
	{
		deltaTime = glfwGetTime() - previousTime;
		previousTime = glfwGetTime();

		// Check input
		glfwPollEvents();
		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cout << "OpenGL error: " << err << std::endl;
		}
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Decide if it's time to update or not
		GLdouble currentTime = glfwGetTime();
		GLdouble timeSinceLastUpdate = currentTime - timeOfLastUpdate;
		if (timeSinceLastUpdate > 0.010)
		{
			//Do updates here
			update(timeSinceLastUpdate);
			//Critical to loop, don't delete
			timeOfLastUpdate = glfwGetTime();
		}
		//call draw method for the world currently in use
		currentWorld->draw(timeSinceLastUpdate); //only one world created but easily extensible for more
		glfwSwapBuffers(window);
	}

	return 0;
}

GLvoid update(GLfloat deltaTime)
{
	//Update Current Game World
	currentWorld->update(deltaTime);
}

GLint initialiseContext()
{
	glfwInit();
	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 4);
	window = glfwCreateWindow(WIDTH, HEIGHT, "Procedural Terrain", nullptr, nullptr);
	glfwSetWindowPos(window, 200, 200);


	// check window was created 
	if (window == nullptr)
	{
		std::cout << "Did not create window successfully: " << std::endl;
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);

	// set key callback function
	glfwSetKeyCallback(window, input);
	glfwSetMouseButtonCallback(window, mouseButton);
	glfwSetCursorPosCallback(window, mouseInput);
	glfwSetScrollCallback(window, scrollInput);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Did not sucessfully initialise glew: " << std::endl;
		glfwTerminate();
		return 1;
	}

	glViewport(0, 0, WIDTH, HEIGHT);

	return 0;
}


GLvoid input(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		exit(1);
	}

	if (key == GLFW_KEY_1 && action == GLFW_RELEASE)
	{
		delete(currentWorld);
		currentWorld = new TerrainWorld();
	}
	currentWorld->input(window, key, scancode, action, mode);
}

GLvoid mouseInput(GLFWwindow* window, double xPosition, double yPosition)
{
	currentWorld->mouseInput(window, xPosition, yPosition);
}

GLvoid scrollInput(GLFWwindow* window, double xScroll, double yScroll)
{
	currentWorld->scrollInput(window, xScroll, yScroll);
}

GLvoid mouseButton(GLFWwindow* window, int button, int action, int mods)
{
	currentWorld->mouseButton(window, button, action, mods);
}