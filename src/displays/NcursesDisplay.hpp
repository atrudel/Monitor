/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NcursesDisplay.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:38:34 by agrumbac          #+#    #+#             */
/*   Updated: 2018/04/07 14:57:38 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NCURSESDISPLAY_H
# define NCURSESDISPLAY_H

#include <ncurses.h>

class NcursesDisplay : public IMonitorDisplay {

public:

	NcursesDisplay( void );
	NcursesDisplay( NcursesDisplay const & src );
	virtual ~NcursesDisplay();

	NcursesDisplay &		operator=( NcursesDisplay const & rhs );

	virtual void 			init( void );
	virtual void 			update( void );
	virtual void 			render( void ) const;
	void 					quit( void );

private:

	int					_window_width;
	int					_window_height;

};

#endif
