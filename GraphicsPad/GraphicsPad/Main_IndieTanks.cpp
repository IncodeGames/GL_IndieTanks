
#include <iostream>
#include <GL/glew.h>

#include "Main_IndieTanks.h"
#include "Display.h"
#include "Sprite.h"


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

void Main_IndieTanks::Start()
{
}

void Main_IndieTanks::Update()
{

	glClearDepth(1.0f);
	glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Sprite sprite(0.0f, 0.0f, 0.5f, 0.5f);
	sprite.draw();
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