#include <string>
#include <iostream>
#include <Zookeeper.h>
#include <unistd.h>
#include <thread>
using namespace std; 
using namespace zk;


int main() {
	ZooKeeper zk ("localhost",2181);
	std::promise<bool> prom; 
	std::future<bool> fut = prom.get_future();
	zk.startZk(prom);
	bool isConnected = fut.get(); 
	std::cout << " Connection to zookeeper established : " << isConnected << endl;
	zk.stopZk();
	return 0;
}
