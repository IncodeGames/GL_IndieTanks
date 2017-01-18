#ifndef SPRITE_H
#define SPRITE_H

#include <GL\glew.h>

class Sprite
{
	public:
		Sprite(float x, float y, float width, float height);
		~Sprite();

		void draw();
	private:
		float xPos;
		float yPos;
		float width;
		float height;
		GLuint vboID;

};

#endif