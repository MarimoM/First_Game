#include "pch.h"
#include "Objektai.h"
#include "Piesimas.h"
#include "Game.h"
#include <iostream>
#include <fstream>
#include "SDL.h"
#include <stdlib.h> 
using namespace std;

bool flagObst = false;
bool GameOver = false;
bool pradzia = true;

int birdPose[2];
int rocketPos;
int score = 0;
int framecounter;
double speed;

Objektas::Objektas(const char * texturesheet, int x, int y)
{
	//Atidarome paveiksliuka
	objTexture = Piesimas::LoadTexture(texturesheet);
	xpos = x;
	ypos = y;
	speed = 0;
}

void Objektas::Update(int h, int w, int judam)
{
	SDL_Event event;
	SDL_PollEvent(&event);
	Game obj;

	speed += 1;

	//background
	if (judam==1)
	{
		if (pradzia) xpos = 0;
		else if(GameOver) xpos = -6600;
		else if (xpos == -630 || xpos == - 1050 || xpos == -1800 || 
			xpos == -2570 || xpos == -3320 
			|| xpos == -3790 || xpos == -4100 || xpos == -4790 || xpos == -5230)
		{
			flagObst = true;
			xpos -= 10;
		}
		else if (xpos < -5880) xpos = -510;
		else xpos -= 10;
	}
	else if (judam == 2)
	{
		xpos-=20;
		rocketPos = xpos;
		if (xpos <= 0 && GameOver==false) xpos = rand() % 7000 + 700;
		else xpos += 0;
	}
	else if (judam == 3)
	{
		xpos -= 10;
		ypos += 10;
		if (ypos > 500 && GameOver == false)
		{
			xpos = rand() % 6000 + 500;
			ypos = -100;
		}
		else ypos += 0;
		birdPose[0] = ypos;
		birdPose[1] = xpos;
	}
	//Player
	else
	{
		if (pradzia)
		{
			if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) pradzia = false;
		}
		else 
		{
			//Kliutys
			if ((flagObst == true && ypos == 310) || (rocketPos<200 && ypos==180) || (birdPose[0]<400 && birdPose[1]<150) && ypos==310)
			{
				GameOver = true;
			}
			else if (flagObst == true && ypos != 310)
			{
				flagObst = false;
				score++;
			}
			//Sokinejimas
			if (event.type == SDL_KEYDOWN && pradzia == false) obj.NewFrame(1); 
			if (event.type == SDL_KEYUP) obj.NewFrame(2);
			//Jei pabaiga
			if (GameOver)
			{
				if (event.type == SDL_KEYDOWN)
				{
					if (event.key.keysym.sym == SDLK_q) obj.Busena();
					obj.NewFrame(2);
				}
				if (event.type == SDL_KEYUP) {
					if (event.key.keysym.sym == SDLK_r) {
						GameOver = false;
						flagObst = false;
					}
				}
				else obj.NewFrame(0);
			}
		}
	}
	//Staciakampis
	srcRect.h = h;
	srcRect.w = w;
	srcRect.x = 0;
	srcRect.y = 0;

	//Paveiksliukas
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w ;
	destRect.h = srcRect.h ;
}

void Objektas::Render()
{
	//Atvaizdavimas
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
