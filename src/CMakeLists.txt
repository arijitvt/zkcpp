set(SOURCES zkcpp_configuration.cpp
	zkcpp_leader_manager.cpp
	zkcpp_participant.cpp
	Zookeeper.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_library(ZKCPP SHARED ${SOURCES})
target_include_directories(ZKCPP PUBLIC ${PROJECT_BINARY_DIR}/include)
