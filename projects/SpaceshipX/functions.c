#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <time.h>
#include "functions.h"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


void KeyboardInput(SDL_Event event, int *up, int *down, int *right, int *left,int *starting, int *playing, int *gameover_screen, int *closing, int *try_again)
{
	if(*starting)
	{
		switch (event.type)
		{
		case SDL_QUIT :
			*starting = *playing = *gameover_screen = 0; *closing = 1; break;
		case SDL_KEYDOWN :
			switch (event.key.keysym.scancode)
			{
			case SDL_SCANCODE_ESCAPE:
				*starting = *playing = *gameover_screen = 0; *closing = 1;  break;
			default:
				break;
			}
			break;
		}
	}
	else if(*playing)
	{
		switch (event.type)
		{
		case SDL_QUIT :
			*starting = *playing = *gameover_screen = 0; *closing = 1; break;
		case SDL_KEYDOWN :
			switch (event.key.keysym.scancode)
			{
			case SDL_SCANCODE_RIGHT:
				*right = 1; break;
			case SDL_SCANCODE_LEFT:
				*left = 1; break;
			case SDL_SCANCODE_UP:
				*up = 1; break;
			case SDL_SCANCODE_DOWN:
				*down = 1; break;
			case SDL_SCANCODE_ESCAPE:
				*starting = *playing = *gameover_screen = 0; *closing = 1; break;
			default:
				break;
			}
			break;
		case SDL_KEYUP :
			switch (event.key.keysym.scancode)
			{
			case SDL_SCANCODE_RIGHT:
				*right = 0; break;
			case SDL_SCANCODE_LEFT:
				*left = 0; break;
			case SDL_SCANCODE_UP:
				*up = 0; break;
			case SDL_SCANCODE_DOWN:
				*down = 0; break;
			default:
				break;
			}
		}
	}
	else if(*gameover_screen)
	{
		switch (event.type)
		{
		case SDL_QUIT :
			*starting = *playing = *gameover_screen = 0; *closing = 1; break;
		case SDL_KEYDOWN :
			switch (event.key.keysym.scancode)
			{
			case SDL_SCANCODE_RETURN:
				*try_again = 1; break;
			case SDL_SCANCODE_ESCAPE:
				*starting = *playing = *gameover_screen = 0; *closing = 1; break;
			default:
				break;
			}
			break;
		}
	}
}



void UpdatePlayerPosition(SDL_Rect *player_dst, int up, int down, int right, int left)
{
	if (up && !down && !right && !left)
	{
		player_dst->y -= 5;
	}
	else if (down && !up && !right && !left)
	{
		player_dst->y += 5;
	}
	else if (right && !left && !up && !down)
	{
		player_dst->x += 5;
	}
	else if (left && !right && !up && !down)
	{
		player_dst->x -= 5;
	}
	else if (up && !down && right && !left)
	{
		player_dst->y -= 4;
		player_dst->x += 4;
	}
	else if (up && !down && !right && left)
	{
		player_dst->y -= 4;
		player_dst->x -= 4;
	}
	else if (down && !up && right && !left)
	{
		player_dst->y += 4;
		player_dst->x += 4;
	}
	else if (down && !up && !right && left)
	{
		player_dst->y += 4;
		player_dst->x -= 4;
	}

	if (player_dst->x < 0) player_dst->x = 0;
	if (player_dst->y < 0) player_dst->y = 0;
	if (player_dst->x > WINDOW_WIDTH - player_dst->w) player_dst->x = WINDOW_WIDTH - player_dst->w;
	if (player_dst->y > WINDOW_HEIGHT - player_dst->h) player_dst->y = WINDOW_HEIGHT - player_dst->h;
}


