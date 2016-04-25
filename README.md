#ZKCPP
The C++ api library for Zookeeper. This is Modular asychronous way to access zookeeper from c++ program.


#Leader Election 
 - There will be a configuration class, which will contain ther configuration parameters, 
 	 * How many masters.
	 * Maximum number of participants.
	 * Master eviction is required.(Random master eviction will elect a new master).
	 * Should trigger  error message if there is  no master in the cluster.

 - Participant
 	This class will hold the information about each participant of the cluster. 
	Each participant should also tell the health of it, so that during an election, 
	Zk should not make an ill perticipant as master. 


 - HealthChecker.
   This will check the health of the system and will do various things. 

