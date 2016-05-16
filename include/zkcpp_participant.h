
#ifndef INCLUDE_ZKCPP_PARTICIPANTS
#define INCLUDE_ZKCPP_PARTICIPANTS

/***
 * @Author : Arijit Chattopadhyay
 ***/


#include <string>
#include <zkcpp_leader_manager.h>

namespace zkcpp {

class Participant {
	public :
        Participant(LeaderManagerP leaderManager);
		Participant(LeaderManagerP leaderManager,
				const std::string& name);
		virtual ~Participant();
		bool offerLeaderShip()const;


	private:
		LeaderManagerP 	d_leaderManagerP;
		std::string 	d_name;		
		std::string 	d_ip;
};

} // closing package namespace

#endif
