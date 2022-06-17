#include <iostream>
#include <SDL.h>

const int WIDTH = 640;
const int HEIGHT = 480;

bool init();
void end();
bool loadImage();

SDL_Window* window = NULL;
SDL_Surface* wScreen = NULL;
SDL_Surface* Image = NULL;

int main(int argc, char* argv[]) {
	SDL_Event e;
	bool quit = false;

	if (!init()) {
		std::cout << "init failed!";
	}
	else {
		if (!loadImage()) {
			std::cout << "loading image failed!";
		}
		else {
			SDL_BlitSurface(Image, NULL, wScreen, NULL);
			SDL_UpdateWindowSurface(window);
			while (!quit) {
				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) quit = true;
				}
			}
		}
	}
	end();
	return 0;
}

bool init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "failed to init!, error: " << SDL_GetError();
		return false;
	}
	else {
		window = SDL_CreateWindow("Here's a Penguin!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			std::cout << "winow creation failed!, error: " << SDL_GetError();
			return false;
		}
		else {
			wScreen = SDL_GetWindowSurface(window);
		}
	}
	return true;
}

void end() {
	SDL_FreeSurface(Image);
	Image = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}

bool loadImage() {

	Image = SDL_LoadBMP("penguin.bmp");

	if (Image == NULL) {
		std::cout << "image loading failed!, error: " << SDL_GetError();
		return false;
	}
	return true;
}