#ifndef MONITOR_BEAUTIFULDISPLAY_HPP
# define MONITOR_BEAUTIFULDISPLAY_HPP

#include "SdlDisplay.hpp"
#include "../IMonitorDisplay.hpp"

class BeautifulDisplay : public IMonitorDisplay {

public:
    BeautifulDisplay(void);
    BeautifulDisplay(const BeautifulDisplay& src);
    virtual ~BeautifulDisplay(void);

    BeautifulDisplay& operator=(const BeautifulDisplay& rhs);

	void init(void);
    void update(void);
	void render(const std::map<std::string, IMonitorModule*> &module);

private:
	SdlDisplay	_display;

};


#endif
