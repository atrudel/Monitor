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

# include "displays/dummy/DummyDisplay.hpp"
# include "modules/dummy/DummyModule.hpp"
# include "modules/Hostname/Hostname.hpp"

class IMonitorModule;
class IMonitorDisplay;

#define LIB_OPT		0b10000000
#define OS_OPT		0b00000001
#define CPU_OPT		0b00000010
#define RAM_OPT		0b00000100
#define TIME_OPT	0b00001000
#define NETWORK_OPT	0b00010000

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

	void init(int display_options);
	void update();
	void render();

	void start(int display_options);
	void stop();
	void loop();

	void test();
};

#endif
