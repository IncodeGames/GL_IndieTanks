#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "GLSLProgram.h"




GLSLProgram::GLSLProgram() : programID(0), vertShaderID(0), fragShaderID(0), attributeCount(0)
{
}


GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::CompileShaders(const std::string &vertShaderFilePath, const std::string &fragShaderFilePath)
{
	programID = glCreateProgram();

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

	compileShader(vertShaderFilePath, vertShaderID);
	compileShader(fragShaderFilePath, fragShaderID);
}

void GLSLProgram::LinkShaders()
{
	//programID = glCreateProgram();

	//Attach shaders to program
	glAttachShader(programID, vertShaderID);
	glAttachShader(programID, fragShaderID);

	glLinkProgram(programID);

	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(programID, maxLength, &maxLength, &errorLog[0]);

		//Cleanup program
		glDeleteProgram(programID);

		//Cleanup shaders
		glDeleteShader(vertShaderID);
		glDeleteShader(fragShaderID);

		std::printf("%s\n", &(errorLog[0]));
		std::printf("Shaders failed to link \n");

		return;
	}

	//Always detach shaders after a successful link
	glDetachShader(programID, vertShaderID);
	glDetachShader(programID, fragShaderID);

	glDeleteShader(vertShaderID);
	glDeleteShader(fragShaderID);

}

void GLSLProgram::AddAttribute(const std::string &attributeName)
{
	glBindAttribLocation(programID, attributeCount, attributeName.c_str());
	attributeCount++;
}

GLint GLSLProgram::GetUniformLocation(const std::string &uniformName)
{
	GLint location = glGetUniformLocation(programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX)
	{
		std::cerr << "Uniform not found in shader. Uniform name: " + uniformName + "\n" << std::endl; //TODO: make an error class
	}
	return location;
}

void GLSLProgram::Use()
{
	glUseProgram(programID);
	for (int i = 0; i < attributeCount; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::Unuse()
{
	glUseProgram(0);
	for (int i = 0; i < attributeCount; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

//Helper function for compiling a particular shader
void GLSLProgram::compileShader(const std::string &filePath, GLuint id)
{

	std::ifstream vertexFile(filePath);
	if (vertexFile.fail())
	{
		std::cerr << "Failed to open :" + filePath << std::endl;
	}

	std::string fileContents = "";
	std::string line;

	while (std::getline(vertexFile, line))
	{
		fileContents += line + "\n";
	}

	vertexFile.close();

	const char *contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);
	glCompileShader(id);

	GLint isCompiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(id);
		
		std::printf("%s\n", &(errorLog[0]));
		std::printf("Shader &s failed to compile.", filePath.c_str());
		return;

	}
}