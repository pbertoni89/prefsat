/*
 * SetArguments.h
 *
 *  Created on: 3 Jun 2013
 *      Author: geryo
 */

#ifndef SETARGUMENTS_H_
#define SETARGUMENTS_H_

#include <map>
#include <string>
#include <iterator>
#include <algorithm>
#include <iostream>
//usato dall'algoritmo di tarjan
#include <vector>
//hash table use
#include <unordered_map>

using namespace std;

#include "Argument.h"

/**
 * @brief Class defining a const iterator for the elements of a set of arguments
 */
class SetArgumentsIterator : public map<string, Argument *>::const_iterator
{
public:
	SetArgumentsIterator() : map<string, Argument *>::const_iterator() {};
	SetArgumentsIterator(map<string, Argument *>::const_iterator it) : map<string, Argument *>::const_iterator(it) {};
	Argument ** operator->() {
		return (Argument ** const)&(map<string, Argument *>::const_iterator::operator->()->second);
	};
	Argument* operator*() {
		return map<string, Argument *>::const_iterator::operator*().second;
	}
	SetArgumentsIterator &operator=(const SetArgumentsIterator &param) {
		map<string, Argument *>::const_iterator::operator = (param);
		return *this;
	}
};

class SetArguments
{
	/**represents a map that associate for each argument Identifier (a string) the argument itself.
	 * Note that the arguments are stored by reference, so different SetArguments can point to the same Argument.
	 * This function is of type map because in this way the search of one element is much quicker.
	 */
	map<string, Argument *> arguments;
	/**Represents a map that associate for each argument Identifier (an integer) the relative argument Identfier (a stirng).
	 * In this way you can easily represents a argument both by name and by integer.
	 *
	 * \dot
	 *  digraph example {
	 *		rankdir="LR";
	 *		nodesep=0.005;
	 *
	 *		nummap [shape="record" label="<l0>|<l1>|<l2>|<l3>|<l4>", height=2.5];
	 *		namemap [shape="record" label="<ls0>|<ls1>|<ls2>|<ls3>|<ls4>", height=2.5];
	 *
	 *		arg1;
	 *		arg2;
	 *		arg3;
	 *		arg4;
	 *		arg5;
	 *
	 *		nummap:l3 -> namemap:ls2;
	 *		namemap:ls0 -> arg4;
	 *		nummap:l0 -> namemap:ls1;
	 *		namemap:ls1 -> arg5;
	 *		nummap:l1 -> namemap:ls0;
	 *		namemap:ls2 -> arg2;
	 *		nummap:l2 -> namemap:ls3;
	 *		namemap:ls3 -> arg3;
	 *		nummap:l4 -> namemap:ls4;
	 *		namemap:ls4 -> arg1;
	 *  }
	 * \enddot
	 *
	 */
	map<int, string> key_assoc;
public:
	SetArguments();
	SetArguments(AF af, string names[], int length);
	void add_Argument(Argument *);
	virtual ~SetArguments();
	Argument *getArgumentByName(string);
	Argument *getArgumentByNumber(int num);
	int cardinality() const;
	bool empty();
	SetArgumentsIterator begin() const;
	SetArgumentsIterator end() const;
	bool exists(Argument *);
	bool is_subset_equal(SetArguments *);
	bool is_subset(SetArguments *);

	void synchWithSet(SetArguments* otherset);

	vector<SetArguments*> getSingletons();
	SetArguments* getArgumentAttackersInSet(Argument*);
	SetArguments* getArgumentAttacksInSet(Argument*);
	SetArguments* getAllAttackers();
	SetArguments* getAllAttacks();
	SetArguments* getAllAttackersInSet();
	SetArguments* getAllAttacksInSet();
	SetArguments* getSubsetAttackedBy(SetArguments*);
	SetArguments* getSubsetAttacks(SetArguments*);
	SetArguments* getExternalAttackers(void);
	SetArguments* getExternalAttacks(void);
	void setSafeRestrict(SetArguments*, SetArguments*);
	void merge(SetArguments*, SetArguments *);
	void intersect(SetArguments *, SetArguments *);
	void setminus(SetArguments *, SetArguments *);
	void remove(Argument *);
	void remove_All_Arguments();
	void clean();
	void clone(SetArguments *);
	bool equal(const SetArguments &other) const;
	bool operator==(const SetArguments &other) const;
	bool operator!=(const SetArguments &other) const;
	void printNodeRelations(void);
	void printGraph(void);
	bool graphHasEdges(void);

private:
	void strongConnected(Argument*, int*, vector<Argument*>*, vector<SetArguments*>*, int*, int*);
};

ostream& operator<<(ostream& , const SetArguments& );

#endif /* SETARGUMENTS_H_ */
