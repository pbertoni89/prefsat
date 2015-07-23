#ifndef GROUNDED_H_
#define GROUNDED_H_

#include <iostream>

#include "AF.h"
#include "SetArguments.h"

//#define DEBUG_GROUNDED

using namespace std;

class Grounded {
public:

	Grounded();
	static void doGrounded(SetArguments gamma, SetArguments C, SetArguments* e, SetArguments* I);
	virtual ~Grounded();

private:
	//while esiste N sottoinsieme C che contiene solo nodi che non sono attaccati da nodi in I
	static bool isNempty(SetArguments*,SetArguments*,SetArguments*);
	static void computeNSet(SetArguments* C, SetArguments* I,SetArguments* N);
};

#endif /* GROUNDED_H_ */
