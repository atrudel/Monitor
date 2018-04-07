
#include "OSModule.hpp"
#include <mach-o/dyld.h>
#include <sys/sysctl.h>
#include "IMonitorModule.hpp"

OSModule::OSModule(void)
{


    char str[256];
    size_t size = sizeof(str);
    int ret = sysctlbyname("kern.osrelease", str, &size, NULL, 0);

    // this->_name = NULL;
    

    // this->_graphs;
    // this->_datas = NULL;
}

  void OSModule::fetch(void) {} ;
  
  void OSModule::update(void) {} ;

    std::map<std::string, std::queue<float> > OSModule::getGraphs(void) const 
    {
        return std::map<std::string, std::queue<float> >();
    }

  std::map<std::string, std::string> OSModule::getData(void) const 
  {
      return std::map<std::string, std::string>();
    }

OSModule::OSModule(OSModule const &src)
{
    *this = src;
}

OSModule::~OSModule()
{
    //
}

std::string OSModule::getName(void) const
{
    return (this->_name);
}

OSModule &OSModule::operator=(OSModule const &rhs) {

    // this->_foo = rhs.getValue();
    return *this;
}