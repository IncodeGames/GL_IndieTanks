#ifndef MESH_INCLUDED_H
#define MESH_INCLUDED_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "obj_loader.h"
#include "../Primitives/ShapeBase.h"

enum MeshBufferPositions
{
	POSITION_VB,
	TEXCOORD_VB,
	NORMAL_VB,
	INDEX_VB
};

class Mesh
{
public:
	Mesh(const std::string& fileName);
	Mesh(Vertex3D* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);

	void Draw();

	virtual ~Mesh();
protected:
private:
	static const unsigned int NUM_BUFFERS = 4;
	void operator=(const Mesh& mesh) {}
	Mesh(const Mesh& mesh) {}

	void InitMesh(const IndexedModel& model);

	GLuint vboID;
	GLuint vertexArrayBuffers[NUM_BUFFERS];
	unsigned int numIndices;
};

#endif