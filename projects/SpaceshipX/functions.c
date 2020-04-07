#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <time.h>
#include <math.h>
#include "functions.h"
#define WINDOW_WIDTH 920
#define WINDOW_HEIGHT 700
#define ROCK_NUM 10


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
	int speed = 7, diognal_speed = 5;

	if (up && !down && !right && !left)
	{
		player_dst->y -= speed;
	}
	else if (down && !up && !right && !left)
	{
		player_dst->y += speed;
	}
	else if (right && !left && !up && !down)
	{
		player_dst->x += speed;
	}
	else if (left && !right && !up && !down)
	{
		player_dst->x -= speed;
	}
	else if (up && !down && right && !left)
	{
		player_dst->y -= diognal_speed;
		player_dst->x += diognal_speed;
	}
	else if (up && !down && !right && left)
	{
		player_dst->y -= diognal_speed;
		player_dst->x -= diognal_speed;
	}
	else if (down && !up && right && !left)
	{
		player_dst->y += diognal_speed;
		player_dst->x += diognal_speed;
	}
	else if (down && !up && !right && left)
	{
		player_dst->y += diognal_speed;
		player_dst->x -= diognal_speed;
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


void UpdateRocksPositions(SDL_Rect *rock_src, SDL_Rect *rock_dst, int starting, int playing, int gameover_screen)
{
        static int frame_num = 0, acceleration = 10, accel_ratio = 180, speed[ROCK_NUM];
        frame_num++;

        if(frame_num > accel_ratio)
        {
                acceleration++;
                frame_num = 0;
                accel_ratio = accel_ratio * 1.5;
        }

	int x = 0;
        //initializing the rocks' positions 
	if(starting)
	{
		frame_num = 0; acceleration = 10; accel_ratio = 180;
		for(int i=0; i<ROCK_NUM; i++)
		{
			x = (rand() % 4) + 6;
			speed[i] = acceleration - x;
			rock_dst[i].w = rock_src->w * x/10;
			rock_dst[i].h = rock_src->h * x/10;
			rock_dst[i].x = rock_src->w * i;
			rock_dst[i].y = - rock_dst[i].h - rand() % WINDOW_HEIGHT;
		}
	}
	else if(playing)
	{
		for(int i=0; i<ROCK_NUM; i++)
		{
			//this respawn a rock after it goes off screen
			if( rock_dst[i].y > WINDOW_HEIGHT )
			{
				x = (rand() % 4) + 6;
				speed[i] = acceleration - x;
				if (speed[i] == 1) speed[i]++;
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
		for(int i=0; i<ROCK_NUM; i++)
		{
			//only move down a rock if it is already on the screen
			if( (rock_dst[i].y < WINDOW_HEIGHT) && (rock_dst[i].y + rock_dst[i].h > 0) )
			{
				rock_dst[i].y += speed[i];
			}
		}
	}
}


void DisplayRocks(SDL_Renderer *renderer, SDL_Texture *tex_rocks, SDL_Rect *rock_dst, int *no_rock_left, int playing, int gameover_screen)
{
	if (playing)
	{
		for(int i=0; i<ROCK_NUM; i++)
		{
			SDL_RenderCopy(renderer, tex_rocks, NULL, &rock_dst[i]);
		}
	}
	else if (gameover_screen)
	{
		for (int i=0; i<ROCK_NUM; i++)
		{
			if( (rock_dst[i].y < WINDOW_HEIGHT) && (rock_dst[i].y + rock_dst[i].h > 0) )
			{
				SDL_RenderCopy(renderer, tex_rocks, NULL, &rock_dst[i]);
				*no_rock_left = 0;
			}
		}
	}
}



int CheckIfLost(SDL_Rect player_dst, SDL_Rect *rock_dst)
{
	int tolerence = 10;
	for (int i=0; i<ROCK_NUM; i++)
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
