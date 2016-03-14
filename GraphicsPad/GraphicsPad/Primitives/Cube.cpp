#include "Cube.h"

#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof (*a)

Cube::Cube(GLuint vertexID)
{
	vboID = vertexID;
	glGenBuffers(1, &vboID);

	ShapeData3D shapeData3d;
	Vertex3D cube[24];

	cube[0].position = glm::vec3(-0.5, -0.5, -0.5);
	cube[1].position = glm::vec3(-0.5, 0.5, -0.5); 
	cube[2].position = glm::vec3(0.5, 0.5, -0.5);       
	cube[3].position = glm::vec3(0.5, -0.5, -0.5);

	cube[4].position = glm::vec3(0.5, -0.5, 0.5);
	cube[5].position = glm::vec3(0.5, 0.5, 0.5);
	cube[6].position = glm::vec3(-0.5, 0.5, 0.5);
	cube[7].position = glm::vec3(-0.5, -0.5, 0.5);

	// Purple side - RIGHT
	cube[8].position = glm::vec3(0.5, -0.5, -0.5);
	cube[9].position = glm::vec3(0.5, 0.5, -0.5);
	cube[10].position = glm::vec3(0.5, 0.5, 0.5);
	cube[11].position = glm::vec3(0.5, -0.5, 0.5);

	// Green side - LEFT
	cube[12].position = glm::vec3(-0.5, -0.5, 0.5);
	cube[13].position = glm::vec3(-0.5, 0.5, 0.5);
	cube[14].position = glm::vec3(-0.5, 0.5, -0.5);
	cube[15].position = glm::vec3(-0.5, -0.5, -0.5);

	// Blue side - TOP
	cube[16].position = glm::vec3(0.5, 0.5, 0.5);
	cube[17].position = glm::vec3(0.5, 0.5, -0.5);
	cube[18].position = glm::vec3(-0.5, 0.5, -0.5);
	cube[19].position = glm::vec3(-0.5, 0.5, 0.5);

	// Red side - BOTTOM
	cube[20].position = glm::vec3(0.5, -0.5, -0.5);
	cube[21].position = glm::vec3(0.5, -0.5, 0.5);
	cube[22].position = glm::vec3(-0.5, -0.5, 0.5);
	cube[23].position = glm::vec3(-0.5, -0.5, -0.5);


	shapeData3d.numVertices = NUM_ARRAY_ELEMENTS(cube);
	shapeData3d.vertices = new Vertex3D[shapeData3d.numVertices];
	memcpy(shapeData3d.vertices, cube, sizeof(cube));


	GLushort indices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 };
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
