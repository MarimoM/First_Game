#pragma once
#include "Game.h"
#include <fstream>

class Objektas {
	int xpos;
	int ypos;
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
public:
	Objektas(const char* texturesheet, int x, int y);
	void Update(int h, int w, int judam);
	void Render();
};
