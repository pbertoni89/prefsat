/**
 * 	@file ExtendedArgument.cpp
 * 	@class ExtendedArgument
 *	@brief Represents a class containing the information used in the Tarjan Algorithm
 *
 *	The class allows you to contains the additional information required to compute successfully
 *	the Tarjan algorithm, used in the SCCSEQ.h class.
 *	The function does <b>NOT</b> incorporate the Argument itself: it only stores the lowlink and index information.
 *	This concept may be clearer with a picture: the association between arguments and additional information (ExtendedArguments)
 *	is implemented with an external structure (like a map or an unordered_map). In this way we can recover the additional
 *	information knowing the arguments, scenario extremely common in the Tarjan Algorithm.
 *
 *	\dot
 *		digraph {
 *			rankdir="LR";
 *			arg [label="Argument\nnn01"];
 *			earg [label="ExtendedArgument\nlowlink=3 index=2"];
 *			map [shape="record" label="{<p0>|<f0>}|{<p1>|<f1>}|{<p2>|<f2>}|{<p3>|<f3>}" height="2.5" color="blue"];
 *			arg -> map:p1;
 *			map:f1-> earg;
 *		}
 *	\enddot
 *
 *	For further information about the Tarjan Algorithm itself, please visit the wikipedia page
 *	http://en.wikipedia.org/wiki/Tarjan's_strongly_connected_components_algorithm.
 *
 * 	\date Aug 27, 2013
 * 	\author koldar
 * 	\copyright GNU Public License v2
 */

#include "ExtendedArgument.h"


/**@brief construct a new class
 *
 * build a new ExtendedArgument with:
 * \li index field set to INDEXDEFAULT;
 * \li lowlink field set to LOWLINKDEFAULT;
 *
 * \post
 *  \li a new ExtendedArgument is allocated in the memory and therefore it must be freed <b>manually</b>
 */
ExtendedArgument::ExtendedArgument(){
	this->index=INDEXDEFAULT;
	this->lowlink=LOWLINKDEFAULT;
}

/**@brief prints out the lowlink field and index field of this class
 *
 * This operator is usefull in the debug part of development.
 * The operator prints the information in this class with this syntax:
 *
 * [index=X lowlink=Y]
 *
 * @param out the stream to be altered
 * @param arg the ExtendedArgument to be printed out
 * @return a new stream modified
 */
ostream& operator<<(ostream& out, const ExtendedArgument& arg){
	out << "[index=";
	out << arg.index;
	out << " lowlink=";
	out << arg.lowlink;
	out << "]";
	return out;
}

/**@brief deallocates from the heap an ExtendedArgument
 *
 */
ExtendedArgument::~ExtendedArgument() {
}

