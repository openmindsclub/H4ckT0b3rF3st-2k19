#ifndef FUNCTION_H_
#define FUNCTION_H_


void KeyboardInput(SDL_Event event, int *up, int *down, int *right, int *left,int *playing);

void DisplayPlayer(int *flame, SDL_Renderer *renderer, SDL_Texture *tex_player, SDL_Rect *player_src, SDL_Rect *player_dst);

void UpdatePlayerPosition(SDL_Rect *player_dst, int up, int down, int right, int left);

#endif
