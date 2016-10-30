#include <ncurses.h>

void help() {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	attron(A_UNDERLINE); 
	attron(A_BOLD); 
	printw("HOW TO PLAY?\n");
	attroff(A_BOLD); 
	attroff(A_UNDERLINE); 
	printw("\t'./project play' to play\n\t");
	printw("Use arrow keys to navigate through the chessboard.\n\tPress enter to select a choice.\n\tPress q to quit.\n\n");
	attron(A_UNDERLINE); 
	attron(A_BOLD); 
	printw("RULES\n");
	attroff(A_BOLD); 
	attroff(A_UNDERLINE); 
	printw("\t2 player (human) chess game.\n\tTouch to play.");
	attron(A_REVERSE); 
	mvprintw(LINES - 1, 1, "Press q to quit.");
	attroff(A_REVERSE);
	refresh();
	char choice;
	int flag = 0;
	while(1) {
		choice = getch();
		switch(choice) {
			case 'q':flag = 1;
		}
		if(flag == 1)
			break;
	}
	endwin();
}
