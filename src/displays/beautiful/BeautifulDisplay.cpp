#include "BeautifulDisplay.hpp"

BeautifulDisplay::BeautifulDisplay(void)
	: _display(SdlDisplay(500, 1000))
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
        _display = rhs._display;
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

void BeautifulDisplay::renderModule(const IMonitorModule &module, int &curr_x, int &curr_y)
{
	_display.button("x", _display.getWidth() - 16 - 5, curr_y + 16, 16, 16, 0xaa0000);
	_display.drawString(module.getName(), curr_x, curr_y);
	curr_y += TITLE_HEIGHT;

	typedef std::map<std::string, std::string>::const_iterator	data_iterator;
	for (data_iterator it = module.getData().begin(); it != module.getData().end(); it++)
	{
		std::string str = it->first + ": " + it->second;
		_display.drawString(str, curr_x, curr_y);
		curr_y += DATA_HEIGHT;
	}

	int j = -1;
	typedef std::map<std::string, std::deque<float> >::const_iterator	graph_iterator;
	for (graph_iterator it = module.getGraphs().begin(); it != module.getGraphs().end(); it++)
	{
		++j;
		std::string name = it->first;

		_display.drawString(name, curr_x, curr_y);

		std::deque<float> data = it->second;
		for (size_t x = data.size() - 1; x > 0; x--)
		{
			for (int y = data[x] * 100 - 1; y > 0; y--)
			{
				int r = 255 - j * 50;
				int g = 128 + j * 50;
				int b = y * 2;
				int color = (r << 16) | (g << 8) | b;

				_display.drawPix(static_cast<int>(x) + (curr_x + LEFT_MARGIN_GR), (100 + curr_y - y) , color);
			}
		}
		curr_y += GRAPH_HEIGHT;
	}

}

void BeautifulDisplay::render(const std::map<std::string, IMonitorModule*> &modules)
{
	(void) modules;
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

//	 _display.setSize(200, static_cast<int>(modules.size() * 100));

	for (int y = 0; y < _display.getHeight(); y++)
		for (int x = 0; x < _display.getWidth(); x++)
			_display.drawPix(x, y, 0x111111);

	typedef std::map<std::string, IMonitorModule*>::const_iterator iterator;

	if (_display.button("Exit", _display.getWidth() - 45, 5, 40, 12, 0xaa0000))
		exit(0);

	if (_display.button("OS", 5, 5, 40, 12, 0x00aa00))
	{

	}

	_display.button("CPU", 5 + 45, 5, 40, 12, 0x00aa00);
	_display.button("RAM", 5 + 45 * 2, 5, 40, 12, 0x00aa00);
	_display.button("NET", 5 + 45 * 3, 5, 40, 12, 0x00aa00);

	int curr_x = LEFT_OFFSET;
	int curr_y = TOP_OFFSET;
	for (iterator it = modules.begin(); it != modules.end(); it++)
	{
		renderModule(*it->second, curr_x, curr_y);
		curr_y += MODULE_GAP;
	}

	_display.draw();
}

int	 BeautifulDisplay::calculateTotalHeight(const std::map<std::string, IMonitorModule*> &modules) const {
    int height= 0;

    height += TOP_OFFSET;

    typedef std::map<std::string, IMonitorModule*>::const_iterator iterator;
    for (iterator it = modules.begin(); it != modules.end(); it++)
    {
        height += calculateModuleHeight(it->second);
    }
    height += MODULE_GAP * (modules.size() - 1);
    height += BOTTOM_OFFSET;
    return height;
}

int	 BeautifulDisplay::calculateModuleHeight(const IMonitorModule* module) const {
    int height = 0;
    height += TITLE_HEIGHT;
    height += DATA_HEIGHT * module->getData().size();
    height += GRAPH_HEIGHT * module->getGraphs().size(); // to change
    height += MODULE_GAP * (module->getGraphs().size() -1); // to change
    return height;
}
