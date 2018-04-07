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

  virtual const std::string &getName(void) const;
  virtual const std::map<std::string, std::deque<float> > &getGraphs(void) const;
  virtual const std::map<std::string, std::string> &getData(void) const;
  virtual const std::map<std::string, float> &getGraphsMin(void) const;
  virtual const std::map<std::string, float> &getGraphsMax(void) const;


  private:

  void set_osrelease(void);
  void set_osname(void);
  void set_osversion(void);
  
    std::string _name;
    std::map<std::string, float> _graphMin;
    std::map<std::string, float> _graphMax;
    std::map<std::string, std::deque<float> > _graphs;
    std::map<std::string, std::string> _datas;
};

#endif