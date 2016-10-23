#include <ncurses.h>
#include <panel.h>
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
void highlight_moves(input *, WINDOW ***, PANEL *[]);
void unhighlight_moves(input *, WINDOW ***, PANEL *[]);
void move_piece(input *, WINDOW ***, int, PANEL *[]);
int main() {
//	char ***pp;
	initpos();				//initialise starting position
	init_chess_piece();
	initpiece();				//Initializing all the attributes of the pieces.
	input *ip;
	ip = (input *)malloc(sizeof(input));
	WINDOW **window[8];
	WINDOW *win, *win1, *win_input;
	int startx, starty, i, j, s, col, inputstart_x = 0, inputstart_y = 0, ifcheck;
	for(i = 0; i < 8; i++) {
		window[i] = (WINDOW **)malloc(sizeof(WINDOW *) * 8);
	}
	PANEL *panel[67];
	PANEL *temp;
	temp = NULL;
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
			window[i - 1][j - 1] = create_newwin(s, s, starty, startx, col, i, j);
			panel[((i - 1) * 8) + (j - 1)] = new_panel(window[i - 1][j - 1]);
			if(i != 1 && j != 1) {
				set_panel_userptr(temp, panel[((i - 1) * 8) + (j - 1)]);
			}
			temp = panel[((i - 1) * 8) + (j - 1)];
			mvwprintw(window[i -1][j - 1], ((s / 2) - 1), (s - 2), "%s", pp[i -1][j - 1]);
			wrefresh(window[i - 1][j - 1]);
			startx = startx + (2 * s) - 1;	// -1 to overlap squares.
//			usleep(2000000);
		}
		starty = starty + s - 1;		// -1 to overlap square.
		startx = ((COLS / 2) - (8 * s));
	}
	win = newwin((s / 2), (s * 16), starty, startx);//To remove black background of the last squares (bottom), created a white window.
	panel[64] = new_panel(win);
	set_panel_userptr(temp, panel[64]);
	temp = panel[64];
	win1 = newwin((s - 1) * 8, s, ((LINES / 2) - (4 * s) + 4), ((COLS/2) + (8 * (s - 1))));// "" (side)
	panel[65] = new_panel(win1);
	set_panel_userptr(temp, panel[65]);
	temp = panel[65];
	inputstart_y = ((LINES / 2) - (2 * s) + 4);
	inputstart_x = ((COLS/2) + (8 * (s - 1)) + s);
	win_input = newwin(s * 3, s * 6, inputstart_y, inputstart_x);
	panel[66] = new_panel(win_input);
	set_panel_userptr(temp, panel[66]);
	temp = panel[66];
	wbkgd(win, COLOR_PAIR(1));
	wbkgd(win1, COLOR_PAIR(1));
	wbkgd(win_input, COLOR_PAIR(2));
	wrefresh(win);
	wrefresh(win1);
	wrefresh(win_input);
	ip -> player = 1;
	while(1) {
		//Before taking input check for resizing of the window.
	//	print_chess_piece();
		ip = input_piece(win_input, inputstart_y, inputstart_x, ip);
		
		highlight_moves(ip, window, panel);
		i = 0;
		move(1,0);
		clrtoeol();
		printw(" In chessboard :- ");
		while((ip -> fm)[i][1] != -1) {
			if(ip -> fm[i][1] == -2) {
				i++;
				continue;
			}
			printw("(%d, %d) ", ip -> fm[i][0], ip -> fm[i][1]);
			i++;
		}
		refresh();
		input_move(win_input, ip);
		unhighlight_moves(ip, window, panel);
		move_piece(ip, window, s, panel);
		i = initialise_future_move(ip);
		if(i == 0)
			printw("There is something wrong in initializing fm.");
		if(ip -> player == 1)
			ip -> player = 0;
		else
			ip -> player = 1;
		ifcheck = check(ip, pp);
		move(5,1);
		clrtoeol();
		if(ifcheck) {
			if(ip -> player == 1)
				printw("Black Check");
			else
				printw("white Check");
		}
		refresh();
	}
	mvgetch(LINES/2, COLS/2);
//	refresh();
	getch();
	endwin();
	return 0;
}

