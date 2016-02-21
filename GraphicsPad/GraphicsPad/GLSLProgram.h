#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include <string>
#include <GL/glew.h>

class GLSLProgram
{
	public:
		GLSLProgram();
		~GLSLProgram();

		void CompileShaders(const std::string &vertShaderFilePath, const std::string &fragShaderFilePath);

		void LinkShaders();

	private:
		GLuint programID;

		GLuint vertShaderID;
		GLuint fragShaderID;
};

#endif