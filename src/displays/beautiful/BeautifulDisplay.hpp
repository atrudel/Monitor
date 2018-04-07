#ifndef MONITOR_BEAUTIFULDISPLAY_HPP
# define MONITOR_BEAUTIFULDISPLAY_HPP

#include "../IMonitorDisplay.hpp"
#include "../../modules/IMonitorModule.hpp"

class BeautifulDisplay : public IMonitorDisplay {

public:
    BeautifulDisplay(void);
    BeautifulDisplay(const BeautifulDisplay& src);
    virtual ~BeautifulDisplay(void);

    BeautifulDisplay& operator=(const BeautifulDisplay& rhs);
    virtual void init(void);
    virtual void update(void);
    virtual void render(void) const;
    virtual void close(void);

private:
    std::map<std::string, IMonitorModule*>&	_modules;
    bool                                    _check_module_info(IMonitorModule*);
};


#endif
