#ifndef	SHAPE_BASE_H
#define SHAPE_BASE_H

#include "ShapeData3D.h"

class ShapeBase
{
public:

	virtual void draw();
protected:
	GLuint vboID;
	GLushort numIndices;
};

#endif