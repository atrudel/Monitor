#ifndef SDLDISPLAY_HPP
# define SDLDISPLAY_HPP

# include <iostream>
# include <SDL.h>

class SdlDisplay
{
private:
	SDL_Window		*_window;
	SDL_Renderer	*_renderer;
	SDL_Texture		*_texture;
	int				_width;
	int				_height;
	int				*_pixels;

	SdlDisplay();
public:

	SdlDisplay(const int &x, const int &y);

	SdlDisplay(const SdlDisplay &o);

	virtual ~SdlDisplay();

	SdlDisplay &operator=(const SdlDisplay &o);

	void drawPix(int x, int y, int color);
	void init();
	void swap();

	int getWidth() const;

	int getHeight() const;

	int *getPixels() const;

};

#endif
