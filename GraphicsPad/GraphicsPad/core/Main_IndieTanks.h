#ifndef MAIN_INDIETANKS_H
#define MAIN_INDIETANKS_H

#include "GLSLProgram.h" //TODO: remove this
#include "Display.h"


class Main_IndieTanks
{
	public:
		Main_IndieTanks();
		~Main_IndieTanks();

		void Run();
		int getWidth() const
		{
			return mainWidth;
		}
		int getHeight() const
		{
			return mainHeight;
		}

		enum GameState
		{
			RUNNING = 0,
			QUIT = 1,
		};

	private:
		Display *display;
		GameState gameState;

		GLSLProgram colorShaderProgram;

		int mainWidth;
		int mainHeight;
		float time;

		void InitSystems();
		void InitShaders();
		void GameLoop();
		void Start();
		void Update();
		void ProcessInput();
};




#endif