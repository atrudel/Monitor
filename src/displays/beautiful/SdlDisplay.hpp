//
// Created by Marc-andre PLOUX on 4/7/18.
//

#ifndef PISINE_CPP_SDLDISPLAY_HPP
# define PISINE_CPP_SDLDISPLAY_HPP

# include <iostream>
# include <SDL.h>

class SdlDisplay
{
private:
	SDL_Window	*_window;

public:
	SdlDisplay();

	SdlDisplay(/* const attributes */);

	SdlDisplay(const SdlDisplay &o);

	virtual ~SdlDisplay();

	SdlDisplay &operator=(const SdlDisplay &o);
};

std::ostream &operator<<(std::ostream &s, const SdlDisplay &o);


#endif
