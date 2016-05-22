
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

		const std::string& getName() const {
			return d_name;
		}

		const std::string& getIp() const {
			return d_ip;
		}


	private:
		Participant(const Participant& rhs) ; // Do not implement
		void operator=(const Participant& rhs) ; //Do not implement
			


	private:
		LeaderManagerP 	d_leaderManagerP;
		std::string 	d_name;		
		std::string 	d_ip;
};

} // closing package namespace

#endif
