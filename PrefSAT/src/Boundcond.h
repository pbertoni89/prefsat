/*
 * Boundcond.h poteva star benissimo in SetArguments ma l'abbiam piazzato qui.
 *
 *  Created on: Oct 3, 2013
 *  @author: patrizio
 */

#ifndef BOUNDCOND_H_
#define BOUNDCOND_H_

#include <iostream>
#include "AF.h"
#include "SetArguments.h"

// #define DEBUG_BOUNDCOND //scommentare per output....

using namespace std;

class AF;
class SetArguments;

class Boundcond {
public:
	Boundcond();
	virtual ~Boundcond();
	/*
	 * @param[out] O è il sottoinsieme dei nodi di S[i] attaccati da nodi in e
	 * @param[out] I è il sottoinsieme dei nodi di S[i]\O che
						non subiscono attacchi da parte di nodi in G esterni a S[i]
						_xor_
						subiscono eventuali attacchi solo da parte di nodi che
							sono contenuti in G ma non in (S[i] join e)
							_and_
							sono attaccati da nodi in e
	 */
	static void doBoundcond(SetArguments* A, SetArguments* B, SetArguments* C, SetArguments* O, SetArguments* I);
};

#endif /* BOUNDCOND_H_ */
