#include "Time.hpp"

int main()
{
    std::map<std::string, std::string> result;
    
    IMonitorModule *time = new TimeModule;
    time->update();

    result = time->getData();
    std::cout << result["uptime"] << std::endl;
    
    return 0;
}