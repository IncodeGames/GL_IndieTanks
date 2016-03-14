#include "Sprite.h"
#include "Vertex2D.h"

#include <cstddef>


Sprite::Sprite(float x, float y, float width, float height) : vboID(0)
{
	glGenBuffers(1, &vboID);

	Vertex2D vertexData[6];

	vertexData[0].position.x = x + width;
	vertexData[0].position.y = y + height;

	vertexData[1].position.x = x;
	vertexData[1].position.y = y + height;

	vertexData[2].position.x = x;
	vertexData[2].position.y = y;

	vertexData[3].position.x = x;
	vertexData[3].position.y = y;

	vertexData[4].position.x = x + width;
	vertexData[4].position.y = y;

	vertexData[5].position.x = x + width;
	vertexData[5].position.y = y + height;

	for (int i = 0; i < 6; i++)
	{
		vertexData[i].color.r = 255;
		vertexData[i].color.g = 0;
		vertexData[i].color.b = 255;
		vertexData[i].color.a = 255;
	}

	

	vertexData[1].color.SetColor(0, 0, 255, 255);

	vertexData[4].color.SetColor(0, 255, 0, 255);

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


Sprite::~Sprite()
{
	if (vboID != 0)
	{
		glDeleteBuffers(1, &vboID);
	}
}

void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glEnableVertexAttribArray(0);

	//This is positional attribute pointer //TODO: name a variable to clarify attribute pointers
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, position));
	//This is the color attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, color));

	//Draw the vertices of the arrays
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Disable the vertex attribute array
	glDisableVertexAttribArray(0);

	//Unbind the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}