#include <string>
#include <iostream>
#include <unistd.h>
#include <thread>
#include <vector>
#include <algorithm>
#include <chrono>
#include <zkcpp_leader_manager.h>
#include <zkcpp_participant.h>
#include <Zookeeper.h>
using namespace std; 
using namespace zkcpp;


void oldtestcode();
void leaderManagerTesting();

int main() {
	leaderManagerTesting();
	return 0;
}

void leaderManagerTesting() {
	string applicationName("Arijit");
	std::shared_ptr<LeaderManager>  leaderMgrPtr (new LeaderManager(applicationName));
	Participant first(leaderMgrPtr,"first");
	Participant second(leaderMgrPtr,"second");
	Participant third(leaderMgrPtr,"third");
	vector<Participant> participants = {first,second,third};
	for_each(participants.begin(),participants.end(),[](const Participant &p){
		p.offerLeaderShip();
	});

	std::this_thread::sleep_for(std::chrono::seconds(5));

}


void oldtestcode() {
	ZooKeeper zk ("localhost",2181);
	std::promise<bool> prom; 
	std::future<bool> fut = prom.get_future();
	zk.startZk(prom);
	bool isConnected = fut.get(); 
	std::cout << " Connection to zookeeper established : " << isConnected << endl;
	std::string nodeName("/arijit");
	std::string nodeValue("This is the value of the node");
	std::promise<bool> nodeCreationPromise;
	NODE_TYPE nodeType;
   	int rc = zk.createEphemeralNodeSync(nodeName,nodeValue,nodeCreationPromise); 
	std::cout << "Return value from node creation : " << rc << std::endl;
	std::future<bool> nodeCreationFuture = nodeCreationPromise.get_future();
	bool isNodeCreated = nodeCreationFuture.get();
	std::cout << " IS node created : " << isNodeCreated << std::endl;
	std::promise<bool> persistentNodeCreationPromise;
	std::future<bool> persistentNodeCreationFuture = persistentNodeCreationPromise.get_future();
	rc = zk.createPersistentNodeSync("/rajni","Rajni Persistent Node",persistentNodeCreationPromise);
	bool isPersistentNodeCreated = persistentNodeCreationFuture.get();
	std::cout << " Is persistent Node created : " << isPersistentNodeCreated << std::endl;
	zk.stopZk();
}
