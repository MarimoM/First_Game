#pragma once

#include "Game.h"

class Piesimas {
public:
	static SDL_Texture* LoadTexture(const char* texture);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};