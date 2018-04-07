#include "Time.hpp"

TimeModule::TimeModule() : _name("uptime"), _min(0), _max(0) {}
TimeModule::~TimeModule(void) {}

void TimeModule::fetch(void) {}
void TimeModule::update(void)
{
    _data["uptime"] = this->uptime();
    _data["now"] = this->now();
}

const std::string &TimeModule::getName(void) const
{
    return _name;
}

const std::map<std::string, std::deque<float>> &TimeModule::getGraphs(void) const
{
    return _graphs;
}

const std::map<std::string, std::string> &TimeModule::getData(void) const
{
    return _data;
}

const float &TimeModule::getGraphsMin(void) const
{
    return _min;
}

const float &TimeModule::getGraphsMax(void) const
{
    return _max;
}

/* PRIVATE SECTION */

std::string TimeModule::uptime()
{
    struct timeval boottime;
    size_t len = sizeof(boottime);
    int mib[2] = {CTL_KERN, KERN_BOOTTIME};
    if (sysctl(mib, 2, &boottime, &len, NULL, 0) < 0)
        return "-1.0";
    time_t bsec = boottime.tv_sec, csec = time(NULL);

    return this->timeToString(difftime(csec, bsec));
}

std::string TimeModule::now()
{
    return this->timeToString(std::time(NULL));
}

std::string TimeModule::timeToString(time_t time)
{
    std::tm *ptm = std::localtime(&time);
    char buffer[32];
    // Format: Mo, 15.06.2009 20:20:00
    std::strftime(buffer, 32, "%a, %d.%m.%Y %H:%M:%S", ptm);
    std::string result(buffer);
    return result;
}