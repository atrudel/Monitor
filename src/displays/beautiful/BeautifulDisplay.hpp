#ifndef MONITOR_BEAUTIFULDISPLAY_HPP
# define MONITOR_BEAUTIFULDISPLAY_HPP

#include "SdlDisplay.hpp"
#include "../IMonitorDisplay.hpp"
#include "../../modules/IMonitorModule.hpp"

// Contour
# define TOP_OFFSET     5
# define BOTTOM_OFFSET  5
# define LEFT_OFFSET    5
# define RIGHT_OFFSET   5

// Spacing between modules
# define MODULE_GAP     10

// Module elements
//** Y dimension
# define TITLE_HEIGHT   25
# define DATA_HEIGHT    15
# define GRAPH_HEIGHT   100

//** X dimension
# define LEFT_MARGIN_GR 100
# define GRAPH_WIDTH    DEQUE_SIZE


// Overall dimensions
# define TOTAL_WIDTH  (LEFT_OFFSET + LEFT_MARGIN_GR + GRAPH_WIDTH + RIGHT_OFFSET)
//** total height can be calculated using calculageTotalHeight() method


class BeautifulDisplay : public IMonitorDisplay {

public:
    BeautifulDisplay(void);
    BeautifulDisplay(const BeautifulDisplay& src);
    virtual ~BeautifulDisplay(void);

    BeautifulDisplay& operator=(const BeautifulDisplay& rhs);

	void renderModule(const IMonitorModule &module, int &curr_x, int &curr_y);
	void init(void);
    void update(void);
	void render(const std::map<std::string, IMonitorModule*> &modules);
	int	 calculateTotalHeight(const std::map<std::string, IMonitorModule*> &modules) const;
    int	 calculateModuleHeight(const IMonitorModule* module) const;
private:
	SdlDisplay	_display;
};

#endif
