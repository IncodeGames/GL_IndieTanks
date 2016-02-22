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

		void AddAttribute(const std::string &attributeName);

		GLint GetUniformLocation(const std::string &uniformName);

		void Use();
		void Unuse();

	private:
		//Neccessary IDs
		GLuint programID;
		GLuint vertShaderID;
		GLuint fragShaderID;

		//Attribute variables
		int attributeCount;


		void compileShader(const std::string &filePath, GLuint id);
};

#endif