/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 15:42:38 by agrumbac          #+#    #+#             */
/*   Updated: 2018/04/07 17:05:03 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NcursesDisplay.hpp"

int		main( void )
{
	NcursesDisplay	dsp;

	std::map<std::string, IMonitorModule*>	modules;
	modules["test"] = nullptr;
	dsp.init(modules);
	while (!dsp.quit())
	{
		dsp.update();
		dsp.render(modules);
	}
	return (0);
}
