#include "SdlDisplay.hpp"

SdlDisplay::SdlDisplay()
	: _width(0), _height(0)
{
}

SdlDisplay::SdlDisplay(const int &w, const int &h)
	: _width(w), _height(h)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw  std::runtime_error("sdl error: unable to initialize sdl !");
	_window = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
	if (!_window)
		throw  std::runtime_error("sdl error: unable to create window !");
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);
	_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, w, h);
	_pixels = new int[w * h];
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

void SdlDisplay::drawPix(int x, int y, int color)
{
	if (x < 0 || y < 0 || x >= _width || y >= _height)
		return ;
	_pixels[x + y * _width] = color;
}

void SdlDisplay::init()
{
	SDL_SetRenderDrawColor(_renderer, 255, 0, 255, 255);
	SDL_RenderPresent(_renderer);
	SDL_RenderClear(_renderer);
}

void SdlDisplay::swap()
{
	SDL_UpdateTexture(_texture, NULL, _pixels, _width * sizeof(int));
	SDL_RenderCopy(_renderer, _texture, NULL, NULL);
	SDL_RenderPresent(_renderer);
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
