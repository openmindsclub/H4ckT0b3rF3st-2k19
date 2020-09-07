#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "functions.h"

#define WINDOW_WIDTH 920
#define WINDOW_HEIGHT 700
#define ROCK_NUM 10


int main(int argc, char *argv[])
{
	srand(time(NULL));
	int starting = 0, playing = 0, gameover_screen = 0, closing = 0, try_again = 0;
	int flame = 0, no_rock_left = 0;
	int up = 0, down = 0, left = 0, right = 0;

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Surface *surface;
	SDL_Texture *tex_bg, *tex_player, *tex_rocks, *tex_gameover;
	SDL_Rect player_src[3], player_dst, rock_src, player_dimentions, gameover_dst, rock_dst[ROCK_NUM];
	SDL_Event event;


	//Initializing SDL
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

	window = SDL_CreateWindow("Game",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


	//Initializing TTF
	TTF_Init();
	TTF_Font *font = TTF_OpenFont("font/benethFREE.ttf", 90);
	SDL_Color White = {255, 255, 255};
	if (font == NULL)
	{
		puts("Error : font file not found\n");
		return 1; //return error
	}
	

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

	//Loading the rocks image and creating a texture
	surface = IMG_Load("images/rock.png");
	tex_rocks = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_QueryTexture(tex_rocks, NULL, NULL, &rock_src.w, &rock_src.h);
	SDL_FreeSurface(surface);
        if (surface == NULL)
        {
		puts("Error : images/rock.png not found\n");
                return 1; //return error
        }

	//Loading the game over image and creating a texture
	surface = TTF_RenderText_Blended_Wrapped(font, "GAME OVER\n   press enter", White, 400);
	tex_gameover = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	gameover_dst.w = 300;
	gameover_dst.h= 150;

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

	starting = 1;
	//the game's main loop
	while (!closing) 
	{
		if (starting)//display the first animation
		{
			up = down = left = right = 0;

			player_dst.x = (WINDOW_WIDTH - player_dst.w) /2;
			player_dst.y = WINDOW_HEIGHT;

			DisplayPlayer(&flame, renderer, tex_player, tex_bg, player_src, &player_dst, &starting, &playing, &gameover_screen, &closing);
			UpdateRocksPositions(&rock_src, rock_dst, starting, playing, gameover_screen);

			starting = 0;
			playing = !closing;
		}

		while (playing)
		{
			//if the player hit a rock break from playing loop and enter gameover loop
			gameover_screen = CheckIfLost(player_dst, rock_dst);
			playing = !gameover_screen;
	
			while (SDL_PollEvent(&event))
			{
				KeyboardInput(event, &up, &down, &right, &left, &starting, &playing, &gameover_screen, &closing, NULL);
			}

			UpdatePlayerPosition(&player_dst, up, down, right, left);
			UpdateRocksPositions(&rock_src, rock_dst, starting, playing, gameover_screen);

			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, tex_bg, NULL, NULL);	
			
			DisplayRocks(renderer, tex_rocks, rock_dst, &no_rock_left, playing, gameover_screen);
			DisplayPlayer(&flame, renderer, tex_player, tex_bg, player_src, &player_dst, &starting, &playing, &gameover_screen, &closing);

			SDL_RenderPresent(renderer);
			SDL_Delay(1000/60);
		}

		//initialize game over text position
		gameover_dst.x = (WINDOW_WIDTH-gameover_dst.w) /2;
		gameover_dst.y = (WINDOW_HEIGHT-gameover_dst.h) /2;
		
		while (gameover_screen)
		{
			while (SDL_PollEvent(&event))
			{
				KeyboardInput(event,  NULL, NULL, NULL, NULL, &starting, &playing, &gameover_screen, &closing, &try_again);
			}

			no_rock_left = 1;//assume that there is no rock left in the screen
			if (try_again) gameover_dst.y += 5;//if the player hit enter to play again the gameover text moves down 

			SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer, tex_bg, NULL, NULL);

			UpdateRocksPositions(&rock_src, rock_dst, starting, playing, gameover_screen);
			DisplayRocks(renderer, tex_rocks, rock_dst, &no_rock_left, playing, gameover_screen);
			
			SDL_RenderCopy(renderer, tex_gameover, NULL, &gameover_dst);
			SDL_RenderPresent(renderer);
			SDL_Delay(1000/60);

			//if the gameover text is no longer in the screen than break out of the loop and start a new game
			if ( (gameover_dst.y > WINDOW_HEIGHT) && no_rock_left )
			{
				gameover_screen = try_again = 0;
				starting = 1;
			}
		}
	}	


	//clean by destroying everything to free the system resources
	SDL_DestroyTexture(tex_bg);
	SDL_DestroyTexture(tex_player);
	SDL_DestroyTexture(tex_rocks);
	SDL_DestroyTexture(tex_gameover);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
