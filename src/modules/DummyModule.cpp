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

void    DummyModule::update() {
    float dummy1 = rand() % 100;
    _graphs_max["dummy1"] = _graphs_max["dummy2"] = 100;
    _graphs["dummy1"].push_back(dummy1);
    float dummy2 = rand() % 100;
    _graphs_min["dummy1"] = _graphs_min["dummy2"] = 0;
    _graphs["dummy2"].push_back(dummy2);
    _data["dummy1"] = std::string(dummy1) + "%";
    _data["dummy2"] = std::string(dummy2) + "%";
}

