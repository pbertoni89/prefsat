/*
 * Argument.h
 *
 *  Created on: 13 May 2013
 *      Author: geryo
 */

#ifndef ARGUMENT_H_
#define ARGUMENT_H_

#include <string>
#include <sstream> // per conversioni itoa
using namespace std;


class AF;
class SetArguments;
/**
 * @class Variable Argument.h Argument.h
 * @brief `Variable` is defined easily as a `typedef int Variable`
 */
typedef int Variable;

/**
 * @def NOT(x)
 * @brief	Computes the negation of `Variable` x
 */
#define NOT(x) (-x)


class Argument
{
	string name;
	/* Identificativo assegnato al nodo dal parser. INIZIANO DA ZERO*/
	int number;
	AF *af;
	SetArguments *attacks;
	SetArguments *attackers;
public:
	Argument(string, int, AF*);
	virtual ~Argument();
	string getName() const;
	int getNumber() const;
	string print() const;
	AF *get_af();
	Variable InVar();
	Variable OutVar();
	Variable UndecVar();
	Variable NotInVar();
	Variable NotOutVar();
	Variable NotUndecVar();
	bool operator==(const Argument &other) const;
	bool operator!=(const Argument &other) const;
	void add_attacks(Argument *);
	void add_attackers(Argument *);
	void remove_attacks(Argument *);  //pat
	void remove_attackers(Argument *); //pat
	SetArguments *get_attacks();
	SetArguments *get_attackers();
};

ostream& operator<<(ostream& f, const Argument& arg);
ostream& operator<<(ostream& , const SetArguments& );

#ifndef GRAPH_H_
#include "AF.h"
#include "SetArguments.h"
#endif


#endif /* ARGUMENT_H_ */
