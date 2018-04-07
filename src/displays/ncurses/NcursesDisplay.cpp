/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NcursesDisplay.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:38:03 by agrumbac          #+#    #+#             */
/*   Updated: 2018/04/07 17:19:59 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NcursesDisplay.hpp"

NcursesDisplay::NcursesDisplay( void )
{ }

NcursesDisplay::NcursesDisplay( NcursesDisplay const & src )
{
	*this = src;
}

NcursesDisplay::~NcursesDisplay()
{ }


NcursesDisplay &		NcursesDisplay::operator=( NcursesDisplay const & rhs )
{
	//TODO fill this
	(void)rhs;
	return *this;
}

void 					NcursesDisplay::init(void)
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);

	start_color();
	init_pair(DISP_WHITE, COLOR_WHITE, COLOR_BLACK);
	init_pair(DISP_RED, COLOR_RED, COLOR_BLACK);
	init_pair(DISP_GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(DISP_BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(DISP_CYAN, COLOR_CYAN, COLOR_BLACK);
	init_pair(DISP_YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(DISP_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
}

bool 					NcursesDisplay::quit( void )
{
	int					ch = getch();

	if (ch == KEY_ESC)
	{
		endwin();
		return true;
	}
	return false;
}

void 					NcursesDisplay::update(void)
{ }

void 					NcursesDisplay::render(void) const
{
	box(stdscr, 0, 0);
	attron(COLOR_PAIR(PLAYER_COLOR));
	mvprintw(LINES, COLS);
}
