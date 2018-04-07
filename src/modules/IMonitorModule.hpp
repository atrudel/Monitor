#ifndef IMONITORMODULE_HPP
#define IMONITORMODULE_HPP

#include <iostream>
#include <map>
#include <queue>

class IMonitorModule
{

public:

  virtual ~IMonitorModule(void);

  virtual void fetch(void) = 0;
  virtual void update(void) = 0;

  virtual const std::string &getName(void) const = 0;
  virtual const std::map<std::string, std::deque<float> > &getGraphs(void) const = 0;
  virtual const std::map<std::string, std::string> &getData(void) const = 0;
};

#endif //  IMONITORMODULE_HPP