#include "Display.h"
#include <GL\glew.h>
#include <iostream>


Display::Display(int width, int height, const std::string& title)
{
	//Initialize SDL 
	//TODO:(move elsewhere if using for anything other than windowing)
	SDL_Init(SDL_INIT_EVERYTHING);

	//Set SDL window attributes
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Create SDL window
	sdlWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	glContext = SDL_GL_CreateContext(sdlWindow);

	GLenum status = glewInit();

	if (status != GLEW_OK)
	{
		std::cerr << "Glew failed to initialize!" << std::endl;
	}

	isClosed = false;
}


Display::~Display()
{
	//Cleanup context and window
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();
}

void Display::Update()
{
	SDL_GL_SwapWindow(sdlWindow);

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			isClosed = true;
		}
	}
}

bool Display::IsClosed()
{
	return isClosed;
}