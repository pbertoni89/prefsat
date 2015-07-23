/*
 * Preferred.cpp
 *
 *  Created on: 10 Jun 2013
 *      Author: geryo
 */

#include "Preferred.h"

/**clean all the metadata in this instance to allow the developers to reuse this structure to compute other
 * preSAT. So you need to call more than once prefSAT you should:
 * \code
 * 	Preferred pref=new Preferred();
 * 	pref->prefSAT(set1,otherset2);
 * 	//retrieve solution
 * 	pref->cleanlabs();
 * 	pref->prefSAT(set2,otherset2);
 * \endcode
 *
 * \post
 *  \li metadata used to solve prefSAT is clear and the instance is ready to compute another prefSAT problem
 *
 */
void Preferred::cleanlabs()
{
	while (!this->labellings.empty())
		this->labellings.pop_back();
}

/**
 * @brief Method for filling in the attribute sat_new_pigreek
 */
int Preferred::compute_new_pigreek()
{
	SetArguments subtraction = SetArguments();
	this->A->setminus(this->C, &subtraction);

	for (SetArgumentsIterator it_sub = subtraction.begin();
			it_sub != subtraction.end(); it_sub++)
	{
		if (debug)
		{
			cout << "Subtraction " << (*it_sub)->getName() << endl;
		}
		//c2
		this->sat_new_pigreek.appendOrClause(
				OrClause(1, (*it_sub)->NotInVar()));
		this->sat_new_pigreek.appendOrClause(
				OrClause(2, (*it_sub)->OutVar(), (*it_sub)->UndecVar()));
		this->sat_new_pigreek.appendOrClause(
				OrClause(2, (*it_sub)->NotOutVar(), (*it_sub)->NotUndecVar()));

		//c-to-add
		if ((*it_sub)->get_attackers()->empty())
		{
			this->sat_new_pigreek.appendOrClause(OrClause(1, (*it_sub)->UndecVar()));
		}

	}

	if (debug)
	{
		cout << "Set arguments: " << endl;
		cout << *(this->A) << endl;

		cout << "C set:" << endl;
		cout << *(this->C) << endl;
	}

	OrClause noempty_clause = OrClause();
	for (SetArgumentsIterator it_args = this->C->begin();
			it_args != this->C->end(); it_args++)
	{
		//c1
		if (encoding == 0 || encoding == 1 || encoding == 2 || encoding == 3
				|| encoding == 4 || encoding == 5)
		{
			this->sat_new_pigreek.appendOrClause(
					OrClause(3, (*it_args)->InVar(), (*it_args)->OutVar(),
							(*it_args)->UndecVar()));

			this->sat_new_pigreek.appendOrClause(
					OrClause(2, (*it_args)->NotInVar(),
							(*it_args)->NotOutVar()));

			this->sat_new_pigreek.appendOrClause(
					OrClause(2, (*it_args)->NotInVar(),
							(*it_args)->NotUndecVar()));

			this->sat_new_pigreek.appendOrClause(
					OrClause(2, (*it_args)->NotOutVar(),
							(*it_args)->NotUndecVar()));
		}

		noempty_clause.appendVariable((*it_args)->InVar());

		SetArguments *pred = (*it_args)->get_attackers();

		if (debug)
		{
			cout << "predecessors of " << (*it_args)->getName() << ": ";

			for (SetArgumentsIterator it_pred = pred->begin();
					it_pred != pred->end(); it_pred++)
				cout << (*it_pred)->getName() << " ";
			cout << endl;
		}

		if (pred->empty())
		{
			//c3
			this->sat_new_pigreek.appendOrClause(
					OrClause(1, (*it_args)->InVar()));

			this->sat_new_pigreek.appendOrClause((*it_args)->NotOutVar());

			this->sat_new_pigreek.appendOrClause((*it_args)->NotUndecVar());
		}
		else
		{
			OrClause c4_last_clause = OrClause();
			OrClause c9_or_undec_clause = OrClause();
			OrClause c8_bigor_clause = OrClause();

			for (SetArgumentsIterator it_pred = pred->begin();
					it_pred != pred->end(); it_pred++)
			{

				if (!this->A->exists(*it_pred))
					continue;

				//c5
				if (encoding == 0 || encoding == 1 || encoding == 3
						|| encoding == 5)
				{
					this->sat_new_pigreek.appendOrClause(
							OrClause(2, (*it_args)->NotInVar(),
									(*it_pred)->OutVar()));
				}

				//c4
				if (encoding == 0 || encoding == 2 || encoding == 3
						|| encoding == 5)
				{
					c4_last_clause.appendVariable((*it_pred)->NotOutVar());
				}

				//c9
				if (encoding == 0 || encoding == 1 || encoding == 4
						|| encoding == 5)
				{
					this->sat_new_pigreek.appendOrClause(
							OrClause(2, (*it_args)->NotUndecVar(),
									(*it_pred)->NotInVar()));

					c9_or_undec_clause.appendVariable((*it_pred)->UndecVar());
				}

				if (encoding == 0 || encoding == 2 || encoding == 4
						|| encoding == 5)
				{
					c8_bigor_clause.appendVariable((*it_pred)->InVar());
				}
			}

			//c4-end
			if (encoding == 0 || encoding == 2 || encoding == 3
					|| encoding == 5)
			{
				c4_last_clause.appendVariable((*it_args)->InVar());
				this->sat_new_pigreek.appendOrClause(c4_last_clause);
			}

			//c9-end
			if (encoding == 0 || encoding == 1 || encoding == 4
					|| encoding == 5)
			{
				c9_or_undec_clause.addHeadVariable((*it_args)->NotUndecVar());
				this->sat_new_pigreek.appendOrClause(c9_or_undec_clause);
			}

			//c8
			if (encoding == 0 || encoding == 2 || encoding == 4
					|| encoding == 5)
			{
				for (SetArgumentsIterator it_pred = pred->begin();
						it_pred != pred->end(); it_pred++)
				{
					OrClause to_add = OrClause();
					c8_bigor_clause.clone(&to_add);
					to_add.appendVariable((*it_pred)->NotUndecVar());
					to_add.appendVariable((*it_args)->UndecVar());
					this->sat_new_pigreek.appendOrClause(to_add);
				}
			}

		}
	}

	for (SetArgumentsIterator it_args = this->A->begin();
			it_args != this->A->end(); it_args++)
	{

		OrClause c7_last_clause = OrClause();
		SetArguments *pred = (*it_args)->get_attackers();

		if (pred->empty())
			continue;

		for (SetArgumentsIterator it_pred = pred->begin();
				it_pred != pred->end(); it_pred++)
		{

			if (!this->A->exists(*it_pred))
				continue;

			//c6
			if (encoding == 0 || encoding == 2 || encoding == 3
					|| encoding == 4)
			{
				this->sat_new_pigreek.appendOrClause(
						OrClause(2, (*it_pred)->NotInVar(),
								(*it_args)->OutVar()));
			}

			//c7
			if (encoding == 0 || encoding == 1 || encoding == 3
					|| encoding == 4)
			{
				c7_last_clause.appendVariable((*it_pred)->InVar());
			}
		}

		//c7-end
		if (encoding == 0 || encoding == 1 || encoding == 3 || encoding == 4)
		{
			c7_last_clause.appendVariable((*it_args)->NotOutVar());
			this->sat_new_pigreek.appendOrClause(c7_last_clause);
		}

	}

	this->sat_new_pigreek.appendOrClause(noempty_clause);

	return this->sat_new_pigreek.size();
}

