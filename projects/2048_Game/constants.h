#ifndef DEF_CONSTANTS
#define DEF_CONSTANTS

	#define DELAY 100000
	#define NB 4
	#define SQ_X	 7
	#define SQ_Y 	 3
	#define MAX_X 	 NB*SQ_X
	#define MAX_Y 	 NB*SQ_Y

	#define BOUCLE(i,j)   for (i=0; i<NB; i++)   for (j=0; j< NB; j++)
	// COLORS
 	#define YELLOW_PAIR 	init_pair(1,COLOR_WHITE,COLOR_GREEN)
	#define GREEN_PAIR 		init_color(COLOR_YELLOW,0,750,0); init_pair(2,COLOR_WHITE,COLOR_YELLOW)
	#define RED_PAIR		init_color(COLOR_RED,700,0,0); init_pair(3,COLOR_WHITE,COLOR_RED)
	#define BLUE_PAIR		init_pair(4,COLOR_WHITE,COLOR_BLUE)
	#define MAGENTA_PAIR	init_pair(5,COLOR_WHITE,COLOR_MAGENTA)
	#define CYAN_PAIR		init_pair(6,COLOR_WHITE,COLOR_CYAN)
	#define WHITE_PAIR		init_pair(7,COLOR_BLACK,COLOR_WHITE)
	#define GRAY_PAIR		init_pair(8,COLOR_WHITE,COLOR_BLACK)
	#define ORANGE_PAIR		init_color(9,1000,505,0); init_pair(9,COLOR_WHITE,9)
	#define BROWN_PAIR		init_color(10,656,500,66); init_pair(10,COLOR_WHITE,10)
	#define DARKGREEN_PAIR  init_color(11,0,400,0); init_pair(11,COLOR_WHITE,11)
	#define LIGHTRED_PAIR	init_color(12,900,50,50); init_pair(12,COLOR_WHITE,12)
	#define ORANGE_RED_PAIR	init_color(13,1000,215,0); init_pair(13,COLOR_WHITE,13)
	#define PURPLE_PAIR	init_color(14,776,00,1000); init_pair(14,COLOR_WHITE,14)
	#define DARKBLUE_PAIR	init_color(15,0xc6,00,1000);  init_pair(15,COLOR_WHITE,15)
	#define PINK_PAIR		init_color(16,1000,0,435);  init_pair(16,COLOR_WHITE,16)

	#define YELLOW 1
	#define GREEN 2
	#define RED 3
	#define BLUE 4
	#define MAGENTA 5
	#define CYAN 6
	#define WHITE 7
	#define GRAY 8
	#define ORANGE 9
	#define BROWN 10
	#define DARKGREEN 11
	#define LIGHTRED 12
	#define ORANGE_RED 13
	#define PURPLE 14
	#define DARKBLUE 15
	#define PINK 16

	#define COL_LEFT(i,j)   tab[i][j-1]
	#define COL_RIGHT(i,j)   tab[i][j+1]
	#define COL_UP(i,j)   tab[i-1][j]
	#define COL_DOWN(i,j)   tab[i+1][j]

#endif
