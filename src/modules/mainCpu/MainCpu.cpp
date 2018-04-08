#include "MainCpu.hpp"

unsigned long long MainCpu::_previousTotalTicks = 0;
unsigned long long MainCpu::_previousIdleTicks = 0;

MainCpu::MainCpu(void) : _name("CPU"), _min(0.0f), _max(100.0f), _graphs(std::map< std::string, std::deque<float> >()), _data(std::map<std::string, std::string>())
{
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

float MainCpu::CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
	unsigned long long totalTicksSinceLastTime = totalTicks - this->_previousTotalTicks;
	unsigned long long idleTicksSinceLastTime = idleTicks - this->_previousIdleTicks;

	float ret = 1.0f - ((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime) / totalTicksSinceLastTime : 0);

	this->_previousTotalTicks = totalTicks;
	this->_previousIdleTicks = idleTicks;
	return ret;
}

float MainCpu::GetCPULoad()
{
	host_cpu_load_info_data_t cpuinfo;
	mach_msg_type_number_t count;
	count = HOST_CPU_LOAD_INFO_COUNT;
	std::memset(&cpuinfo, 0, sizeof(host_cpu_load_info_data_t));
	if (host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, (host_info_t)&cpuinfo, &count) == KERN_SUCCESS)
	{
		unsigned long long totalTicks = 0;
		for (int i = 0; i < CPU_STATE_MAX; i++)
		{
//			std::cout << "by cpu " << cpuinfo.cpu_ticks[i] << std::endl;
			totalTicks += cpuinfo.cpu_ticks[i];
		}

		// std::cout << "in get cpu load " << this->CalculateCPULoad(cpuinfo.cpu_ticks[CPU_STATE_IDLE], totalTicks) << std::endl;
		return this->CalculateCPULoad(cpuinfo.cpu_ticks[CPU_STATE_IDLE], totalTicks);
	}
	else
		return -1.0f;
}

void MainCpu::dequeUpdate(std::string name, float ret)
{
	if (!this->_graphs[name].empty())
	{
		if (this->_graphs[name].size() >= DEQUE_SIZE)
			this->_graphs[name].pop_back();
		this->_graphs[name].push_front(ret);
	}
	else
		this->_graphs[name] = std::deque<float>(DEQUE_SIZE, -1);
}

void MainCpu::update(void)
{
//	char buff[BUFFERLEN];
//	size_t buffLen = BUFFERLEN;

	float ret = this->GetCPULoad();
//	std::cout << "ret val" << ret << std::endl;

	MainCpu::dequeUpdate("cpuUsage", ret);
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