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

void BeautifulDisplay::renderModule(const IMonitorModule &module, int index)
{
	int j = -1;

	typedef std::map<std::string, std::string>::const_iterator	data_iterator;
	for (data_iterator it = module.getData().begin(); it != module.getData().end(); it++)
	{
		j++;
		std::string str = it->first + ": " + it->second;
		_display.drawString(str, 10, 20 + j * 10);
	}

	j = -1;
	typedef std::map<std::string, std::deque<float> >::const_iterator	graph_iterator;
	for (graph_iterator it = module.getGraphs().begin(); it != module.getGraphs().end(); it++)
	{
		j++;
		std::string name = it->first;
		std::cout << name << std::endl;
		_display.drawString(name, 5, 5 + (index + j) * 120);
		std::deque<float> data = it->second;
		for (size_t x = data.size() - 1; x > 0; x--)
		{
			for (int y = data[x] * 100 - 1; y > 0; y--)
			{
				int r = 255 - j * 50;
				int g = 128 + j * 50;
				int b = y * 2;
				int color = (r << 16) | (g << 8) | b;
				_display.drawPix(static_cast<int>(x) + 100, (100 + module.getData().size() * 10) - y + (index + j) * 120, color);
			}
		}
	}
}

void BeautifulDisplay::render(const std::map<std::string, IMonitorModule*> &module)
{
	(void) module;
	static int i = 0;
	i++;

	_display.swap();

	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		_display.handleEvents(event);
		if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
		{
			exit(0);
		}
	}

	// _display.setSize(200, static_cast<int>(module.size() * 100));

	for (int y = 0; y < _display.getHeight(); y++)
		for (int x = 0; x < _display.getWidth(); x++)
			_display.drawPix(x, y, 0);

	typedef std::map<std::string, IMonitorModule*>::const_iterator iterator;

	int index = 0;
	for (iterator it = module.begin(); it != module.end(); it++)
	{
		renderModule(*it->second, index);
		index++;
	}

	_display.draw();
}
