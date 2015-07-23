#ifndef ORCLAUSE_H_
#define ORCLAUSE_H_

#include <vector>
#include <string>
#include <sstream>
#include <cstdarg>
#include "Argument.h"
using namespace std;

class OrClause {
	vector<Variable> clause;
public:
	OrClause();
	OrClause(int, ...);
	void appendVariable(Variable);
	void addHeadVariable(Variable);
	void toSS(stringstream *) const;
	void clone(OrClause *);
	virtual ~OrClause();
};
ostream& operator<<(ostream& , const OrClause& );

#endif /* ORCLAUSE_H_ */
