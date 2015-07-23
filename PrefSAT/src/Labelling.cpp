/**
 * @file 		Labelling.cpp
 * @class 		Labelling
 * @brief 		Class representing a single labelling assignment
 * @author 		Federico Cerutti <federico.cerutti@acm.org>
 * @copyright	GNU Public License v2
 */


#include "Labelling.h"

/**
 * @var Label Labelling::lab_in
 * @brief Label representing an `in` argument
 */
const Label Labelling::lab_in = "in";

/**
 * @var Label Labelling::lab_out
 * @brief Label representing an `out` argument
 */
const Label Labelling::lab_out = "out";

/**
 * @var Label Labelling::lab_undec
 * @brief Label representing an `undec` argument
 */
const Label Labelling::lab_undec = "undec";

/**
 * @brief	Constructor
 */
Labelling::Labelling()
{
	this->labelling = map<Argument *, Label>();
	this->in = SetArguments();
	this->out = SetArguments();
	this->undec = SetArguments();
}

/**@brief construct a new Labelling structure starting from a SetArguments.
 *
 * Use this constructor if you want to convert a SetArguments data in a Labelling instance
 *
 * \pre
 *	\li set not NULL
 *
 *
 * @param set represents the set that contains all the initial Arguments of this Labelling
 */
Labelling::Labelling(SetArguments* set){
	this->labelling = map<Argument *, Label>();
	this->in = SetArguments();
	this->out = SetArguments();
	this->undec = SetArguments();
	for (auto it=set->begin();it!=set->end();it++){
		this->add_label(*it,(*it)->getName());
	}
}

/**@brief Return the first Label of the argument inside this set
 *
 * The function is used to cycle among all the Argument* stored in this Labelling instance.
 * You can use this function to enumerate the arguments store in this instance using this code:
 *
 * \code
 *  for (auto it=labelingInstance->begin();it!=labellingInstance->end(); it++){
 *  	cout << "argument stored: << afInstance.getArgumentsByName(*it)<< endl;
 *  }
 * \endcode
 *
 * @return an iterator pointing the Label of the first argument stored in this class
 *
 */
LabelIterator Labelling::begin() const{
	return LabelIterator(this->labelling.begin());
}

/**@brief Return the last Label of the argument inside this set
 *
 * The function is used to cycle among all the Argument* stored in this Labelling instance.
 * You can use this function to enumerate the arguments store in this instance using this code:
 *
 * \code
 *  for (auto it=labelingInstance->begin();it!=labellingInstance->end(); it++){
 *  	cout << "argument stored: << afInstance.getArgumentsByName(*it)<< endl;
 *  }
 * \endcode
 *
 * @return an iterator pointing the Label of the last argument stored in this class
 *
 */
LabelIterator Labelling::end() const{
	return LabelIterator(this->labelling.end());
}

/**@brief converts a Labelling structure in a SetArguments
 *
 * The function creates a new SetArguments instance from a Labelling ones. Both structures
 * represents, more or less, a set of Arguments, but thery are incompatible between them.
 * While the constructor of Labelling resolves the conversion from SetArguments to Labelling, this function
 * solve the opposite conversion.
 *
 * \post
 *  \li a new SetArguments instance is allocate din the heap and must be freed <b>manually</b>
 *
 * @return a SetArguments instance with the same Arguments store in the caller structure
 *
 */
SetArguments* Labelling::getSetArguments(){
	SetArguments* result = new SetArguments();
	//map<Argument*,Label>::iterator
	//adding directly the pointers to the arguments: it makes it more quick
	for (auto it=this->labelling.begin(); it!=this->labelling.end();it++)
		result->add_Argument(it->first);
	return result;
}

/**
 * @brief	Add a new label to this set of labelling
 *
 * This function allows you to add a association <Argument*, Label> inside the
 * map structure held in the caller Labelling structure. Before to add the association
 * to the map, however, this function check if the key arg is already present in the map:
 * \li if it isn't, the association is added to the map;
 * \li if it is the map remains <b>unchanged</b>;
 *
 * \pre
 *  \li arg points to an existing Argument
 * \post
 *  \li the association <arg,l>is added to the map only if the uniqueness of the key is preserved.
 *
 *
 * @param[in] arg	The argument to which this labelling applies
 * @param[in] l		The label. Valid values for are:
 * 					 * Labelling::lab_in
 * 					 * Labelling::lab_out
 * 					 * Labelling::lab_undec
 */
void Labelling::add_label(Argument * arg, Label l)
{
	this->labelling.insert(pair<Argument *, Label>(arg, l));
	if (l.compare(Labelling::lab_in) == 0)
		this->in.add_Argument(arg);
	else if (l.compare(Labelling::lab_out) == 0)
		this->out.add_Argument(arg);
	else if (l.compare(Labelling::lab_undec) == 0)
		this->undec.add_Argument(arg);
}

