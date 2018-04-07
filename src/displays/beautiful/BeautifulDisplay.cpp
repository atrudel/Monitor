
#include "BeautifulDisplay.hpp"

BeautifulDisplay::BeautifulDisplay(void) {
    return;
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

void BeautifulDisplay::init(void) {
    return;
}

void BeautifulDisplay::update(void) {
    return;
}

void BeautifulDisplay::render(const std::map<std::string, IMonitorModule*> &disp) const {
    (void) disp;
    return;
}

void BeautifulDisplay::close(void) {
    return;
}