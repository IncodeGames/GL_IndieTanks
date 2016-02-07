#ifndef	DISPLAY_H
#define DISPLAY_H

#include <SDL2\SDL.h>
#include <string>

class Display
{
public:
	Display(int width, int height, const std::string& title);
	virtual ~Display();

	void BufferUpdate();

protected:
private:
	Display(const Display& other) {}
	Display& operator=(const Display& other) {}

	SDL_Window* sdlWindow;
	SDL_GLContext glContext;

	bool isClosed;
};

#endif