/**
 * @file 		SetArgumentsVector.cpp
 * @class 		SetArgumentsVector
 * @brief 		Class representing a vector of labelling assignment
 * @author 		Massimo Bono
 */

#include "SetArgumentsVector.h"

/**@brief constructs an empty vector of SetArgumentsVector
 *
 * This funcition creates a new instance of a SetArgumentsVector where:
 * \li the set of SetArguments is empty
 */
SetArgumentsVector::SetArgumentsVector() {
	this->v = vector<SetArguments*>();
}

/**@brief clone all the references used in the caller set
 *
 * The function clones the caller SetArgumentsVector and puts the clone in the area of memory pointed by the input parameter.
 * The function copies only the references to the object under the caller set, not the objects themselves: pratically
 * no Argument or Label contained in any SetArguments will be cloned. In the figure the red lines are created by this functions.
 *
 * \dot
 * 	digraph x {
 * 		subgraph cluster_set0 {
 * 			rankdir="LR";
 * 			A;
 * 			B;
 * 			C;
 * 		}
 * 		subgraph cluster_set1 {
 * 			rankdir="LR";
 * 			D;
 * 		}
 * 		subgraph cluster_set2 {
 * 			rankdir="LR";
 * 			E;
 * 			F;
 * 		}
 *
 *		subgraph cluster_lablist {
 *			label="caller";
 *			nodesep=0.05;
 *			vector [shape="record", label="<set0>|<set1>|<set2>", width="2.5"];
 *			vector:set0 -> A [lhead="cluster_set0"];
 *			vector:set1 -> D [lhead="cluster_set1"];
 *			vector:set2 -> E [lhead="cluster_set2"];
 *		}
 *
 *		subgraph cluster_lablist_clone {
 *			color="red";
 *			label="clone";
 *			nodesep=0.05;
 *			nodeclone [shape="record", label="<set0>|<set1>|<set2>", width="2.5", color="red"];
 *			nodeclone:set0 -> A [lhead="cluster_set0", color="red"];
 *			nodeclone:set1 -> D [lhead="cluster_set1", color="red"];
 *			nodeclone:set2 -> E [lhead="cluster_set2", color="red"];
 *		}
 *
 * 	}
 * \enddot
 *
 * \pre
 *  \li list must be constructed correctly;
 * \post
 *  \li the instance pointed by list contains the exact data of the caller
 *
 * @param list the object that will hold the clone of the caller
 */
void SetArgumentsVector::clone(SetArgumentsVector* list){
	for (auto it=this->begin(); it!=this->end();it++){
		list->push_back(*it);
	}
}

/**@brief Construct a SetArgumentsVector with stored the same elements stored in the parameter
 *
 * The function copies the values of the _list in the newly create instance, so changes to the new structure
 * will not change the original one. Moreover, because of the reference, this copy is fast.
 *
 * \pre
 *  \li _list must have been built correctly
 *
 * @param _list the initial value of the set of set of Arguments
 */
SetArgumentsVector::SetArgumentsVector(vector<SetArguments*>& _list){
	this->v = vector<SetArguments*>(_list);
}

