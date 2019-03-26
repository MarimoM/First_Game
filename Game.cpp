#include "pch.h"
#include "Game.h"
#include "SDL.h"
#include "Objektai.h"
#include <iostream>
using namespace std;


//Zaidimo onlektai
Objektas* player;
Objektas* playerUP;
Objektas* playerRIGHT1;
Objektas* playerRIGHT;
Objektas* background;
Objektas* background2;
Objektas* Rocket;
Objektas* Bird;

SDL_Renderer* Game::renderer = nullptr;
bool Over;
int frame;
int counter;


//Piesiame nauja langa
void Game::init(const char * title, int xpos, int ypos, int width, int height, bool fullscreeen)
{
	int flags = 0; frame = 0; counter = 0;
	if (fullscreeen) flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, xpos, ypos, width, height, false);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);}
		isRunning = true;
	}
	else { isRunning = false;}

	Zaidejai(); //sukuria objektus
}
void Game::NewFrame(int newFrame) { frame = newFrame;}
int Game::Frame()
{
	if (frame > 0) return frame;
	else return 0;
}
void Game::Busena() {Over = true;}

void Game::Zaidejai()
{
	player = new Objektas("pictures/01_stand1.png", 20, 310);
	playerUP = new Objektas("pictures/02_jump.png", 20, 180);
	playerRIGHT = new Objektas("pictures/03_walk.png", 20, 310);
	playerRIGHT1 = new Objektas("pictures/03a_walk.png", 20, 310);
	background = new Objektas("pictures/a.png", 0, 0);
	background2 = new Objektas("pictures/a - Copy (3).png", 0, 0);
	Rocket = new Objektas("pictures/Rock.png", 5000, 150);
	Bird = new Objektas("pictures/Kamikadze.png", 1000, 0);
}

void Game::update(int busena)
{
	//Judinam
	if (busena == 0) player->Update(125, 193, 0);
	else if (busena == 1) playerUP->Update(125, 193, 0);
	else if (busena == 2 && counter < 8) playerRIGHT->Update(125, 193, 0);
	else playerRIGHT1->Update(125, 193, 0);
	Rocket->Update(140, 250, 2);
	Bird->Update(64, 97, 3);
	background->Update(500, 7624, 1);
}

void Game::render(int busena)
{
	//Rodom
	SDL_RenderClear(renderer);

	background->Render();
	Rocket->Render();
	Bird->Render();

	if (busena == 0) player->Render();
	else if (busena == 1) playerUP->Render();
	else if (busena == 2 && counter < 8)
	{
		playerRIGHT->Render();
		counter++;
	}
	else
	{
		playerRIGHT1->Render();
		counter++;
		if (counter > 16) counter = 0;
	}
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

bool Game::running()
{
	if (Over) isRunning = false;
	return isRunning;
}