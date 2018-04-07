#include "BeautifulDisplay.hpp"

BeautifulDisplay::BeautifulDisplay(void)
	: _display(SdlDisplay(128, 128))
{

}

BeautifulDisplay::BeautifulDisplay(const BeautifulDisplay& src)
	: _display(SdlDisplay(128, 128))
{
    *this = src;
    return;
}

BeautifulDisplay::~BeautifulDisplay(void) {
    return;
}

BeautifulDisplay& BeautifulDisplay::operator=(const BeautifulDisplay& rhs) {
    if (this != &rhs) {
        // TODO
    }
    return *this;
}

void BeautifulDisplay::init(void)
{
	_display.init();
}

void BeautifulDisplay::update(void)
{

}

void BeautifulDisplay::render(const std::map<std::string, IMonitorModule*> &module)
{
	(void) module;
	_display.swap();
	static int i = 0;
	i++;

	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN &&
										event.key.keysym.sym == SDLK_ESCAPE))
		{
			exit(0);
		}
	}

	for (int y = 0; y < _display.getHeight(); y++)
		for (int x = 0; x < _display.getHeight(); x++)
			_display.drawPix(x, y, i * x * y);
	// typedef std::map<std::string, IMonitorModule*>::const_iterator iterator;
	//
	// for (iterator i = module.begin(); i != module.end(); i++)
	// 	std::cout << i->first << ": " << std::endl;
}
