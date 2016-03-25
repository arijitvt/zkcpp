#include <Zookeeper.h>
#include <sstream>
#include <unistd.h>

namespace {


void watcher(zhandle_t *zk,int type, int state, const char *path,void *context) {
	std::promise<bool> *prom  = (std::promise<bool>*) context;
	if(type == ZOO_SESSION_EVENT) {
		if(state == ZOO_CONNECTED_STATE) {
			prom->set_value(true);
		}
	}
}

} // closing namespace

namespace zk {

ZooKeeper::ZooKeeper(const std::string& host, int port ) 
	:d_host(host)
	 ,d_port(port)
	 ,d_zkHandle(NULL) {
	std::stringstream ss; 
	ss<< host << ":" <<port; 
	d_hostPort = ss.str();
	std::cout << "Host port  : " << d_hostPort << std::endl;
}

void ZooKeeper::startZk(std::promise<bool>& prom) {
	if(!d_zkHandle) {
		std::cout << " Starting the connection"<< std::endl;
		d_zkHandle = zookeeper_init(d_hostPort.c_str(),watcher,10000,0,&prom,0);
	}
}

void ZooKeeper::stopZk() {
	if(d_zkHandle) {
		zookeeper_close(d_zkHandle);
	}
}


void ZooKeeper::createPath(const std::string& path, std::promise<bool>& prom) {
	// handle is already initialized
	if(d_zkHandle) {
	
	}  else {  // handle is not  initialized so init it start the 
		std::cerr <<  " Please call the startZk before calling this " << std::endl;
	}
}


} // closing namespace
