#include "DummyDisplay.hpp"

DummyDisplay::DummyDisplay(void) {
    return;
}

DummyDisplay::DummyDisplay(const DummyDisplay& src) {
    *this = src;
    return;
}

DummyDisplay::~DummyDisplay(void) {
    return;
}

DummyDisplay& DummyDisplay::operator=(const DummyDisplay& rhs) {
    if (this != &rhs) {
        // TODO
    }
    return *this;
}

void DummyDisplay::init(void) {

}

void DummyDisplay::update(void) {

}

void DummyDisplay::render(const std::map<std::string, IMonitorModule*> &modules) {
    for (std::map<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, IMonitorModule*>::const_iterator i = modules.begin(); i != modules.end(); i++){
        _displayModule(i->second);
    }
}

void DummyDisplay::close(void) {

}

void DummyDisplay::_printData(const std::map<std::string, std::string>& data) const {
    for (std::map<std::string, std::string>::const_iterator i = data.begin(); i != data.end() ; i++) {
        std::cout << i->first << ": " << i->second << std::endl;
    }
}
void DummyDisplay::_printGraphs(const std::map<std::string, std::deque<float> > graphs) const {
    for (std::map<std::string, std::deque<float> >::const_iterator i = graphs.begin(); i != graphs.end(); i++){
        std::cout << i->first << ": " << std::endl;
        _printQueue(i->second);
        std::cout << std::endl;
    }
}
void DummyDisplay::_printQueue(const std::deque<float> queue) const {
    for(std::deque<float>::const_iterator i = queue.begin(); i != queue.end(); i++){
        std::cout << *i << " | ";
    }
    std::cout << std::endl;
}
void DummyDisplay::_displayModule(const IMonitorModule* module) const{
    std::cout << "===========================  DISPLAYING module named " << module->getName() << " ======================" << std::endl;
    if (!module->getData().empty()) {
        std::cout << "---------- Data --------" << std::endl << std::endl;
        _printData(module->getData());
        std::cout << std::endl;
    }
    if (!module->getGraphs().empty()) {
        std::cout << "---------- Graphs -------" << std::endl;
        std::cout << "min: " << module->getGraphMin() << "      max: " << module->getGraphMax() << std::endl;
        _printGraphs(module->getGraphs());
    }
    else
        std::cout << std::endl;
}

