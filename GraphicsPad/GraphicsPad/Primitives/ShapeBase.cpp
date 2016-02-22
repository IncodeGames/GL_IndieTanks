#include "ShapeBase.h"
#include <GLM\glm.hpp>
#include "Vertex3D.h"

#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof (*a)


//TODO: modify draw to handle 2d and 3d
void ShapeBase::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glEnableVertexAttribArray(0);

	//This is positional attribute pointer //TODO: name a variable to clarify attribute pointers
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, position));
	//This is the color attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, color));

	//Draw the vertices of the arrays
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Disable the vertex attribute array
	glDisableVertexAttribArray(0);

	//Unbind the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
