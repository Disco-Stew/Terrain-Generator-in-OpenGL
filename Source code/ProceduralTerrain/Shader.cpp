#include "Shader.h"

Shader::Shader(const GLchar* vertexFilePath, const GLchar* fragmentFilePath)
{
	std::ifstream vertexStream;
	std::ifstream fragmentStream;

	std::string vertexString;
	std::string fragmentString;

	// Allow streams to throw exceptions
	vertexStream.exceptions(std::ifstream::badbit);
	fragmentStream.exceptions(std::ifstream::badbit);

	try
	{

		vertexStream.open(vertexFilePath);
		fragmentStream.open(fragmentFilePath);

		std::stringstream vertexStringStream;
		std::stringstream fragmentStringStream;

		vertexStringStream << vertexStream.rdbuf();
		fragmentStringStream << fragmentStream.rdbuf();

		// raii don't need the below? 
		vertexStream.close();
		fragmentStream.close();

		vertexString = vertexStringStream.str();

		fragmentString = fragmentStringStream.str();

	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Shader ERROR: File not opened. " << std::endl;
	}


	// c style stuff
	const GLchar* vertexStringBuffer = vertexString.c_str();
	const GLchar* fragmentStringBuffer = fragmentString.c_str();

	// Make sure an opengl context exists before any openGL calls
	GLint success;
	GLchar infoLog[512];

	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexStringBuffer, nullptr);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << shaderName << "::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentStringBuffer, nullptr);
	glCompileShader(fragmentShader);

	// Check for compile time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << shaderName << "::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

}

Shader::Shader(GLchar* name, const GLchar* vertexFilePath, const GLchar* fragmentFilePath)
{
	Shader::Shader(vertexFilePath, fragmentFilePath);
	shaderName = name;
}

GLuint Shader::getProgram()
{
	return program;
}

void Shader::useProgram()
{
	glUseProgram(program);
}