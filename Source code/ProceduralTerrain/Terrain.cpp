#include "Terrain.h"

Terrain::Terrain()
	:ProceduralGrid()
{
	/*m_hTex[0] = SOIL_load_OGL_texture("Textures\\Rock.dds", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_TEXTURE_REPEATS);
	m_hTex[1] = SOIL_load_OGL_texture("Textures\\Sand.dds", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_TEXTURE_REPEATS);
	m_hTex[2] = SOIL_load_OGL_texture("Textures\\Grass.dds", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_TEXTURE_REPEATS);
	m_hTex[3] = SOIL_load_OGL_texture("Textures\\Snow.dds", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_TEXTURE_REPEATS);*/
	shaderProgram = new Shader("Shaders/terrainVertex.txt", "Shaders/terrainFragment.txt");
	//Fault(250, 5.0f, 0.999f);
	//RandomNoise(5.0f);
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
	/*glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_pVertices) * sizeof(Vertex), &m_pVertices[0], GL_STATIC_DRAW);*/

	/*helper.createVertexArray(vao);
	addVertexArrayAttrib(vao, vbo, 0, 3, m_uiNumVertices * sizeof(GLfloat), 0);
	addVertexArrayAttrib(vao, vbo, 1, 3, m_uiNumVertices * sizeof(GLfloat), 3);
	addVertexArrayAttrib(vao, vbo, 2, 2, m_uiNumVertices * sizeof(GLfloat), 6);
	helper.fillVertexArrayWithIndices(vao, ibo, pIndices, 3 * NumTriangles * sizeof(GLuint));*/
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
	/*glMaterialfv(GL_FRONT, GL_SPECULAR, material.Specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, material.Emissive);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material.Diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, material.Ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, material.Shininess);
	*/
	//Setup array usage states
	//glActiveTexture(GL_TEXTURE0);
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
	/*m_Technique.Set();
	m_Technique.SetTexture0(m_hTex[0]);
	m_Technique.SetTexture1(m_hTex[1]);
	m_Technique.SetTexture2(m_hTex[2]);
	m_Technique.SetTexture3(m_hTex[3]);
	m_Technique.SetMedianHeight(m_fMedianHeight);*/
	
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
