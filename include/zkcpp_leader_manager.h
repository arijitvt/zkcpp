
#ifndef INCLUDE_ZKCPP_LEADER_MANAGER
#define INCLUDE_ZKCPP_LEADER_MANAGER

/***
 * @Author : Arijit Chattopadhyay
 ***/


#include <memory>
#include <string>
#include <vector>
#include <Zookeeper.h>

namespace  zkcpp {

class LeaderManager;

typedef std::shared_ptr<LeaderManager> LeaderManagerP;

class LeaderManager {
	public : 
		LeaderManager(const std::string& applicationName);
		virtual ~LeaderManager();
		bool doLeaderElection(const std::string& participantName);

	private:
		std::string 				d_serverName;
		int 						d_port;
		std::string 				d_applicationName;

		// there may be more than one leader.
		std::vector<std::string> 	d_leaderName ;
		std::shared_ptr<ZooKeeper> 	d_zooKeeperP;
};

} // closing package namespace


#endif
