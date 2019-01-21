#include "TerrainWorld.h"



TerrainWorld::TerrainWorld()
{
	terrain = new Terrain();
	
	float height;
	glm::vec3 terrainsize, norm;
	
}


TerrainWorld::~TerrainWorld()
{
}


void TerrainWorld::update(GLfloat deltaTime)
{
	camera.move(deltaTime);
}

void TerrainWorld::draw(GLfloat deltaTime)
{
	glm::mat4 view = camera.getView();
	glm::mat4 projection = camera.getProjection();
	
	terrain->Render(view, projection);
	
	glDepthFunc(GL_LEQUAL);
	skyBox.draw(camera.getView());
	
	glDepthFunc(GL_LESS);
}

GLvoid TerrainWorld::input(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		exit(1);
	}

	if (key == GLFW_KEY_L && action == GLFW_RELEASE)
	{
		lines = !lines;
		if (lines)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (key == GLFW_KEY_N && action == GLFW_RELEASE)
	{
		terrain->reset();
	}
	if (action == GLFW_PRESS)
	{
		camera.setKey(key, true);
		
	}

	if (action == GLFW_RELEASE)
	{
		camera.setKey(key, false);
	}

	if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
	{
		camera.addCameraSpeed(100);
	}

	if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
	{
		camera.addCameraSpeed(-100);
	}

	if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
	{
		
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
	{
		
	}
}

GLvoid TerrainWorld::mouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		camera.setKey(button, true);
	}

	if (action == GLFW_RELEASE)
	{
		camera.setKey(button, false);
	}
}


GLvoid TerrainWorld::mouseInput(GLFWwindow* window, double xPosition, double yPosition)
{
	camera.updateFront(xPosition, yPosition);
}

GLvoid TerrainWorld::scrollInput(GLFWwindow* window, double xPosition, double yPosition)
{

}