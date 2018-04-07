#ifndef IMONITORDISPLAY_HPP
#define IMONITORDISPLAY_HPP

class IMonitorDisplay
{
  public:
    virtual ~IMonitorDisplay(void){};

    virtual void init(void) = 0;
    virtual void update(void) = 0;
    virtual void render(void) const = 0;
};

#endif //  IMONITORDISPLAY_HPP
