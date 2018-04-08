#include "SdlDisplay.hpp"

SdlDisplay::SdlDisplay()
	: _width(0), _height(0)
{
}

SdlDisplay::SdlDisplay(const int &w, const int &h)
	: _width(w), _height(h), _font("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.;,:=+-*/\\()!?@ ")
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw  std::runtime_error("sdl error: unable to initialize sdl !");
	_window = SDL_CreateWindow("ft_gkrellm", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
	if (!_window)
		throw  std::runtime_error("sdl error: unable to create window !");
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);
	_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, w, h);
	_pixels = new int[w * h];
	_fontImg = SDL_CreateTextureFromSurface(_renderer, SDL_LoadBMP("font.bmp"));
	SDL_SetWindowResizable(_window, SDL_TRUE);
	SDL_SetWindowBordered(_window, SDL_FALSE);
}

SdlDisplay::SdlDisplay(const SdlDisplay &o)
{
	*this = o;
}

SdlDisplay::~SdlDisplay()
{
	delete _pixels;
}

SdlDisplay &SdlDisplay::operator=(const SdlDisplay &o)
{
	(void) o;
	return *this;
}

void SdlDisplay::setSize(const int &w, const int &h)
{
	if (w <= 0 || h <= 0 || w > 10000 || h > 10000)
		return;
	if (_width != w || _height != h)
		resize(w, h);
}

void SdlDisplay::update()
{
	int rx, sx;
	int ry, sy;
	int wx, wy;
	int xOffs = 0, yOffs = 0;

	if (SDL_GetMouseState(&rx, &ry))
	{
		SDL_GetGlobalMouseState(&sx, &sy);
		SDL_GetWindowPosition(_window, &wx, &wy);
		SDL_DisplayMode screen;
		SDL_GetCurrentDisplayMode(0, &screen);
		if (wx + _width > screen.w)
			xOffs = screen.w - (wx + _width);
		if (wx < 0)
			xOffs = -wx;
		if (wy + _height > screen.h)
			yOffs = screen.h - (wy + _height);
		SDL_SetWindowPosition(_window, sx - rx + xOffs, sy - ry + yOffs);
	}
}

void SdlDisplay::drawPix(const int &x, const int &y, const int &color)
{
	if (x < 0 || y < 0 || x >= _width || y >= _height)
		return ;
	_pixels[x + y * _width] = color;
}

void SdlDisplay::init()
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
	SDL_RenderPresent(_renderer);
	SDL_RenderClear(_renderer);
}

void SdlDisplay::drawString(const std::string &str, const int &x, const int &y)
{
	(void) str;
	(void) x;
	(void) y;

	for (size_t i = 0; i < str.length(); i++)
	{
		char c = std::toupper(str[static_cast<int>(i)]);
		int index = _font.find(c);

		SDL_Rect imgPartRect;
		imgPartRect.x = (index % 26) * 8;
		imgPartRect.y = (index / 26) * 8;
		imgPartRect.w = 8;
		imgPartRect.h = 8;

		SDL_Rect dst;
		dst.x = x + static_cast<int>(i) * 8;
		dst.y = y;
		dst.w = 8;
		dst.h = 8;

		SDL_RenderCopy(_renderer, _fontImg, &imgPartRect, &dst);
	}
}

void SdlDisplay::swap()
{
	SDL_UpdateTexture(_texture, NULL, _pixels, _width * sizeof(int));
	SDL_RenderCopy(_renderer, _texture, NULL, NULL);
}

void SdlDisplay::draw()
{
	SDL_RenderPresent(_renderer);
}

void SdlDisplay::resize(const int &w, const int &h)
{
	_width = w;
	_height = h;
	if (_width < 200)
	{
		_width = 200;
		SDL_SetWindowSize(_window, _width, _height);
	}
	if (_pixels != NULL)
		delete _pixels;
	_pixels = new int[_width * _height];
	if (_texture != NULL)
		SDL_DestroyTexture(_texture);
	_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, _width, _height);
	init();
	swap();
}

void SdlDisplay::handleEvents(const SDL_Event &e)
{
	switch (e.window.event)
	{
		case SDL_WINDOWEVENT_RESIZED:
			resize(e.window.data1, e.window.data2);
			break;
	}
}

int SdlDisplay::getWidth() const
{
	return _width;
}

int SdlDisplay::getHeight() const
{
	return _height;
}

int *SdlDisplay::getPixels() const
{
	return _pixels;
}
