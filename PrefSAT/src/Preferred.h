/**
 * @file
 *
 * @brief use this class to compute PrefSAT
 *
 * This class offers you an implementation of prefSAT algorithm.
 * To use this class effectively you can code like this:
 * \code
 * 	Preferred pref=new Preferred();
 * 	//compute solution
 * 	pref->prefSAT(&someSet,&someSet);
 * 	//print solutions
 * 	for (auto it=pref->begin();it!=pref->end();it++){
 * 		cout << "subset: " << *it << endl;
 * 	}
 * 	//clean temporary variables to allows instance reuse
 * 	pref->cleanlabs();
 * \endcode
 *
 *
 *  Created on: 10 Jun 2013
 *      Author: geryo
 */

#ifndef PREFERRED_H_
#define PREFERRED_H_

#include "Labelling.h"
#include "SetArguments.h"
#include <vector>
#include "AF.h"
#include "SATFormulae.h"
#include "SetArgumentsVector.h"
#include <iostream>
#include <sstream>

using namespace std;

class PreferredIterator : public vector<Labelling>::const_iterator
{
public:
	//SetArgumentsIterator() : map<string, Argument *>::const_iterator() {};
	PreferredIterator(vector<Labelling>::const_iterator it) : vector<Labelling>::const_iterator(it) {};
	//Argument ** operator->() {return (Argument ** const)&(map<string, Argument *>::const_iterator::operator->()->second); };
	Labelling operator*() { return vector<Labelling>::const_iterator::operator*(); }
	//PreferredIterator &operator=(const PreferredIterator &param) { vector<Labelling>::const_iterator::operator = (param); return *this; }
};


int precosat_lib(stringstream *the_cnf, int num_var, int num_cl, vector<int> *result);

extern bool debug;

class Preferred
{
	/*FIXME ho aggiunto questa amicizia tra classi per poter usare vector<Labelling>
	 * in PreferredExtension alla riga:
	 * E_star=LabellingList(this->preferred.labellings);
	 */
	//friend class PreferredExtension;
	SetArguments *A; //!< @brief the set of arguments A
	SetArguments *C; //!< @brief the set of arguments C
	int encoding;
	SATFormulae sat_new_pigreek;
	//E star
	vector<Labelling> labellings;
	int compute_new_pigreek();
	bool satlab(SATFormulae, Labelling *);
	void cleanlabs();
public:
	typedef vector<Labelling>::iterator iterator;
	Preferred();
	virtual ~Preferred();
	void prefSAT(SetArguments *, SetArguments *);


	PreferredIterator begin() const;
	PreferredIterator end() const;

	SetArgumentsVector* getSolution();

};

ostream& operator<<(ostream& , const Preferred& );

#endif /* PREFERRED_H_ */
