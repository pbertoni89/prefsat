/**
 *  @brief represents the type of the solution returned by Preferred.prefSAT() function.
 *
 *  This class contains useful routine to read more easily the result of the function prefSAT().
 *
 *  Created on: 16/ott/2013
 *  Author: Koldar
 */

#ifndef SETARGUMENTSVECTOR_H_
#define SETARGUMENTSVECTOR_H_

#include <vector>
#include <iterator>
#include <iostream>
#include "Labelling.h"

using namespace std;

class SetArgumentsVectorIterator : public vector<SetArguments*>::const_iterator
{
public:
	SetArgumentsVectorIterator() : vector<SetArguments*>::const_iterator() {};
	SetArgumentsVectorIterator(vector<SetArguments*>::const_iterator it) : vector<SetArguments*>::const_iterator(it) {};
	SetArguments* operator*() { return vector<SetArguments*>::const_iterator::operator*(); }
	SetArgumentsVectorIterator &operator=(const SetArgumentsVectorIterator &param) { vector<SetArguments*>::const_iterator::operator = (param); return *this; }
};


class SetArgumentsVector {
private:
	vector<SetArguments*> v;
	static void swap(SetArgumentsVector& first, SetArgumentsVector& second);
public:

	SetArgumentsVector();
	SetArgumentsVector(vector<SetArguments*>& _list);
	virtual ~SetArgumentsVector();
	void clone(SetArgumentsVector* list);

	SetArguments* at(unsigned int i) const;
	void push_back(SetArguments* lab);

	void clearAll();
	unsigned int size() const;
	SetArgumentsVectorIterator begin() const;
	SetArgumentsVectorIterator end() const;

	SetArgumentsVector& operator=(SetArgumentsVector rhs);
	bool operator==(const SetArgumentsVector &other) const;
	bool operator!=(const SetArgumentsVector &other) const;
	bool exist(const SetArguments* lab) const;
	void addSetArgumentsToAll(const SetArguments* set);
	bool empty();
	void pop_back();
	void printLabellingList();
};

ostream& operator<<(ostream& , const SetArgumentsVector& );

SetArgumentsVector operator+(SetArgumentsVector , const SetArgumentsVector& );

#endif /* LABELLINGLIST_H_ */
