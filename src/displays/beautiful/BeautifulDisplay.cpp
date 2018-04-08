#include "BeautifulDisplay.hpp"

BeautifulDisplay::BeautifulDisplay(void)
	: _display(SdlDisplay(500, 1000))
{
    SDL_DisplayMode screen;
    SDL_GetCurrentDisplayMode(0, &screen);

    _display.setMove(screen.w - TOTAL_WIDTH, 0);
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

bool BeautifulDisplay::renderModule(const IMonitorModule &module, int &curr_x, int &curr_y, Core &core)
{

	if (_display.button("x", _display.getWidth() - 16 - 5, curr_y + 16, 16, 16, 0xaa0000))
	{
		std::string newname = module.getName();
		core.deleteModule(newname);
		return true;
	}
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

		if (_time % 10 == 0)
			_values[it->first] = data.front();

		if (_values.find(it->first) != _values.end())
		{
			std::ostringstream os;
			os << _values[it->first];
			_display.drawString(os.str(), curr_x + 10, curr_y + GRAPH_HEIGHT / 2);
		}

		for (size_t x = data.size() - 1; x > 0; x--)
		{
			for (int y = _scale(x, data, module) * GRAPH_HEIGHT - 1; y > 0; y--)
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
	return false;

}

void BeautifulDisplay::render(const std::map<std::string, IMonitorModule*> &modules, Core &core)
{
	(void) modules;
	static int i = 0;
	i++;
	_time++;

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

	 _display.setSize(TOTAL_WIDTH, static_cast<int>(_calculateTotalHeight(modules)));

	for (int y = 0; y < _display.getHeight(); y++)
		for (int x = 0; x < _display.getWidth(); x++)
			_display.drawPix(x, y, 0x111111);

	typedef std::map<std::string, IMonitorModule*>::const_iterator iterator;

	if (_display.button("Exit", _display.getWidth() - 45, 5, 40, 12, 0xaa0000))
		exit(0);


	if (_display.button("OS", 5, 5, 40, 12, 0x00aa00))
		core.addModule("OS");
	if (_display.button("CPU", 5 + 45, 5, 40, TOP_BTN_HEIGHT, 0x00aa00))
		core.addModule("CPU");
	if (_display.button("RAM", 5 + 45 * 2, 5, 40, TOP_BTN_HEIGHT, 0x00aa00))
		core.addModule("Memory");
	if (_display.button("NET", 5 + 45 * 3, 5, 40, TOP_BTN_HEIGHT, 0x00aa00))
		core.addModule("Network");
	if (_display.button("HOST", 5 + 45 * 4, 5, 40, TOP_BTN_HEIGHT, 0x00aa00))
		core.addModule("Intel(R) Core(TM) i5-3470S");
	if (_display.button("TIME", 5 + 45 * 5, 5, 40, TOP_BTN_HEIGHT, 0x00aa00))
		core.addModule("uptime");
	int curr_x = LEFT_OFFSET;
	int curr_y = TOP_OFFSET;
	for (iterator it = modules.begin(); it != modules.end(); it++)
	{
		if (renderModule(*it->second, curr_x, curr_y, core))
			return ;
		curr_y += MODULE_GAP;
	}

	_display.draw();
}

int	 BeautifulDisplay::_calculateTotalHeight(const std::map<std::string, IMonitorModule*> &modules) const {
    int height= 0;

    height += TOP_OFFSET;// + TOP_BTN_HEIGHT;

    typedef std::map<std::string, IMonitorModule*>::const_iterator iterator;
    for (iterator it = modules.begin(); it != modules.end(); it++)
    {
        height += _calculateModuleHeight(it->second);
    }
    height += MODULE_GAP * (modules.size() - 1);
    height += BOTTOM_OFFSET;
    return height;
}

int	 BeautifulDisplay::_calculateModuleHeight(const IMonitorModule* module) const {
    int height = 0;
    height += TITLE_HEIGHT;
    height += DATA_HEIGHT * module->getData().size();
    height += GRAPH_HEIGHT * module->getGraphs().size(); // to change
    height += MODULE_GAP * ((module->getGraphs().size() > 0) ? module->getGraphs().size() -1 : 0 ); // to change
    return height;
}
float   BeautifulDisplay::_scale(size_t x, std::deque<float> data, const IMonitorModule& module) const {
	float range = 0;

	if (module.getGraphMax() == -1)
		range = *std::max_element(data.begin(), data.end()) - module.getGraphMin();
	else
		range = module.getGraphMax() - module.getGraphMin();
	return data[x] / range;
}
