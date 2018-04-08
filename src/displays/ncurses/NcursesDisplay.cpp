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
            _module_separation_size(1), _module_height(MODULE_HEIGHT),
			_max_module_width(MODULE_WIDTH), _module_width(_max_module_width),
			_window_height(LINES), _window_width(COLS)
{ }

NcursesDisplay::NcursesDisplay( NcursesDisplay const & src ) :
            _module_separation_size(1), _module_height(MODULE_HEIGHT),
			_max_module_width(MODULE_WIDTH), _module_width(_max_module_width),
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
mvprintw(0, 50,"	        _             _ _           ");
mvprintw(1, 50,"   __ _| | ___ __ ___| | |_ __ ___  ");
mvprintw(2, 50,"  / _` | |/ / '__/ _ \\ | | '_ ` _ \\ ");
mvprintw(3, 50," | (_| |   <| | |  __/ | | | | | | |");
mvprintw(4, 50,"  \\__, |_|\\_\\_|  \\___|_|_|_| |_| |_|");
mvprintw(5, 50,"  |___/                             ");
	// border box creation
	for(std::map<std::string, WINDOW *>::const_iterator it=_fenetres.begin(); it != _fenetres.end(); it++) {
        box(it->second, ACS_VLINE, ACS_HLINE);
    }
	// content creation
	for(std::map<std::string, WINDOW *>::const_iterator it=_fenetres.begin(); it != _fenetres.end(); it++) {
        // titre du module
		mvwprintw(it->second, 1, 1,("Ceci est la fenetre du " + it->first).c_str());
		int j = 2;
		std::map<std::string, IMonitorModule*>::const_iterator mainit = disp.find(it->first);
		mvwprintw(it->second, j, 1, "[%s] min %6.2f max %6.2f ", mainit->second->getName().c_str(), mainit->second->getGraphMin(), mainit->second->getGraphMax());
		j++;
		int i = 0;
		float cpu = 0;
		for (std::map<std::string, std::deque<float> >::const_iterator secondit = mainit->second->getGraphs().begin(); secondit != mainit->second->getGraphs().end();secondit++) {
			for (std::deque<float>::const_iterator eqiter = secondit->second.begin(); eqiter !=  secondit->second.end(); eqiter++){
				cpu += *eqiter;
				i++;
			}
			mvwprintw(it->second,j,10, " [%6.2f %%] %s  ",cpu / i, secondit->first.c_str());
			j++;
		}
		j++;
		for (std::map<std::string, std::string>::const_iterator datait =  mainit->second->getData().begin(); datait != mainit->second->getData().end(); datait++){
			mvwprintw(it->second,j,10, " [%6.2f %%] %s  ",cpu / i, datait->first.c_str());
		}
		j++;
	}
	// refresh function
    refresh();
    for(std::map<std::string, WINDOW *>::const_iterator it=_fenetres.begin(); it != _fenetres.end(); it++) {
        wrefresh(it->second);
    }
//	attron(COLOR_PAIR(PLAYER_COLOR));
//	mvprintw(LINES, COLS);
}
