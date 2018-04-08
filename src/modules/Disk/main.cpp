#include <iostream>
#include "NetworkModule.hpp"
#include "../IMonitorModule.hpp"
#include <unistd.h>


int		main(void)
{
	std::map<std::string, std::string> tmp;
	std::map<std::string, std::deque<float> > tmpgraph;
	IMonitorModule* truc = new NetworkModule();

	for (int i = 0; i < 1000; i++)
	{
		truc->update();
		tmp = truc->getData();
		tmpgraph = truc->getGraphs();

		std::cout << tmp["pk_in"] << std::endl;
		std::cout << tmp["pk_out"]<< std::endl;
		std::cout << tmp["in_b"] << std::endl;
		std::cout << tmp["out_b"] << std::endl;


		for (int j=0;j<tmpgraph["ins"].size();j++)
		{
  		   std::cout <<  tmpgraph["ins"][j] <<  " ";
		}
		std::cout << std::endl;
		
				
		usleep(1000000);
		// tmpgraph["ins"].begin();
		// tmpgraph["outs"].begin();
		// std::cout << "In/s " << *tmpgraph["ins"].begin() << std::endl;
		// std::cout << "Out/s " << *tmpgraph["outs"].begin() << std::endl;
	}


	return 1;
}
