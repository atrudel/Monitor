#ifndef DUMMYMODULE_HPP
# define DUMMYMODULE_HPP

#include "IMonitorModule.hpp"

class DummyModule : IMonitorModule{

public:
    DummyModule(void);
    DummyModule(const DummyModule& src);
    virtual ~DummyModule(void);
    DummyModule& operator=(const DummyModule& rhs);

private:
    std::string const                           _name;
    std::map<std::string, std::deque<float> >   _graphs;
    std::map<std::string, std::string>          _data;
};


#endif
