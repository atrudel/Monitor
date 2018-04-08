#include "BeautifulDisplay.hpp"

BeautifulDisplay::BeautifulDisplay(void)
	: _display(SdlDisplay(200, 200))
{

}

BeautifulDisplay::BeautifulDisplay(const BeautifulDisplay& src)
	: _display(SdlDisplay(200, 200))
{
    *this = src;
    return;
}

BeautifulDisplay::~BeautifulDisplay(void) {
    return;
}

BeautifulDisplay& BeautifulDisplay::operator=(const BeautifulDisplay& rhs) {
    if (this != &rhs)
	{
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
	_display.update();
}

void BeautifulDisplay::renderModule(const IMonitorModule &module)
{
	(void) module;
//	for (int y = _display.getWidth() - 1; y > 100; y++)
//		for (int x = 0; x < _display.getWidth(); x++)
//			_display.drawPix(x, y, 0x000000);
	typedef std::map<std::string, std::deque<float> >::const_iterator	module_iterator;

	for (module_iterator it = module.getGraphs().begin(); it != module.getGraphs().end(); it++)
	{
//		for (int x = 0; x < _display.getWidth(); x++)
		{
			std::deque<float> data = it->second;
			std::cout << data.size() << std::endl;
			for (size_t x = data.size() - 1; x > 0; x--)
			{
				for (int y = data[x] * 100 - 1; y > 0; y--)
				{
					_display.drawPix(static_cast<int>(x), 100 - y, 0x00ffff);
				}
				for (int y = data[x] * 100 - 1; y > 0; y--)
				{
					_display.drawPix(static_cast<int>(x), 100 - y + 100, 0x00ffff);
				}
			}
		}
	}
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
		_display.handleEvents(event);
		if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
		{
			exit(0);
		}
	}

	for (int y = 0; y < _display.getHeight(); y++)
		for (int x = 0; x < _display.getWidth(); x++)
			_display.drawPix(x, y, 0);

	typedef std::map<std::string, IMonitorModule*>::const_iterator iterator;

	for (iterator it = module.begin(); it != module.end(); it++)
		renderModule(*it->second);
}
