
#include "NetworkModule.hpp"

NetworkModule::NetworkModule(void) : _name("Network"), _graphMin(0), _graphMax(-1)
    , _graphs(std::map<std::string, std::deque<float> >()), _datas(std::map<std::string, std::string>())
{
    _time = 0;
    //
    reset_net();
}

NetworkModule::~NetworkModule()
{
    //
}

void NetworkModule::update(void)
{
    if ( _time % 60 == 0)
    {
        reset_net();
        _time = 0;
    }
    _time++;
}


void NetworkModule::reset_net()
{
    long int totalibytes = 0;
    long int totalobytes = 0;
    long int pkobytes = 0;
    long int pkibytes = 0;

    int ret;

    int mib[] = {
        CTL_NET,
        PF_ROUTE,
        0,
        0,
        NET_RT_IFLIST2,
        0
    };
    size_t len;
    ret = sysctl(mib, 6, NULL, &len, NULL, 0);
    char buf[len];
    ret = sysctl(mib, 6, buf, &len, NULL, 0);

    char *lim = buf + len;
    char *next = NULL;


    for (next = buf; next < lim; ) {
        struct if_msghdr *ifm = (struct if_msghdr *)next;
        next += ifm->ifm_msglen;
        if (ifm->ifm_type == RTM_IFINFO2) {
            struct if_msghdr2 *if2m = (struct if_msghdr2 *)ifm;

            if(if2m->ifm_data.ifi_type != 18)
            {
                totalibytes += if2m->ifm_data.ifi_ibytes;
                totalobytes += if2m->ifm_data.ifi_obytes;
                pkibytes += if2m->ifm_data.ifi_ipackets;
                pkobytes += if2m->ifm_data.ifi_opackets;
            }
        }
    }

    dequeUpdate("in (B/s)", static_cast<float>(pkibytes) - _lastin);
    dequeUpdate("out (B/s)", static_cast<float>(pkobytes) - _lastout);

    _lastin = static_cast<float>(pkibytes);
    _lastout = static_cast<float>(pkobytes);

    std::ostringstream stream;
    stream << static_cast<double>(totalibytes) / 1000000000.0;
    std::string str = stream.str().substr(0, 7);

    _datas["in_b"] = str.c_str();
    _datas["in_b"] += " Gb IN";

    std::ostringstream stream2;
    stream2 << static_cast<double>(totalobytes) / 1000000000.0;
    std::string str2 = stream2.str().substr(0, 7);

    _datas["out_b"] = str2.c_str();
    _datas["out_b"] += " Gb OUT";

     std::ostringstream stream3;
   stream3 << pkibytes;
   std::string str3 = stream3.str().substr(0, 5);
    _datas["pk_in"] = str3.c_str();
    _datas["pk_in"] += " pck IN";

   std::ostringstream stream4;
   stream4 << pkobytes;
   std::string str4 = stream4.str().substr(0, 5);
   _datas["pk_out"] = str4.c_str();
   _datas["pk_out"] += " pck OUT";

}


void NetworkModule::dequeUpdate(std::string name, float ret)
{
   // std::cout << ret << std::endl;
   if (!this->_graphs[name].empty())
   {
       if (this->_graphs[name].size() >= DEQUE_SIZE)
           this->_graphs[name].pop_back();
       this->_graphs[name].push_front(ret);
   }
   else
        this->_graphs[name] = std::deque<float>(DEQUE_SIZE, 0);
}

const std::map<std::string, std::deque<float> > &NetworkModule::getGraphs(void) const
{
    return this->_graphs;
}

const float &NetworkModule::getGraphMin(void) const
{
    return this->_graphMin;
}
 const float &NetworkModule::getGraphMax(void) const
 {
    return this->_graphMax;
 }

const std::map<std::string, std::string> &NetworkModule::getData(void) const
  {
      return this->_datas;
    }

NetworkModule::NetworkModule(NetworkModule const &src)
{
    *this = src;
}

const std::string &NetworkModule::getName(void) const
{
    return (this->_name);
}

NetworkModule &NetworkModule::operator=(NetworkModule const &rhs) {
    this->_name = rhs.getName();
    this->_graphs = rhs.getGraphs();
    this->_datas = rhs.getData();
    this->_graphMin = rhs.getGraphMin();
    this->_graphMax = rhs.getGraphMax();
    this->_lastin = rhs._lastin;
    this->_lastout = rhs._lastout;
    this->_time = rhs._time;
    return *this;
}
