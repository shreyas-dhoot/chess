#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
WINDOW *create_newwin(int, int, int, int, int, int, int);
int main() {
	WINDOW *win, *win1;
	WINDOW ***pp[8];
	int startx, starty, i, j, s, col;
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
	starty = ((LINES / 2) - (4 * s)) + 4;	//because of vertical rectangle
	for(i = 1;i <= 8; i++) {
		for(j = 1; j <= 8; j++) {
			if(((i % 2 == 1) && (j % 2 == 1)) || ((i % 2 == 0) && (j % 2 == 0)))	//white color
				col = 1;
			else									//black color
				col = 0;
			for(i = 0;i < 8;i++) {
				pp[i] = (WINDOW ***)malloc(sizeof(WINDOW **) * 8);
				for(j = 0;j < 8;j++) {
					pp[i][j] = (WINDOW **)create_newwin(s, s, starty, startx, col, i, j);
				}
			}	
			startx = startx + (2 * s) - 1;	// -1 to overlap squares.
//			usleep(2000000);
		}
		starty = starty + s - 1;		// -1 to overlap square.
		startx = ((COLS / 2) - (8 * s));
	}
	win = newwin((s), (s * 16), starty, startx);	//To remove black background of the last squares (bottom), created a white window.
	win1 = newwin(s * 8, s, ((LINES / 2) - (4 * s)), ((COLS/2) + (8 * s) - 8));// "" (top)
	wbkgd(win, COLOR_PAIR(1));
	wbkgd(win1, COLOR_PAIR(1));
	wrefresh(win);
	wrefresh(win1);
	mvgetch(LINES/2, COLS/2);
	refresh();
	endwin();
	return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx, int i, int j, int k) {//j represents row no.
	WINDOW *local_win;
	local_win = newwin(width , (2 *  width) , starty, startx);
	int x1, y1, x2, y2;
	getbegyx(local_win, y1, x1);
	getmaxyx(local_win, y2, x2);
//	usleep(2000000);
	if(i == 0) {
		wbkgd(local_win, COLOR_PAIR(1));
		wrefresh(local_win);		/* Show that box 		*/
	}
	else {
		wbkgd(local_win, COLOR_PAIR(2));
		wrefresh(local_win);		/* Show that box 		*/
	}
		return local_win;
}
