#include "MainCpu.hpp"

MainCpu::MainCpu(void) : _name("CPU"), _min(0.0f), _max(100.0f), _graphs(std::map< std::string, std::deque<float> >()), _data(std::map<std::string, std::string>())
{
    this->update();
}

MainCpu::MainCpu(MainCpu const &src)
{
    *this = src;
}

MainCpu::~MainCpu()
{
}

void MainCpu::fetch(void)
{
}


void MainCpu::setCPUsLoad()
{
    natural_t                       cpuCount;
    processor_cpu_load_info_t       cpuInfo;
    mach_msg_type_number_t          nbInfo;
    size_t    totalSystemTime = 0, totalUserTime = 0, totalIdleTime = 0;

    if (host_processor_info(mach_host_self(),
                        PROCESSOR_CPU_LOAD_INFO,
                        &cpuCount,
                        reinterpret_cast<processor_info_array_t *>(&cpuInfo),
                        &nbInfo) != KERN_SUCCESS)
        throw std::runtime_error("cpu module: host_processor_info failed");

    for (natural_t i = 0; i < cpuCount; i++)
    {
        if (i >= WORLD_WIDE_MAX_CPU_ON_UNIT)
            throw std::runtime_error("cpu error: world wide max cpu record beaten");
        size_t system = cpuInfo[i].cpu_ticks[CPU_STATE_SYSTEM];
        size_t user = cpuInfo[i].cpu_ticks[CPU_STATE_USER] + cpuInfo[i].cpu_ticks[CPU_STATE_NICE];
        size_t idle = cpuInfo[i].cpu_ticks[CPU_STATE_IDLE];

        std::ostringstream ss;
        ss << "cpu" << i << "Usage";

        dequeUpdate(ss.str(), calculateCPULoad(system + user, _oldCpusWorkTicks[i], system + user + idle, _oldCpusTotalTicks[i]));
        
        _oldCpusWorkTicks[i] = system + user;
        _oldCpusTotalTicks[i] = system + user + idle;

        totalSystemTime += system;
        totalUserTime += user;
        totalIdleTime += idle;
    }
       std::cout << std::endl
                  << this->getName() << std::endl;

    size_t newTotal = totalIdleTime + totalSystemTime + totalUserTime;
    size_t newWork = totalSystemTime + totalUserTime;

    dequeUpdate("cpuTotalUsage", calculateCPULoad(newWork, _oldWorkTicks, newTotal, _oldTotalTicks));

    _oldTotalTicks = newTotal;
    _oldWorkTicks = newWork;
}

float MainCpu::calculateCPULoad(size_t newWorkTicks, size_t oldWorkTicks,  size_t newTotalTicks, size_t oldTotalTicks)
{
    float work = newWorkTicks - oldWorkTicks;
    float total = newTotalTicks - oldTotalTicks;
    if (!total)
        return 0.0f;
    return work / total * 100;
}

void MainCpu::dequeUpdate(std::string name, float ret)
{
    if (!this->_graphs[name].empty())
    {
        while (this->_graphs[name].size() > DEQUE_SIZE)
            this->_graphs[name].pop_front();
        this->_graphs[name].push_back(ret);
    }
    else
        this->_graphs[name] = std::deque<float>(DEQUE_SIZE, 0);
}

void MainCpu::update(void)
{
    char buff[BUFFERLEN];
    size_t buffLen = BUFFERLEN;

    this->setCPUsLoad();
}

const float &MainCpu::getGraphMin(void) const
{
    return this->_min;
}

const float &MainCpu::getGraphMax(void) const
{
    return this->_max;
}

const std::map< std::string, std::deque<float> > &MainCpu::getGraphs(void) const
{
    return this->_graphs;
}

const std::map<std::string, std::string> &MainCpu::getData(void) const
{
    return this->_data;
}

const std::string &MainCpu::getName(void) const
{
    return this->_name;
}

void MainCpu::setName(std::string name)
{
    this->_name = name;
}

MainCpu &MainCpu::operator=(MainCpu const &rhs)
{
    this->_name = rhs.getName();
    return *this;
}