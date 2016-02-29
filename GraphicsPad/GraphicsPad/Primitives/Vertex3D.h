#ifndef VERTEX3D_H
#define VERTEX3D_H

#include <GL/glew.h>
#include <GLM\glm.hpp>

struct Position
{
	float x;
	float y;
	float z;

	void SetPosition(float newX, float newY, float newZ)
	{
		x = newX;
		y = newY;
		z = newZ;
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
	glm::vec3 position;
	Color color;
};


#endif