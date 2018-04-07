#ifndef DUMMYMODULE_HPP
# define DUMMYMODULE_HPP

#include "IMonitorModule.hpp"

class DummyModule : public IMonitorModule{

public:
    DummyModule(void);
    DummyModule(const DummyModule& src);
    virtual ~DummyModule(void);
    DummyModule& operator=(const DummyModule& rhs);

    virtual void fetch(void);
    virtual void update(void);
    virtual const std::string &getName(void) const;
    virtual const std::map<std::string, std::deque<float> > &getGraphs(void) const;
    virtual const std::map<std::string, float> &getGraphsMin(void) const;
    virtual const std::map<std::string, float> &getGraphsMax(void) const;
    virtual const std::map<std::string, std::string> &getData(void) const;
private:
    std::string const                           _name;
    std::map<std::string, std::deque<float> >   _graphs;
    std::map<std::string, float>                _graphs_min;
    std::map<std::string, float>                _graphs_max;
    std::map<std::string, std::string>          _data;
};


#endif
