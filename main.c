#include <stdio.h>
#include "SDL.h"
#include "GL/glew.h"
#include "SDL2/SDL_opengl.h"
#include "gl.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL;
SDL_GLContext gGLContext = NULL;

void initGL()
{
	SDL_GL_CreateContext(gWindow);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glewExperimental = GL_TRUE;
	glewInit();
	
	setupTriangle();
}

int main(int argc, char* argv[])
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL cannot init with error %s\n", SDL_GetError());
		return -1;
	}

	gWindow = SDL_CreateWindow(
		"ToZ",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
	);

	if(gWindow == NULL)
	{
		printf("Cannot create window with error %s\n", SDL_GetError());
		return -1;
	}

	initGL();

	int quit = false;

	SDL_Event sdlEvent;

	while(!quit)
	{
		while(SDL_PollEvent(&sdlEvent) != 0)
		{
			switch(sdlEvent.type)
			{
				case SDL_QUIT:
					quit = true;

				break;
			}
		}

		// Graphics update here
		draw();
		SDL_GL_SwapWindow(gWindow);
		//SDL_Delay(64);
		
	}

	// Clear resources
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();

	return 0;
}
