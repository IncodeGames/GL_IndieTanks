#include <iostream>
#include "Display.h"
#include <GL/glew.h>

int main(int argc, char* args[])
{
	Display display(800, 600, "Hello world");

	while (!display.IsClosed())
	{
		glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		display.Update();
	}

	return 0;
}