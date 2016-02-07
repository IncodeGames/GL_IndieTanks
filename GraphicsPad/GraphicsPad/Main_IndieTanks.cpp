
#include <iostream>
#include "Main_IndieTanks.h"
#include "Display.h"
#include <GL/glew.h>

Main_IndieTanks::Main_IndieTanks()
{
	gameState = GameState::RUNNING;
}

Main_IndieTanks::~Main_IndieTanks()
{

}

void Main_IndieTanks::Run()
{
	InitDisplay();
	GameLoop();
}

void Main_IndieTanks::Update()
{
	glClearDepth(1.0f);
	glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableClientState(GL_COLOR_ARRAY);
	
	glBegin(GL_TRIANGLES);
	glColor3f(.5f, .75f, .1f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.5f, 0.2f);
	glEnd();

	display->BufferUpdate();
}

void Main_IndieTanks::GameLoop()
{
	while (gameState != GameState::QUIT)
	{
		ProcessInput();
		Update();
	}
}

void Main_IndieTanks::ProcessInput()
{
	//SDL_PollEvent();
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

void Main_IndieTanks::InitDisplay()
{
	display = new Display(800, 600, "Hello world");

}

int main(int argc, char* args[])
{
	Main_IndieTanks indieTanks;
	indieTanks.Run();

	return 0;
}