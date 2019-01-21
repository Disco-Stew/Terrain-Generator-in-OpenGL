#include "SkyBox.h"


GLuint loadCubeMap(std::vector<const GLchar*> faces);

SkyBox::SkyBox()
	:shader{ "Shaders/skyBoxVertex.txt", "Shaders/skyBoxFragment.txt" }
{
	GLfloat radius = 1.0f;

	GLfloat vertices[] =
	{
		// back face
		-radius, -radius, -radius,
		-radius,  radius, -radius,
		 radius, -radius, -radius,

		-radius,  radius, -radius,
		 radius,  radius, -radius,
		 radius, -radius, -radius,

		// front face
		-radius, -radius,  radius,
		-radius,  radius,  radius,
		 radius, -radius,  radius,

		-radius,  radius,  radius,
		 radius,  radius,  radius,
		 radius, -radius,  radius,

		// left face
		-radius, -radius,  radius,
		-radius,  radius,  radius,
		-radius,  radius, -radius,

		-radius,  radius, -radius,
		-radius, -radius, -radius,
		-radius, -radius,  radius,

		// right face
		 radius, -radius,  radius,
		 radius,  radius,  radius,
		 radius,  radius, -radius,

		 radius,  radius, -radius,
		 radius, -radius, -radius,
		 radius, -radius,  radius,

		// bottom face
		-radius, -radius,  radius,
		-radius, -radius, -radius,
		 radius, -radius, -radius,

		 radius, -radius, -radius,
		 radius, -radius,  radius,
		-radius, -radius,  radius,

		// top face
		-radius,  radius,  radius,
		-radius,  radius, -radius,
		 radius,  radius, -radius,

		 radius,  radius, -radius,
		 radius,  radius,  radius,
		-radius,  radius,  radius,
	};


	// Generate Vertex Array object and vertex buffer
	helper.createVertexArray(vertexArray);
	helper.fillVertexArrayWithVertices(vertexArray, vertexBuffer, vertices, sizeof(vertices), 0);
	
	glGenBuffers(1, &textureBuffer);

	// Cubemap (Skybox)
	faces.push_back("skybox/right.bmp");
	faces.push_back("skybox/left.bmp");
	faces.push_back("skybox/top.bmp");
	faces.push_back("skybox/bottom.bmp");
	faces.push_back("skybox/back.bmp");
	faces.push_back("skybox/front.bmp");
	texture = loadCubeMap(faces);
	

	//int width, height;
	//unsigned char* image = SOIL_load_image("picture.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//glGenerateMipmap(GL_TEXTURE_2D);
	//SOIL_free_image_data(image);
	//glBindTexture(GL_TEXTURE_2D, 0);

}

SkyBox::~SkyBox()
{

}

void SkyBox::draw(glm::mat4 viewMatrix)
{
	// skybox cube
	shader.useProgram();

	// Remember to turn depth writing off
	glDepthMask(GL_FALSE);

	// Remove any translation component of the view matrix
	glm::mat4 view = glm::mat4(glm::mat3(viewMatrix));	

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);

	GLint program = shader.getProgram();
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	// skybox cube
	glBindVertexArray(vertexArray);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(program, "skybox"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	// Turn depth writing back on
	glDepthMask(GL_TRUE);
}

GLuint loadCubeMap(std::vector<const GLchar*> faces)
{
	GLuint textureID;
	glGenTextures(1, &textureID);

	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for (GLuint i = 0; i < faces.size(); i++)
	{
		image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}

GLuint SkyBox::getTexture()
{
	return texture;
}