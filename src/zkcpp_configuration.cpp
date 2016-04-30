#include <zkcpp_configuration.h>

namespace zkcpp {

Configuration::Configuration() {
	d_applicationName = "test";
	d_numOfLeaders = 1; 
	d_healthCheckInterval = 20;
	d_maxNumOfParticipants = 100;
}

} // closing package namespace

