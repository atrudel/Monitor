#ifndef CORE_HPP
# define CORE_HPP

# include <unistd.h>
# include <iostream>
# include <vector>
# include <map>
# include <string>

# include "displays/IMonitorDisplay.hpp"
# include "displays/beautiful/BeautifulDisplay.hpp"
# include "modules/IMonitorModule.hpp"
# include "displays/ncurses/NcursesDisplay.hpp"

# include "modules/time/TimeModule.hpp"
# include "modules/mainCpu/MainCpu.hpp"
# include "modules/Network/NetworkModule.hpp"
# include "modules/Cat/Cat.hpp"
# include "modules/memory/MainMemory.hpp"
#include "modules/Hostname/Hostname.hpp"
#include "modules/Os/OSModule.hpp"
#include "modules/time/TimeModule.hpp"

// # include "displays/dummy/DummyDisplay.hpp"
// # include "modules/dummy/DummyModule.hpp"
# include "modules/Hostname/Hostname.hpp"

#define SIZE_OPT	10

class IMonitorModule;
class IMonitorDisplay;

class Core
{
private:
	bool									_running;
	std::vector<IMonitorDisplay*>			_displays;
	std::map<std::string, IMonitorModule*>	_modules;
	int										_activeDisplayIndex;


public:
	Core();

	Core(const Core &o);

	virtual ~Core();

	Core &operator=(const Core &o);

	void init(char display_options[SIZE_OPT]);
	void update();
	void render();

	void start(char display_options[SIZE_OPT]);
	void stop();
	void loop();

	void deleteModule(std::string);
	void addModule(std::string);
	void test(int iterations);
};

#endif
