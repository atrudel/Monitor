#ifndef CORE_HPP
# define CORE_HPP

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

// # include "displays/dummy/DummyDisplay.hpp"
// # include "modules/dummy/DummyModule.hpp"
# include "modules/Hostname/Hostname.hpp"

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

	void init();
	void update();
	void render();

	void start();
	void stop();
	void loop();

	void test();
};

#endif
