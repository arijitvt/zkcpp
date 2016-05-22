#include <zkcpp_leader_manager.h>
#include <future>
#include <algorithm>

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
	std::cout << "Exiting leader manager for application : " << d_applicationName << std::endl;
	std::cout << "First cleanup all the leaders  " << std::endl; 

	std::promise<bool> leaderDeletionPromise ; 
	std::string nodePath = "/"+d_applicationName+"/leader";
	d_zooKeeperP->deleteNodeSync(nodePath,leaderDeletionPromise);
	std::cout << " Deletion complete waiting for the  future " << std::endl;
	std::future<bool> leaderDeletionFuture = leaderDeletionPromise.get_future(); 
	bool isDestroyed = leaderDeletionFuture.get(); 
	if(isDestroyed) {
		std::cout << " node is successfully terminated" << std::endl;
	} else {
		std::cerr << " Error in node deletiong  " << std::endl;
	}

	isDestroyed = false;

	std::promise<bool> destroyApplicationPromise; 
	std::string applicationPath = "/"+d_applicationName ;
	d_zooKeeperP->deleteNodeSync(applicationPath,destroyApplicationPromise);
	std::cout << " Deletion complete waiting for the  future " << std::endl;
	std::future<bool> destructionFuture = destroyApplicationPromise.get_future(); 
	isDestroyed = destructionFuture.get(); 
	if(isDestroyed) {
		std::cout << " Application is successfully terminated" << std::endl;
	} else {
		std::cerr << " Error in application termination  " << std::endl;
	}
	d_zooKeeperP->stopZk();
}

void LeaderManager::registerParticipant(const std::string& participantName) {
	d_participantList.insert(participantName);
}

void LeaderManager::unregisterParticipant(const std::string& participantName) {
	auto itr = d_participantList.find(participantName); 
	if (itr != d_participantList.end()) {
		d_participantList.erase(itr);
	}

}

bool LeaderManager::doLeaderElection(const std::string& participantName) {
	if(d_participantList.end() == 
			std::find(d_participantList.begin(),d_participantList.end(),participantName)) {
		std::cerr << "Partipcant is not register" << std::endl;
		return false;
	}

	std::cout << " Leader election is getting called " 
		<< participantName << std::endl;
	std::string leaderPath = "/"+d_applicationName+"/leader";
	std::cout << "Complete leader path : " << leaderPath << std::endl;
	std::promise<bool> leaderPromise;
	d_zooKeeperP->createEphemeralNodeSync(leaderPath,participantName,leaderPromise);
	std::future<bool> leaderFuture = leaderPromise.get_future();
	bool isLeader  = leaderFuture.get();
	if(isLeader) {
		std::string leaderInfo = "";
		int rc = d_zooKeeperP->getPathInfoSync(leaderPath,leaderInfo); 
		std::cout  << " Leader node info : " << leaderInfo << std::endl;
		if (leaderInfo == participantName ) {
			std::cout << participantName << " is elected Leader " << std::endl;
			d_leaderName = participantName;
			return true;
		}else {
			std::cerr << " Participant name  : " << participantName << " Leader : " 
				<< leaderInfo << std::endl;
			return false;
		}
	
	} else {
		std::cout << participantName << " is not a leader " << std::endl;
		return false;
	}
}

}// closing package namespace
