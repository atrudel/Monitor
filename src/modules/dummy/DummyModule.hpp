#ifndef DUMMYMODULE_HPP
# define DUMMYMODULE_HPP

#include "../IMonitorModule.hpp"

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
    virtual const float &getGraphMin(void) const;
    virtual const float &getGraphMax(void) const;
    virtual const std::map<std::string, std::string> &getData(void) const;
private:
    std::string const                           _name;
    std::map<std::string, std::deque<float> >   _graphs;
    float                                       _graph_min;
    float                                       _graph_max;
    std::map<std::string, std::string>          _data;
    static int                                  _i;
};


#endif
