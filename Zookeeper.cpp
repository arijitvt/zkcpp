#include <Zookeeper.h>

namespace zk {


ZooKeeper::ZooKeeper(const std::string& host, int port ) 
	:d_host(host),d_port(port) {}
} // closing namespace
