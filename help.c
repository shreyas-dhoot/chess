#include <ncurses.h>

void help() {
	initscr();
	//start_color();
	//use_default_colors();
	//init_pair(5, -1, -1);
	//init_pair(6, COLOR_BLACK, COLOR_RED);
//	wbkgd(stdscr, 5);
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
	printw("\t2 player (human) chess game.\n\tTouch to play (NO UNDO).\n\n");

	attron(A_UNDERLINE); 
	attron(A_BOLD);
	printw("WHAT IT MEANS?\n");
	attroff(A_BOLD); 
	attroff(A_UNDERLINE);
	printw("\thighlighted green - legal move\n");
	printw("\thighlighted blue - current cursor position\n");
	printw("\twr1 / wr2 - White rook\n");
	printw("\twn1 / wn2 - White knight\n");
	printw("\twb1 / wb2 - White bishop\n");
	printw("\twq - White queen\n");
	printw("\twk - White king\n");
	printw("\twp1 / wp2 / wp3 / wp4 / wp5 / wp6 / wp7 / wp8- White pawn\n");
	printw("\tbr1 / br2 - Black rook\n");
	printw("\tbn1 / bn2 - Black knight\n");
	printw("\tbb1 / bb2 - Black bishop\n");
	printw("\tbq - Black queen\n");
	printw("\tbk - Black king\n");
	printw("\tbp1 / bp2 / bp3 / bp4 / bp5 / bp6 / bp7 / bp8- Black pawn\n");
	
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
