
#include <iostream>
#include <GL/glew.h>

#include "Main_IndieTanks.h"
#include "Display.h"
#include "Sprite.h"


Main_IndieTanks::Main_IndieTanks(): gameState(GameState::RUNNING), 
									time(0)
{
	display = new Display(1024, 768, "Hello world");
}

Main_IndieTanks::~Main_IndieTanks()
{

}

void Main_IndieTanks::Run()
{
	InitSystems();
	GameLoop();
}

void Main_IndieTanks::Start()
{
}

void Main_IndieTanks::Update()
{
	//Clear color and depth buffers
	glClearDepth(1.0f);
	glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	colorShaderProgram.Use();

	//Set uniforms
	GLuint timeLocation = colorShaderProgram.GetUniformLocation("time");
	glUniform1f(timeLocation, time);

	Sprite sprite(0.0f, 0.0f, 0.5f, 0.5f);
	sprite.draw();

	colorShaderProgram.Unuse();

	display->BufferUpdate();
}

void Main_IndieTanks::GameLoop()
{
	while (gameState != GameState::QUIT)
	{
		ProcessInput();
		time += 0.01f; //TODO: make a time related class, and handle time for physics, and rendering
		Update();
	}
}

void Main_IndieTanks::ProcessInput()
{
	SDL_Event inputEvent;

	while (SDL_PollEvent(&inputEvent))
	{
		switch (inputEvent.type)
		{
			case SDL_MOUSEMOTION:
			{
				printf("X mouse position: %i \n", inputEvent.motion.x );
				printf("Y mouse position: %i \n\n", inputEvent.motion.y );				
				break;
			}
			case SDL_QUIT:
			{
				gameState = GameState::QUIT;
				break;
			}
		}
	}
}

void Main_IndieTanks::InitSystems()
{
	//display = new Display(1024, 768, "Hello world");
	InitShaders();

}

void Main_IndieTanks::InitShaders()
{
	colorShaderProgram.CompileShaders("Shaders/vertShading.vert", "Shaders/fragShading.frag");
	colorShaderProgram.AddAttribute("vertexPosition");
	colorShaderProgram.AddAttribute("vertexColor");
	colorShaderProgram.LinkShaders();
}

int main(int argc, char* args[])
{
	Main_IndieTanks indieTanks;
	indieTanks.Run();

	return 0;
}