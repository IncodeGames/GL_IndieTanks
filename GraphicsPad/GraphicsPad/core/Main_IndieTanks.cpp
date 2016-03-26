
#include <iostream>
#include <GL/glew.h>
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>

#include "Main_IndieTanks.h"
#include "Display.h"
#include "..\Primitives\Sprite.h"
#include "..\Primitives\ShapeData3D.h"
#include "..\Primitives\Triangle.h"
#include "..\Primitives\Cube.h"
#include "Camera.h"
float x = 0.0f;
float y = 0.0f;

float rotX = 0.0f;
float rotY = 0.0f;

Main_IndieTanks::Main_IndieTanks(): gameState(GameState::RUNNING), 
									time(0),
									mainWidth(1024),
									mainHeight(768)
{
	display = new Display(mainWidth, mainHeight, "Hello world");
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
	glViewport(0, 0, getWidth(), getHeight());

	//Use shader programs
	colorShaderProgram.Use();

	Camera camera(glm::vec3(0, 0, -7), 70.0f, (float)getWidth() / getHeight(), 0.01f, 1000.0f);

	glm::mat4 projectionMatrix = camera.GetViewProjection();
	glm::mat4 translationProjectionMatrix = glm::translate(projectionMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 modelMatrix = glm::rotate(translationProjectionMatrix, rotY, glm::vec3(x, y, 1.0f));

	//Set uniforms
	glUniformMatrix4fv(colorShaderProgram.GetUniformLocation("mvpMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);
	GLuint timeLocation = colorShaderProgram.GetUniformLocation("time");
	glUniform1f(timeLocation, time);

	Triangle triangle(0);
	triangle.draw();

	Cube cube(0);
	cube.draw();

	Sprite sprite(0.75f, 0.0f, 0.5f, 0.5f);
	sprite.draw();

	//Unuse shader programs
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
				x = inputEvent.motion.x;
				y = inputEvent.motion.y;
				break;
			}
			case SDL_KEYDOWN:
			{
				SDL_Keysym key = inputEvent.key.keysym;
				if (key.sym == SDLK_ESCAPE)
				{
					gameState = GameState::QUIT;
				}
				if (key.sym == SDLK_RIGHT)
				{
					rotX += 0.1f;
				}
				if (key.sym == SDLK_LEFT)
				{
					rotX -= 0.1f;
				}
				if (key.sym == SDLK_UP)
				{
					rotY += 0.1f;
				}
				if (key.sym == SDLK_DOWN)
				{
					rotY -= 0.1f;
				}
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
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
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