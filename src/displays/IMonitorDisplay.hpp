#ifndef IMONITORDISPLAY_HPP
#define IMONITORDISPLAY_HPP

# include "../modules/IMonitorModule.hpp"

class Core;

class IMonitorDisplay
{
  public:
    virtual ~IMonitorDisplay(void){};

    virtual void init(void) = 0;
    virtual void update(void) = 0;
	virtual void render(const std::map<std::string, IMonitorModule*> &disp, Core &core) = 0;
};

#endif //  IMONITORDISPLAY_HPP
