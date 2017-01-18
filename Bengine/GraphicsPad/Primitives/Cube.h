#ifndef CUBE_H
#define CUBE_H

#include "ShapeBase.h"

class Cube: public ShapeBase
{
public:
	Cube(GLuint vertexID);
	~Cube();
};

#endif