#ifndef	SHAPE_DATA3D_H
#define SHAPE_DATA3D_H

#include <GL\glew.h>
#include "Vertex3D.h"

struct ShapeData3D
{
	ShapeData3D() :
		vertices(0), numVertices(0),
		indices(0), numIndices(0) {}
	Vertex3D *vertices;
	GLuint numVertices;
	GLushort *indices;
	GLuint numIndices;

	inline GLsizeiptr vertexBufferSize() const
	{
		return numVertices * sizeof(Vertex3D);
	}
	GLsizeiptr indexBufferSize() const
	{
		return numIndices * sizeof(GLushort);
	}

	void Cleanup()
	{
		delete[] vertices;
		delete[] indices;
		numVertices = numIndices = 0;
	}
};

#endif
