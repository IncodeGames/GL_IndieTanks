#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "GLSLProgram.h"




GLSLProgram::GLSLProgram() : programID(0), vertShaderID(0), fragShaderID(0)
{
}


GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::CompileShaders(const std::string &vertShaderFilePath, const std::string &fragShaderFilePath)
{
	vertShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (vertShaderID == 0)
	{
		std::cerr << "Vertex shader creation failed." << std::endl;
	}

	fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragShaderID == 0)
	{
		std::cerr << "Fragment shader creation failed." << std::endl;
	}

	std::ifstream vertexFile(vertShaderFilePath);
	if (vertexFile.fail())
	{
		std::cerr << "Failed to open :" + vertShaderFilePath << std::endl;
	}

	std::string fileContents = "";
	std::string line;

	while (std::getline(vertexFile, line))
	{
		fileContents += line + "\n";
	}

	vertexFile.close();

	const char *contentsPtr = fileContents.c_str();
	glShaderSource(vertShaderID, 1, &contentsPtr, nullptr);
	glCompileShader(vertShaderID);

	GLint isCompiled = 0;
	glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertShaderID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(vertShaderID, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(vertShaderID);
		return;

	}

	glCompileShader(fragShaderID);
}

void GLSLProgram::LinkShaders()
{
	
}