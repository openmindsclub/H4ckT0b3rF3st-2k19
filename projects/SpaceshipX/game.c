//gcc game.c functions.c -lSDL2 -lSDL2_ttf -lSDL2_image -Wall -o SpaceshipX

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "functions.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


int main(int argc, char *argv[])
{
	srand(time(NULL));
	int playing = 0, flame = 0;
	int up = 0, down = 0, left = 0, right = 0;

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Surface *surface;
	SDL_Texture *tex_bg, *tex_player;
	SDL_Rect player_src[3], player_dst, player_dimentions;
	SDL_Event event;

	//Initializing SDL
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

	window = SDL_CreateWindow("Game",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	

	//Loading the background image and creating a texture
	surface = IMG_Load("images/background.png");
	tex_bg = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (surface == NULL)
	{
		puts("Error : images/background.png not found\n");
		return 1; //return error
	}

	//Loading the rockets image and creating a texture
	surface = IMG_Load("images/mini_rockets.png");
	tex_player = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_QueryTexture(tex_player, NULL, NULL, &player_dimentions.w, &player_dimentions.h);
	SDL_FreeSurface(surface);
	if (surface == NULL)
	{
		puts("Error : images/mini_rockets.png not found\n");
		return 1; //return error
	}

	//initializing the source rockets
	for (int i=0; i<3; i++)
	{
		player_src[i].w = player_dimentions.w/3;
		player_src[i].h = player_dimentions.h;
		player_src[i].x = i * player_dimentions.w/3;
		player_src[i].y = 0;
	}

	//initializing the destination rocket
	player_dst.w = player_dimentions.w/3;
	player_dst.h = player_dimentions.h;
	player_dst.x = WINDOW_WIDTH/2 - player_dst.w/2;
	player_dst.y = WINDOW_HEIGHT * 3/4;

	playing = 1;
	//the game's main loop
	while (playing) 
	{
		while (SDL_PollEvent(&event))
		{
			KeyboardInput(event, &up, &down, &right, &left, &playing);
		}

		UpdatePlayerPosition(&player_dst, up, down, right, left);

		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, tex_bg, NULL, NULL);	
		
		DisplayPlayer(&flame, renderer, tex_player, player_src, &player_dst);

		SDL_RenderPresent(renderer);
		SDL_Delay(1000/60);
	}	


	//clean by destroying everything to free the system resources
	SDL_DestroyTexture(tex_bg);
	SDL_DestroyTexture(tex_player);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
