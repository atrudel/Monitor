/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NcursesDisplay.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:38:03 by agrumbac          #+#    #+#             */
/*   Updated: 2018/04/07 15:10:52 by agrumbac         ###   ########.fr       */
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

virtual void 			NcursesDisplay::init(void)
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);

	start_color();

	// init_pair(PLAYER_COLOR, COLOR_GREEN, COLOR_BLACK);
	// init_pair(PLAYER2_COLOR, COLOR_CYAN, COLOR_BLACK);
	// init_pair(MISSILES_COLOR, COLOR_RED, COLOR_BLACK);
	// init_pair(ENEMIES_COLOR, COLOR_YELLOW, COLOR_BLACK);
	// init_pair(EMISSILES_COLOR, COLOR_MAGENTA, COLOR_BLACK);
	// init_pair(STARS_COLOR, COLOR_WHITE, COLOR_BLACK);
}

virtual void 			NcursesDisplay::update(void)
{ }

virtual void 			NcursesDisplay::render(void) const
{ }

void 					NcursesDisplay::quit( void )
{
	endwin();
}
