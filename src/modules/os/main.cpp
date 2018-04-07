#include <iostream>
#include "OSModule.hpp"
#include "../../../includes/IMonitorModule.hpp"


int		main(void)
{
	IMonitorModule* truc = new OSModule;

	delete truc;
	return 1;
}
