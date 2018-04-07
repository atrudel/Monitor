
#include "OSModule.hpp"
#include <mach-o/dyld.h>
#include <sys/sysctl.h>
#include "IMonitorModule.hpp"

OSModule::OSModule(void) : _name(""), _graphMin(0), _graphMax(0), _graphs(std::map<std::string, std::deque<float> >()), _datas(std::map<std::string, std::string>())
{
    set_osrelease();
    this->_name += " "; 
    set_osname();
    this->_name += " "; 
    set_osversion();
}

OSModule::~OSModule()
{
    //
}

void OSModule::set_osname()
{

    const char*     strtmp ="sw_vers -productName";
    char str[256];

    FILE*           ret = popen(strtmp, "r");

    if (!ret)
        return ;

    while(!feof(ret)) {
       fgets(str, 256, ret);
    }

    this->_name += strtok(str, "\n");

    pclose(ret);
}

void OSModule::set_osversion()
{
    const char*     strtmp ="sw_vers -productVersion";
    char str[256];

    FILE*           ret = popen(strtmp, "r");

    if (!ret)
        return ;

   
    while(!feof(ret)) {
       fgets(str, 256, ret);
    }

    this->_name += strtok(str, "\n");

    pclose(ret);
}

void OSModule::set_osrelease()
{
    char str[256];
    size_t size = sizeof(str);
    int ret = sysctlbyname("kern.osrelease", str, &size, NULL, 0);

    this->_name += str;
}


  void OSModule::update(void) {
  }

const std::map<std::string, std::deque<float> > &OSModule::getGraphs(void) const 
    {
        return this->_graphs;
    }

const float &OSModule::getGraphMin(void) const 
{
        return this->_graphMin;
}
 const float &OSModule::getGraphMax(void) const 
 {
    return this->_graphMax;
 }

const std::map<std::string, std::string> &OSModule::getData(void) const 
  {
      return this->_datas;
    }

OSModule::OSModule(OSModule const &src)
{
    *this = src;
}


const std::string &OSModule::getName(void) const
{
    return (this->_name);
}

OSModule &OSModule::operator=(OSModule const &rhs) {

    // this->_foo = rhs.getValue();
    return *this;
}