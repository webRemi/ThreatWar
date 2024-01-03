#include <SDL2/SDL.h>
#include <stdlib.h>

SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer);

int main(int argc, char *argv[]) {
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Color black = {255, 255, 255, 1};
	SDL_Texture *image = NULL;
	SDL_Texture *malware = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
		goto Quit;
	
	window = SDL_CreateWindow("ThreatWar", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
	
	if (window == NULL) 
		goto Quit;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	if (renderer == NULL)
		goto Quit;

	if (SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a) != 0) 
		goto Quit;

	if (SDL_RenderClear(renderer) != 0) 
		goto Quit;

	image = loadImage("world.bmp", renderer);
	malware = loadImage("malware.bmp", renderer);

	if (image == NULL)
		goto Quit;
	
	if (malware == NULL)
		goto Quit;

	SDL_Rect dstRect = {0, 0, 1920, 1080}; 
    SDL_RenderCopy(renderer, image, NULL, &dstRect);
	
	int x = 400, y = 300, w = 50, h = 50;
	
	//USA attacking italy
	while (x != 1000) {
		SDL_Rect dstRect2 = {x, y, w, h};
		SDL_RenderCopy(renderer, malware, NULL, &dstRect2);
		x++;
		SDL_RenderPresent(renderer);
		SDL_Delay(10);
	}
	
	//SDL_RenderPresent(renderer);
	SDL_Delay(3000);
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

Quit:
	SDL_Quit();
}

SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer) {
	SDL_Surface *tmp = NULL;
	SDL_Texture *texture = NULL;
	tmp = SDL_LoadBMP(path);
	
	if (tmp == NULL) {
		fprintf(stderr, "Error: %s", SDL_GetError());
		return NULL;
	}

	texture = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);
	
	if (texture == NULL) {
		fprintf(stderr, "Error: %s", SDL_GetError());
		return NULL;
	}
	
	return texture;
}
