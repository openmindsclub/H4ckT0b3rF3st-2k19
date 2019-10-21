#ifndef GAME2048_HEADER
#define GAME2048_HEADER

	#include "constants.h"
	extern int score;
	extern int old[NB][NB];
	extern int old_score;

	void init(WINDOW* squares[NB][NB],int tab[NB][NB]);	    // Initialize the board by generating and colorating two numbers and put '.' to the empty cases 
	void colorize(WINDOW* win, int tab[NB][NB], int i, int j);    // Colorize a square depending on the number
	//void setnumber(WINDOW*  win , int tab[NB][NB], int i, int j , int n);   //  Put the number on the square and colorize its background.
	int isfull(int tab[NB][NB]);  // Check if the board is full
	int generate_number(WINDOW* win[NB][NB] , int tab[NB][NB], int enable);   // Generate a random number ( 2 or 4 ) and put it in an empty case randomly
	int game_over(int tab[NB][NB]);	// of corse , check if the game is over
	int blank_columns(int tab[NB][NB]);  // return how many black columns is in the board
	void print_board(WINDOW* squares[NB][NB], int tab[NB][NB]);   //  Print the board
	void reset_board(WINDOW* squares[NB][NB], int tab[NB][NB]);   // Reset board to it initial state ( e.g : to restart the game)
	int move_right(WINDOW* squares[NB][NB] , int tab[NB][NB]);
	int move_left(WINDOW* squares[NB][NB] , int tab[NB][NB]);
	int move_up(WINDOW* squares[NB][NB] , int tab[NB][NB]);
	int move_down(WINDOW* squares[NB][NB] , int tab[NB][NB]);
	int val_in_tab(int tab[3],int v); // check if a value is in the tab
	void rotate(int tab[NB][NB]); // Rotate the matrix by 90 degress in order to just create move_right and the others rotate and then move_right
	void save_board(int tab[NB][NB], int old[NB][NB]);
	int move_board(WINDOW* squares[NB][NB] , int tab[NB][NB], int c); // Move the board 
	//void restore_tab(int tab[NB][NB], int old[NB][NB]);
	FILE* open_file(char* name,char* mode);
	void score2file();
	int get_lines(FILE* file);
	int* get_scores(FILE* file);
	void put_scores(int* file_scores , FILE* file);
	int* sort_scores(FILE* file);

#endif 
