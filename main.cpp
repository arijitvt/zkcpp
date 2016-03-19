#include <string>
#include <iostream>
#include <Zookeeper.h>
#include <unistd.h>
#include <thread>
using namespace std; 
using namespace zk;

void executor(future<bool>& fut) {
	bool isConnected = fut.get();
	if(isConnected) {
		cout << "Connection complete " << endl;
	}
}


int main() {
	ZooKeeper zk ("localhost",2181);
	future<bool> fut ;
	thread executorThread(executor,ref(fut));
	zk.startZk(fut);
	sleep(5);
	zk.stopZk();
	executorThread.join();
	return 0;
}