/**
 * @brief	Check whether an argument is in this labelling or not
 * @param[in] arg A pointer to an Argument
 * @retval bool
 */
bool Labelling::exists_argument_labelling(Argument *arg)
{
	return (this->labelling.find(arg) != this->labelling.end());
}

/**
 * @brief Returns the label of a given argument
 * @param[in] arg	A pointer to an argument
 * @retval Label
 */
Label Labelling::get_label(Argument *arg)
{
	return this->labelling.at(arg);
}

/**
 * @brief Returns the set of arguments labelled as `in`
 * @retval SetArguments *
 */
SetArguments *Labelling::inargs()
{
	return &(this->in);
}

/**
 * @brief Returns the set of arguments labelled as `out`
 * @retval SetArguments *
 */
SetArguments *Labelling::outargs()
{
	return &(this->out);
}

/**
 * @brief Returns the set of arguments labelled as `undec`
 * @retval SetArguments *
 */
SetArguments *Labelling::undecargs()
{
	return &(this->undec);
}

/**
 * @brief Check whether or not this labelling is empty
 * @retval bool
 */
bool Labelling::empty()
{
	return this->labelling.empty() && this->in.empty() && this->out.empty() && this->undec.empty();
}

/**
 * @brief Clone this labelling into a new one
 * @param[out] other A pointer to a Labelling which will be the clone of this one
 * @retval void
 */
void Labelling::clone(Labelling *other)
{
	map<Argument *, Label>::iterator it;
	for (it = this->labelling.begin(); it != this->labelling.end(); it++)
	{
		other->add_label((*it).first, (*it).second);
	}
}

Labelling::~Labelling()
{
	// TODO Auto-generated destructor stub
}


/**@brief get the number of elements stored in this set
 *
 * @return the number of elements stored in this set
 */
unsigned int Labelling::size() const{
	return this->labelling.size();
}

/**@brief find a Label which has as key the pointer to an Argument
 *
 * This function allows you to search in this set of Arguments to find a particular Label.
 * You can use this function like this:
 *
 * \code
 * 	SetArguments* A=new SetArguments(af,(string[]){"A","B","D"},3);
 * 	Labelling* lab=new Labelling(A);
 * 	auto it=lab->find(af.getArgumentsByName("B"));
 * 	cout << *it << endl;
 * \endcode
 *
 * \pre
 *  \li arg not NULL
 *
 * @param arg the pointer of the argument which has as name the Label to found
 * @return
 * 	\li an iterator to the label of the Argument arg;
 * 	\li this->end() if the key was not found
 */
LabelIterator Labelling::find(const Argument* arg){
	return LabelIterator(this->labelling.find((Argument*)(arg)));
}


/**@brief compare two Labelling according to their list.
 *
 * The operator returns TRUE if any Arguments held by lhs  is also stored in rhs and viceversa.
 * The order of the elements is irrelevant to the output of the function; so these 2 instances are equal:
 *
 * \f[
 * 	A = {a,b,c,d,e}
 * \f]\f[
 *  B = {b,e,a,d,c}
 * \f]
 *
 * @param lhs the first Labelling to compare;
 * @param rhs the second Labelling to compare;
 * @return TRUE if:
 *  \li lhs has the same Arguments stored in rhs, regardless of the order.
 *
 */
bool operator==(const Labelling& lhs,const Labelling& rhs) {
	if (lhs.size()!=rhs.size())
		return false;

	const Argument* arg;
	for (auto it=lhs.begin();it!=lhs.end();it++){
		arg=it.getKeyValue();
		if (((Labelling&)rhs).find(arg)==rhs.end()){
			return false;
		}
	}
	return true;
}

/**@brief computes the opposite of the operator ==
 *
 * @param lhs the first Labelling to compare
 * @param rhs the second Labelling to compare
 * @return TRUE if:
 *  \li the size of lhs is different from rhs one;
 *  \li lhs owns different Arguments from rhs;
 *
 *  FALSE otherwise;
 */
bool operator!=(const Labelling& lhs,const Labelling& rhs) {
	return !(lhs==rhs);
}


/**@brief prints a list of labels' nodes contained in this instance
 *
 * This operator allows you to quickly display all the elements stored in a Labelling structure, like a normal SetArguments
 *
 */
ostream& operator<<(ostream& stream, const Labelling& lab){
	stream << "{";
	for (LabelIterator it=lab.begin();it!=lab.end();it++){
		stream << *it << " ";
	}
	stream << "}";
	return stream;
}

