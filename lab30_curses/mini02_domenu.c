/*******************************************************************************
**	File:
**
**		mini02_domenu.c
**
**  Contents:
**		LINUX system programming
**
**	History:
**		Date        Name              Description
**		------------------------------------------------------------------------
**
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <curses.h>
#include "menu.h"

char *mtab[8] = {
	"apples",
	"bananas",
	"carrots",
	"",
	"melons",
	"",
	"peaches",
	"zucchini",
};

struct menu m1 = {
	8, 8,
	"Select a Fruit or Vegetable",
	&mtab[0]
};

char isblanks(char *s)
{
	while(*s == ' ')
		s++;

	return *s == '\0' ? 1: 0;
}

//
// domenu -- handle a simple menu on stdscr
//
int domenu(struct menu *m)
{
	int option, lastoption, j, c, y, x;
	char *p;

	// save current terminal state, then set required modes
	savetty();

	cbreak(); nonl(); noecho(); standend();

	// empty screen
	clear();

	// initialize keypad, TRUE is defined in curses.h
	keypad(stdscr, TRUE);

	// print centered title on line one
	move(0, (COLS - strlen(m->m_title))/2);
	addstr(m->m_title);

	// work out position for top left corner of menu
	y = (LINES - m->m_height)/2 +1;
	x = (COLS -m->m_width)/2;

	// display menu
	for(j =0; j < m->m_height; j++)
		mvaddstr(y+j, x, m->m_data[j]);

	// initial values for cursor pos. and option setting
	move(y, x);

	// this assumes first line in menu isn't blank
	lastoption = option = 0;

	for(;;){
		// remove highlight bar from last option
		if(lastoption != option)
			mvaddstr( lastoption+y, x, m->m_data[lastoption]);

		// put highlight bar on current option
		standout();
		mvaddstr(option+y, x, m->m_data[option]);
		standend();
		move(option+y, x);

		// save current option
		lastoption = option;
		refresh();

		// process input
		switch( (c=getch()) ){
		case '\r':
		case '\n':
			if(option < 0){
				beep();
				break;
			}

			// restore initial state and return
			resetty();
			return option;
		case KEY_DOWN:
		case KEY_RIGHT:
			do{
				option = (++option < m->m_height) ? option: 0;
			}while(isblanks(m->m_data[option]));
			break;
		case KEY_UP:
		case KEY_LEFT:
			do{
				option = (--option >= 0) ? option : m->m_height-1;
			}while(isblanks(m->m_data[option]));
			break;
		default:
			for(j=0; j<m->m_height; j++){
				for(p=m->m_data[j]; *p==' '; p++)
					;
				if(*p == '\0')
					continue;

				if(*p == c)
				{
					option = j;
					break;
				}
			}
			if(j >= m->m_height)
				beep();
			break;
		}
	}
}

main(void)
{
	initscr();
	domenu(&m1);
	endwin();
}

/* mini02_domenu.c */
