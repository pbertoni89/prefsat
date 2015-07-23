/**
 * @file 		OrClause.cpp
 * @class 		OrClause
 * @brief 		Class encompassing a list of SAT variables (type `Variable`) linked by or operators
 * @details		For example, the or clause "var1 OR var2 OR var3 OR not var 4 OR var 5" can
 * 				be defined as OrClause(5, var1, var2, var3, not var4, var5)
 * @author 		Federico Cerutti <f.cerutti@abdn.ac.uk>
 * @copyright	GNU Public License v2
 */

#include "OrClause.h"

/**
 * @brief		Simple constructor
 * @details		No parameters required, it initializes the data structure
 * 				but it adds no variables to the clause
 */
OrClause::OrClause()
{
	this->clause = vector<Variable>();
}

/**
 * @brief				Constructor that can receive as input a list of variables
 * @param[in] count		The number of variables that follows
 * @param[in] ....		The list of variables that follows, instances of type `Variable`
 * @details				For instance, OrClause(3, var1, var2, var3)
 */
OrClause::OrClause(int count, ...)
{
	va_list ap;
	va_start(ap, count);
	this->clause = vector<Variable>();
	for (int i = 0; i < count; i++)
	{
		this->clause.push_back(va_arg(ap, Variable));
	}
	va_end(ap);
}

/**
 * @brief			Method for adding a variable at the end of the clause
 * @param[in] x		The variable to add
 * @retval void
 */
void OrClause::appendVariable(Variable x)
{
	(this->clause).push_back(x);
}

/**
 * @brief			Method for adding a variable at the beginning of the clause
 * @param[in] x		The variable to add (of type `Variable`)
 * @retval void
 */
void OrClause::addHeadVariable(Variable x)
{
	this->clause.insert(this->clause.begin(), x);
}

/**
 * @brief 				Method for returning a string representation of the Or clause in
 * 						a `stringstream` object
 * @param[in,out] ss	A pointer to an already initialised `stringstream` object which will
 * 						contain the string representation of this object
 * @retval void
 */
void OrClause::toSS(stringstream *ss) const
{
	if ((int) this->clause.size() != 0)
	{
		string sep = " ";
		string endcl = "0";
		for (int i = 0; i < (int) this->clause.size(); i++)
			(*ss) << this->clause.at(i) << sep;
		(*ss) << endcl;
	}
}

/**
 * @brief						Method for cloning this OrClause into a new OrClause that is passed as input
 * 								output parameter
 * @param[in,out] newclause		Pointer to another `OrClause` object, which is newly initialised, and then
 * 								which will become a clone (*not a pointer*) of this object
 * @retval void
 */
void OrClause::clone(OrClause *newclause)
{
	(*newclause) = OrClause();
	for (int i = 0; i < (int) this->clause.size(); i++)
		(*newclause).appendVariable(this->clause.at(i));
}

ostream& operator<<(ostream& out, const OrClause& r)
{
	stringstream ss(stringstream::in | stringstream::out);
	r.toSS(&ss);
	out << ss.str();
	return out;
}

OrClause::~OrClause()
{
}

