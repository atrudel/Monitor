#ifndef MAINCPU_HPP
#define MAINCPU_HPP

#include <iostream>
#include <map>
#include <deque>
#include <sys/sysctl.h>
#include <mach/mach_init.h>
#include <mach/mach_error.h>
#include <mach/mach_host.h>
#include <mach/vm_map.h>

#include "IMonitorModule.hpp"

#define BUFFERLEN 128
#define DEQUE_SIZE 100

class MainCpu : public IMonitorModule
{
  public:
    MainCpu(void);
    MainCpu(MainCpu const &src);
    virtual ~MainCpu(void);

    MainCpu &operator=(MainCpu const &rhs);

    void fetch(void);
    void update(void);

    void setName(std::string name);
    virtual const std::string &getName(void) const;

    virtual const std::map< std::string, std::deque<float> > &getGraphs(void) const;
    virtual const float &getGraphMin(void) const;
    virtual const float &getGraphMax(void) const;
    virtual const std::map<std::string, std::string> &getData(void) const;

    float CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks);
    float GetCPULoad();
    void dequeUpdate(std::string name, float ret);
    

  private:
    std::string _name;
    float _min;
    float _max;
    std::map< std::string, std::deque<float> > _graphs;
    std::map<std::string, std::string> _data;
    static unsigned long long _previousTotalTicks;
    static unsigned long long _previousIdleTicks;
};


#endif //MAINCPU_HPP