/**
 * @brief Method for deriving a labelling from a SAT Formulae
 * @details	This method is a wrapper for a SAT Solver
 * @param[in] sat	The SATFormulae as input
 * @param[out] sat	The computed Labelling
 * @retval bool `true` if a solution is found, `false` otherwise
 */
bool Preferred::satlab(SATFormulae sat, Labelling *lab)
{
	stringstream cnf_string(stringstream::in | stringstream::out);
	sat.toSS(&cnf_string);

	if (debug)
	{
		cout << "Preparing the satsolver" << "\n";
		cout << cnf_string.str() << endl;
	}

	vector<int> lastcompfound = vector<int>();
	int retsat = precosat_lib(&cnf_string,
			3 * ((*(this->A->begin()))->get_af()->numArgs()), sat.size(),
			&lastcompfound);

	if (debug)
	{
		cout << retsat << endl;

		for (vector<int>::iterator solit = lastcompfound.begin();
				solit != lastcompfound.end(); solit++)
		{
			cout << *solit << " ";
		}
		cout << endl;
	}

	if (retsat != 20)
	{
		for (SetArgumentsIterator it = this->A->begin(); it != this->A->end();
				it++)
		{
			if (find(lastcompfound.begin(), lastcompfound.end(), (*it)->InVar())
					!= lastcompfound.end())
			{
				lab->add_label((*it), Labelling::lab_in);
				if (debug)
				{
					cout << (*it)->getName() << endl;
				}
				continue;
			}
			if (find(lastcompfound.begin(), lastcompfound.end(),
					(*it)->OutVar()) != lastcompfound.end())
			{
				lab->add_label((*it), Labelling::lab_out);
				continue;
			}
			if (find(lastcompfound.begin(), lastcompfound.end(),
					(*it)->UndecVar()) != lastcompfound.end())
			{
				lab->add_label((*it), Labelling::lab_undec);
				continue;
			}
		}
		if (debug)
		{
			cout << endl;
			cout << "in " << *(lab->inargs()) << endl;
			cout << "out " << *(lab->outargs()) << endl;
			cout << "undec " << *(lab->undecargs()) << endl;
		}
		return true;
	}
	return false;
}