//TODO testing
/**@brief Free correctly a SetArgumentsVector
 *
 *
 * The destructor free all the SetArguments pointed by this class. No Argument will be free though.
 * The way this function works can be shown with the graph displayed: all the red stuff is deallocates while the black items reamin untouched;
 * as the figure shows, only the Arguments themselves are not freed.
 *
 * \dot
 * 	digraph {
 * 		rankdir="LR";
 * 		subgraph clusterA {
 * 			color="red";
 * 			label="SetArgumentsVector";
 * 			P1 [label="pointer to SetArguments1" color="red"];
 * 			P2 [label="pointer to SetArguments2" color="red"];
 * 			P3 [label="pointer to SetArguments3" color="red"];
 * 			P4 [label="pointer to SetArguments4" color="red"];
 * 		}
 *
 * 		A1 [shape="record" label="{SetArguments1|{<f1>|<f2>|<f3>}}" color="red"];
 *		A2 [shape="record" label="{SetArguments2|{<f3>|<f4>}}" color="red"];
 *		A3 [shape="record" label="{SetArguments3|{<f0>|<f2>|<f7>}}" color="red"];
 *		A4 [shape="record" label="{SetArguments4|{<f6>|<f9>|<f2>|<f5>}}" color="red"];
 *
 *		P1->A1 [color="red"];
 * 		P2->A2 [color="red"];
 * 		P3->A3 [color="red"];
 * 		P4->A4 [color="red"];
 *
 *		subgraph nodes {
 *			rank="same";
 *			rankdir="LR";
 *	 		arg0 [label="n00"];
 * 			arg1 [label="n01"];
 * 			arg2 [label="n02"];
 * 			arg3 [label="n03"];
 * 			arg4 [label="n04"];
 * 			arg5 [label="n05"];
 * 			arg6 [label="n06"];
 * 			arg7 [label="n07"];
 * 			arg8 [label="n08"];
 * 			arg9 [label="n09"];
 *		}
 *		A1:f1 -> arg1 [color="red"];
 *		A1:f2 -> arg2 [color="red"];
 *		A1:f3 -> arg3 [color="red"];
 *		A2:f3 -> arg3 [color="red"];
 *		A2:f4 -> arg4 [color="red"];
 *		A3:f0 -> arg0 [color="red"];
 *		A3:f2 -> arg2 [color="red"];
 *		A3:f7 -> arg7 [color="red"];
 *		A4:f6 -> arg6 [color="red"];
 *		A4:f9 -> arg9 [color="red"];
 *		A4:f2 -> arg2 [color="red"];
 *		A4:f5 -> arg5 [color="red"];
 * 	}
 * \enddot
 *
 */
SetArgumentsVector::~SetArgumentsVector() {
	/*for (auto it=this->v.begin();it!=this->v.end();it++){
		cout << "elimino: " << endl;
		delete (*it);
	}*/
}

/**@brief add to all the set in the SetArgumentsVector the elements stored in the parameter
 *
 * This function allows you to add for each SetArguments inside the caller object every Argument stored
 * in the SetArguments named set.
 * Theorically this function implements the operator \f$ \otimes \f$:
 * \f[
 * 	A \otimes E \hat{=} \{ e_{i}^{new} : e_{i}^{new}=e_{i} \cup A\}
 * \f]
 * where:
 * \li A is a set of Arguments;
 * \li E is a set of set of Arguments;
 * \li \f$ e_{i} \f$ is a generic set inside E;
 *
 * Let's make it clearer with an example:
 * \li \f$ A=\{ a, b \}\f$
 * \li \f$ E=\{ \{ e, d \} \{ a, e \} \{ b, c, d \} \{ a, b \} \}\f$
 * If you assume this hypothesis then \f$ A \otimes E \f$ will be:
 * \f[
 * 	A \otimes E = \{ \{ a, b, e, d \} \{ a, b, e \} \{ a, b, c, d \} \{ a, b \} \}
 * \f]
 *
 * \pre
 *  \li set built correctly;
 * \post
 *  \li every set held in the caller object contains every Arguments stored in set object
 *
 * @param set the list of elements to be added to all the SetArguments stored in the caller object
 */
void SetArgumentsVector::addSetArgumentsToAll(const SetArguments* set){
	for (auto itlab=this->begin(); itlab!=this->end();itlab++){
		for (auto itset=set->begin(); itset!=set->end();itset++){
			(*itlab)->add_Argument(*itset);
			//itlab->add_label(*itset,(Label)((*itset)->getName()));
			//itlab->inargs()->add_Argument(*itset);
		}
	}
}

/**@brief check wether or not this set is completely empty.
 *
 *
 *
 * @return TRUE if in the caller object there are no SetArguments references, FALSE otherwise
 */
bool SetArgumentsVector::empty(){
	return this->v.empty();
}

/**
 * @brief pop the top SetArguments of the vector
 *
 */
