/*			Copyright 2016 Shreyas Dhoot
	This file is part of Chess 2.0.
	Chess 2.0 is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Chess 2.0 is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Chess 2.0.  If not, see <http://www.gnu.org/licenses/>. */
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
input *second_type_input(input *, WINDOW ***, PANEL **, WINDOW *, int *, int *);
void highlight_window(WINDOW ***, PANEL **, int, int, int, input *);
input *second_type_input_move(input *, WINDOW ***, PANEL **, WINDOW *, int *, int *);
void help();
int main(int argc, char *argv[]) {
	
	if(argc < 2 || argc > 2) {				//Implementing --help option
		printf("You must specify 'play'. \nTry './project --help' for more information.\n");	
		endwin();
		return 0;
	}
	else {
		if(strcmp(argv[1], "--help") == 0) {
			help();
			endwin();
			return 0;
		}
		else if (strcmp(argv[1], "play") == 0) {
		}
		else {
			printf("You must specify 'play'. \nTry './project --help' for more information.\n");
			endwin();
			return 0;
		}
	}
	
//	char ***pp;
	initpos();				//initialise starting position
	init_chess_piece();			//inittialising enum of chess pieces
	initpiece();				//Initializing all the attributes of the pieces.
	input *ip;				//stores all info about input
	ip = (input *)malloc(sizeof(input));
	int a[1][2];
	a[0][0] = -1;
	a[0][1] = -1;
	ip -> fm = a;				//initialise fm of ip
	WINDOW **window[8];			//stores 64 windows (chess board)
	WINDOW *win, *win1, *win_input;		//input window
	int startx, starty, i, j, s, col, inputstart_x = 0, inputstart_y = 0, ifcheck, ifcheckmate, prevx = 0, prevy = 0;	//prevx and prey is to store present cursor coordinates
	for(i = 0; i < 8; i++) {
		window[i] = (WINDOW **)malloc(sizeof(WINDOW *) * 8);
	}
	PANEL *panel[67];			//panel of 64 window (chess board) + input window
	PANEL *temp;
	temp = NULL;
	initscr();
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	wbkgd(stdscr, COLOR_PAIR(1));
	refresh();
	char min = ((2 * LINES) > COLS) ? 'c' : 'l';
	if (min == 'l') {			//deciding the width and height of the square of chessboard
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
			if(i != 1 && j != 1) {							//integrating panel with windows
				set_panel_userptr(temp, panel[((i - 1) * 8) + (j - 1)]);
			}
			temp = panel[((i - 1) * 8) + (j - 1)];
			mvwprintw(window[i -1][j - 1], ((s / 2) - 1), (s - 2), "%s", pp[i -1][j - 1]);
			wrefresh(window[i - 1][j - 1]);
			startx = startx + (2 * s) - 1;			// -1 to overlap squares.
		}
		starty = starty + s - 1;				// -1 to overlap square.
		startx = ((COLS / 2) - (8 * s));
	}
	attron(A_BOLD);
	mvprintw(LINES - 1, COLS / 3,"Press h for help");
	mvprintw(LINES - 1, (2 * COLS) / 3,"Press q to quit");
	attroff(A_BOLD);
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
	wbkgd(win_input, COLOR_PAIR(1));
	wrefresh(win);
	wrefresh(win1);
	wrefresh(win_input);
	ip -> player = 1;
	while(1) {
	//	print_chess_piece();				//print enum of chess pieces
		ip = second_type_input(ip, window, panel, win_input, &prevx, &prevy);
		if(ip == NULL) {
			break;
		}
//		ip = input_piece(win_input, inputstart_y, inputstart_x, ip);	//second way for input of piece (by words)
		
		highlight_moves(ip, window, panel);
		i = 0;
		move(1,0);
		clrtoeol();
		ip = second_type_input_move(ip, window, panel, win_input, &prevx, &prevy);
		if(ip == NULL) {
			break;
		}
//		input_move(win_input, ip);					//second way for input of move (by cordinates)
		unhighlight_moves(ip, window, panel);				//unhighlight cursor position
		move_piece(ip, window, s, panel);				//move piece
		i = initialise_future_move(ip);
		if(i == 0)
			printw("There is something wrong in initializing fm.");
		if(ip -> player == 1)						//change turn
			ip -> player = 0;
		else
			ip -> player = 1;
		ifcheck = check(ip, pp);
		ifcheckmate = checkmate(ifcheck, ip);
		if(ifcheckmate == 1 && ip -> player == 1) {
			wmove(win_input, 5,0);
			wclrtoeol(win_input);
			wmove(win_input, 4,0);
			wclrtoeol(win_input);
			wprintw(win_input, "White Checkmate \n");
			wprintw(win_input, "Player 2 wins");
			wrefresh(win_input);
			attron(A_REVERSE); 
			mvprintw(LINES - 1, 1, "Press q to quit.");
			attroff(A_REVERSE);
			refresh();
			char choice;
			int flag = 0;
			while(1) {
				choice = getch();
				switch(choice) {
					case 'q':case 'Q':flag = 1;
				}
				if(flag == 1)
					break;
			}
			break;
		}
		else if(ifcheckmate == 1 && ip -> player == 0) {
			wmove(win_input, 5,0);
			wclrtoeol(win_input);
			wmove(win_input, 4,0);
			wclrtoeol(win_input);
			wprintw(win_input, "Black Checkmate \n");
			wprintw(win_input, "Player 1 wins");
			wrefresh(win_input);
			attron(A_REVERSE); 
			mvprintw(LINES - 1, 1, "Press q to quit.");
			attroff(A_REVERSE);
			refresh();
			char choice;
			int flag = 0;
			while(1) {
				choice = getch();
				switch(choice) {
					case 'q':case 'Q':flag = 1;
				}
				if(flag == 1)
					break;
			}
			break;
		}
		werase(win_input);
		move(5,1);
		clrtoeol();
		if(ifcheck) {
			if(ip -> player == 1) {
				wmove(win_input, 5,0);
				wclrtoeol(win_input);
				wmove(win_input, 4,0);
				wclrtoeol(win_input);
				wprintw(win_input, "White Check");
				wrefresh(win_input);
			}
			else {
				wmove(win_input, 5,0);
				wclrtoeol(win_input);
				wmove(win_input, 4,0);
				wclrtoeol(win_input);
				wprintw(win_input, "Black Check");
				wrefresh(win_input);
			}
		}
		refresh();
	}
	for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j++) {
			free(pp[i][j]);
		}
		free(pp[i]);
	}
	endwin();
	return 0;
}

