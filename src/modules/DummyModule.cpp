#include "DummyModule.hpp"

DummyModule::DummyModule(void): _name("Dummy") {

    return;
}

DummyModule::DummyModule(const DummyModule& src) {
    *this = src;
    return;
}

DummyModule::~DummyModule(void) {
    return;
}

DummyModule& DummyModule::operator=(const DummyModule& rhs) {
    if (this != &rhs) {
        _graphs = rhs._graphs;
        _data = rhs._data;
    }
    return *this;
}
const std::string& DummyModule::getName(void) const {
    return _name;
}
const std::map<std::string, std::deque<float>> & DummyModule::getGraphs(void) const{
    return _graphs;
}
const std::map<std::string, std::string> & DummyModule::getData(void) const {
    return _data;
}

void    DummyModule::fetch() {
    _graphs["cpu1"].push_back(rand() % 80);
    _graphs["cpu2"].push_back(rand() % 80);
    _graphs._data["load"] = std::string(rand() % )
}

