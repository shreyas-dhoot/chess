#include <ncurses.h>
#include <unistd.h>
WINDOW *create_newwin(int, int, int, int, int, int, int);
int main() {
	WINDOW *win, *win1;
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
			win = create_newwin(s, s, starty, startx, col, i, j);
			startx = startx + (2 * s) - 1;	// -1 to overlap squares.
//			usleep(2000000);
		}
		starty = starty + s - 1;		// -1 to overlap square.
		startx = ((COLS / 2) - (8 * s));
	}
	win = newwin((s), (s * 16), starty, startx);	//To remove black background of the last squares (bottom), created a white window.
	win1 = newwin(s * 8, s, ((LINES / 2) - (4 * s)), ((COLS/2) + (8 * s) - 8));// "" (top)
//	box(win1, 0, 0);
	wbkgd(win, COLOR_PAIR(1));
	wbkgd(win1, COLOR_PAIR(1));
	wrefresh(win);
	wrefresh(win1);
/*	for(i = 0;i <= (8 * ((2 * s) - 1) - 1);i++){
	//	if(((8 * ((2 * s) - 1) - 1) / 8) 
		mvaddch(((LINES / 2) - (4 * s) + i), ((COLS/2) + (8 * s) - 8), '|');
		mvaddch(starty, startx + i, ACS_S1);
	}*/
	
//	mvaddch(((LINES / 2) - (4 * s) + 4), ((COLS/2) - (8 * s)), ACS_ULCORNER);
//	mvaddch(((LINES / 2) - (4 * s) + 4), ((COLS/2) + (8 * s) -8), ACS_URCORNER);
	mvgetch(LINES/2, COLS/2);
	refresh();
	endwin();
	return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx, int i, int j, int k) {//j represents row no.
	WINDOW *local_win;
	local_win = newwin(width , (2 *  width) , starty, startx);
//	box(local_win, 0, 0);		
					/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	int x1, y1, x2, y2;
	getbegyx(local_win, y1, x1);
	getmaxyx(local_win, y2, x2);
//	usleep(2000000);
	if(i == 0) {
		wbkgd(local_win, COLOR_PAIR(1));
		wrefresh(local_win);		/* Show that box 		*/
/*		if(j == 1) {
			for(i = 0; i <= width + 3; i++) 
			mvaddch(y1, (x1 + i), ACS_S1);
			refresh();
		//	mvaddch(y1, (x1 + 1), ACS_S1);
		//	mvaddch(y1, (x1 + 2), ACS_S1);
		//	mvaddch(y1, (x1 + 3), ACS_S1);
		//	mvaddch(y1, (x1 + 4), ACS_S1);
		//	mvaddch(y1, (x1 + 5), ACS_S1);
		//	mvaddch(y1, (x1 + 6), ACS_S1);
		//	refresh();
		}
		if(k == 1) {
			for(i = 0; i<= height + 1; i++)
				mvaddch(y1 + i, x1, ACS_VLINE);
				refresh();
		}
		if(k == 8) {
			for(i = 0; i<= height + 1; i++)
				mvaddch(y1 + i, x1 + width + 3, ACS_VLINE);
				refresh();
		}*/
	}
	else {
		wbkgd(local_win, COLOR_PAIR(2));
		wrefresh(local_win);		/* Show that box 		*/
	}
		return local_win;
}
