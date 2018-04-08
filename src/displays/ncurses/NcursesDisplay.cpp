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
	// border box creation
	for(std::map<std::string, WINDOW *>::const_iterator it=_fenetres.begin(); it != _fenetres.end(); it++) {
        box(it->second, ACS_VLINE, ACS_HLINE);
    }
	// content creation
	for(std::map<std::string, WINDOW *>::const_iterator it=_fenetres.begin(); it != _fenetres.end(); it++) {
        // titre du module
		mvwprintw(it->second, 1, 1,("Ceci est la fenetre du " + it->first).c_str());
		int j = 2;
		for (std::map<std::string, IMonitorModule*>::const_iterator mainit = disp.begin();mainit != disp.end();mainit++) {
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
		}
/*		mvwprintw(it->second, 2, 1, "test [%s]", disp.find(it->first)->second->getName().c_str());
		std::map<std::string, std::deque<float> > modulegraph = disp.find(it->first)->second->getGraphs();
		int i = 0;
		float cpu = 0;
		mvwprintw(it->second, 3, 1, "modulegraph %i : [%s]", i, modulegraph.begin()->first.c_str());
		for (std::deque<float>::const_iterator eqiter = modulegraph.begin()->second.begin(); eqiter !=  modulegraph.begin()->second.end(); eqiter++){
		//	mvwprintw(it->second, i, 1, "modulegraph %i : [%6.2f]", i, *eqiter);
		//	mvwprintw(it->second, 4, 1 + i * 8, "%6.2f", *eqiter);
			cpu += *eqiter;
			i++;
		}
		mvwprintw(it->second, 4, 1, "moyenne : [%6.2f %%]", cpu / i);*/
//		;
//		for (std::map<std::string, std::deque<float> >::const_iterator  mdlit = modulegraph.begin(); mdlit != modulegraph.end(); mdlit++) {
//			mvwprintw(it->second, i, 1, "modulegraph %i : [%s]", i, mdlit->first.c_str());
//			i++;
//		}
	//	mvwprintw(it->second, 4, 1, "test [%s]", disp.find(it->first)->second->getName().c_str());
    
	
	}
	// refresh function
    refresh();
    for(std::map<std::string, WINDOW *>::const_iterator it=_fenetres.begin(); it != _fenetres.end(); it++) {
        wrefresh(it->second);
    }
//	attron(COLOR_PAIR(PLAYER_COLOR));
//	mvprintw(LINES, COLS);
}
