#include "DummyModule.hpp"

#define QUEUE_SIZE 10

DummyModule::DummyModule(void): _name("Dummy") {
    _graphs["dummy1"] = std::deque<float>(QUEUE_SIZE);
    _graphs["dummy2"] = std::deque<float>(QUEUE_SIZE);
    _graphs_max["dummy1"] = _graphs_max["dummy2"] = 100;
    _graphs_min["dummy1"] = _graphs_min["dummy2"] = 0;
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
const std::string & DummyModule::getName(void) const {
    return _name;
}
const std::map<std::string, std::deque<float> > & DummyModule::getGraphs(void) const{
    return _graphs;
}

const std::map<std::string, std::string> & DummyModule::getData(void) const {
    return _data;
}
const std::map<std::string, float>& DummyModule::getGraphsMin(void) const {
    return _graphs_min;
}
const std::map<std::string, float>& DummyModule::getGraphsMax(void) const {
    return _graphs_max;
}

void    DummyModule::fetch() {
    return;
}

void    DummyModule::update() {
    float dummy1 = rand() % 100;

    _graphs["dummy1"].push_back(dummy1);
    float dummy2 = rand() % 100;
    _graphs["dummy2"].push_back(dummy2);
    _data["dummy1"] = std::to_string(dummy1) + "%";
    _data["dummy2"] = std::to_string(dummy2) + "%";
}
