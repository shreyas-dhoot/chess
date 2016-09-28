#include <ncurses.h>
#include <unistd.h>
void create_newwin(int, int, int, int);
int main() {
	int startx, starty, width, height, i, j, s;
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	char min = (LINES > COLS) ? 'c' : 'l';
	if (min == 'l') {
		s = LINES / 12;
	}
	else {
		s = COLS / 12;
	}
	startx = ((LINES / 2) - (4 * s));
	starty = ((COLS / 2) - (4 * s));
	for(i = 1;i <= 8; i++) {
		for(j = 1; j <= 8; j++) {
			create_newwin(s, s, starty, startx);
			startx = startx + s;
		}
		starty = starty + s;
		startx = ((LINES / 2) - (4 * s));
	}
	refresh();
//	min = getch();
	endwin();
	return 0;
}

void create_newwin(int height, int width, int starty, int startx) {
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/
}