input *input_piece(WINDOW *inputwin, int inputstart_y, int inputstart_x, input *ip) {
	int inputmax_x, inputmax_y;
	getbegyx(inputwin, inputstart_y, inputstart_x);
	getmaxyx(inputwin, inputmax_y, inputmax_x);
	wmove(inputwin, 0 , 0);
	wclrtoeol(inputwin);
	if(ip -> player == 1)
		mvwprintw(inputwin, (inputmax_y) / 8, 2,  "White's turn \n ", ip -> player);
	else
		mvwprintw(inputwin, (inputmax_y) / 8, 2, "Black's turn \n ", ip -> player);
	mvwprintw(inputwin,(inputmax_y / 4) + 1, 1, "Enter piece to be moved\n > ");
	wrefresh(inputwin);
	wclrtoeol(inputwin);
	wgetstr(inputwin, ip -> piece);
	int flag_piece;
	int flag_move;
	int i;
	while(1) {
		flag_piece = check_chess_piece(ip -> player, ip -> piece);
		if(flag_piece != -1) {
			ip -> enum_piece = flag_piece;
			char a[3];
			if(ip -> player == 1) {
				strcpy(a, "w");
				strcat(a, ip -> piece);
			}
			else {
				strcpy(a, "b");
				strcat(a, ip -> piece);
			}
			strcpy(ip -> piece, a);
			ip = find_present_cordinates(ip);
			if(ip -> px == -1 || ip -> py == -1) {
				printw("There is something wrong in the program");
				getch();
				endwin();
				exit(1);
			}
			i = generate_future_move(ip);
			check_before_turn(ip, pp, 1);
			if(i == 0) {
				printw("There is something wrong in generate future move.");
				getch();
				endwin();
				exit(1);
			}
			flag_move = check_chess_ifmove(ip);
			if(flag_move == 0) {
				wmove(inputwin, (inputmax_y / 4), 0);
				wclrtoeol(inputwin);
				wprintw(inputwin, "No move available!!\n ");
				wclrtoeol(inputwin);
				wprintw(inputwin, "Enter piece to be moved \n > ");
				wrefresh(inputwin);
				wclrtoeol(inputwin);
				wgetstr(inputwin, ip -> piece);
			}
			else {
				ip -> enum_piece = flag_piece;
				break;
			}
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
	return ip;
}

void input_move(WINDOW *inputwin, input *ip) {
	int x, y;
	getyx(inputwin, y,x);
	wprintw(inputwin, "\nEnter move\n > ");
	wrefresh(inputwin);
	wclrtoeol(inputwin);
	wgetstr(inputwin, ip -> move);
	int flag = 0;
	
	while(1) {
		flag = check_chess_move(ip);
		if(flag == 1) {
			break;
		}
		else if(flag == -1) {
			wprintw(inputwin, "No move available!");
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
			wgetstr(inputwin, ip -> move);
		}
	}
	wrefresh(inputwin);
}

void move_piece(input *ip, WINDOW ***win, int s, PANEL *high_panel[67]) {
	int movex = (ip -> move[0]) - '0';
	int movey = (ip -> move[1]) - '0';
	int k;
	PANEL *top;
	pp[ip -> px][ip -> py][0] = '\0';
	if(pp[movex][movey][0] != '\0') {
		char temp_piece[4];
		strcpy(temp_piece, pp[movex][movey]);
		if((temp_piece[0] == 'w' && ip -> player == 1) || (temp_piece[0] == 'b' && ip -> player != 1)) {
			printw("There is something wrong in the program (move_piece)");
		}
		else {
			temp_piece[0] = temp_piece[1];
			if(temp_piece[2] == '\0')
				temp_piece[1] = '\0';
			else{
				temp_piece[1] = temp_piece[2];
				temp_piece[2] = '\0';
			}
		}
		refresh();
		int i;
		if(ip -> player == 1)
			i = check_chess_piece(0, temp_piece);
		else
			i = check_chess_piece(1, temp_piece);
		chess_piece[i][0] = '\0';
	}
	strcpy(pp[movex][movey], ip -> piece);
	wmove(win[ip -> px][ ip -> py], ((s / 2) - 1), (s - 2));
	wclrtoeol(win[ip -> px][ip -> py]);
	wprintw(win[ip -> px][ip -> py], "%s", pp[ip -> px][ip -> py]);
	wrefresh(win[ip -> px][ip -> py]);
	k = (ip -> px) * 8 + ip -> py;
	while(k != 67) {
		top = high_panel[k];
		top = (PANEL *)panel_userptr(top);
		top_panel(top);
		k++;
	}
	update_panels();
	doupdate();
	wmove(win[movex][movey], ((s / 2) - 1), (s - 2));
	wclrtoeol(win[movex][movey]);
	wprintw(win[movex][movey], "%s", pp[movex][movey]);
	wrefresh(win[movex][movey]);
	k = (movex) * 8 + movey;
	while(k != 67) {
		top = high_panel[k];
		top = (PANEL *)panel_userptr(top);
		top_panel(top);
		k++;
	}
	update_panels();
	doupdate();
}

void highlight_moves(input *ip, WINDOW ***win, PANEL *high_panel[67]) {
	int i = 0;
	int x, y;
	init_pair(3, COLOR_BLUE, COLOR_RED);
	PANEL *top;
	int k;
	while((ip -> fm)[i][1] != -1) {
		if(ip -> fm[i][1] == -2) {
			i++;
			continue;
		}
		x = (ip -> fm)[i][0];
		y = (ip -> fm)[i][1];
		wbkgd(win[x][y], COLOR_PAIR(3));
		wrefresh(win[x][y]);
		k = (x * 8) + y + 1;
		while(k != 67) {
			top = high_panel[k];
			top = (PANEL *)panel_userptr(top);
			top_panel(top);
			k++;
		}
		update_panels();
		doupdate();
		i++;
	}
	
}

void unhighlight_moves(input *ip, WINDOW ***win, PANEL *high_panel[67]) {
	int x, y, k, i = 0;
	PANEL *top;
	while((ip -> fm)[i][1] != -1) {
		if(ip -> fm[i][1] == -2) {
			i++;
			continue;
		}
		x = (ip -> fm)[i][0];
		y = (ip -> fm)[i][1];
		if(((x % 2 == 1) && (y % 2 == 1)) || ((x % 2 == 0) && (y % 2 == 0))) {	//white color
			wbkgd(win[x][y], COLOR_PAIR(2));
		}
		else {									//black color
			wbkgd(win[x][y], COLOR_PAIR(1));
		}
		k = (x * 8) + y + 1;
		while(k != 67) {
			top = high_panel[k];
			top = (PANEL *)panel_userptr(top);
			top_panel(top);
			k++;
		}
		update_panels();
		doupdate();
		wrefresh(win[x][y]);
		i++;
	}
}



WINDOW *create_newwin(int height, int width, int starty, int startx, int col, int j, int k) {//j represents row no.
	WINDOW *local_win;
	local_win = newwin(width , (2 *  width) , starty, startx);
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
