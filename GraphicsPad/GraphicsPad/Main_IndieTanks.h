#ifndef MAIN_INDIETANKS_H
#define MAIN_INDIETANKS_H
#include "Display.h"

class Main_IndieTanks
{
	public:
		Main_IndieTanks();
		~Main_IndieTanks();

		void Run();

		enum GameState
		{
			RUNNING = 0,
			QUIT = 1,
		};

	private:
		Display *display;
		GameState gameState;

		void InitDisplay();
		void GameLoop();
		void Update();
		void ProcessInput();
};




#endif