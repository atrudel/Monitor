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

void DummyDisplay::render(void) const {
    std::for_each(_modules.begin(), _modules.end(), _displayModule)
}

void DummyDisplay::close(void) {

}

void DummyDisplay::_printData(std::map<std::string, std::string>& data){
    for (std::map<std::string, std::string>::iterator i = data.begin(); i != data.end() ; i++) {
        std::cout << i->first << ": " << i->second << std::endl;
    }
}
void DummyDisplay::_printGraphs(std::map<std::string, std::deque<float> > graphs) {
    for (std::map<std::string, std::deque<float> >::iterator i; i != graphs.end()){
        std::cout << i->first << ": " << std::endl;
        _printQueue(i->second);
        std::cout << std::endl;
    }
}
void DummyDisplay::_printQueue(std::deque<float> queue){
    for(std::iterator i = queue.begin(); i != queue.end(); i++){
        std::cout << *i << " | ";
    }
    std::cout << std::endl;
}
void DummyDisplay::_displayModule(IMonitorModule* module) {
    module =
    std::cout << "===========================  DISPLAYING module named " << module->getName() << " ======================" << std::endl;
    std::cout << std::endl;
    std::cout << "---------- Data --------" << std::endl << std::endl;
    _printData(module->getData());
    std::cout  << std::endl;
    std::cout << "---------- Graphs -------" << std::endl << std::endl;
    std::cout << "min: " << module->getGraphsMin() << "      max: " << module->getGraphsMax() << std::endl;
    _printGraphs(module->getGraphs());
}

