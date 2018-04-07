#ifndef HOSTNAME_HPP
#define HOSTNAME_HPP

#include <iostream>
#include <map>
#include <deque>
#include <sys/sysctl.h>

#include "IMonitorModule.hpp"

#define BUFFERLEN 128

class Hostname: public IMonitorModule
{
  public:
    Hostname(void);
    Hostname(Hostname const &src);
    virtual ~Hostname(void);

    Hostname &operator=(Hostname const &rhs);

    void fetch(void);
    void update(void);

    void    setName(std::string name);
    virtual const std::string   &getName(void) const;
    virtual const std::map< std::string, std::deque<float> >    &getGraphs(void) const;
    virtual const std::map<std::string, float>      &getGraphsMin(void) const;
    virtual const std::map<std::string, float>      &getGraphsMax(void) const;
    virtual const std::map<std::string, std::string>    &getData(void) const;

  private:
    std::string _name;
    std::map<std::string, float> _min;
    std::map<std::string, float> _max;
    std::map< std::string, std::deque<float> > _graphs;
    std::map<std::string, std::string> _data;
};

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
void Hostname::update(void)
{
}
void Hostname::fetch()
{
    char buff[BUFFERLEN];
    size_t buffLen = BUFFERLEN;

    sysctlbyname("kern.hostname", &buff, &buffLen, NULL, 0);

    std::string name(buff);
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

#endif //HOSTNAME_HPP
