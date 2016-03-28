
#include <iostream>
#include <GL/glew.h>
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>

#include "Main_IndieTanks.h"
#include "Display.h"
#include "..\Primitives\Sprite.h"
#include "..\Primitives\ShapeData3D.h"
#include "..\Primitives\Triangle.h"
#include "..\Primitives\Plane.h"
#include "..\Primitives\Cube.h"
#include "..\Rendering\Mesh.h"
#include "..\Rendering\Texture.h"
#include "Time.h"
#include "Camera.h"

class Time;

float x = 0.0f;
float y = 0.0f;

float relativeX = 0.0f;
float relativeY = 0.0f;

float rotX = 0.0f;
float rotY = 0.0f;

float zoom = 0.0f;
Main_IndieTanks::Main_IndieTanks(): gameState(GameState::RUNNING), 
									time(0),
									mainWidth(1920),
									mainHeight(1080)
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
	
	Camera camera(glm::vec3(0, 0, -12), 70.0f, (float)getWidth() / getHeight(), 0.01f, 1000.0f);
	camera.move(glm::vec3(relativeX, relativeY, zoom));
	camera.rotate(rotX, rotY);

	glm::mat4 projectionMatrix = camera.GetViewProjection();
	glm::mat4 translationProjectionMatrix = glm::translate(projectionMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 modelMatrix = glm::rotate(translationProjectionMatrix, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));

	//Set uniforms
	glUniformMatrix4fv(colorShaderProgram.GetUniformLocation("mvpMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);
	glm::mat4 Normal = modelMatrix;
	glUniformMatrix4fv(colorShaderProgram.GetUniformLocation("Normal"), 1, GL_FALSE, &Normal[0][0]);
	glUniform3f(colorShaderProgram.GetUniformLocation("lightDirection"), 0.0f, 0.0f, 1.0f);
	GLuint timeLocation = colorShaderProgram.GetUniformLocation("time");
	glUniform1f(timeLocation, (float)Time::time);

	Triangle triangle(0);
	triangle.draw();

	Plane plane(0);
	plane.draw();

	Cube cube(0);
	cube.draw();
	
	Mesh mesh2("./Assets/Tank.obj");
	Texture texture("./Textures/MetalPlates.jpg");
	texture.Bind();
	mesh2.Draw();

	//Unuse shader programs
	colorShaderProgram.Unuse();

	display->BufferUpdate();
}

void Main_IndieTanks::GameLoop()
{
	const int MAX_UPDATE_ITERATIONS = 6;
	const float TARGET_FRAMERATE = 60.0f;
	float preivousTicks = SDL_GetTicks();

	while (gameState != GameState::QUIT)
	{
		float newTicks = SDL_GetTicks();
		float frameTime = newTicks - preivousTicks;
		preivousTicks = newTicks;
		printf("%f\n", frameTime);

		float totalDeltaTime = frameTime / TARGET_FRAMERATE;

		ProcessInput();

		Time::Timestep(totalDeltaTime); //TODO: make a time related class, and handle time for physics, and rendering

		int i = 0;
		if (totalDeltaTime > 0.0f && i < MAX_UPDATE_ITERATIONS)
		{
			Update();
			i++;
		}
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
				printf("X mouse position: %i \n", inputEvent.motion.xrel );
				printf("Y mouse position: %i \n\n", inputEvent.motion.yrel );	
				x = inputEvent.motion.x;
				y = inputEvent.motion.y;
				if (inputEvent.button.button == SDL_BUTTON_MIDDLE)
				{
					
					relativeX -= inputEvent.motion.xrel / 5;
					relativeY -= inputEvent.motion.yrel / 5;
				}
				if (inputEvent.button.button == SDL_BUTTON(SDL_BUTTON_RIGHT))
				{
					
					rotX += inputEvent.motion.xrel / 1000.0f;
					rotY -= inputEvent.motion.yrel / 1000.0f;
				}
				
				break;
			}
			case SDL_MOUSEWHEEL:
			{
				zoom += inputEvent.wheel.y;
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
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glDepthFunc(GL_LESS);
	InitShaders();

}

void Main_IndieTanks::InitShaders()
{
	colorShaderProgram.CompileShaders("Shaders/vertShading.vert", "Shaders/fragShading.frag");
	colorShaderProgram.AddAttribute("vertexPosition");
	colorShaderProgram.AddAttribute("vertexColor");
	//colorShaderProgram.AddAttribute("texCoord");
	//colorShaderProgram.AddAttribute("normal");
	colorShaderProgram.LinkShaders();
}

int main(int argc, char* args[])
{
	Main_IndieTanks indieTanks;
	indieTanks.Run();

	return 0;
}