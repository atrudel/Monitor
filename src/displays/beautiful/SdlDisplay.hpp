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
	SDL_Texture		*_fontImg;
	std::string		_font;
	bool			_clicked;

	SdlDisplay();
public:

	SdlDisplay(const int &x, const int &y);

	SdlDisplay(const SdlDisplay &o);

	virtual ~SdlDisplay();

	SdlDisplay &operator=(const SdlDisplay &o);

	void update();

	void drawPix(const int &x, const int &y, const int &color);
	void init();
	void swap();
	void draw();

	void drawString(const std::string &str, const int &x, const int &y);

	bool button(const std::string &str, const int &x, const int &y, const int &w, const int &h);
	bool button(const std::string &str, const int &x, const int &y, const int &w, const int &h, const int &color);
	bool button(const std::string &str, const int &x, const int &y, const int &w, const int &h, const int &color, const int &clickColor);

	void setSize(const int &w, const int &h);

	void setMove(const int &x, const int &y);

	void handleEvents(const SDL_Event &e);

	void resize(const int &w, const int &h);

	int getWidth() const;

	int getHeight() const;

	int *getPixels() const;

	SDL_Window *getWindow() const;
	SDL_Renderer *getRenderer() const;

	SDL_Texture *getTexture() const;

	SDL_Texture *getFontImg() const;

	std::string getFont() const;

};

#endif