void highlight_window(WINDOW ***win, PANEL **high_panel, int x, int y, int ifhlt, input *ip) {	//ifhlt flag to highlight or unhighlight
	PANEL *top;
	int k, flag = 1, i = 0;
	if(ifhlt) {
		wbkgd(win[x][y], COLOR_PAIR(4));
	}
	else {
		while((ip -> fm)[i][1] != -1) {
			if(x == ip -> fm[i][0] && y == ip -> fm[i][1]) {
				flag = 0;
				break;
			}
			i++;
		}
		if(flag) {
			if(((x % 2 == 1) && (y % 2 == 1)) || ((x % 2 == 0) && (y % 2 == 0))) {	//white color
				wbkgd(win[x][y], COLOR_PAIR(2));
			}
			else {									//black color
				wbkgd(win[x][y], COLOR_PAIR(1));
			}
		}
		else {
			wbkgd(win[x][y], COLOR_PAIR(3));
		}
	}
	wrefresh(win[x][y]);
	if(flag) {
		k = (x * 8) + y + 1;
		while(k != 67) {
			top = high_panel[k];
			top = (PANEL *)panel_userptr(top);
			top_panel(top);
			k++;
		}
		update_panels();
		doupdate();
	}
}

input *second_type_input(input *ip, WINDOW ***win, PANEL **high_panel, WINDOW *inputwin, int *prevx, int *prevy) {
	int x = *prevx, y = *prevy, i;
	init_pair(4, COLOR_RED, COLOR_BLUE);
	int flag = 0, c, inputmax_x, inputmax_y;
	char choice;
	getmaxyx(inputwin, inputmax_y, inputmax_x);
	wmove(inputwin, 0 , 0);
	wclrtoeol(inputwin);
	wattron(inputwin, A_BOLD);
	wattron(inputwin, A_UNDERLINE);
	if(ip -> player == 1) {
		mvwprintw(inputwin, 0, 2,  "White's turn\n");
		wattroff(inputwin, A_BOLD); 
		wattroff(inputwin, A_UNDERLINE);
		wprintw(inputwin, "\nSelect piece");
	}
	else {
		mvwprintw(inputwin, 0, 2, "Black's turn\n");
		wattroff(inputwin, A_BOLD); 
		wattroff(inputwin, A_UNDERLINE);
		wprintw(inputwin, "\nSelect piece");
	}
	wrefresh(inputwin);
	highlight_window(win, high_panel, x, y, 1, ip);
	int flag_piece, flag_move;
	char temp_piece[3];
	int flag_quit;					//flag when quit option is used
	int help_flag = 0;				//flag when help option is used
	while (1) {
		if(help_flag == 1) {
			c = KEY_UP;
			help_flag++;
		}
		else if(help_flag == 2) {
			c = KEY_DOWN;
			help_flag++;
		}
		else {
			c = getch();
			help_flag = 0;
		}
		wmove(inputwin, (3 * (inputmax_y / 4)), 0);
		wclrtoeol(inputwin);
		wrefresh(inputwin);
			switch(c) {				//keyboard inputs (navigate with arrow keys, enter to select, h for help, q to quit)
			flag = 0;
			case KEY_UP:	
					wmove(inputwin, (inputmax_y / 4), 0);
					wclrtoeol(inputwin);
					highlight_window(win, high_panel, x, y, 0, ip);
					if(x == 0)
						x = 7;
					else
						x--;
					highlight_window(win, high_panel, x, y, 1, ip);
				      
				     	break;
			case KEY_DOWN:	wmove(inputwin, (inputmax_y / 4), 0);
					wclrtoeol(inputwin);
					highlight_window(win, high_panel, x, y, 0, ip);
					if(x == 7)
						x = 0;
					else
					 	x++;	
					highlight_window(win, high_panel, x, y, 1, ip);
					break;
			case KEY_RIGHT: wmove(inputwin, (inputmax_y / 4), 0);
					wclrtoeol(inputwin);
					highlight_window(win, high_panel, x, y, 0, ip);
					 if(y == 7)
						y = 0;
					 else
					 	y++;
					highlight_window(win, high_panel, x, y, 1, ip);
					break;
			case KEY_LEFT: 	wmove(inputwin, (inputmax_y / 4), 0);
					wclrtoeol(inputwin);
					highlight_window(win, high_panel, x, y, 0, ip);
					if(y == 0)
						y = 7;
					else
						y--;
					highlight_window(win, high_panel, x, y, 1, ip);
					break;
			case 72:	
			case 104:	
					savetty();		/* Save the tty modes		  */
					erase();
					endwin();
					help();
					erase();
					resetty();		/* Return to the previous tty mode*/
					wbkgd(stdscr, COLOR_PAIR(1));
					mvprintw(LINES - 1, COLS / 3,"Press h for help");
					mvprintw(LINES - 1, (2 * COLS) / 3,"Press q to quit");
					refresh();
					help_flag = 1;
					break;
			case 81:
			case 113:	wmove(inputwin, (inputmax_y / 4), 0);
					wclrtoeol(inputwin);
					echo();
					flag_quit = 1;
					while(1){
						curs_set(1);
						wmove(inputwin, 4, 0);
						wprintw(inputwin, "Do you really want to quit? (y/n) ");
						wrefresh(inputwin);
						choice = wgetch(inputwin);
						curs_set(0);
						switch(choice) {
							case 'Y':
							case 'y':return NULL;
							case 'N':
							case 'n':flag_quit = 0;
								 wmove(inputwin, 4, 0);
								 wclrtoeol(inputwin);
								 wmove(inputwin, 5, 0);
								 wclrtoeol(inputwin);
								 wrefresh(inputwin);
								break;
							default:wmove(inputwin, 4, 0);
								wclrtoeol(inputwin);
								wmove(inputwin, 5, 0);
								wclrtoeol(inputwin);
								wrefresh(inputwin);
						}
						if(flag_quit == 0)
							break;
					}
					noecho();
					break;
			case 10:wmove(inputwin, (inputmax_y / 4), 0);
				wclrtoeol(inputwin);
				strcpy(ip -> piece, pp[x][y]);
				if((ip -> player == 0 && ip -> piece[0] == 'b') || (ip -> player == 1 && ip -> piece[0] == 'w')) {
					temp_piece[0] = ip -> piece[1];
					if(ip -> piece[2] == '\0')
						temp_piece[1] = '\0';
					else {
						temp_piece[1] = ip -> piece[2];
						temp_piece[2] = '\0';
					}
					flag_piece = check_chess_piece(ip -> player, temp_piece);
					if(flag_piece != -1) {
						ip -> enum_piece = flag_piece;
					}
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
						wclrtoeol(inputwin);
						wprintw(inputwin, "No move available!!\n ");
						wrefresh(inputwin);
					}
					else {
						highlight_window(win, high_panel, x, y, 0, ip);
						flag = 1;
						ip -> enum_piece = flag_piece;
						*prevx = x;
						*prevy = y;
						break;
					}
				}
				else {
					wmove(inputwin, (inputmax_y / 4), 0);
					wclrtoeol(inputwin);
					wprintw(inputwin, " Invalid piece!!\n ");
					wrefresh(inputwin);
				}
					break;
			default:
				mvwprintw(inputwin, (3 * (inputmax_y / 4)), 0, "Wrong Entry.");
				wrefresh(inputwin);
		}
		if(flag == 1)
			break;
	}
	return ip;
}

