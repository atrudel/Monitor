#include "DummyModule.hpp"

#define QUEUE_SIZE 10

DummyModule::DummyModule(void): _name("Dummy") {
    _graphs["dummy1"] = std::deque<float>(QUEUE_SIZE);
    _graphs["dummy2"] = std::deque<float>(QUEUE_SIZE);
    _graph_min = 0;
    _graph_max = 100;
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


void    DummyModule::fetch() {
    std::cerr << "Fetch function (called on DummyModule) is deprecated" << std::endl;
    return;
}

void    DummyModule::update() {
    float dummy1 = rand() % 100;

    _graphs["dummy1"].push_back(dummy1);
    float dummy2 = rand() % 100;
    _graphs["dummy2"].push_back(dummy2);
    _data["dummy1"] = std::to_string(static_cast<int>(dummy1)) + "%";
    _data["dummy2"] = std::to_string(static_cast<int>(dummy2)) + "%";
}

const float& DummyModule::getGraphMin(void) const {
    return _graph_min;
}

const float& DummyModule::getGraphMax(void) const {
    return _graph_max;
}