void Preferred::prefSAT(SetArguments *the_a, SetArguments *the_c)
{
	this->cleanlabs();
	this->A = the_a;
	this->C = the_c;
	this->compute_new_pigreek();
	SATFormulae cnf = SATFormulae();

	this->sat_new_pigreek.clone(&cnf);
	do
	{
		Labelling prefcand = Labelling();
		SATFormulae cnfdf = SATFormulae();
		cnf.clone(&cnfdf);

		while (true)
		{
			Labelling res = Labelling();
			if (!this->satlab(cnfdf, &res))
			{
				break;
			}

			if (debug)
			{
				cout << endl;
				cout << "{";
				SetArgumentsIterator it;
				for (it = res.inargs()->begin(); it != res.inargs()->end();
						it++)
				{
					cout << (*it)->getName() << " ";
				}
				cout << "}" << endl;
			}

			res.clone(&prefcand);
			if (res.inargs()->cardinality() == C->cardinality())
				break;

			SetArgumentsIterator iter;
			for (iter = res.inargs()->begin(); iter != res.inargs()->end();
					iter++)
			{
				cnfdf.appendOrClause(OrClause(1, (*iter)->InVar()));
			}

			SetArguments difference = SetArguments();
			this->C->setminus(res.inargs(), &difference);
			OrClause remaining = OrClause();
			for (iter = difference.begin(); iter != difference.end(); iter++)
			{
				remaining.appendVariable((*iter)->InVar());
			}
			cnfdf.appendOrClause(remaining);
		}

		if (prefcand.empty())
			break;

		this->labellings.push_back(prefcand);

		OrClause oppsolution = OrClause();
		SetArgumentsIterator it;

		SetArguments difference = SetArguments();
		this->C->setminus(prefcand.inargs(), &difference);
		for (it = difference.begin(); it != difference.end(); it++)
		{
			oppsolution.appendVariable((*it)->InVar());
		}
		cnf.appendOrClause(oppsolution);

	} while (true);

	if (this->labellings.empty())
	{
		this->labellings.push_back(Labelling());
	}
}

/**@brief constructs a new instance computing prefSAT problems.
 *
 * Construct a new instance of Preferred type. The newly created instance has the solution of a SAT problem set to
 * an empty set by default.
 *
 */
Preferred::Preferred(){
	this->encoding = 0;
	this->labellings = vector<Labelling>();
	this->sat_new_pigreek = SATFormulae();
}

Preferred::~Preferred(){
	//TODO capire se questo provoca delle memory leak!
}

//FIXME ho modificato il prototipo di end aggiungendo un const finale! Parlarne con la Zanella!
//questa modifica serve solo per far funzionare l'operatore <<
/**@brief first element of the solution computed by prefSAT().
 *
 *	This function is, together with end(), one the basics functions to use to read the <b>whole</b> solution got by invoking
 *	the prefSAT() function. To read the result of that function you can:
 *
 *	\code
 *		Preferred pref=new Preferred();
 *		pref->prefSAT(a,c);
 *		//now we should read the result to ensure correctness of the algorithm
 *		for (auto it=pref->begin();it!=pref->end();it++){
 *			cout << *it << endl;
 *		}
 *	\endcode
 *
 *	Note that the <b>whole</b> solution computed by prefSAT() is <b>not</b> the solution interesting for the class PrefAlgorithm.
 *	If you want that solution, you can use getSolution() method.
 *
 * @return the iterator of the first element in the labellings.
 */
PreferredIterator Preferred::begin() const{
	return PreferredIterator(this->labellings.begin());
}

//FIXME ho modificato il prototipo di end aggiungendo un const finale! Parlarne con la Zanella!
//questa modifica serve solo per far funzionare l'operatore <<
/**@brief last element of the solution computed by the function prefSat().
 *
 * Use this function to cycle throughout the structure of labellings. For example:
 * \code
 * 	for (auto it=preferred->begin();it!=preferred; it++){
 * 		cout << "a set contained in preferred is "<< *it << endl;
 * 	}
 * \endcode
 *
 * Note that the <b>whole</b> solution computed by prefSAT() is <b>not</b> the solution interesting for the class PrefAlgorithm.
 * If you want that solution, you can use getSolution() method.
 *
 * @return the iterator of the last element in the labellings
 */
PreferredIterator Preferred::end() const{
	return PreferredIterator(this->labellings.end());
}

/**@brief get a copy of the solution computed by
 *
 * @return
 */
SetArgumentsVector* Preferred::getSolution(){
	SetArgumentsVector* result=new SetArgumentsVector();
	SetArguments* cloned;
	for (auto it=this->labellings.begin(); it!=this->labellings.end();it++){
		cloned=new SetArguments();
		(*it).inargs()->clone(cloned);
		result->push_back(cloned);
	}
	return result;
}


/**@brief prints out only the part of the solution interesting for the PrefAlgorithm class.
 *
 *
 * @param stream the stream to change
 * @param pref the Preferred structure holding the <b>whole</b> solution of prefSAT() algorithm
 * @return the stream changed
 */
ostream& operator<<(ostream& stream, const Preferred& pref){
	stream << "{ ";
	for (PreferredIterator it=pref.begin(); it!=pref.end();it++){
		stream << "{ ";
		for (auto itarg=(*it).inargs()->begin();itarg!=(*it).inargs()->end();itarg++){
			stream << (*itarg)->getName() << " ";
		}
		stream << "} ";
	}
	stream << "}";
	return stream;
}
