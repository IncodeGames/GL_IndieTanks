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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, position));
	//This is the color attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, color));

	//Draw the vertices of the arrays
	glDrawArrays(GL_QUADS, 0, 24); //TODO: determine best line to use here, originally GL_TRIANGLES, 0, 6
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);

	//Disable the vertex attribute array
	glDisableVertexAttribArray(0);

	//Unbind the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
