#include "ProceduralGrid.h"

ProceduralGrid::ProceduralGrid()
{
	init();
	createBuffers();
	setBuffers();
}
ProceduralGrid::~ProceduralGrid(void)
{
	deleteBuffers();
}
GLvoid ProceduralGrid::init() {
	vertexCount = 257;
	size = 3200;
	srand(time(NULL));
	seed = (GLfloat)rand();
	amplitude = 1000;
	count = vertexCount * vertexCount;
	verticesCount = count * 3;
	textureCoordsCount = count * 2;
	indicesCount = 6 * (vertexCount - 1) * (vertexCount - 1);
	noise = new FractalNoise(log2(vertexCount), seed, 0.50);
}
GLvoid ProceduralGrid::createBuffers()
{
	// Using heap memory due to the amount of memory required
	vertices = new GLfloat[verticesCount];
	normals = new GLfloat[verticesCount];
	textureCoords = new GLfloat[textureCoordsCount];
	indices = new GLuint[indicesCount];
	normalVectors = new glm::vec3[count * 2];

}
GLvoid ProceduralGrid::deleteBuffers()
{
	delete noise;
	delete[] vertices;
	delete[] normals;
	delete[] textureCoords;
	delete[] indices;
	delete[] normalVectors;
}
GLvoid ProceduralGrid::setBuffers() {
	GLuint i, j;
	GLuint vertexLocation = 0;
	for (GLuint i = 0; i < vertexCount; i++)
	{

		for (GLuint j = 0; j < vertexCount; j++)
		{

			// Vertices
			// x 
			vertices[vertexLocation * 3] = (GLfloat)j / ((GLfloat)vertexCount - 1) * size;

			// y 
			GLfloat height;
			if (i == vertexCount - 1 || i == 0 || j == 0 || j == vertexCount - 1)
			{
				height = 0;
				vertices[vertexLocation * 3 + 1] = 0.0f;
				glm::vec2 key = glm::vec2(j, i);
			}
			else
			{
				GLfloat value = noise->getAltitude(j, i);
				value *= amplitude;
				height = value;
				vertices[vertexLocation * 3 + 1] = value;
			}

			// z
			vertices[vertexLocation * 3 + 2] = (float)i / ((float)vertexCount - 1) * size;


			// Generate normals
			normals[vertexLocation * 3] = 0.0f;
			normals[vertexLocation * 3 + 1] = 1.0f;
			normals[vertexLocation * 3 + 2] = 0.0f;

			// texture coords
			textureCoords[vertexLocation * 2] = (float)j / ((float)vertexCount - 1);
			textureCoords[vertexLocation * 2 + 1] = (float)i / ((float)vertexCount - 1);

			vertexLocation++;
		}
	}
	m_fMedianHeight = 0.0f;
	CalculateMedianHeight();
	//generating normals
	GLuint pointer = 0;
	GLuint triangleIndex = 0;
	for (GLuint zIncrement = 0; zIncrement < vertexCount - 1; zIncrement++)
	{
		for (GLuint xIncrement = 0; xIncrement < vertexCount - 1; xIncrement++)
		{
			//4 points of a quad
			GLuint bottomRight = (zIncrement * (vertexCount)) + xIncrement;
			GLuint bottomLeft = bottomRight + 1;
			GLuint topRight = ((zIncrement + 1) * (vertexCount)) + xIncrement;
			GLuint topLeft = topRight + 1;
			
			indices[pointer++] = bottomRight;
			indices[pointer++] = topRight;
			indices[pointer++] = topLeft;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomRight;
			indices[pointer++] = bottomLeft;

	

			
			//bottomRight
			glm::vec3 p1 = glm::vec3(vertices[bottomRight * 3], vertices[bottomRight * 3 + 1], vertices[bottomRight * 3 + 2]);

			//topRight
			glm::vec3 p2 = glm::vec3(vertices[topRight * 3], vertices[topRight * 3 + 1], vertices[topRight * 3 + 2]);

			//topLeft
			glm::vec3 p3 = glm::vec3(vertices[topLeft * 3], vertices[topLeft * 3 + 1], vertices[topLeft * 3 + 2]);

			//bottomLeft
			glm::vec3 p4 = glm::vec3(vertices[bottomLeft * 3], vertices[bottomLeft * 3 + 1], vertices[bottomLeft * 3 + 2]);

			//TRIANGLE 1 NORMALS
			normalVectors[triangleIndex] = generateNormal(p1, p2, p3);
			
			triangleIndex++;

			//TRIANGLE 2 NORMALS
			normalVectors[triangleIndex] = generateNormal(p3, p4, p1);
			triangleIndex++;
		}
	}
}
glm::vec3 ProceduralGrid::generateNormal(glm::vec3 trianglePoint1, glm::vec3 trianglePoint2, glm::vec3 trianglePoint3)
{
	// point 2 - point 1
	glm::vec3 side1 = trianglePoint2 - trianglePoint1;

	// point 3 - point 1 
	glm::vec3 side2 = trianglePoint3 - trianglePoint1;

	//calculating the cross product
	glm::vec3 normalVector;
	normalVector.x = (side1.y * side2.z) - (side1.z * side2.y);
	normalVector.y = (side1.z * side2.x) - (side1.x * side2.z);
	normalVector.z = (side1.x * side2.y) - (side1.y * side2.x);

	//normalizing so all x,y and z only add up to 1.0 and it doesn't increase the force's magnitude
	glm::vec3 scaledNormalVector;
	scaledNormalVector.x = normalVector.x / (fabs(normalVector.x) + fabs(normalVector.y) + fabs(normalVector.z));
	scaledNormalVector.y = normalVector.y / (fabs(normalVector.x) + fabs(normalVector.y) + fabs(normalVector.z));
	scaledNormalVector.z = normalVector.z / (fabs(normalVector.x) + fabs(normalVector.y) + fabs(normalVector.z));

	return scaledNormalVector;
}
void ProceduralGrid::CalculateMedianHeight(void)
{
	GLuint i, j;
	//std::cout << "Bone count: " << m_iWidth << std::endl;
	GLuint vertexLocation = 0;
	for (GLuint i = 0; i < vertexCount; i++)
	{
		for (GLuint j = 0; j < vertexCount; j++)
		{
			m_fMedianHeight += vertices[vertexLocation * 3 + 1];
		}

	}
	m_fMedianHeight = m_fMedianHeight / float(m_uiNumVertices);
}

