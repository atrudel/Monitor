#include "Core.hpp"

Core::Core()
	: _running(false)
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

}

void Core::update()
{

}

void Core::render()
{

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
	int time = 0;
	double tickTime = 1000000.0 / 60.0;
	clock_t beforeTime = clock();
	while (_running)
	{
		clock_t currentTime = clock();
		if (currentTime - beforeTime > tickTime)
		{
			time++;
			if (time % 60 == 0)
				std::cout << (time / 60) << " seconds..." << std::endl;
			update();
			render();
			beforeTime = clock();
		}
	}
}