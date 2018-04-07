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
    virtual void render(void) const;
    virtual void close(void);

private:
    std::map<std::string, IMonitorModule*>&	_modules;
    void                                    _displayModule(IMonitorModule*);
    void                                    _printData(std::map<std::string, std::string>& data);
    void                                    _printGraphs(std::map<std::string, std::deque<float> >);
    void                                    _printQueue(std::deque<float> queue){
};


#endif
