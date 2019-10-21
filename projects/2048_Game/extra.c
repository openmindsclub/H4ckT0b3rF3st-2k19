#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "extra.h"
#include "math.h"

int score;
int old[NB][NB];
int old_score;

void init(WINDOW* squares[NB][NB],int tab[NB][NB]){
	int i,j;
	BOUCLE(i,j) tab[i][j] = 0;
	// Generate 2 numbers to start
	generate_number(squares,tab,1);
	generate_number(squares,tab,1);
	// Fill the table with points or numbers and bkgr colors
	print_board(squares,tab);
}

int generate_number(WINDOW* win[NB][NB] , int tab[NB][NB],int enable){
		if (isfull(tab) || !enable) return 1;
		short i , j , k=0 , x , bc = blank_columns(tab);
		short* blank = malloc(bc*sizeof(short));
		BOUCLE(i,j)  if(tab[i][j]==0) blank[k++]=i*10+j;
		x = rand()%bc;
		i = blank[x]/10;
		j = blank[x]%10;
		x = (rand()%10 + 1 <= 7) ? 2 : 4;
		// Print the number
		int digits = floor(log10(abs(x))) + 1;
		tab[i][j] = x;
		colorize(win[i][j],tab,i,j);
		mvwprintw(win[i][j], MAX_Y/NB/2 , (MAX_X/NB-digits)/2,"%d",x);
		free(blank);
		return 0;
}

int blank_columns(int tab[NB][NB]){
	int i,j,k=0;
	BOUCLE(i,j)  if (tab[i][j]==0) k++;
	return k;
}

void print_board(WINDOW* squares[NB][NB], int tab[NB][NB]){
		int i,j,digits;
		char c , *format;
		BOUCLE (i,j)  {
			digits = floor(log10(abs(tab[i][j]))) + 1;
			colorize(squares[i][j],tab,i,j);
			if (tab[i][j] == 0) mvwprintw(squares[i][j], MAX_Y/NB/2 , (MAX_X/NB )/2 ,"%c",'.');
			else 				mvwprintw(squares[i][j], MAX_Y/NB/2 , (MAX_X/NB-digits)/2 ,"%d",tab[i][j]);
		}
}

void reset_board(WINDOW* squares[NB][NB],int tab[NB][NB]){
	int i,j;
	BOUCLE(i,j) tab[i][j]=0;
	init(squares,tab);
	score = 0;
}

int isfull(int tab[NB][NB]){
	int i,j;
	BOUCLE(i,j)	if(tab[i][j] == 0) return 0;
	return 1;
}

int game_over(int tab[NB][NB]){
	if (!isfull(tab)) return 0;
	int i=0,j=0,c;
	BOUCLE(i,j) {
		c = tab[i][j];
		if ( (j>1 && c == COL_LEFT(i,j))  || (j<3  && c == COL_RIGHT(i,j) ) ||  (i>1 && c == COL_UP(i,j) )  ||  (i<3 && c == COL_DOWN(i,j) )  )  return 0;
	}
	return 1;
}

void colorize(WINDOW* win, int tab[NB][NB], int i, int j){
	int color;
	switch(tab[i][j]){
		case 0:   	GRAY_PAIR; 	color=GRAY; 		break;
		case 2:		YELLOW_PAIR;	color=YELLOW;		break;
		case 4:   	GREEN_PAIR; 	color=GREEN; 		break;
		case 8:   	ORANGE_PAIR; 	color=ORANGE; 		break;
		case 16:  	CYAN_PAIR; 	color=CYAN;  		break;
		case 32:  	MAGENTA_PAIR; 	color=MAGENTA; 		break;
		case 64:  	BROWN_PAIR; 	color=BROWN;  		break;
		case 128: 	LIGHTRED_PAIR;	color=LIGHTRED;		break;
		case 256: 	RED_PAIR; 	color=RED;		break;
		case 512: 	BLUE_PAIR; 	color=BLUE;		break;
		case 1024: 	WHITE_PAIR; 	color=WHITE;		break;
		case 2048: 	RED_PAIR; 	color=RED;		break;
		case 4096: 	PURPLE_PAIR; 	color=PURPLE;  		break;
		case 8192: 	DARKBLUE_PAIR; 	color=DARKBLUE; 	break;
		case 16384: 	PINK_PAIR; 	color=PINK;		break;
		default:  	color=rand()%16 + 1;

	}
	attron(COLOR_PAIR(color));
	wbkgd(win,COLOR_PAIR(color));
	attroff(COLOR_PAIR(color));
}

int val_in_tab(int tab[3],int v){
	int i;
	for (i=0; i < 3; i++) if (tab[i]==v) return 1;
	return 0;
}

void rotate(int tab[NB][NB]){
    int tab2[NB][NB] = {0};
    int i,j,ii=0,jj=0;
    for (j=0; j<NB; j++) {
        for (i=NB-1; i>=0; i--)	tab2[ii][jj++] = tab[i][j];
        jj=0;
        ii++;
        }
    BOUCLE(i,j) tab[i][j] = tab2[i][j];
}

int move_board(WINDOW* squares[NB][NB] , int tab[NB][NB], int c){
	int temp[NB][NB] = {0};
	save_board(tab,temp);
	int k;
	switch(c){
		case KEY_RIGHT:   k= move_right(squares,tab);	break;
		case KEY_LEFT:	  k= move_left(squares,tab);	break;
		case KEY_UP:	  k= move_up(squares,tab);		break;
		case KEY_DOWN:	  k= move_down(squares,tab);	break;
	}
	if (k==1) save_board(temp,old);
	return k;
}

int move_right(WINDOW* squares[NB][NB] , int tab[NB][NB]){
	int i,j,k=0,in=0,c,oldv=0;
	int tmp[NB][NB];
	int b[3]; // an array wich will contains postions of merged elemnts so that this element will not be merged twice
	for (i=0; i < NB; i++){
			for (in=0; in < 3; in++)  b[in]=-1;
			in=0;
			for (c=1; c < NB; c++)
				for (j=NB-1; j > 0;  j--)
					if (COL_LEFT(i,j)*tab[i][j] == 0 || (COL_LEFT(i,j) == tab[i][j] && !val_in_tab(b,j) && !val_in_tab(b,j-1) ))
					{
						if (COL_LEFT(i,j)*tab[i][j] != 0) { b[in++] = j; score += 2*tab[i][j]; }  // Save the merged position
						oldv = tab[i][j];
						tab[i][j] += COL_LEFT(i,j);
						COL_LEFT(i,j) = 0;
						if (tab[i][j] != oldv) k=1; // a move is done ,this number will be returned to know if we have to generate a new number.
					}


	}
	return k;
}

int move_up(WINDOW* squares[NB][NB] , int tab[NB][NB]){

	rotate(tab);
	int k = move_right(squares,tab);
	rotate(tab);
	rotate(tab);
	rotate(tab);

	return k;
}

int move_left(WINDOW* squares[NB][NB] , int tab[NB][NB]){
	rotate(tab);
	rotate(tab);
	int k = move_right(squares,tab);
	rotate(tab);
	rotate(tab);

	return k;
}

int move_down(WINDOW* squares[NB][NB] , int tab[NB][NB]){
	rotate(tab);
	rotate(tab);
	rotate(tab);
	int k = move_right(squares,tab);
	rotate(tab);
	return k;
}

void save_board(int tab[NB][NB], int old[NB][NB]){
	int i,j;
	BOUCLE(i,j) old[i][j] = tab[i][j];
	old_score = score;
}
