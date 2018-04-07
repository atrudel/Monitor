#ifndef OSMODULE_HPP
#define OSMODULE_HPP

#include "../../../includes/IMonitorModule.hpp"

class OSModule : public IMonitorModule
{
  public:
    OSModule(void);
    OSModule(OSModule const &src);
    virtual  ~OSModule(void);

    OSModule &operator=(OSModule const &rhs);

  virtual void fetch(void);
  virtual void update(void);

  virtual std::string getName(void) const;
  virtual std::map<std::string, std::queue<float> > getGraphs(void) const;
  virtual std::map<std::string, std::string> getData(void) const;

  private:
    std::string _name;
};

#endif