#include <iostream>
#include "os/OSModule.hpp"
#include "IMonitorModule.hpp"
#include "Hostname/Hostname.hpp"

int		main(void)
{
	IMonitorModule* truc = new OSModule;
	IMonitorModule* plop = new Hostname;

		plop->update();
	for (int i = 0; i< 1000; i++)
	{
		std::cout << plop->getName() << std::endl;
		std::cout << std::endl;
		std::cout << truc->getName() << std::endl;
		std::cout << std::endl;
	}

	delete plop;
	delete truc;
	return 1;
}
