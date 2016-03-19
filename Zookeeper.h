
#ifndef INCLUDE_ZK
#define INCLUDE_ ZK

/***
 * @Author : Arijit Chattopadhyay
 ***/


#include <zookeeper/zookeeper.h>
#include <string>
#include <iostream>


namespace zk  {

class ZooKeeper {
	private:
		std::string 	d_host; 
		int 	d_port;

	public:
		ZooKeeper(const std::string& host, int port);
		void startZk(); 
		void stopZk();
		void createPath(const std::string& path);
};

} //closing namespace

#endif
