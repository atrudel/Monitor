#ifndef MONITOR_DUMMYDISPLAY_HPP
# define MONITOR_DUMMYDISPLAY_HPP

#include "../IMonitorDisplay.hpp"
#include "../../modules/IMonitorModule.hpp"

class DummyDisplay : public IMonitorDisplay {

public:
    DummyDisplay(void);
    DummyDisplay(const DummyDisplay& src);
    virtual ~DummyDisplay(void);

    DummyDisplay& operator=(const DummyDisplay& rhs);
    virtual void init(void);
    virtual void update(void);
    virtual void render(const std::map<std::string, IMonitorModule*> &disp);
    virtual void close(void);

private:
    void _displayModule(const IMonitorModule*) const;
    void _printData(const std::map<std::string, std::string>& data) const ;
    void _printGraphs(const std::map<std::string, std::deque<float> >) const ;
    void _printQueue(const std::deque<float> queue) const ;
};


#endif
