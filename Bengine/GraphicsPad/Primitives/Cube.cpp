#include "Cube.h"

#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof (*a)

Cube::Cube(GLuint vertexID)
{
	vboID = vertexID;
	glGenBuffers(1, &vboID);

	ShapeData3D shapeData3d;
	Vertex3D cube[24];

	cube[0].position = glm::vec3(-1.0f, +1.0f, +1.0f);
	cube[1].position = glm::vec3(+1.0f, +1.0f, +1.0f);
	cube[2].position = glm::vec3(+1.0f, +1.0f, -1.0f);
	cube[3].position = glm::vec3(-1.0f, +1.0f, -1.0f);

	cube[4].position = glm::vec3(-1.0f, +1.0f, -1.0f);
	cube[5].position = glm::vec3(+ 1.0f, +1.0f, -1.0f);
	cube[6].position = glm::vec3(+1.0f, -1.0f, -1.0f);
	cube[7].position = glm::vec3(-1.0f, -1.0f, -1.0f);

	// Purple side - RIGHT
	cube[8].position = glm::vec3(+1.0f, +1.0f, -1.0f);
	cube[9].position = glm::vec3(+1.0f, +1.0f, +1.0f);
	cube[10].position = glm::vec3(+1.0f, -1.0f, +1.0f);
	cube[11].position = glm::vec3(+1.0f, -1.0f, -1.0f);

	// Green side - LEFT
	cube[12].position = glm::vec3(-1.0f, +1.0f, +1.0f);
	cube[13].position = glm::vec3(-1.0f, +1.0f, -1.0f);
	cube[14].position = glm::vec3(-1.0f, -1.0f, -1.0f);
	cube[15].position = glm::vec3(-1.0f, -1.0f, +1.0f);

	// Blue side - TOP
	cube[16].position = glm::vec3(+1.0f, +1.0f, +1.0f);
	cube[17].position = glm::vec3(-1.0f, +1.0f, +1.0f);
	cube[18].position = glm::vec3(-1.0f, -1.0f, +1.0f);
	cube[19].position = glm::vec3(+1.0f, -1.0f, +1.0f);

	// Red side - BOTTOM
	cube[20].position = glm::vec3(+1.0f, -1.0f, -1.0f);
	cube[21].position = glm::vec3(-1.0f, -1.0f, -1.0f);
	cube[22].position = glm::vec3(-1.0f, -1.0f, +1.0f);
	cube[23].position = glm::vec3(+1.0f, -1.0f, +1.0f);


	shapeData3d.numVertices = NUM_ARRAY_ELEMENTS(cube);
	shapeData3d.vertices = new Vertex3D[shapeData3d.numVertices];
	memcpy(shapeData3d.vertices, cube, sizeof(cube));


	GLushort indices[] = { 
		0,   1,  2,  0,  2,  3, // Top
		4,   5,  6,  4,  6,  7, // Front
		8,   9, 10,  8, 10, 11, // Right
		12, 13, 14, 12, 14, 15, // Left
		16, 17, 18, 16, 18, 19, // Back
		20, 22, 21, 20, 23, 22, // Bottom
	};
	shapeData3d.numIndices = NUM_ARRAY_ELEMENTS(indices);
	shapeData3d.indices = new GLushort[shapeData3d.numIndices];
	memcpy(shapeData3d.indices, indices, sizeof(indices));

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, shapeData3d.vertexBufferSize(), shapeData3d.vertices, GL_STATIC_DRAW); //TODO: May need buffer sub data to allow dynamic draw

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shapeData3d.Cleanup();
}


Cube::~Cube()
{
	if (vboID != 0)
	{
		glDeleteBuffers(1, &vboID);
	}
}
