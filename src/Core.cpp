#include "Core.hpp"

Core::Core()
	: _running(false),
	  _displays(std::vector<IMonitorDisplay*>()),
	  _modules(std::map<std::string, IMonitorModule*>()),
	  _activeDisplayIndex(0)
{
}

Core::Core(const Core &o)
{
	*this = o;
}

Core::~Core()
{
}

Core &Core::operator=(const Core &o)
{
	if (this != &o)
	{
		_running = o._running;
		_displays = o._displays;
		_modules = o._modules;
	}
	return *this;
}

void Core::init()
{
	_displays.push_back(new BeautifulDisplay());

//	_modules["time"] = new TimeModule();
	_modules["main_cpu"] = new MainCpu();
//	_modules["net"] = new NetworkModule();
//	_modules["main_cpu_2"] = new MainCpu();
//	_modules["Hostname"] = new Hostname();
	// _modules["ram"] = new RamModul();
}

void Core::update()
{
	typedef std::map<std::string, IMonitorModule*>::iterator iterator;

	for (iterator modul = _modules.begin(); modul != _modules.end(); modul++)
		modul->second->update();

	if (!_displays.empty())
		_displays[_activeDisplayIndex]->update();
}

void Core::render()
{
	if (!_displays.empty())
		_displays[_activeDisplayIndex]->render(_modules);
}

void Core::start()
{
	_running = true;

	init();
	loop();
}

void Core::stop()
{
	_running = false;
}

void Core::loop()
{
//	int seconds = 0;
	double tickTime = 1000000.0 / 60.0;
	clock_t beforeTime = clock();
	while (_running)
	{
		clock_t currentTime = clock();
		if (currentTime - beforeTime > tickTime)
		{
//			seconds++;
//			if (seconds % 60 == 0)
//				std::cout << (seconds / 60) << " seconds..." << std::endl;
			update();
			render();
			beforeTime = clock();
		}
	}
}

void Core::test()
{
    _displays.push_back(new DummyDisplay());

    // ADD YOUR MODULES HERE, AS A NEW ENTRY IN THE MAP
    _modules["dummy"] = new DummyModule();
    _modules["hostname"] = new Hostname();
//    _modules["os"] = new OSModule();
    _modules["time"] = new TimeModule();

    update();
    render();
}
