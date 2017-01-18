#ifndef VERTEX2D_H
#define VERTEX2D_H

#include <GL/glew.h>

struct Position
{
	float x;
	float y;

	void SetPosition(float newX, float newY)
	{
		x = newX;
		y = newY;
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

struct Vertex2D
{
	Position position;
	Color color;
};


#endif