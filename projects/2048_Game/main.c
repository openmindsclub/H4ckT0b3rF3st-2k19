#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "extra.h"
#include <math.h>

#define REFRESH() 	refresh();wrefresh(main); BOUCLE(i,j)  wrefresh(squares[i][j]); wrefresh(score_box); wrefresh(hscore_box);
#define CLEAR()		clear();  wclear(main);	  BOUCLE(i,j)  wclear(squares[i][j]); wclear(score_box); wrefresh(hscore_box);

int main(){
	initscr();
	start_color();
	noecho();
	curs_set(FALSE);
	use_default_colors();
	keypad(stdscr,TRUE);
	srand(time(NULL));

	int i=0 , j=0, c , is_moved=0 , digs=0;
	int tab[NB][NB] = {0};
	char key;

	// Creating main WIndow and the Squares as sub-windows
	WINDOW* main = newwin(MAX_Y	+2, MAX_X +2, 0 , 0);
	WINDOW* score_box = newwin(3,MAX_X/2 + 1,MAX_Y+2,0);
	WINDOW* hscore_box = newwin(3,MAX_X/2+1,MAX_Y+2,MAX_X/2+1);
	WINDOW* squares[NB][NB];
	BOUCLE(i,j)   squares[i][j] = subwin(main,SQ_Y,SQ_X,i*(SQ_Y)+1,j*(SQ_X)+1);

	// Initilaize the tab with 2 random numbers
	init(squares,tab);
	do{

			// Check if the game is over
			if (game_over(tab)) {
				mvprintw(MAX_Y + 7,6," GAME IS OVER , Press 'q' to quit or 'r' to Restart \n");
				REFRESH();
				while (c != 'q' && c != 'r') c=getch();
				if (c=='q')
				  break;
				else
				  reset_board(squares,tab);
			}
			//clear everything;
			CLEAR();
			switch (c){
				case 'r':			reset_board(squares,tab);			break;
				// add UNDO here
				case KEY_RIGHT:			is_moved = move_board(squares,tab,c); 		break;
				case KEY_LEFT:			is_moved = move_board(squares,tab,c);		break;
				case KEY_UP:			is_moved = move_board(squares,tab,c);		break;
				case KEY_DOWN:			is_moved = move_board(squares,tab,c);		break;
				default: 			is_moved=0;
			}

			// Drawing the border and the squares and boxes and refresh everything
			box(main,ACS_VLINE,ACS_HLINE);
			box(score_box,ACS_VLINE,ACS_HLINE);
			box(hscore_box,ACS_VLINE,ACS_HLINE);
			mvwprintw(score_box,0,MAX_X/NB - 2,"Score");
			mvwprintw(hscore_box,0,3,"High-Score");
			mvwprintw(score_box,1,MAX_X/NB - digs/2,"%d",score);
			print_board(squares,tab);

			REFRESH();

			// Wait some milliseconds then generate a new number if a move is done , then print the board and refresh again
			usleep(DELAY);
			if (is_moved)  generate_number(squares,tab,is_moved);
			print_board(squares,tab);
			REFRESH();

	} while ((c=getch()) != 'q');

	delwin(main);
	BOUCLE(i,j)  delwin(squares[i][j]);
	endwin();

}