input *second_type_input_move(input *ip, WINDOW ***win, PANEL **high_panel, WINDOW *inputwin, int *prevx, int *prevy) {
	int x = *prevx, y = *prevy;
	init_pair(4, COLOR_RED, COLOR_BLUE);
	int flag = 0, flag_quit, flag_move, c;
	int inputmax_x, inputmax_y;
	char choice;
	getmaxyx(inputwin, inputmax_y, inputmax_x);
	wmove(inputwin, 2, 0);
	wclrtoeol(inputwin);
	wprintw(inputwin, "Enter move ");
	wrefresh(inputwin);
	highlight_window(win, high_panel, x, y, 1, ip);
	int help_flag = 0;
	while (1) {
		if(help_flag == 1) {
			c = KEY_UP;
			help_flag++;
		}
		else if(help_flag == 2) {
			c = KEY_DOWN;
			help_flag++;
		}
		else {
			c = getch();
			help_flag = 0;
		}
		wmove(inputwin, (3 * (inputmax_y / 4)), 0);
		wclrtoeol(inputwin);
		wrefresh(inputwin);

			switch(c) {				//keyboard inputs (navigate with arrow keys, enter to select, h for help, q to quit)
			flag = 0;
			case KEY_UP:	wmove(inputwin, (inputmax_y) / 8 + 2, 2);
					wclrtoeol(inputwin);
					highlight_window(win, high_panel, x, y, 0, ip);
					if(x == 0)
						x = 7;
					else
						x--;
					highlight_window(win, high_panel, x, y, 1, ip);
				      
				     	break;
			case KEY_DOWN:	wmove(inputwin, (inputmax_y) / 8 + 2, 2);
					wclrtoeol(inputwin);
					highlight_window(win, high_panel, x, y, 0, ip);
					if(x == 7)
						x = 0;
					else
					 	x++;	
					highlight_window(win, high_panel, x, y, 1, ip);
					break;
			case KEY_RIGHT:	wmove(inputwin, (inputmax_y) / 8 + 2, 2);
					wclrtoeol(inputwin);
					highlight_window(win, high_panel, x, y, 0, ip);
					 if(y == 7)
						y = 0;
					 else
					 	y++;
					highlight_window(win, high_panel, x, y, 1, ip);
					break;
			case KEY_LEFT: 	wmove(inputwin, (inputmax_y) / 8 + 2, 2);
					wclrtoeol(inputwin);
					highlight_window(win, high_panel, x, y, 0, ip);
					if(y == 0)
						y = 7;
					else
						y--;
					highlight_window(win, high_panel, x, y, 1, ip);
					break;
			case 72:	
			case 104:	
					savetty();		/* Save the tty modes		  */
					erase();
					endwin();
					help();
					erase();
					resetty();		/* Return to the previous tty mode*/
					wbkgd(stdscr, COLOR_PAIR(1));
					mvprintw(LINES - 1, COLS / 3,"Press h for help");
					mvprintw(LINES - 1, (2 * COLS) / 3,"Press q to quit");
					refresh();
					help_flag = 1;
					break;

			case 81:
			case 113:	wmove(inputwin, (inputmax_y) / 8 + 2, 2);
					wclrtoeol(inputwin);
					echo();
					flag_quit = 1;
					while(1){
						curs_set(1);
						wmove(inputwin, 4, 0);
						wprintw(inputwin, "Do you really want to quit? (y/n) ");
						wrefresh(inputwin);
						choice = wgetch(inputwin);
						curs_set(0);
						switch(choice) {
							case 'Y':
							case 'y':return NULL;
							case 'N':
							case 'n':flag_quit = 0;
								 wmove(inputwin, 4, 0);
								 wclrtoeol(inputwin);
								 wmove(inputwin, 5, 0);
								 wclrtoeol(inputwin);
								 wrefresh(inputwin);
								break;
							default:wmove(inputwin, 4, 0);
								wclrtoeol(inputwin);
								wmove(inputwin, 5, 0);
								wclrtoeol(inputwin);
								wrefresh(inputwin);
						}
						if(flag_quit == 0)
							break;
					}
					noecho();
					break;

			case 10:	wmove(inputwin, (inputmax_y) / 8 + 2, 2);
					wclrtoeol(inputwin);
					sprintf(ip -> move, "%d%d", x, y);
					flag_move = check_chess_move(ip);
					if(flag_move == 1){
						*prevx = x;
						*prevy = y;
						flag = 1;
					}
					else {
						wprintw(inputwin, "Invalid move!!\n ");
						wrefresh(inputwin);
					}
					break;
			default:
				mvwprintw(inputwin, (3 * (inputmax_y / 4)), 0, "Wrong Entry.");
				wrefresh(inputwin);
		}
		if(flag == 1)
			break;
	}
	return ip;
}

/*void input_move(WINDOW *inputwin, input *ip) {		//input piece (words)
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
}*/

/*input *input_piece(WINDOW *inputwin, int inputstart_y, int inputstart_x, input *ip) { 	//input move (co-ordinates)
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
}*/



void move_piece(input *ip, WINDOW ***win, int s, PANEL **high_panel) {
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

void highlight_moves(input *ip, WINDOW ***win, PANEL **high_panel) {
	int i = 0;
	int x, y;
	init_pair(3, COLOR_BLUE, COLOR_GREEN);
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

void unhighlight_moves(input *ip, WINDOW ***win, PANEL **high_panel) {
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



WINDOW *create_newwin(int height, int width, int starty, int startx, int col, int j, int k) {	//j represents row no.
	WINDOW *local_win;									//create chessboard
	local_win = newwin(width , (2 *  width) , starty, startx);
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

input *find_present_cordinates(input *ip) {							//find present coordinates of input piece
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
