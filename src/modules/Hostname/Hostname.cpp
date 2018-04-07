#include <iostream>
#include <map>
#include <deque>
#include <sys/sysctl.h>

#include "IMonitorModule.hpp"
#include "Hostname.hpp"

Hostname::Hostname(void): _name(""), _min(std::map<std::string, float>()), _max(std::map<std::string, float>()), _graphs(std::map< std::string, std::deque<float> >()), _data(std::map<std::string, std::string>())
{
}

Hostname::Hostname(Hostname const &src)
{
    *this = src;
}

Hostname::~Hostname()
{
}
void Hostname::fetch(void)
{
}
void Hostname::update(void)
{
    char buff[BUFFERLEN];
    size_t buffLen = BUFFERLEN;

    sysctlbyname("kern.hostname", &buff, &buffLen, NULL, 0);

    std::string name(buff);
    std::cout << name << std::endl;
    this->setName(name);
}

const std::map<std::string, float> &Hostname::getGraphsMin(void) const
{
    return this->_min;
}

const std::map<std::string, float> &Hostname::getGraphsMax(void) const
{
    return this->_max;
}

const std::map< std::string, std::deque<float> > &Hostname::getGraphs(void) const
{
    return this->_graphs;
}

const std::map<std::string, std::string> &Hostname::getData(void) const
{
    return this->_data;
}
const std::string &Hostname::getName(void) const
{
    return this->_name;
}

void Hostname::setName(std::string name)
{
    this->_name = name;
}

Hostname &Hostname::operator=(Hostname const &rhs)
{
    this->_name = rhs.getName();
    return *this;
}
