//TODO documentazione!!!!
/** PreferredExtension.h è la classe principale per l'elaborato. viene istanziata con un grafo e offre la computazione
 *  delle "preferred extensions"
 */

#ifndef PREFALGORITHM_H_
#define PREFALGORITHM_H_

#include <iostream>
//usato dall'algoritmo di tarjan
#include <vector>
#include <list>
#include <stack>
//usato dentro toposort
#include <sstream>
#define CHRONOPREF
#ifdef CHRONOPREF
	#include <chrono>
#endif
using namespace std;

#include "semopt.h"
#include "SetArguments.h"
#include "Grounded.h"
#include "SCCSEQ.h"
#include "Boundcond.h"
#include "Preferred.h" //external for PrefSAT()
#include "AF.h"
#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <string>

#define PREF_CALL 0
#define GROUNDED_CALL 1
#define BOUNDCOND_CALL 2
#define SATPREF_CALL 3
#define CALLING_TYPES 4

class PrefAlgorithm {

public:
	AF framework;
	Preferred preferred;
	SetArgumentsVector handlePref(bool);
	PrefAlgorithm(string);
	static void pushCall(unsigned short);
	static unsigned int getCalls(unsigned short);

private:
	static unsigned int calls[CALLING_TYPES];
	/** @brief main method. */
	SetArgumentsVector Pref(SetArguments, SetArguments);
	/** @brief main method, with optimization as suggested. */
	SetArgumentsVector PrefImproved(SetArguments, SetArguments);
};

#endif /* PREFERREDEXTENSION_H_ */
