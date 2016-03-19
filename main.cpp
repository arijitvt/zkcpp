#include <string>
#include <iostream>
#include <Zookeeper.h>
#include <unistd.h>
using namespace std; 
using namespace zk;


int main() {
	ZooKeeper zk ("localhost",2181);
	zk.startZk();
	sleep(5);
	zk.stopZk();
	return 0;
}
