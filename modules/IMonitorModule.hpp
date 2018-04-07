#ifndef IMONITORMODULE_HPP
#define IMONITORMODULE_HPP

#include <iostream>
#include <map>
#include <queue>

class IMonitorModule
{

protected:
  virtual ~IMonitorModule(void);

  virtual IMonitorModule &operator=(IMonitorModule const &rhs) = 0;

  virtual std::string getName(void) const = 0;
  virtual std::map<std::string, std::queue<float> > getGraphs(void) const = 0;
  virtual std::map<std::string, std::string> getData(void) const = 0;

};

#endif //  IMONITORMODULE_HPP