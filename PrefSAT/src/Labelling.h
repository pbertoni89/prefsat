
#include <map>
#include <string>
using namespace std;

#include "Argument.h"
#include "SetArguments.h"
#include <iostream>
#include <map>

#ifndef LABELLING_H_
#define LABELLING_H_

typedef string Label;

/**
 * @brief Class defining a const iterator for the elements of a the labellings
 */
class LabelIterator : public map<Argument*, Label>::const_iterator
{
public:
	LabelIterator() : map<Argument*, Label>::const_iterator() {
	};
	LabelIterator(map<Argument*, Label>::const_iterator it) : map<Argument*, Label>::const_iterator(it) {
	};
	Label* operator->() {
		return (Label* const)&(map<Argument*,Label>::const_iterator::operator->()->second);
	};
	Label operator*() {
		return map<Argument*, Label>::const_iterator::operator*().second;
	}
	LabelIterator &operator=(const LabelIterator &param) {
		map<Argument*, Label>::const_iterator::operator = (param);
		return *this;
	}
	/**@brief return the value of the key of the pair pointed by this iterator
	 *
	 * You can use this function to retrieve from an iterator, the value of the key stored in the pair of the map. For example:
	 * \code
	 * 		cout << "arguments stored in this Labelling:"<<endl;
	 *		for (auto it=this->labelling.begin();it!=this-<labelling.end();it++){
	 *			cout << *(it.getKeyValue()) << endl;
	 *		}
	 * \endcode
	 * */
	Argument* getKeyValue(){
		return (map<Argument*,Label>::const_iterator(*this))->first;
	}
};

class Labelling
{
	/**a map that associate to each pointer of argument its name.
	 * It might be a little odd to set this field in this way. At the first glance, it should be better to define the data structure
	 * like this:
	 * \code
	 * 	map<Label,Argument*> labelling;
	 * \endcode
	 * However, you should keep in mind that the Argument* is just a pointer while the Label is an entire string.
	 * So it is just natural to set as key of map a pointer (tiny structure) and the label as the value of the map (large structure).
	 */
	map<Argument *, Label> labelling;
	SetArguments in;
	SetArguments out;
	SetArguments undec;

public:

	const static Label lab_in;
	const static Label lab_out;
	const static Label lab_undec;
	Labelling();
	Labelling(SetArguments* set);
	virtual ~Labelling();
	void add_label(Argument *, Label);
	bool exists_argument_labelling(Argument *);
	Label get_label(Argument *);
	SetArguments *inargs();
	SetArguments *outargs();
	SetArguments *undecargs();
	bool empty();
	void clone(Labelling *);

	SetArguments* getSetArguments();
	LabelIterator begin() const;
	LabelIterator end() const;
	unsigned int size() const;

	LabelIterator find(const Argument* arg);

};

bool operator==(const Labelling& lhs,const Labelling& rhs);
bool operator!=(const Labelling& lhs,const Labelling& rhs);

ostream& operator<<(ostream& , const Labelling& );

#endif /* LABELLING_H_ */
