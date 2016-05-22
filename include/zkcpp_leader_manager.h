
#ifndef INCLUDE_ZKCPP_LEADER_MANAGER
#define INCLUDE_ZKCPP_LEADER_MANAGER

/***
 * @Author : Arijit Chattopadhyay
 ***/


#include <Zookeeper.h>
#include <memory>
#include <string>
#include <set>


namespace  zkcpp {

class LeaderManager;

typedef std::shared_ptr<LeaderManager> LeaderManagerP;

class LeaderManager {
	public : 
		LeaderManager(const std::string& applicationName);
		virtual ~LeaderManager();
		bool doLeaderElection(const std::string& participantName);
		void registerParticipant(const std::string& participantName);
		void unregisterParticipant(const std::string& participantName);

	private:
		std::string 				d_serverName;
		int 						d_port;
		std::string 				d_applicationName;

		std::string 	d_leaderName;
		std::shared_ptr<ZooKeeper> 	d_zooKeeperP;
		std::set<std::string> 	d_participantList;

};

} // closing package namespace


#endif
