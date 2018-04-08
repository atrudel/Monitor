#include "MainCpu.hpp"
#include <unistd.h>

int main()
{
    MainCpu toto;
    for (int i = 0; i < 50; i++)
    {
        toto.update();
        usleep(1000000);
 
        std::map<std::string, std::deque<float> > pouet = toto.getGraphs();
        for (std::map<std::string, std::deque<float> >::iterator i = pouet.begin(); i != pouet.end(); ++i)
            for (std::deque<float>::iterator it = i->second.begin(); it != i->second.end(); ++it)
                // std::cout << ' ' << *it;
    }
    return 0;
}
