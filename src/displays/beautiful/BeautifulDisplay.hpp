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
    virtual void render(const std::map<std::string, IMonitorModule*> &disp) const;
    virtual void close(void);

private:

};


#endif
