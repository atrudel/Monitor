/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NcursesDisplay.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:38:34 by agrumbac          #+#    #+#             */
/*   Updated: 2018/04/07 17:22:01 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NCURSESDISPLAY_H
# define NCURSESDISPLAY_H

#include <ncurses.h>
#include <iostream>
#include "IMonitorDisplay.hpp"

class NcursesDisplay : public IMonitorDisplay {

public:

	NcursesDisplay( void );
	NcursesDisplay( NcursesDisplay const & src );
	virtual ~NcursesDisplay();

	NcursesDisplay &		operator=( NcursesDisplay const & rhs );

	virtual void 			init( void );
	virtual void 			update( void );
	virtual void 			render( void ) const;
	bool 					quit( void );

private:
	std::map<std::string, WINDOW *>                   fenetres;

};

# define DISP_WHITE		0
# define DISP_RED		1
# define DISP_GREEN		2
# define DISP_BLUE		3
# define DISP_CYAN		4
# define DISP_YELLOW	5
# define DISP_MAGENTA	6

# define KEY_ESC		27

#endif