void SetArgumentsVector::pop_back(){
	this->v.pop_back();
}

/**@brief check wether or not a SetArguments exist in the caller SetArgumentsVector
 *
 * This function allows you to check if a SetArguments is stored in the caller object.
 * The function check the real value of the sets, not only the reference.
 *
 * \dot
 * 	digraph x {
 * 		rankdir="LR";
 *
 * 		A [label="A\n{a,b,c}"];
 * 		B [label="B\n{a,d,e}"];
 * 		C [label="C\n{a,b,c}"];
 * 		D [label="D\n{d,f,e}"];
 *
 * 		setA [shape="record" label="<f1>|<f2>|<f3>"];
 *
 * 		setA:f1->A;
 * 		setA:f2->B;
 * 		setA:f3->D;
 * 	}
 * \enddot
 *
 * Let assume that you want to check if the set "C" exist in the SetArgumentsVector.
 * C is identical to A, so C is basically contained in the SetArgumentsVector. The function
 * check first if the pointer is stored in the set and only then check if the real value
 * is contained in the set; in this way:
 * \li the search of the pointer itself results in failure;
 * \li the search of value results in success;
 *
 *
 * @param lab the SetArguments to look for
 * @return TRUE if the SetArguments is stored in the caller objct, FALSE otherwise
 */
bool SetArgumentsVector::exist(const SetArguments* lab)const {
	// confronto per puntatori e poi per valori. l'or è lazy
	for (auto it=this->begin(); it!=this->end(); it++)
		if ( lab==(*it) )
			return true;

	for (auto it=this->begin(); it!=this->end(); it++)
		if (lab->equal(**it))
			return true;

	return false;
}

/**@brief the SetArguments positioned to i index
 *
 *
 * @return the SetArguments stored at the i position
 */
SetArguments* SetArgumentsVector::at(unsigned int i) const{
	return this->v.at(i);
}

/**@brief add a new SetArguments in this set
 *
 * \pre
 *  \li set not NULL;
 * \post
 *  \li the set data is copied into the data structure
 *
 * @param set the new label to insert in the structure
 */
void SetArgumentsVector::push_back(SetArguments* set){
	this->v.push_back(set);
}

/**removes all the structured contained in the instance.
 *
 */
void SetArgumentsVector::clearAll(){
	this->v.clear();
}

/**@brief the size of this set of SetArguments
 *
 * @returns the number of SetArguments stored in this instance
 *
 */
unsigned int SetArgumentsVector::size() const{
	return this->v.size();
}

/**@brief return the first element of the list
 *
 * This function is essential to navigate in the data structure, usually to find an element.
 * You can do it easily like this code:
 * \code
 * 	for (auto it=labellingListInstance.begin();it!=labellingListInstance.end();it++){
 * 		cout << "labelling element: " << *it << endl;
 * 	}
 * \endcode
 *
 * @return a pointer to the first element of this SetArguments list
 */
SetArgumentsVectorIterator SetArgumentsVector::begin() const{
	return SetArgumentsVectorIterator(this->v.begin());
}

/**@brief return the last element of the list
 *
 * This function is essential to navigate in the data structure, usually to find an element.
 * You can do it easily like this code:
 * \code
 * 	for (auto it=labellingListInstance.begin();it!=labellingListInstance.end();it++){
 * 		cout << "labelling element: " << *it << endl;
 * 	}
 * \endcode
 *
 * @return a pointer to the last element of this SetArguments list
 */
SetArgumentsVectorIterator SetArgumentsVector::end() const{
	return SetArgumentsVectorIterator(this->v.end());
}

/**@brief overriding of the operator <<
 *
 * The operator will print a string representation of lablist.
 * An example of output stream of this function may be:
 *
 * \p { {a c } {b c d } {e g d a w f }}
 *
 * The operator will return the sentence:
 * \p { }
 * if and only if lablist size is zero.
 *
 */
ostream& operator<<(ostream& stream, const SetArgumentsVector& lablist){
	stream << "{ ";
	if (lablist.size()!=0)
		for (auto it=lablist.begin();it!=lablist.end();it++)
			stream << **it << " ";
	stream << " }";
	return stream;
}

