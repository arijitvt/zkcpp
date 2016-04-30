
#ifndef INCLUDE_ZKCPP_PARTICIPANTS
#define INCLUDE_ZKCPP_PARTICIPANTS

/***
 * @Author : Arijit Chattopadhyay
 ***/


#include <string>

namespace zkcpp {

class Participant {
	public :
        Participant();

	private:
		std::string d_name;		
};

} // closing package namespace

#endif
