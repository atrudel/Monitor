#ifndef IMONITORMODULE_HPP
#define IMONITORMODULE_HPP

#include <iostream>
#include <exception>
#include <map>
#include <queue>

#define DEQUE_SIZE 400

class IMonitorModule
{

public:
	virtual ~IMonitorModule(void) {};

    virtual void update(void) = 0;

    virtual const std::string &getName(void) const = 0;
    virtual const std::map<std::string, std::deque<float> > &getGraphs(void) const = 0;
    virtual const float &getGraphMin(void) const = 0;
    virtual const float &getGraphMax(void) const = 0;
    virtual const std::map<std::string, std::string> &getData(void) const = 0;
};

#endif //  IMONITORMODULE_HPP
