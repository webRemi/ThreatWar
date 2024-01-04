#include <SDL2/SDL.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>

SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer);
SDL_Texture* loadText(const char text[], const char fontPath[], int fontSize, SDL_Color textColor, SDL_Renderer* renderer);

int main(int argc, char *argv[]) {
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Color black = {255, 255, 255, 1};
	SDL_Texture *image = NULL;
	SDL_Texture *point = NULL;
	SDL_Texture *malware = NULL;
	SDL_Color text_color = {0, 0, 0, 1};
	SDL_Texture *comment = NULL;
	SDL_Texture *city = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
		goto Quit;

	if (TTF_Init() != 0) 
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
	point = loadImage("point.bmp", renderer);
	malware = loadImage("malware.bmp", renderer);
	comment = loadText("Backdoored server", "cyber.ttf", 20, text_color, renderer);
	city = loadText("United States -> Italy", "cyber.ttf", 20, text_color, renderer);

	if (image == NULL)
		goto Quit;
	
	if (malware == NULL)
		goto Quit;
	
	if (comment == NULL)
		goto Quit;

	SDL_Rect dstRect = {0, 0, 1920, 1080}; 
    SDL_RenderCopy(renderer, image, NULL, &dstRect);
	
	int x = 400, y = 300, w = 5, h = 5;
	
	/*SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	int gridSpacing = 40;

	for (int x = 0; x <= 1920; x += gridSpacing) {
        SDL_RenderDrawLine(renderer, x, 0, x, 1080);
    }

    // Draw horizontal lines
    for (int y = 0; y <= 1080; y += gridSpacing) {
        SDL_RenderDrawLine(renderer, 0, y, 1920, y);
    }*/

	//USA attacking italy
	while (x != 1000) {
		SDL_Rect dstRect2 = {x, y, w, h};
		SDL_RenderCopy(renderer, point, NULL, &dstRect2);
		
		SDL_Rect dstRect3 = {10, 700, 50, 50};
		SDL_RenderCopy(renderer, malware, NULL, &dstRect3);
		
		SDL_Rect dstRect4 = {70, 700, 200, 20};
		SDL_RenderCopy(renderer, comment, NULL, &dstRect4);
		
		SDL_Rect dstRect5 = {70, 730, 200, 20};
		SDL_RenderCopy(renderer, city, NULL, &dstRect5);
		
		SDL_RenderPresent(renderer);
		
		SDL_Delay(10);
		
		x += 2;
	}

	SDL_Rect dstRect6 = {1000, 275, 50, 50};
	SDL_RenderCopy(renderer, malware, NULL, &dstRect6);
	
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &dstRect);
	SDL_RenderCopy(renderer, image, NULL, &dstRect);
	SDL_RenderPresent(renderer);
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

SDL_Texture* loadText(const char text[], const char fontPath[], int fontSize, SDL_Color textColor, SDL_Renderer* renderer) {
    SDL_Surface *tmp = NULL;
	SDL_Texture *texture = NULL;
	TTF_Font *font = NULL;
	font = TTF_OpenFont(fontPath, fontSize);
	tmp = TTF_RenderText_Solid(font, text, textColor);

    if (tmp == NULL) {
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        return NULL;
    }

	texture = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);

	if (texture == NULL) {
		fprintf(stderr, "Error: %s\n", SDL_GetError());
	}

    TTF_CloseFont(font);

    return texture;
}
