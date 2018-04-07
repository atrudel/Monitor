#include "BeautifulDisplay.hpp"

BeautifulDisplay::BeautifulDisplay(void) {
    std::cout << "YOLO !" << std::endl;
}

BeautifulDisplay::BeautifulDisplay(const BeautifulDisplay& src) {
    *this = src;
    return;
}

BeautifulDisplay::~BeautifulDisplay(void) {
    return;
}

BeautifulDisplay& BeautifulDisplay::operator=(const BeautifulDisplay& rhs) {
    if (this != &rhs) {
        // TODO
    }
    return *this;
}

void BeautifulDisplay::init(void)
{

}

void BeautifulDisplay::update(void)
{

}

void BeautifulDisplay::render(const std::map<std::string, IMonitorModule*> &module) const
{
	(void) module;
	// typedef std::map<std::string, IMonitorModule*>::const_iterator iterator;
    //
	// for (iterator i = module.begin(); i != module.end(); i++)
	// 	std::cout << i->first << ": " << std::endl;
}