void DisplayPlayer(int *flame, SDL_Renderer *renderer, SDL_Texture *tex_player, SDL_Texture *tex_bg, SDL_Rect *player_src, SDL_Rect *player_dst, int *starting, int *playing, int *gameover_screen, int *closing)
{
	int i = 0;
	if(*starting)
	{
		SDL_Event event;
		while( *starting && (player_dst->y > WINDOW_HEIGHT * 3/4) )
		{
			while (SDL_PollEvent(&event))
			{
				KeyboardInput(event, NULL, NULL, NULL, NULL, starting, playing, gameover_screen, closing, NULL);
			}

			//animate the rocket's fire
			if (*flame >= 30) *flame = 0;
			i = (*flame/10);
			(*flame)++;

			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, tex_bg, NULL, NULL);
			SDL_RenderCopy(renderer, tex_player, &player_src[i], player_dst);
			SDL_RenderPresent(renderer);

			player_dst->y -= 3;
			SDL_Delay(1000/60);
		}
	}
	else if(*playing)
	{
		//animate the rocket's fire
		if (*flame >= 30) *flame = 0;
		i = (*flame/10);
		(*flame)++;

		SDL_RenderCopy(renderer, tex_player, &player_src[i], player_dst);
	}
}


void UpdateRocksPositions(int rock_num, int *speed, SDL_Rect *rock_src, SDL_Rect *rock_dst, int starting, int playing, int gameover_screen)
{
	int x = 0;
        //initializing the rocks' positions 
	if(starting)
	{
		for(int i=0; i<rock_num; i++)
		{
			x = (rand() % 4) + 6;
			speed[i] = 10 - x;
			rock_dst[i].w = rock_src->w * x/10;
			rock_dst[i].h = rock_src->h * x/10;
			rock_dst[i].x = rock_src->w * i;
			rock_dst[i].y = - rock_dst[i].h - rand() % WINDOW_HEIGHT;
		}
	}
	else if(playing)
	{
		for(int i=0; i<rock_num; i++)
		{
			//this respawn a rock after it goes off screen
			if( rock_dst[i].y > WINDOW_HEIGHT )
			{
				x = (rand() % 4) + 6;
				speed[i] = 10 - x;
				rock_dst[i].w = rock_src->w * x/10;
				rock_dst[i].h = rock_src->h * x/10;
				rock_dst[i].y = - rock_dst[i].h - rand() % WINDOW_HEIGHT;
			}
			else
			{
				rock_dst[i].y += speed[i];
			}
		}
	}
	else if(gameover_screen)
	{
		for(int i=0; i<rock_num; i++)
		{
			//only move down a rock if it is already on the screen
			if( (rock_dst[i].y < WINDOW_HEIGHT) && (rock_dst[i].y + rock_dst[i].h > 0) )
			{
				rock_dst[i].y += speed[i];
			}
		}
	}
}


void DisplayRocks(SDL_Renderer *renderer, SDL_Texture *tex_rocks, SDL_Rect *rock_src, SDL_Rect *rock_dst, int rock_num, int *no_rock_left, int playing, int gameover_screen)
{
	if (playing)
	{
		for(int i=0; i<rock_num; i++)
		{
			SDL_RenderCopy(renderer, tex_rocks, rock_src, &rock_dst[i]);
		}
	}
	else if (gameover_screen)
	{
		for (int i=0; i<rock_num; i++)
		{
			if( (rock_dst[i].y < WINDOW_HEIGHT) && (rock_dst[i].y + rock_dst[i].h > 0) )
			{
				SDL_RenderCopy(renderer, tex_rocks, rock_src, &rock_dst[i]);
				*no_rock_left = 0;
			}
		}
	}
}



int CheckIfLost(SDL_Rect player_dst, int rock_num, SDL_Rect *rock_dst)
{
	int tolerence = 10;
	for (int i=0; i<rock_num; i++)
	{
		//if the player and the rock are in the same vertical line
		if ( ( player_dst.x + player_dst.w - tolerence ) > rock_dst[i].x &&
		     ( player_dst.x < (rock_dst[i].x + rock_dst[i].w - tolerence ) ) )
		{
			//if the player and the rock are in the same horizontale line
			if ( (player_dst.y < (rock_dst[i].y + rock_dst[i].h - tolerence)) && 
			     (player_dst.y + player_dst.h - tolerence) > rock_dst[i].y )
			{
				//the player has lost
				return 1;
			}
		}
	}

	//the player did not lose yet
	return 0;
}
