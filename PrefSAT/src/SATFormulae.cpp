/**
 * @file 		SATFormulae.cpp
 * @class 		SATFormulae
 * @brief 		Class encompassing a list of `OrClause` linked by and operators
 * @author 		Federico Cerutti <f.cerutti@abdn.ac.uk>
 * @copyright	GNU Public License v2
 */

#include "SATFormulae.h"

/**
 * @brief	Simple constructor
 */
SATFormulae::SATFormulae()
{
	this->clauses_and = vector<OrClause>();
}

/**
 * @brief		Method for appending a new OrClause to the other clause
 * @param[in] c	The OrClause to append
 * @retval void
 */
void SATFormulae::appendOrClause(OrClause c)
{
	this->clauses_and.push_back(c);
}

/**
 * @brief			Method for transforming the SAT formulae into a string `DIMACS` compliant
 * @param[out] ss	A pointer to a stringstream object already initialised
 * @retval void
 */
void SATFormulae::toSS(stringstream *ss) const
{
	string newline = "\n";
	for (int i = 0; i < (int) this->clauses_and.size(); i++)
	{
		(*ss) << this->clauses_and.at(i);
		if (i != (int) this->clauses_and.size() - 1)
			(*ss) << newline;
	}

}

ostream& operator<<(ostream& out, const SATFormulae& r)
{
	stringstream ss(stringstream::in | stringstream::out);
	r.toSS(&ss);
	out << ss.str();
	return out;
}

/**
 * @brief 		Method returning the number of OrClause
 * @retval int	The number of OrClause
 */
int SATFormulae::size()
{
	return (int) this->clauses_and.size();
}

/**
 * @brief 				Method for cloning (not coping the pointers) this object into a new one
 * @param[out] newsat	A pointer to an initialised SATFormulae() object which will contain the copy of this object
 * @retval void
 */
void SATFormulae::clone(SATFormulae *newsat)
{
	(*newsat) = SATFormulae();
	for (int i = 0; i < this->size(); i++)
	{
		OrClause newor = OrClause();
		this->clauses_and.at(i).clone(&newor);
		(*newsat).appendOrClause(newor);
	}

}

/**
 * @brief 	Check if there are no formulae
 * @retval bool
 */
bool SATFormulae::empty()
{
	return this->clauses_and.empty();
}

SATFormulae::~SATFormulae()
{

}

