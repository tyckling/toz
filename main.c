#include <stdio.h>
#include "SDL.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

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
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);

	if(gWindow == NULL)
	{
		printf("Cannot create window with error %s\n", SDL_GetError());
		return -1;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

	bool quit = false;

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
		SDL_RenderClear(gRenderer);
		SDL_RenderPresent(gRenderer);
		SDL_Delay(16);
	}

	// Clear resources
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();

	return 0;
}
