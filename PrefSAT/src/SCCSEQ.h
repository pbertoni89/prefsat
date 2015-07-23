#ifndef SCCSEQ_H_
#define SCCSEQ_H_

// todo gli include sono importati da altro header, rimuovere i non necessari
#include <map>
#include <string>
#include <iterator>
#include <algorithm>

#include <iostream>
//usato dall'algoritmo di tarjan
#include <vector>
#include <list>
#include <stack>
//usato dentro toposorz
#include <string>
#include <sstream>
using namespace std;
#include <unordered_map>

#include "SetArguments.h"
#include "ExtendedArgument.h"

// #define DEBUG_SCCSEQ scommentare per output...

class SCCSEQ {

public:
	static void performSCCSEQ(SetArguments*, vector<SetArguments*>*);
	static void SCC(SetArguments*, vector<SetArguments*>*);
	/** Kahn.  NON in loco (variabile L). complessità: O(|V|+|E|)

			L ← Empty list that will contain the sorted elements
			S ← Set of all nodes with no incoming edges
			while S is non-empty do
				remove a node n from S
				insert n into L
				for each node m with an edge e from n to m do
					remove edge e from the graph
					if m has no other incoming edges then
						insert m into S
			if graph has edges then
				return error (graph has at least one cycle)
			else
				return L (a topologically sorted order)
	*/
	static void SEQ(vector<SetArguments*>*);
	static vector<SetArguments*>* getFathersUnion(vector<SetArguments*>*, SetArguments*);
	static void linkMacroGraph(vector<SetArguments*>*, SetArguments*);
	static string genName(unsigned int i);
	static void toposort(SetArguments, vector<int>*);

private:
	static void strongConnected(Argument* v, SetArguments* graph,int* globalIndex, vector<Argument*>* stack, vector<SetArguments*>* sccresult,unordered_map <int,ExtendedArgument*>* nodeMap);
	/** @brief rimappa gli SCC secondo le posizioni toposortate.*/
	static void finalsorting(vector<SetArguments*>*, vector<int>);
};

#endif /* SCCSEQ_H_ */
