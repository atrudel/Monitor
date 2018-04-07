#ifndef CORE_HPP
# define CORE_HPP

# include <iostream>
# include <vector>
# include <map>
# include "displays/IMonitorDisplay.hpp"
# include "modules/IMonitorModule.hpp"


class Core
{
private:
	bool									_running;
	std::vector<IMonitorDisplay*>			_displays;
	std::map<std::string, IMonitorModule*>	_modules;

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
};

#endif
