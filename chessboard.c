#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include "chess_declaration.h"
WINDOW *create_newwin(int, int, int, int, int, int, int);
input *inputfn(WINDOW *, int, int, input *);
int main() {
//	char ***pp;
	initpos();
//	initpiece();
	input *ip;
	WINDOW **window[8];
	WINDOW *win, *win1, *win_input;
	int startx, starty, i, j, s, col, inputstart_x = 0, inputstart_y = 0;
	for(i = 0; i < 8; i++) {
		window[i] = (WINDOW **)malloc(sizeof(WINDOW *) * 8);
	}
	initscr();
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	wbkgd(stdscr, COLOR_PAIR(1));
	refresh();
	char min = ((2 * LINES) > COLS) ? 'c' : 'l';
	if (min == 'l') {	//deciding the width and height of the square of chessboard
		s = LINES / 8;  
	}
	else {
		s = COLS / 8;	
	}
	startx = ((COLS / 2) - (8 * s));	//width = 2 * height
	starty = ((LINES / 2) - (4 * s) + 4);	//because of horizontal rectangle
	for(i = 1;i <= 8; i++) {
		for(j = 1; j <= 8; j++) {
			if(((i % 2 == 1) && (j % 2 == 1)) || ((i % 2 == 0) && (j % 2 == 0)))	//white color
				col = 1;
			else									//black color
				col = 0;
			window[i - 1][j - 1] = create_newwin(s, s, starty, startx, col, i, j);
			mvwprintw(window[i -1][j - 1], ((s / 2) - 1), (s - 2), "%s", pp[i -1][j - 1]);
			wrefresh(window[i - 1][j - 1]);
			startx = startx + (2 * s) - 1;	// -1 to overlap squares.
//			usleep(2000000);
		}
		starty = starty + s - 1;		// -1 to overlap square.
		startx = ((COLS / 2) - (8 * s));
	}
	win = newwin((s / 2), (s * 16), starty, startx);//To remove black background of the last squares (bottom), created a white window.
	win1 = newwin((s - 1) * 8, s, ((LINES / 2) - (4 * s) + 4), ((COLS/2) + (8 * (s - 1))));// "" (side)
	inputstart_y = ((LINES / 2) - (2 * s) + 4);
	inputstart_x = ((COLS/2) + (8 * (s - 1)) + s);
	win_input = newwin(s * 3, s * 6, inputstart_y, inputstart_x);
	wbkgd(win, COLOR_PAIR(1));
	wbkgd(win1, COLOR_PAIR(1));
	wbkgd(win_input, COLOR_PAIR(1));
	wrefresh(win);
	wrefresh(win1);
	wrefresh(win_input);
	ip -> player = 1;
	//Before taking input check for resizing of the window.
	ip = inputfn(win_input, inputstart_y, inputstart_x, ip);
	mvgetch(LINES/2, COLS/2);
	refresh();
	endwin();
	return 0;
}

input *inputfn(WINDOW *inputwin, int inputstart_y, int inputstart_x, input *ip) {
	int inputmax_x, inputmax_y;
	getbegyx(inputwin, inputstart_y, inputstart_x);
	getmaxyx(inputwin, inputmax_y, inputmax_x);
	mvwprintw(inputwin, (inputmax_y) / 3, 1, "Player %d's turn\n ", ip -> player);
	wprintw(inputwin, "Enter piece to be moved \n > ");
	wrefresh(inputwin);
	char ch = getch();
	wrefresh(inputwin);
	return ip;
}

WINDOW *create_newwin(int height, int width, int starty, int startx, int col, int j, int k) {//j represents row no.
	WINDOW *local_win;
	local_win = newwin(width , (2 *  width) , starty, startx);
	int x1, y1, x2, y2;
	getbegyx(local_win, y1, x1);
	getmaxyx(local_win, y2, x2);
//	usleep(2000000);
	if(col == 0) {
		wbkgd(local_win, COLOR_PAIR(1));
		wrefresh(local_win);		/* Show that box 		*/
	}
	else {
		wbkgd(local_win, COLOR_PAIR(2));
		wrefresh(local_win);		/* Show that box 		*/
	}
	return local_win;
}
