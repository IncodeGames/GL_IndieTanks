#ifndef PLANE_H
#define PLANE_H

#include "ShapeBase.h"

class Plane : public ShapeBase
{
public:
	Plane(GLuint vertexID);
	~Plane();
};

#endif