#ifndef MONITOR_BEAUTIFULDISPLAY_HPP
# define MONITOR_BEAUTIFULDISPLAY_HPP

#include <sstream>
#include <iomanip>
#include "SdlDisplay.hpp"
#include "../IMonitorDisplay.hpp"
#include "../../modules/IMonitorModule.hpp"
#include "../../Core.hpp"

// Contour
# define TOP_OFFSET     20
# define BOTTOM_OFFSET  5
# define LEFT_OFFSET    5
# define RIGHT_OFFSET   5

// Spacing between modules
# define MODULE_GAP     10

// Top buttom
# define TOP_BTN_HEIGHT 12

// Module elements
//** Y dimension
# define TITLE_HEIGHT   25
# define DATA_HEIGHT    15
# define GRAPH_HEIGHT   100

//** X dimension
# define LEFT_MARGIN_GR 130
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

	bool    renderModule(const IMonitorModule &module, int &curr_x, int &curr_y, Core &core);
	void    init(void);
    void    update(void);
	void    render(const std::map<std::string, IMonitorModule*> &modules, Core &core);

private:
    SdlDisplay							_display;
	int									_time;
	std::map	<std::string, float> 	_values;

    int     _calculateTotalHeight(const std::map<std::string, IMonitorModule*> &modules) const;
    int	    _calculateModuleHeight(const IMonitorModule* module) const;
    float   _scale(size_t x, std::deque<float> data, const IMonitorModule& module) const;
};

#endif
