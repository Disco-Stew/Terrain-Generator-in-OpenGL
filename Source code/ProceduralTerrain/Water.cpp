//Class to create a plane of water across the terrain. Nearly implemented but some bugs were stopping it from working correctly
#include "Water.h"
#include "SOIL.h"

Water::Water(char* imagePath)
	:ProceduralGrid()
{
	shaderProgram = new Shader("Shaders/waterVertex.txt", "Shaders/waterFragment.txt");
		
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	int w, h;
	unsigned char* image = SOIL_load_image(imagePath, &w, &h, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	
	helper.texture2DSetRepeatAndLinear(textureID);
	
	model = glm::mat4(1);
	model = glm::translate(model, glm::vec3(0 ,0 ,0));
	
}

Water::~Water(void)
{
}

void Water::Render(glm::mat4 view, glm::mat4 projection, float time)
{
	shaderProgram->useProgram();
	GLint program = shaderProgram->getProgram();
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(glGetUniformLocation(program, "textureID"), 0);
	
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniform1f(glGetUniformLocation(program, "time"), time);

	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glDrawElements(GL_TRIANGLES, 3 * NumTriangles, GL_UNSIGNED_INT, 0);
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	// bind with 0, so, switch back to normal pointer operation
	glBindVertexArray(0);
	

	
	
}
