#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Color blue = {0, 95, 255, 1};

	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
		goto Quit;
	
	window = SDL_CreateWindow("ThreatWar", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
	
	if (window == NULL) 
		goto Quit;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	if (renderer == NULL)
		goto Quit;

	if (SDL_SetRenderDrawColor(renderer, blue.r, blue.g, blue.b, blue.a) != 0) 
		goto Quit;

	if (SDL_RenderClear(renderer) != 0) 
		goto Quit;
	
	SDL_Delay(1);
	SDL_RenderPresent(renderer);
	SDL_Delay(3000);
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

Quit:
	SDL_Quit();
}
