#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <time.h>
#include "functions.h"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


void KeyboardInput(SDL_Event event, int *up, int *down, int *right, int *left,int *playing)
{
	switch (event.type)
	{
	case SDL_QUIT :
		*playing = 0; break;
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
			*playing = 0; break;
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



void DisplayPlayer(int *flame, SDL_Renderer *renderer, SDL_Texture *tex_player, SDL_Rect *player_src, SDL_Rect *player_dst)
{
	int i = 0;

	//animate the rocket's fire
	if (*flame >= 30) *flame = 0;
	i = (*flame/10);

	(*flame)++;

	SDL_RenderCopy(renderer, tex_player, &player_src[i], player_dst);
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