/**@brief overriding of the operator +.
 *
 * \f$ A+B \f$ is a <b>new</b> SetArgumentsVector where all the elements stored in b are appended to a copy of a.
 * "+" operator will only copy the reference, not the elements themselves: so <b>every changes</b> to a variable will
 * probably change all the copied instances.
 * For example if there are 2 SetArgumentsVector:
 * \f[
 *  A={ {1,3}, {3,4,5}, {,5,6,1,2} }
 * \f]\f[
 *	B={ {4}, {5}, {3,4}, {8,6}}
 * \f]
 * The result will be:
 * \f[
 *  A+B={ {1,3}, {3,4,5}, {,5,6,1,2}, {4}, {5}, {3,4}, {8,6} }
 * \f]
 *
 * @param a the first term of the concatenation
 * @param b the second term of the concatenation
 *
 */
SetArgumentsVector operator+(SetArgumentsVector a, const SetArgumentsVector& b){
	SetArgumentsVector result=SetArgumentsVector(a);
	for (auto it=b.begin();it!=b.end();it++)
		result.push_back(*it);
	return result;
}

/**@brief swap to different area of memory occupied by SetArgumentsVector
 *
 * @param first a SetArgumentsVector to be swapped
 * @param second a SetArgumentsVector to be swapped
 */
void SetArgumentsVector::swap(SetArgumentsVector& first, SetArgumentsVector& second){
	using std::swap;
	swap(first.v,second.v);
}

/**@brief assign the same value of the rhs in the lhs
 *
 * @param rhs the value to assign
 * @return the value assigned
 */
SetArgumentsVector& SetArgumentsVector::operator=(SetArgumentsVector rhs){
	SetArgumentsVector::swap(*this,rhs);
	return *this;
}


/**@brief checks if the 2 SetArgumentsVector store the same SetArguments.
 *
 * The functionallows you to compare 2 SetArgumentsVector and
 * test if 2 SetArgumentsVector store the same information.
 * The operator:
 * \li doesn't care about SetArguments order in the SetArgumentsVector. For example these 2 sets are equal:
 * 	\f[A=\{\{a,b,c\}\{d,e,f\}\}\f]
 * 	\f[B=\{\{d,e,f\}\{a,b,c\}\}\f]
 * \li doesn't care about the Argument order in a particular SetArguments. For example these 2 sets are equal:
 *	\f[A=\{\{a,b,c\}\{d,e,f\}\}\f]
 * 	\f[B=\{\{a,c,b\}\{d,e,f\}\}\f]
 *
 * @param other the set to be compared
 * @return TRUE if the 2 Sets are equal, FALSE otherwise
 */
bool SetArgumentsVector::operator==(const SetArgumentsVector &other) const{
	if (this->size()!=other.size())
		return false;
	for (auto it=this->begin();it!=this->end();it++)
		if (other.exist(*it)==false)
			return false;
	return true;
}


/**@brief checks if the 2 SetArgumentsVector differ from somthing.
 *
 * The function allows you to compare 2 SetArgumentsVector and
 * test if 2 SetArgumentsVector store the same information.
 * The operator:
 * \li doesn't care about SetArguments order in the SetArgumentsVector. For example these 2 sets are equal:
 * 	\f[A=\{\{a,b,c\}\{d,e,f\}\}\f]
 * 	\f[B=\{\{d,e,f\}\{a,b,c\}\}\f]
 * \li doesn't care about the Argument order in a particular SetArguments. For example these 2 sets are equal:
 *	\f[A=\{\{a,b,c\}\{d,e,f\}\}\f]
 * 	\f[B=\{\{a,c,b\}\{d,e,f\}\}\f]
 *
 * @param other the set to be compared
 * @return FALSE if the 2 Sets are equal, TRUE otherwise
 */
bool SetArgumentsVector::operator!=(const SetArgumentsVector &other) const{
	return !(*this==other);
}


