#include <Zookeeper.h>
#include <sstream>

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

void ZooKeeper::startZk(std::future<bool>& fut) {
	if(!d_zkHandle) {
		std::cout << " Starting the connection"<< std::endl;
		d_zkHandle = zookeeper_init(d_hostPort.c_str(),watcher,10000,0,&d_promise,0);
	}
	fut = d_promise.get_future();
}

void ZooKeeper::stopZk() {
	//if(d_zkHandle) {
	//	zookeeper_close(d_zkHandle);
	//}
}

} // closing namespace