void ProceduralGrid::RandomNoise(float magnitude)
{
	GLuint i, j;
	GLuint vertexLocation = 0;
	for (i = 0; i<vertexCount; i++)
	{
		for (j = 0; j<vertexCount; j++)
		{
			vertices[vertexLocation * 3+1] += magnitude*((float(rand()) / float(RAND_MAX)) - 0.5f);
			vertexLocation++;
		}
	}
	
	CalculateMedianHeight();
}

void ProceduralGrid::Fault(GLuint iterations, float initdisplacement, float dampening)
{
	GLuint it, i, j;
	float disp = initdisplacement;
	glm::vec3 p1, p2, fault;
	glm::vec3 proj;
	for (it = 0; it<iterations; it++)
	{
		p1.x = m_fTileSize * float(vertexCount) * ((float(rand()) / float(RAND_MAX)) - 0.5f);
		p1.y = 0.0f;
		p1.z = m_fTileSize * float(m_iWidth) * (0.5f - (float(rand()) / float(RAND_MAX)));
		p2.x = m_fTileSize * float(m_iWidth) * ((float(rand()) / float(RAND_MAX)) - 0.5f);
		p2.y = 0.0f;
		p2.z = m_fTileSize * float(m_iWidth) * (0.5f - (float(rand()) / float(RAND_MAX)));
		fault = p2 - p1;
		
		GLuint vertexLocation = 0;
		for (i = 0; i<vertexCount; i++)
		{
			for (j = 0; j<vertexCount; j++)
			{
				proj = glm::vec3(vertices[vertexLocation * 3], vertices[vertexLocation * 3 + 1], vertices[vertexLocation * 3 + 2]);
				proj.y = 0.0f;
				proj = proj - p1;
				proj = glm::cross(proj, fault);
				glm::normalize(proj);
				vertices[vertexLocation * 3 + 1] += disp * proj.y;
				vertexLocation++;
			}
		}
		if (dampening > 0.0f && dampening < 1.0f)
		{
			disp = disp * dampening;
		}
		else
		{
			disp = disp * (float(iterations - it) / float(iterations));
		}
	}
	
	CalculateMedianHeight();
}