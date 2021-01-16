

#ifndef CLI_H_
#define CLI_H_

#include <string.h>
#include "commands.h"

using namespace std;

class CLI {
	DefaultIO* dio;//--STANDART dio OR SOCKET
    Command** commands; //data structure for menu
	// you can add data members
    
    
public:
	CLI(DefaultIO* dio);
	void start();
	virtual ~CLI();
    void setCommand();
};

#endif /* CLI_H_ */
