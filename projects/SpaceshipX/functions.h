#ifndef FUNCTION_H_
#define FUNCTION_H_


void KeyboardInput(SDL_Event event, int *up, int *down, int *right, int *left,int *starting, int *playing, int *gameover_screen, int *closing, int *try_again);

void UpdatePlayerPosition(SDL_Rect *player_dst, int up, int down, int right, int left);

void DisplayPlayer(int *flame, SDL_Renderer *renderer, SDL_Texture *tex_player, SDL_Texture *tex_bg, SDL_Rect *player_src, SDL_Rect *player_dst, int *starting, int *playing, int *gameover_screen, int *closing);

void UpdateRocksPositions(int rock_num, int *speed, SDL_Rect *rock_src, SDL_Rect *rock_dst, int starting, int playing, int gameover_screen);

void DisplayRocks(SDL_Renderer *renderer, SDL_Texture *tex_rocks, SDL_Rect *rock_dst, int rock_num, int *no_rock_left, int playing, int gameover_screen);

int CheckIfLost(SDL_Rect player_dst, int rock_num, SDL_Rect *rock_dst);

#endif
