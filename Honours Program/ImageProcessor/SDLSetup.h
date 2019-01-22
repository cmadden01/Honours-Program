#pragma once
#include "stdafx.h"
#include <SDL.h>
#include "GL/glew.h"



class SDLSetup
{
public:

	SDLSetup()
	{
		running = true;
	}

	bool running;

	void setupRenderContext();
	void createWindow();

	void swapWindow();
	void deleteContext();
	void pollEvent();

private:


	SDL_Window * window;
	SDL_GLContext glContext;

	SDL_Event sdlEvent;

};
