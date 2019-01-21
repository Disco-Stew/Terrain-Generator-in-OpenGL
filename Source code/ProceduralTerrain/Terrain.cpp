#include "Terrain.h"

Terrain::Terrain()
	:ProceduralGrid()
{
	shaderProgram = new Shader("Shaders/terrainVertex.txt", "Shaders/terrainFragment.txt");
	
	createTextures();
	SunLight_Ambient = { 1.0f, 1.0f, 1.0f, 1.0f };
	SunLight_Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	SunLight_Specular = { 1.0f, 1.0f, 1.0f, 1.0f };
	SunLight_Position = { 10.0f, 10.0f, 0.0f, 0.0f };

	helper.createVertexArray(vao);
	helper.fillVertexArrayWithVertices(vao, vertexBuffer, vertices, verticesCount * sizeof(GLfloat), 0);
	helper.fillVertexArrayWithIndices(vao, indexBuffer, indices, indicesCount * sizeof(GLuint));
	helper.fillVertexArrayWithNormals(vao, normalBuffer, normals, verticesCount * sizeof(GLfloat), 1);
	helper.fillVertexArrayWithTextureCoords(vao, textureBuffer, textureCoords, textureCoordsCount * sizeof(GLfloat), 2);
	
	model = glm::mat4(1);
	model = glm::translate(model, glm::vec3(0, 0, 0));
}

Terrain::~Terrain(void)
{
}

void Terrain::Render(glm::mat4 view, glm::mat4 projection)
{
	shaderProgram->useProgram();
	GLint program = shaderProgram->getProgram();
	
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniform1f(glGetUniformLocation(program, "terrmedheight"), m_fMedianHeight);

	bindTextures(program);
	glBindVertexArray(vao);
	
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);

	//Restore previous state
	// bind with 0, so, switch back to normal pointer operation
	glBindVertexArray(0);
}

GLvoid Terrain::reset()
{
	deleteBuffers();
	init();
	createBuffers();
	setBuffers();

	helper.createVertexArray(vao);
	helper.fillVertexArrayWithVertices(vao, vertexBuffer, vertices, verticesCount * sizeof(GLfloat), 0);
	helper.fillVertexArrayWithIndices(vao, indexBuffer, indices, indicesCount * sizeof(GLuint));
	helper.fillVertexArrayWithNormals(vao, normalBuffer, normals, verticesCount * sizeof(GLfloat), 1);
	helper.fillVertexArrayWithTextureCoords(vao, textureBuffer, textureCoords, textureCoordsCount * sizeof(GLfloat), 2);
}
GLvoid Terrain::createTextures()
{
	// texture
	glGenBuffers(1, &snowTexture);
	helper.texture2DSetRepeatAndLinear(snowTexture);
	helper.loadTextureWithImage2D(snowTexture, "Texture/snow.jpg", 0);

	glGenBuffers(1, &rockTexture);
	helper.loadTextureWithImage2D(rockTexture, "Texture/rock.jpg", 1);

	glGenBuffers(1, &grassTexture);
	helper.loadTextureWithImage2D(grassTexture, "Texture/grass.jpg", 2);

	glGenBuffers(1, &sandTexture);
	helper.loadTextureWithImage2D(sandTexture, "Texture/sand.jpg", 3);
}

GLvoid Terrain::bindTextures(GLuint program)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, snowTexture);
	glUniform1i(glGetUniformLocation(program, "snowTexture"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, rockTexture);
	glUniform1i(glGetUniformLocation(program, "rockTexture"), 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, grassTexture);
	glUniform1i(glGetUniformLocation(program, "grassTexture"), 2);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, sandTexture);
	glUniform1i(glGetUniformLocation(program, "sandTexture"), 3);

	glActiveTexture(GL_TEXTURE0);

}
