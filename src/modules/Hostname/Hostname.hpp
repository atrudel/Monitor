#ifndef HOSTNAME_HPP
#define HOSTNAME_HPP

#include <iostream>
#include <map>
#include <queue>
#include <sys/sysctl.h>

#include "IMonitorModule.hpp"

#define BUFFERLEN 128

class Hostname : public IMonitorModule
{
  public:
    Hostname(void);
    Hostname(Hostname const &src);
    ~Hostname(void);

    Hostname &operator=(Hostname const &rhs);

    void fetch(void);
    void update(void);

    void setName(std::string name);
    std::string getName(void) const;
    std::map< std::string, std::queue<float> > getGraphs(void) const;
    std::map<std::string, std::string> getData(void) const;

  private:
    std::string _name;
};

Hostname::Hostname(void)
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
std::map< std::string, std::queue<float> > Hostname::getGraphs(void) const
{
    return std::map<std::string, std::queue<float> >();
}

std::map<std::string, std::string> Hostname::getData(void) const
{
    return std::map<std::string, std::string>();
}
std::string Hostname::getName(void) const
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
