#ifndef VERTEX3D_H
#define VERTEX3D_H

#include <GL/glew.h>
#include <GLM\glm.hpp>

struct Position
{
	glm::vec3  p;

	void SetPosition(float newX, float newY, float newZ)
	{
		p.x = newX;
		p.y = newY;
		p.z = newZ;
	}
};

struct Color
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;

	//Default constructor with no parameters
	Color()
	{
	}

	//Constructor with rgb parameters, defaults to opaque
	Color(GLubyte red, GLubyte green, GLubyte blue)
	{
		r = red;
		g = green;
		b = blue;
		a = 255;
	}

	//Constructor with RGBA parameters
	Color(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha)
	{
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}

	Color(glm::vec3 color) //TODO: make own vectors for instances like this
	{
		r = color.x;
		g = color.y;
		b = color.z;
		a = 255;
	}

	//Function that sets new RGB values based on parameters
	void SetColor(GLubyte red, GLubyte green, GLubyte blue)
	{
		r = red;
		g = green;
		b = blue;
	}

	//Function that sets new RGBA values based on parameters
	void SetColor(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha)
	{
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}
};

struct Vertex3D
{
	Vertex3D() {}
	Vertex3D(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal)
	{
		this->position = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	glm::vec3 position;
	Color color;
	glm::vec2 texCoord;
	glm::vec3 normal;

	glm::vec3* GetPos()
	{
		return &position;
	}

	Color* GetColor()
	{
		return &color;
	}

	glm::vec2* GetTextureCoords()
	{
		return &texCoord;
	}

	glm::vec3* GetNormal()
	{
		return &normal;
	}
};


#endif