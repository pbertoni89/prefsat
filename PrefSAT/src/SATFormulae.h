/*
 * SATFormulae.h
 *
 *  Created on: 9 May 2013
 *      Author: geryo
 */

#ifndef SATFORMULAE_H_
#define SATFORMULAE_H_

#include <vector>
#include <string>
#include <sstream>
#include <cstdarg>
#include "OrClause.h"
#include "Argument.h"
using namespace std;

class SATFormulae {
	vector<OrClause> clauses_and;
public:
	SATFormulae();
	void appendOrClause(OrClause);
	void toSS(stringstream *) const;
	void clone(SATFormulae *);
	int size();
	virtual ~SATFormulae();
	bool empty();
};
ostream& operator<<(ostream& , const SATFormulae& );

#endif /* SATFORMULAE_H_ */
