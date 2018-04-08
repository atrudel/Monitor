#include "DummyModule.hpp"

int DummyModule::_i = 0;

DummyModule::DummyModule(void): _name("Dummy") {
    _graphs["dummy1"] = std::deque<float>(DEQUE_SIZE);
    _graphs["dummy2"] = std::deque<float>(DEQUE_SIZE);
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
    // Generate random percentages
    float dummy1 = rand() % 100;
    float dummy2 = rand() % 100;

    // Add to the graph queues
    _graphs["dummy1"].pop_back();
    _graphs["dummy1"].push_front(dummy1);
    _graphs["dummy2"].pop_back();
    _graphs["dummy2"].push_front(dummy2);

    // Update strings
    _data["dummy1"] = std::to_string(static_cast<int>(dummy1)) + "%";
    _data["dummy2"] = std::to_string(static_cast<int>(dummy2)) + "%";
    // Update data strings every second
}

const float& DummyModule::getGraphMin(void) const {
    return _graph_min;
}

const float& DummyModule::getGraphMax(void) const {
    return _graph_max;
}
