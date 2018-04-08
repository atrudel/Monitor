#ifndef NETWORKMODULE_HPP
#define NETWORKMODULE_HPP

#include <sys/sysctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <net/route.h>
#include <iostream>
#include <sstream>
#include "../IMonitorModule.hpp"

#define DEQUE_SIZE 400

class NetworkModule : public IMonitorModule
{
  public:
    NetworkModule(void);
    NetworkModule(NetworkModule const &src);
    virtual  ~NetworkModule(void);

    NetworkModule &operator=(NetworkModule const &rhs);

  virtual void update(void);

  virtual const std::string &getName(void) const;
  virtual const std::map<std::string, std::deque<float> > &getGraphs(void) const;
  virtual const std::map<std::string, std::string> &getData(void) const;
  virtual const float &getGraphMin(void) const;
  virtual const float &getGraphMax(void) const;

  void reset_net();
  void dequeUpdate(std::string name, float ret);

  private:
    std::string _name;
    float _graphMin;
    float _graphMax;
    std::map<std::string, std::deque<float> > _graphs;
    std::map<std::string, std::string> _datas;
    float _lastin;
    float _lastout;
    int _time;
};

#endif