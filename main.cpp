#include <string>
#include <iostream>
#include <Zookeeper.h>
#include <unistd.h>
#include <thread>
using namespace std; 
using namespace zk;


int main() {
	ZooKeeper zk ("localhost",2181);
	zk.startZk(fut);
	sleep(5);
	zk.stopZk();
	return 0;
}
