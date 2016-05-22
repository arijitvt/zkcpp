
#ifndef INCLUDE_ZK
#define INCLUDE_ZK

/***
 * @Author : Arijit Chattopadhyay
 ***/


#include <zookeeper/zookeeper.h>
#include <string>
#include <iostream>
#include <future>


namespace zkcpp  {

typedef enum {
	PERSISTENT,
	EPHEMERAL,
	SEQUENTIAL,
	EPHEMERAL_SEQ,

} NODE_TYPE;

class ZooKeeper {
	private:
		std::string 		d_host; 
		int 				d_port;
		std::string    		d_hostPort;
		zhandle_t           *d_zkHandle;

		int  createNodeSync(const std::string& path, 
				const std::string& value,
				NODE_TYPE flag,       
				std::promise<bool>& prom);

				

	public:
		ZooKeeper(const std::string& host, int port);
		void startZk(std::promise<bool>& prom);
		void stopZk();
		int createEphemeralNodeSync(const std::string& nodeName,
				const std::string& value,std::promise<bool>& prom);

		int createSequentialNodeSync(const std::string& nodeName,
				const std::string& value,std::promise<bool>& prom);

		int createPersistentNodeSync(const std::string& nodeName,
				const std::string& value,std::promise<bool>& prom);

		int deleteNodeSync(const std::string& path,
				std::promise<bool>& prom);

		bool doesNodeExistsSync(const std::string& nodeName);
};                         

} //closing namespace

#endif
