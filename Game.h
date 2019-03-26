#pragma once

#include <SDL.h>
#include "SDL_image.h"

class Game {
private:
	int count = 0;
	SDL_Window *window;

public:
	bool isRunning;
	int busena;

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreeen);
	void Zaidejai();
	void Busena();
	void NewFrame(int newFrame);
	int Frame();
	void update(int frame);
	void render(int frame);
	void clean();
	static SDL_Renderer *renderer;
	static SDL_Event event;
	bool running();
};
