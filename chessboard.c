#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "chess_declaration.h"
#include "functions_chess.h"
#include "initialise.h"
WINDOW *create_newwin(int, int, int, int, int, int, int);
input *input_piece(WINDOW *, int, int, input *);
void input_move(WINDOW *, input *);
input *find_present_cordinates(input *);

int main() {
//	char ***pp;
	initpos();				//initialise starting position
	init_chess_piece();
	initpiece();				//Initializing all the attributes of the pieces.
	input *ip;
	ip = (input *)malloc(sizeof(input));
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
//	noecho();
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
	wbkgd(win_input, COLOR_PAIR(2));
	wrefresh(win);
	wrefresh(win1);
	wrefresh(win_input);
	ip -> player = 1;
	char a[3];
	//Before taking input check for resizing of the window.
	ip = input_piece(win_input, inputstart_y, inputstart_x, ip);
	if(ip -> player == 1) {
		strcpy(a, "w");
		strcat(a, ip -> piece);
	}
	else {
		strcpy(a, "b");
		strcat(a, ip -> piece);
	}
	strcpy(ip -> piece, a);
	wprintw(win_input,"%s", ip -> piece);
	wrefresh(win_input);

	getch();
	ip = find_present_cordinates(ip);
	if(ip -> px == -1 || ip -> py == -1) {
		printw("There is something wrong in the program");
		getch();
		endwin();
		return 0;
	}
	printw("%d%d", ip -> px, ip -> py);
	getch();
	//store future move in a int **fm
	//highlight all the future moves
	i = generate_future_move(ip);
	if(i == 0) {
		printw("There is something wrong in generate future move.");
		getch();
		endwin();
		return 0;
	}
//	highlight_moves(ip, window);
	i = 0;
/*	while((ip -> fm)[0][i] != -1) {
		printw("\nIn chessboard (%d, %d) ", ip -> fm[0][i], ip -> fm[1][i]);
		i++;
	}*/
	refresh();
	getch();
	input_move(win_input, ip);
	mvgetch(LINES/2, COLS/2);
//	refresh();
	getch();
	endwin();
	return 0;
}

void highlight_moves(input *ip, WINDOW ***win) {
	int i = 0;
	int x, y;
	init_pair(3, COLOR_BLUE, COLOR_RED);
	while((ip -> fm)[i][0] != -1) {
		x = (ip -> fm)[i][0];
		y = (ip -> fm)[i][1];
		wbkgd(win[x][y], COLOR_PAIR(3));
		i++;
	}
}

input *input_piece(WINDOW *inputwin, int inputstart_y, int inputstart_x, input *ip) {
	int inputmax_x, inputmax_y;
	getbegyx(inputwin, inputstart_y, inputstart_x);
	getmaxyx(inputwin, inputmax_y, inputmax_x);
	mvwprintw(inputwin, (inputmax_y) / 4, 1, "Player %d's turn\n ", ip -> player);
	wprintw(inputwin, "Enter piece to be moved\n > ");
	wrefresh(inputwin);
	wgetstr(inputwin, ip -> piece);
	int flag;
	int i;
	while(1) {
		flag = check_chess_piece(ip -> player, ip -> piece);
		if(flag != -1) {
			ip -> enum_piece = flag;
			break;
		}
		else {
			wmove(inputwin, (inputmax_y / 4), 0);
			wclrtoeol(inputwin);
			wprintw(inputwin, " Invalid piece!!\n ");
			wclrtoeol(inputwin);
			wprintw(inputwin, "Enter piece to be moved \n > ");
			wrefresh(inputwin);
			wclrtoeol(inputwin);
			wgetstr(inputwin, ip -> piece);
		}
	}
	for(i = 0; ip -> piece[i] != '\0'; i++){
    		ip -> piece[i] = tolower(ip -> piece[i]);
	}	
	wprintw(inputwin, "Input Successful!!\n ");
	wrefresh(inputwin);
	return ip;
}

void input_move(WINDOW *inputwin, input *ip) {
	int x, y;
	getyx(inputwin, y,x);
	wprintw(inputwin, "\nEnter move\n > ");
	wrefresh(inputwin);
	wgetstr(inputwin, ip -> move);
	int flag = 0;
	
	while(1) {
		flag = check_chess_move(ip);
		if(flag) {
			//chess piece will be moved
			break;
		}
		else {
			wmove(inputwin, y,x);
			wclrtoeol(inputwin);
			wprintw(inputwin, "\nInvalid move!!\n ");
			wclrtoeol(inputwin);
			wprintw(inputwin, "Enter move\n > ");
			wrefresh(inputwin);
			wclrtoeol(inputwin);
			wgetstr(inputwin, ip -> piece);
		}
	}
	wprintw(inputwin,"Valid Chess move\n");
	wrefresh(inputwin);
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

input *find_present_cordinates(input *ip) {
	int i, j;
	printw("%s", ip -> piece);
	getch();
	for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j++) {
			if(strcmp(pp[i][j], ip -> piece) == 0) {
				ip -> px = i;
				ip -> py = j;
				return ip;
			}
		}
	}
	ip -> px = -1;
	ip -> py = -1;
	return ip;
}
