#include <zkcpp_participant.h>
#include <cstdlib>

namespace zkcpp {


Participant::Participant(LeaderManagerP leaderManager) 
:d_leaderManagerP(leaderManager) {

}

Participant::Participant(LeaderManagerP leaderManager,
		const std::string& name)
:d_leaderManagerP(leaderManager),
	d_name(name) {	
	d_leaderManagerP->registerParticipant(name);
}

Participant::~Participant() {
	d_leaderManagerP->unregisterParticipant(d_name);
}

bool Participant::offerLeaderShip() const{
	if(d_leaderManagerP->doLeaderElection(d_name)) {
		std::cout << "Leader is : ------------------------------ " 
			<< d_name << std::endl;
	}
	return false;
	
}

} // closing package namespace 
