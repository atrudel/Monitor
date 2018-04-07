#include "MainCpu.hpp"
#include <unistd.h>

int main()
{
    MainCpu toto;
    for (int i=0; i < 50; i++){
        usleep(1000);
        std::cout << toto.GetCPULoad() << std::endl;
    }
    // std::map< std::string, std::deque<float> > pouet = toto.getGraphs();
    // for (std::deque<float>::iterator it = pouet["cpuUsage"].begin(); it!=pouet["cpuUsage"].end(); ++it)
    //     std::cout << ' ' << *it;
    // std::cout << std::endl << toto.getName() << std::endl;
    return 0;
}
