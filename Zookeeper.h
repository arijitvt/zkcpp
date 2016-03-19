
#ifndef INCLUDE_ZK
#define INCLUDE_ ZK

/***
 * @Author : Arijit Chattopadhyay
 ***/


#include <zookeeper/zookeeper.h>
#include <string>
#include <iostream>
#include <future>


namespace zk  {

class ZooKeeper {
	private:
		std::string 		d_host; 
		int 				d_port;
		std::string    		d_hostPort;
		zhandle_t           *d_zkHandle;
		std::promise<bool> 	d_promise;

	public:
		ZooKeeper(const std::string& host, int port);
		void startZk(std::future<bool>& fut) ;
		void stopZk();
		void createPath(const std::string& path);
};

} //closing namespace

#endif
