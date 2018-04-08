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

NcursesDisplay::NcursesDisplay( void ) : 
            _module_separation_size(1), _module_height(10),
			_max_module_width(70), _module_width(_max_module_width),
			_window_height(LINES), _window_width(COLS)
{ }

NcursesDisplay::NcursesDisplay( NcursesDisplay const & src ) :
            _module_separation_size(1), _module_height(10),
			_max_module_width(70), _module_width(_max_module_width),
			_window_height(LINES), _window_width(COLS)
{
	*this = src;
}

NcursesDisplay::~NcursesDisplay()
{ 

}


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

void 					NcursesDisplay::init(const std::map<std::string, IMonitorModule*> &disp)
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
	int i = 0;
	for (std::map<std::string, IMonitorModule*>::const_iterator it = disp.begin(); it != disp.end(); it++) {
		_fenetres[it->first] = subwin(stdscr, _module_height , _module_width, (_module_height + _module_separation_size) * i , 0);
		i++;
	}
}

bool 					NcursesDisplay::quit( void )
{
	if (getch() == 27) {
		endwin();
		return true;
	}
	return false;
}

void 					NcursesDisplay::update(void)
{ 
    getmaxyx(stdscr, _window_height, _window_width);
}

void 					NcursesDisplay::render( const std::map<std::string, IMonitorModule*> &disp ) 
{
	(void)disp;
	erase();
	box(stdscr, 0, 0);
	// border box creation
	for(std::map<std::string, WINDOW *>::const_iterator it=_fenetres.begin(); it != _fenetres.end(); it++) {
        box(it->second, ACS_VLINE, ACS_HLINE);
    }
	// content creation
	for(std::map<std::string, WINDOW *>::const_iterator it=_fenetres.begin(); it != _fenetres.end(); it++) {
		

        mvwprintw(it->second, 1, 1,("Ceci est la fenetre du " + it->first).c_str());
		mvwprintw(it->second, 2, 1, "test [%s]", disp.find(it->first)->second->getName().c_str());
		std::map<std::string, std::deque<float> > modulegraph = disp.find(it->first)->second->getGraphs();
		int i = 3;
		for (std::map<std::string, std::deque<float> >::const_iterator  mdlit = modulegraph.begin(); mdlit != modulegraph.end(); mdlit++) {
			mvwprintw(it->second, i, 1, "modulegraph %i : [%s]", i, mdlit->first.c_str());
			i++;
		}
		mvwprintw(it->second, 4, 1, "test [%s]", disp.find(it->first)->second->getName().c_str());
    
	
	}
	// refresh function
    refresh();
    for(std::map<std::string, WINDOW *>::const_iterator it=_fenetres.begin(); it != _fenetres.end(); it++) {
        wrefresh(it->second);
    }
//	attron(COLOR_PAIR(PLAYER_COLOR));
//	mvprintw(LINES, COLS);
}
