#include <Zookeeper.h>
#include <sstream>
#include <unistd.h>

namespace {


void zkcpp_watcher(zhandle_t *zk,int type, int state, const char *path,void *context) {
	std::promise<bool> *prom  = (std::promise<bool>*) context;
	if(type == ZOO_SESSION_EVENT) {
		if(state == ZOO_CONNECTED_STATE) {
			prom->set_value(true);
		}
	}
}

void zkcpp_string_stat_completion(int rc, const char *name,
		 const void *data) {
	std::cout << "String completion is getting called" << std::endl;
	std::promise<bool> *prom = (std::promise<bool>*) data;
	if(rc == 0 ) {
		std::cout <<"  Node creation is successful" << std::endl;
		prom->set_value(true);
	} else {
		std::cout << "Node creation is UnSuccessful with error code " 
			<< rc << std::endl;
		prom->set_value(false);
		                                           
	}
}

void zkcpp_stat_completion(int rc, const struct Stat *stat, 
		const void *data) {
	std::cout << "Stat completion is getting called " << std::endl;
	std::promise<bool> *prom  = (std::promise<bool>*) data; 
	if ( rc == 0){
		std::cout << " Node checking is successful" << std::endl;
		prom->set_value(true);
	} else {
		std::cerr << " Node value checking is incomplete " << std::endl;
		prom->set_value(false);
	}
}

void zkcpp_void_completion(int rc, const void *data) {
	std::cout << " Void completion return code : " << rc << std::endl;
	std::promise<bool> *prom = (std::promise<bool>*) data; 
	if(rc == 0 ) {
		std::cout << " Void completion status is success " << std::endl;
		prom->set_value(true);
	} else {
		std::cerr << " Void completion error code : " << rc << std::endl;
		prom->set_value(false);
	}

}

} // closing namespace

namespace zkcpp {

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
		d_zkHandle = zookeeper_init(d_hostPort.c_str(),zkcpp_watcher,10000,0,&prom,0);
	}
}

void ZooKeeper::stopZk() {
	if(d_zkHandle) {
		zookeeper_close(d_zkHandle);
	}
}


int ZooKeeper::createNodeSync(const std::string& path, 
		const std::string& value,
		NODE_TYPE  flag,
		std::promise<bool>& prom) {
	int rc = -1;
	int zkFlag = 0;
	switch(flag) {
		case EPHEMERAL:
			zkFlag |= ZOO_EPHEMERAL;
			break;

		case SEQUENTIAL:
			zkFlag |= ZOO_SEQUENCE;
			break;

		case EPHEMERAL_SEQ:
			zkFlag |= ZOO_SEQUENCE;
			zkFlag |= ZOO_EPHEMERAL;

		default:
			std::cerr << "Unknown flag" << std::endl;
	}
	// handle is already initialized
	if(d_zkHandle) {
		rc = zoo_acreate(d_zkHandle, path.c_str(), value.c_str(), value.size(),
				&ZOO_OPEN_ACL_UNSAFE,
				zkFlag, zkcpp_string_stat_completion,(void*)&prom);
	}  else {  // handle is not  initialized so init it start the                                                         
		std::cerr <<  " Please call the startZk before calling this " << std::endl;	
		rc = -1;
	}

	return rc ; 
}

int ZooKeeper::deleteNodeSync(const std::string& path, 
		std::promise<bool>& prom) {
	std::cout << " deleting ----- " << path << std::endl;
    int rc =  zoo_adelete(d_zkHandle,path.c_str(),-1,zkcpp_void_completion,(void*) &prom);
	return rc; 
	
}


int ZooKeeper::createEphemeralNodeSync(const std::string& nodeName, 
		const std::string& value, std::promise<bool>& prom) {
	return createNodeSync(nodeName,value,EPHEMERAL,prom);
}

int ZooKeeper::createSequentialNodeSync(const std::string& nodeName,
		const std::string& value,std::promise<bool>& prom) {
	return createNodeSync(nodeName,value,SEQUENTIAL,prom);
}
int ZooKeeper::createPersistentNodeSync(const std::string& nodeName,
		const std::string& value,std::promise<bool>& prom) {
	return createNodeSync(nodeName,value,PERSISTENT,prom);
}

bool ZooKeeper::doesNodeExistsSync(const std::string& nodeName) {
	std::promise<bool> nodeExistsProm ;
	int rc = zoo_aexists(d_zkHandle,nodeName.c_str(),0,
			zkcpp_stat_completion,&nodeExistsProm);
	std::cout << "Return code for the api " << rc << std::endl;
	if(!rc) {
		std::future<bool> existsFuture = nodeExistsProm.get_future();
		return existsFuture.get();
	} else {
		return false ;
	}
}

} // closing namespace
