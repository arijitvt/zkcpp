#include <future>
#include <zkcpp_leader_manager.h>

namespace zkcpp {

LeaderManager::LeaderManager(const std::string& applicationName)
 : d_serverName("localhost"),
	d_port(2181) ,
	d_applicationName(applicationName)
	{                                                
	d_zooKeeperP = std::make_shared<ZooKeeper>(d_serverName,d_port);
	std::promise<bool>  connectionCompletionPromise;
	d_zooKeeperP->startZk(connectionCompletionPromise);
	std::future<bool> futureCompletion = connectionCompletionPromise.get_future();
	std::cout << "Connection complete " << std::endl;
	if(futureCompletion.get()) {
		if(d_zooKeeperP->doesNodeExistsSync(d_applicationName)){
			std::cerr << "Application Node already exists" << std::endl;
		} else {
			std::promise<bool> nodeCreationPromise;
			std::string applicationPath="/"+d_applicationName;
			d_zooKeeperP->createPersistentNodeSync(applicationPath, d_applicationName,nodeCreationPromise);
			std::future<bool> nodeCreationFuture = nodeCreationPromise.get_future(); 
			bool isApplicationCreation = nodeCreationFuture.get();
			std::cout << "Is application created " << isApplicationCreation << std::endl;
		}
	}
}

LeaderManager::~LeaderManager() {
	d_zooKeeperP->stopZk();

}

bool LeaderManager::doLeaderElection(const std::string& participantName) {
	std::cout << " Leader election is getting called " 
		<< participantName << std::endl;
	std::string leaderPath = "/"+d_applicationName+"/leader";
	std::cout << "Complete leader path : " << leaderPath << std::endl;
	std::promise<bool> leaderPromise;
	d_zooKeeperP->createEphemeralNodeSync(leaderPath,d_applicationName,leaderPromise);
	std::future<bool> leaderFuture = leaderPromise.get_future();
	return leaderFuture.get();
}

}// closing package namespace
