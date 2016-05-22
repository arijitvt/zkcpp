
#ifndef INCLUDE_ZKCPP_CONFIGURATION
#define INCLUDE_ZKCPP_CONFIGURATION

/***
 * @Author : Arijit Chattopadhyay
 ***/
#include <string>

namespace zkcpp {

class Configuration {

	public:
		Configuration(); 

		const std::string& getApplicationName() const {
			return d_applicationName;
		}

		const int getNumOfLeaders() const {
			return d_numOfLeaders;
		}

		const int getHealthCheckInterval() const {
			return d_healthCheckInterval;
		}

		const int getMaxNumOfParticipants() const {
			return d_maxNumOfParticipants;		
		}

	private:
		std::string d_applicationName;
		int 		d_numOfLeaders; 
		int 		d_healthCheckInterval;
		int 		d_maxNumOfParticipants;
};

}// closing package namespace

#endif
