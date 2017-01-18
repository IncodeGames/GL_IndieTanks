#include "Plane.h"

#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof (*a)

Plane::Plane(GLuint vertexID)
{
	vboID = vertexID;
	glGenBuffers(1, &vboID);

	ShapeData3D shapeData3d;
	Vertex3D plane[5];

	plane[0].position = glm::vec3(-10000.0f, -10.0f, +10000.0f);
	plane[1].position = glm::vec3(+10000.0f, -10.0f, +10000.0f);
	plane[2].position = glm::vec3(+10000.0f, -10.0f, -10000.0f);
	plane[3].position = glm::vec3(-10000.0f, -10.0f, -10000.0f);

	plane[0].color = glm::vec3(125.0f, 125.0f, 125.0f);
	plane[1].color = glm::vec3(125.0f, 125.0f, 125.0f);
	plane[2].color = glm::vec3(125.0f, 125.0f, 125.0f);
	plane[3].color = glm::vec3(125.0f, 125.0f, 125.0f);


	shapeData3d.numVertices = NUM_ARRAY_ELEMENTS(plane);
	shapeData3d.vertices = new Vertex3D[shapeData3d.numVertices];
	memcpy(shapeData3d.vertices, plane, sizeof(plane));


	GLushort indices[] = {
		0,   1,  2,  0,  2,  3, // Top
	};
	shapeData3d.numIndices = NUM_ARRAY_ELEMENTS(indices);
	shapeData3d.indices = new GLushort[shapeData3d.numIndices];
	memcpy(shapeData3d.indices, indices, sizeof(indices));

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, shapeData3d.vertexBufferSize(), shapeData3d.vertices, GL_STATIC_DRAW); //TODO: May need buffer sub data to allow dynamic draw

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shapeData3d.Cleanup();
}


Plane::~Plane()
{
	if (vboID != 0)
	{
		glDeleteBuffers(1, &vboID);
	}
}
