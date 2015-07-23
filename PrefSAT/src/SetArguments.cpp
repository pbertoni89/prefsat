/**
 * @file 		SetArguments.cpp
 * @class 		SetArguments
 * @brief 		Class encompassing a set of arguments
 * @author 		Federico Cerutti <federico.cerutti@acm.org>
 * @copyright	GNU Public License v2
 */

#include "SetArguments.h"

/**
 * @brief Simple constructor
 */
SetArguments::SetArguments()
{
	this->arguments = map<string, Argument *>();
	this->key_assoc = map<int, string>();
}

/**construct a new set of arguments by adding all the arguments whose names are inside the array passed
 *
 * \pre
 *  \li names represents an array of string
 *  \li names is not NULL
 *  \li each element of names represents a valid name of an argument
 *
 * @param af a structure created by parsing a file representing all the possible nodes
 * @param names an array storing the names of all the nodes you want to have inside the set
 * @param length indicates the length of the array passed as parameter
 */
SetArguments::SetArguments(AF af, string names[], int length){
	this->arguments = map<string, Argument *>();
	this->key_assoc = map<int, string>();
	for (int i=0; i<length; i++)
		this->add_Argument(af.getArgumentByName(names[i]));
}

/**
 * @brief	Add an argument to the set
 *
 * The function adds a new argument inside this SetArguments. Because this operation adds only
 * a reference of the Argument, not the Argument itself, it can be removed from the set easily
 * without remove the instanc eof the Argument itself. Moreover because
 * in the map every key must be unique this function check if the Argument is already
 * inside the map:
 * \li if it isn't the reference of the Argument is added in the map;
 * \li if it is, the structure will<b>be</b> changed whatsoever
 *
 * \pre
 *  \li argument must be not NULL
 * \post
 *  \li the argument (if it isn't already stored in the map) is stored in the map
 *
 * @param[in] arg Pointer to an Argument
 */
void SetArguments::add_Argument(Argument *arg)
{
	this->arguments.insert(pair<string, Argument *>(arg->getName(), arg));
	this->key_assoc.insert(pair<int, string>(arg->getNumber(), arg->getName()));
}

/**
 * @brief		Retuns the cardinality of this set
 * @retval int
 */
int SetArguments::cardinality() const {
	return (int) this->arguments.size();
}

/**
 * @brief		This method returns the pointer to the Argument whose name is given as parameter
 * @param[in] name	 The name of the argument
 * @retval Argument* The pointer to the Argument object, or NULL if not found
 */
Argument *SetArguments::getArgumentByName(string name) {

	return this->arguments.at(name);
}

/**
 * @brief		This method returns the pointer to the Argument whose identification number is given as parameter
 * @param[in] num	 The name of the argument
 * @retval Argument* The pointer to the Argument object, or NULL if not found
 */
Argument *SetArguments::getArgumentByNumber(int num) {

	return this->arguments.at(this->key_assoc.at(num));
}

/**
 * @brief	Check wether or not this set is empty
 * @retval bool TRUE if the set is empty, FALSE otherwise
 */
bool SetArguments::empty() {

	return this->arguments.empty();
}

/**
 * @brief 	Begin of the iterator for this set of arguments
 * @retval SetArgumentsIterator An iterator pointing at the first of the elements of this set
 */
SetArgumentsIterator SetArguments::begin() const {

	return SetArgumentsIterator((this->arguments.begin()));
}

/**
 * @brief 	End of the iterator for this set of arguments
 * @retval SetArgumentsIterator An iterator pointing at the last of the elements of this set
 */
SetArgumentsIterator SetArguments::end() const {

	return SetArgumentsIterator(this->arguments.end());
}

/**
 * @brief Check whether this set is a subset of `other`
 * @param[in] other	The other set to check
 * @retval bool
 */
bool SetArguments::is_subset_equal(SetArguments *other) {

	if (this->empty() && other->empty())
		return true;
	if (this->empty() && !other->empty())
		return true;
	if (!this->empty() && other->empty())
		return false;
	if (this->cardinality() > other->cardinality())
		return false;
	for (SetArgumentsIterator it = this->begin(); it != this->end(); it++)
		if (!other->exists((*it)))
			return false;
	return true;
}

/**
 * @brief Check whether this set is a proper subset of `other`
 * @param[in] other	The other set to check
 * @retval bool
 */
bool SetArguments::is_subset(SetArguments *other) {

	if ((this->cardinality() < other->cardinality()) && this->is_subset_equal(other))
		return true;
	return false;
}

/**\brief convert a SetArguments in a vector of SetArguments
 *
 * The figure shows the behaviour of the function: red stuff is created by this function.
 * Note that the called SetArguments will <b>not</b> be changed by this function.
 *
 * \dot
 * 	digraph {
 *
 * 		param [shape="record" label="calling SetArguments\n<l1>|<l2>|<l3>|<l4>|<l5>"];
 *
 *		subgraph cluster_B {
 *			label="vector<Setarguments*> (return value)";
 *			color="red";
 *			s01 [shape="record" label="<l1>" color="red"];
 *			s02 [shape="record" label="<l1>" color="red"];
 *			s03 [shape="record" label="<l1>" color="red"];
 *			s04 [shape="record" label="<l1>" color="red"];
 *			s05 [shape="record" label="<l1>" color="red"];
 *		}
 *
 * 		n01;
 * 		n02;
 * 		n03;
 * 		n04;
 * 		n05;
 *
 * 		param:l1 -> n01;
 * 		param:l2 -> n02;
 * 		param:l3 -> n03;
 * 		param:l4 -> n04;
 * 		param:l5 -> n05;
 *
 *		s01:l1 -> n01 [color="red"];
 *		s02:l1 -> n02 [color="red"];
 *		s03:l1 -> n03 [color="red"];
 *		s04:l1 -> n04 [color="red"];
 *		s05:l1 -> n05 [color="red"];
 *
 * 	}
 * \enddot
 *
 * \post
 *  \li if "n" is the number of Arguments pointed by this SetArguments, "n" new SetArguments will be created inside the memory;
 *
 *
 * \return a vector of SetArguments, where every element is composed by a single Argument held by the calling instance.
 */
vector<SetArguments*> SetArguments::getSingletons() {
	vector<SetArguments*> singletons = vector<SetArguments*>();
	for (SetArgumentsIterator it = this->begin(); it!= this->end(); it++) {
		SetArguments *s = new SetArguments();
		s->add_Argument(*it);
		singletons.push_back(s);
	}
	return singletons;
}

/**
 * computes the nodes which are attacked by the argument passed as parameter.
 * Both the node and its attacks are contained in the caller set.
 * For example in this graph:
 * \dot
 * 	digraph b{
 * 		rankdir="LR";
 * 		subgraph cluster {
 * 		label="setarg";
 * 		A; B; C;
 * 		}
 * 		D; E;
 * 		A->B;
 * 		B->C;
 * 		C->B;
 * 		A->D;
 * 		E->A;
 * 		A->E;
 * 	}
 * \enddot
 * the return value of the call:
 * \code
 *		result=SetArguments();
 *		setarg->getArgumentAttacksInSet(A,result);
 * \endcode
 *	would be only {B} because D and E are not contained in the set "setarg".
 *
 *	\pre
 *	 \li arg is contained in the caller set;
 *	 \li arg not NULL;
 *	 \li setarg is not NULL;
 *
 * @param arg the argument which attack other arguments
 * @return a set of nodes (setArguments) which are attacked by arg parameter and are contained in the caller set
 */
SetArguments* SetArguments::getArgumentAttacksInSet(Argument* arg){
	SetArguments* resulttmp;
	resulttmp=arg->get_attacks();
	//devo togliere da resulttmp tutti i nodi che non appartengono a setarg
	resulttmp->synchWithSet(this);
	return resulttmp;
}

/**
 * computes the nodes which are attacks the argument passed as parameter.
 * Both the node and its attackers are contained in the caller set.
 * For example in this graph:
 * \dot
 * 	digraph b{
 * 		rankdir="LR";
 * 		subgraph cluster {
 * 		label="setarg";
 * 		A; B; C;
 * 		}
 * 		D; E;
 * 		A->B;
 * 		B->C;
 * 		C->B;
 * 		A->D;
 * 		E->A;
 * 		A->E;
 * 	}
 * \enddot
 * the return value of the call:
 *	\code
 *		result=SetArguments();
 *		setarg->getArgumentAttackersInSet(A,result);
 *	\endcode
 *	would be only {} because E is not contained in the set "setarg".
 *
 *	\pre
 *	 \li arg is contained in the caller set;
 *	 \li arg not NULL;
 *	 \li setarg is not NULL;
 *
 * @param arg the argument which is attacked by other arguments
 * @return a set of nodes (setArguments) which attacks arg parameter and are contained in the caller set
 */
SetArguments* SetArguments::getArgumentAttackersInSet(Argument* arg){
	SetArguments* resulttmp;
	resulttmp=arg->get_attackers();
	//devo togliere da resulttmp tutti i nodi che non appartengono a setarg
	resulttmp->synchWithSet(this);
	return resulttmp;
}

/**
 * @brief Setmisun
 *
 * Implements the operator of set minus:
 * \f[
 * 	A-B={a \in A | a \not \in B}
 * \f]
 *
 * The operation return simply a SetArguments without interfere with the Arguments pointed by it
 *
 * @param[in] other The other term of the subtraction
 * @param[out] res	The result of the subtraction
 */
void SetArguments::setminus(SetArguments *other, SetArguments *result) {

	this->clone(result);
	for (SetArgumentsIterator it = other->begin(); it != other->end(); it++)
		if (result->exists((*it)))
			result->remove((*it));
}

/**
 * @brief 	Check whether or not an argument exists in this set
 * @param[in] arg
 * @retval bool
 */
bool SetArguments::exists(Argument * arg) {
	return (this->arguments.find(arg->getName()) != this->arguments.end());
}

/**
 * @brief 	Remove an argument from this set
 *
 * Removes an argument from the current SetArguments. Because the arguments
 * themselves stored in the structured are pointer, using this function will delete only
 * the pointer itself stored in map: so this function <b>will not</b> erase the structured pointed.
 *
 * \pre
 *  \li arg is not NULL
 * \post
 *  \li the reference stored in this structure is removed;
 *  \li the structure pointed by the pointer stored in this structure remain <b>intact</b>
 *
 * @param[in] arg the argument to remove from this map
 */
void SetArguments::remove(Argument * arg) {

	this->arguments.erase(arg->getName());
	//TODO secondo me qui bisogna eliminare anche la referenza in keyassoc!!! Parlarne con Pat
	//Pat: non è un metodo che abbiamo scritto noi, quindi vattelapesca
}

/**Removes all the arguments in the SetArguments keeping it ready to store new values.
 *
 */
void SetArguments::remove_All_Arguments(){
	this->arguments.clear();
	this->key_assoc.clear();
}

/**
 * @brief 	Clone this set.
 *
 * This function clone only this structure. So, since the map storing the arguments stores the pointer,
 * the pointer to the Arguments will <b>be cloned</b>, not the Arguments themselves!
 *
 * @param[in] set The set that will be the new clone
 * @retval void
 */
void SetArguments::clone(SetArguments * set) {

	for (SetArgumentsIterator it = this->begin(); it != this->end(); it++)
		set->add_Argument((*it));
}

/**
 * @brief Get the arguments in the caller set which are attacked by at least one node in attackers
 *
 *
 * The function returns all the nodes which are contained in the caller setArguments attacked by at least one
 * node in attackingSetArguments. For example in this graph the function would return {A,C}
 *
 * \dot
 * digraph a {
 *  rankdir="LR";
 * 	subgraph cluster1 {
 * 		label="caller set"
 * 		A;
 * 		B;
 * 		C;
 * 	}
 * 	subgraph cluster2 {
 * 		label="attacking set"
 * 		D;
 * 		E;
 * 	}
 * 	F;
 * 	G;
 *
 *	A->B;
 *	B->C;
 *	C->A;
 *	D->E;
 *	F->D;
 *	E->C;
 *	E->A;
 *	D->A;
 *	D->G;
 *	G->F;
 *	F->G;
 *	F->B;
 * }
 * \enddot
 *
 * \pre
 *  \li attackers correctly constructed
 * \post
 *  \li a new SetArguments instance is allocated in the heap and must be freed <b>manually</b>
 *
 * @param attackingSetArguments the set attacking the caller set
 * @return the set of arguments which are attacked by at least one node in attackers set
 */
SetArguments* SetArguments::getSubsetAttackedBy(SetArguments* attackersSet){

	SetArguments* nodeset;
	SetArguments* result = new SetArguments();

	for (auto it=this->begin(); it!=this->end(); it++){
		nodeset=(*it)->get_attackers();
		for (auto it2=nodeset->begin(); it2!=nodeset->end(); it2++)
			if (attackersSet->exists(*it2)==true)
				result->add_Argument(*it);
	}
	return result;
}

/**
 * @brief Retrieve the arguments in the caller set which attacks at least one node in the attacked set
 *
 *
 * The function returns all the nodes which are contained in the caller setArguments and attack at least one
 * node in "attacked" SetArgument. For example in this graph the function would return {A}
 *
 * \dot
 * digraph a {
 *  rankdir="LR";
 * 	subgraph cluster1 {
 * 		label="caller set"
 * 		A;
 * 		B;
 * 		C;
 * 	}
 * 	subgraph cluster2 {
 * 		label="attacked set"
 * 		D;
 * 		E;
 * 	}
 * 	F;
 * 	G;
 *
 *	A->B;
 *	A->E;
 *	B->C;
 *	B->F;
 *	C->A;
 *	D->E;
 *	F->D;
 *	E->C;
 *	E->A;
 *	D->A;
 *	D->G;
 *	G->F;
 *	F->G;
 *	F->B;
 * }
 * \enddot
 *
 * \pre
 *  \li attackers correctly constructed
 * \post
 *  \li a new SetArguments instance is allocated in the heap and must be freed <b>manually</b>
 *
 * @param attackingSetArguments the set attacked by the caller set
 * @return the set of arguments which attackS at least one node in attacked set
 */
SetArguments* SetArguments::getSubsetAttacks(SetArguments* attacked){

	SetArguments* nodeset;
	SetArguments* result = new SetArguments();

	for (auto it=this->begin(); it!=this->end(); it++){
		nodeset=(*it)->get_attacks();
		for (auto it2=nodeset->begin(); it2!=nodeset->end(); it2++)
			if (attacked->exists(*it2)==true)
				result->add_Argument(*it);
	}
	return result;
}

/**@brief return all nodes contained in the caller set and contained in other.
 *
 * Computes the nodes inside the caller set which are also stored in "other" set.
 * Theoretically, this function implements the following definition regarding the <i>nodes</i>:
 * \f[
 *  \Gamma_1 = \{ \gamma_{11}; \gamma_{12} ; ... ; \gamma_{1n} \}
 * \f]\f[
 *  \Gamma_2 = \{ \gamma_{21}; \gamma_{22} ; ... ; \gamma_{2n} \}
 * \f]\f[
 *  \Gamma_2 \subseteq \Gamma_1
 * \f]\f[
 * 	\Gamma_1 \downarrow \Gamma_2 \hat{=} \{ \gamma \in \Gamma_1 | \gamma \in \Gamma_2 \}
 * \f]
 * and this definition regarding the <i>arcs</i>:
 * \f[
 * 	{\Gamma}_1 \downarrow {\Gamma}_2 \hat{=} \{ e_{ij} \in {\Gamma}_1 | i \in {\Gamma}_2, j \in {\Gamma}_2 \}
 * \f]
 * In other words \f$ \Gamma_1 \downarrow \Gamma_2 \f$ returns always \f$ \Gamma_2 \f$ but all the arcs
 * that get in or get out from \f$ \Gamma_2 \f$ are discarded. The figure shows in a clearer way the definition:
 *
 * \dot
 *	digraph a{
 *		rankdir="LR";
 *		label="Gamma_1"
 *		A;
 *		B;
 *		subgraph cluster {
 *			label="Gamma_2"
 *			color="red";
 *			C [color="red"];
 *			D [color="red"];
 *			E [color="red"];
 *		}
 *
 *		A->B;
 *		B->A;
 *		A->C;
 *		B->E;
 *		C->D [color="red"];
 *		D->E [color="red"];
 *		E->C [color="red"];
 *	}
 * \enddot
 *
 * the red elements represents what remain if \f$ \Gamma_1 \downarrow \Gamma_2 \f$ is executed.
 * However the data structures simplify this operation: being the attacks/attackers information
 * stopred in the Arguments (and not in SetArguments themselves) the SetArguments has only to
 * store what nodes are in the set, and not what arcs. Selecting what arcs must be kept in considerartion
 * will be basilar in deciding what type of get_attacks/get_attakcers function will be used.
 * For further information, read the documentation of all get_attacks / get_attackers functions.
 *
 * \pre
 *  \li the caller SetArguments has to contains "other" set
 *  \li "other" set must be not NULL
 *  \li "result" must be already initialized
 * \post
 *  \li "result" data structure will be filled with information
 *
 * @param other represents the \f$ \Gamma_2 \f$ set
 * @param result represents the \f$ \Gamma_1 \downarrow \Gamma_2 \f$ set
 */
void SetArguments::setSafeRestrict(SetArguments* other, SetArguments* result){
	other->clone(result);
}

/**removes all the occurence of nodes not in otherset in the set calling this function.
 * For example:
 *
 * \dot
 *  digraph a {
 *  	subgraph cluster {
 *  	A;
 *  	B;
 *  	C;
 *  	}
 *  	D;
 *  	E;
 *
 *  	A->B;
 *  	B->C;
 *  	D->A;
 *  	D->E;
 *  	E->C;
 *  }
 * \enddot
 *
 * if the SetArguments {A,B,C} would call the function with otherset set to {A,B,C,D,E} the function would return {A,B,C}
 *
 * @param otherset the set to be synched with
 */
void SetArguments::synchWithSet(SetArguments* otherset){
	for (auto it=this->begin(); it!=this->end();it++)
		if (otherset->exists(*it)==false)
			this->remove(*it);
}

/**computes the set containing the attackers of all nodes stored in the setArgument.
 * For example the return value of the call:
 * \code
 * 	cout << *(setABC->getAllAttackers()) << endl;
 * \endcode
 * would be {D,A,B,E}
 *
 * \dot
 *  digraph a {
 *  	rankdir="LR";
 *  	subgraph cluster {
 *  	label="setABC"
 *  	A;
 *  	B;
 *  	C;
 *  	}
 *  	D;
 *  	E;
 *
 *  	A->B;
 *  	B->C;
 *  	D->A;
 *  	D->E;
 *  	E->C;
 *  }
 * \enddot
 *
 * This because the function returns <b>all</b> the attackers of the set, not only those included in the set itself.
 * If you want only the attackers incliuded in the caller set, you should use getAllAttackersInSet() function or:
 * \code
 * 	SetArguments* allAttackers=setABC->getAllAttackers();
 *	allAttackers->synchwithSet(setABC);
 * \endcode
 *
 * \post
 *  \li a new SetArguments is allocated in the heap and has to be freed <b>manually</b>
 *
 *
 * @return all the nodes which attacks at least one node in the caller set
 */
SetArguments* SetArguments::getAllAttackers() {

	SetArguments* result=new SetArguments();

	for (SetArgumentsIterator it=this->begin(); it!= this->end(); it++) {
		SetArguments* nodeAttackers = (*it)->get_attackers();
		for (SetArgumentsIterator it2=nodeAttackers->begin(); it2!=nodeAttackers->end(); it2++)
			result->add_Argument(*it2);
	}
	return result;
}

/**computes the set containing the attacks of all nodes stored in the setArgument.
 * For example the return value of the call:
 * \code
 * 	cout << *(setABC->getAllAttacks()) << endl;
 * \endcode
 * would be {B,E,C}
 *
 * \dot
 *  digraph a {
 *  	subgraph cluster {
 *  	label="setABC"
 *  	A;
 *  	B;
 *  	C;
 *  	}
 *  	D;
 *  	E;
 *
 *  	A->B;
 *  	B->C;
 *  	D->A;
 *  	D->E;
 *  	E->C;
 *  	A->E;
 *  }
 * \enddot
 *
 * This because the function returns <b>all</b> the attacks of the set, not only those included in the set itself.
 * If you want only the attacks included in the caller set, you should use getAllAttacksInSet() function or:
 * \code
 * 	SetArguments* allAttacks=setABC->getAllAttacks();
 *	allAttacks->synchwithSet(setABC);
 * \endcode
 *
 * \post
 *  \li a new SetArguments is allocated in the heap and has to be freed <b>manually</b>
 *
 *
 * @return all the nodes which attacks at least one node in the caller set
 */
SetArguments* SetArguments::getAllAttacks() {

	SetArguments* result=new SetArguments();

	for (SetArgumentsIterator it=this->begin(); it!= this->end(); it++) {
		SetArguments* nodeAttacks = (*it)->get_attacks();
		for (SetArgumentsIterator it2=nodeAttacks->begin(); it2!=nodeAttacks->end(); it2++)
			result->add_Argument(*it2);
	}
	return result;
}

/**@brief computes all the nodes who are attacked by other node in this set
 *
 * \dot
 * digraph a {
 * 	rankdir="LR";
 * 	subgraph cluster {
 * 		label="caller set"
 * 		A;
 * 		B;
 * 		C;
 * 	}
 * 	D;
 * 	E;
 *
 * 	A->B;
 * 	B->C;
 * 	A->C;
 * 	D->C;
 *	E->B;
 *	A->D;
 * }
 * \enddot
 *
 * For example in the graph shown the result of the call:
 * \code
 * 	cout << *(this->getAllAttackersInSet()) << endl;
 * \endcode
 * would be {A,B}
 *
 * \post
 *  \li a new SetArguments instance is allocated in the heap and has to be freed <b>manually</b>
 *
 * @return the set of arguments which are attacked by at least one node in this very set
 */
SetArguments* SetArguments::getAllAttackersInSet(){
	SetArguments* result=this->getAllAttackers();
	result->synchWithSet(this);
	return result;
}

/**@brief computes all the nodes which attacks other nodes in this very set
 *
 * \dot
 * digraph a {
 * 	rankdir="LR";
 * 	subgraph cluster {
 * 		label="caller set"
 * 		A;
 * 		B;
 * 		C;
 * 	}
 * 	D;
 * 	E;
 *
 * 	A->B;
 * 	B->C;
 * 	A->C;
 * 	D->C;
 *	E->B;
 *	A->D;
 * }
 * \enddot
 *
 * For example in the graph shown the result of the call:
 * \code
 * 	cout << *(this->getAllAttacksInSet()) << endl;
 * \endcode
 * would be {A,B}
 *
 * \post
 *  \li a new SetArguments instance is allocated in the heap and has to be freed <b>manually</b>
 *
 * @return the set of arguments which attacks at least one node in this very set
 */
SetArguments* SetArguments::getAllAttacksInSet(){
	SetArguments* result=this->getAllAttacks();
	result->synchWithSet(this);
	return result;
}

/** <b>memory alloc</b> Restituisce l'unione di tutti i nodi non in this che attaccano nodi in this. */
SetArguments* SetArguments::getExternalAttackers() {

	SetArguments* result = new SetArguments();
	SetArguments* allAttackers = new SetArguments();
	allAttackers=this->getAllAttackers();
	this->setminus(allAttackers, result);
	delete allAttackers;
	return result;
}

/** <b>memory alloc</b> Restituisce l'unione di tutti i nodi non in this attaccati da nodi in this. */
SetArguments* SetArguments::getExternalAttacks() {

	SetArguments* result = new SetArguments();
	SetArguments* allAttacks = new SetArguments();
	allAttacks=this->getAllAttacks();
	this->setminus(allAttacks, result);
	delete allAttacks;
	return result;
}

/** @brief per ogni nodo del grafo, stampa l'insieme dei suoi nodi attaccanti e di quelli attaccati. */
void SetArguments::printNodeRelations() {

	for (SetArgumentsIterator it = this->begin(); it != this->end(); it++)
		cout << "\tNode:"<< (*it)->getName() << "(" << (*it)->getNumber()
			 << ") | attacks:"<< *(*it)->get_attacks()
			 << " attackers:"<< *(*it)->get_attackers() << endl;
	cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

/** @brief stampa prima il set dei nodi del grafo, e poi richiama nodeRelations */
void SetArguments::printGraph() {
	cout << "~~~~ List of Nodes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << *this << endl;
	printNodeRelations();
}

/**
 * @brief Perform the union of two SetArguments
 *
 *
 * @param[in] the set to be merged with
 * @param[out] the union of these 2 sets
 */
void SetArguments::merge(SetArguments* other, SetArguments* result){
	for (SetArgumentsIterator it= this->begin(); it != this->end(); it++)
		result->add_Argument(*it);
	for (SetArgumentsIterator it= other->begin(); it != other->end(); it++)
		result->add_Argument(*it);
}

/** @brief restituisce TRUE sse nel grafo esiste almeno un arco orientato */
bool SetArguments::graphHasEdges(void) {
	// ricerco l'esistenza di almeno un nodo che sia attaccato <=> il grafo ha archi
	SetArgumentsIterator it = this->begin();
	bool edges = false;
	while (!edges and it != this->end()) {
		SetArguments* attacked = (*it)->get_attacks();
		if (!attacked->empty())
			edges = true;
		it++;
	}
	return false;
}

/**
 * @brief Intersect this set the `other` set and write the result in `res`
 *
 * The funcion compute the operation of intersection between two sets:
 * \f[
 * 	A = \{a_1; a_2; ... ; a_n\}
 * \f]\f[
 * 	B = \{b_1; b_2; ... ; b_m\}
 * \f]\f[
 * 	A \cap B \hat{=} \{c | c \in A, c \in B \}
 * \f]
 *
 * For example in the graph shown calling setIntersect() will return as output {}
 *
 * \dot
 * 	digraph a {
 * 		subgraph cluster1 {
 * 			label="A";
 * 			style="rounded";
 * 			a1;
 * 			a2;
 * 		}
 * 		subgraph cluster2 {
 * 			label="B";
 * 			style="rounded";
 * 			b1;
 * 			b2;
 * 			b3;
 * 			b4;
 * 			b5;
 * 		}
 * 		subgraph cluster3 {
 * 			label="intersect"
 * 			a3;
 * 			a4;
 * 		}
 *
 * 		a1->b2;
 * 		a2->a3;
 * 		a3->a4;
 * 		a4->b1;
 * 		b1->b4;
 * 		b1->a3;
 * 		b2->b3;
 * 		b3->b1;
 * 		b3->a3;
 * 		b4->a1;
 * 		b5->b4;
 * 	}
 * \enddot
 *
 * \pre
 *  \li other not NULL
 *  \li result has already been initialized with a constructor
 * \post
 *  \li in result the intersection nodes has been <b>added</b> to the previos content of the SetArguments
 *
 * @param[in] other The second term of the intersection
 * @param[out] res	The result of the intersection
 */
void SetArguments::intersect(SetArguments *other, SetArguments *result) {

	for (SetArgumentsIterator it1 = this->begin(); it1 != this->end(); it1++)
		for (SetArgumentsIterator it2 = other->begin(); it2 != other->end(); it2++)
			if (*(*it1) == *(*it2))
				result->add_Argument(*it1);
}

/**@brief verify that 2 SetArguments are equal
 *
 * This function is similar to the operator == but it does <b>not</b> keep
 * trace of the order of the elements. So these 2 set are equals:
 * \f[
 * 	\{n01,n45,n13,n03\}
 * \f]\f[
 * 	\{n01,n13,n45,n03\}
 * \f]
 *
 * @param other the other set to confront
 * @return TRUE if all the elements in the first set are contained in the secondo one <b>and</b> viceversa
 */
bool SetArguments::equal(const SetArguments &other) const{
	if (this->cardinality()!=other.cardinality())
		return false;
	for (auto it=this->begin();it!=this->end(); it++)
		if (other.arguments.find((*it)->getName())==other.arguments.end())
			return false;
	return true;
}

/**
 * @brief Overloading of the == operator
 *
 * the function emulates the equal function with set of arguments. However this function keeps trace of the <b>order</b> of the elements; so
 * these set are equal:
 * \p \{n01,n13,n45,n03\} == \{n01,n13,n45,n03\}
 * \p while these set are not:
 * \p \{n01,n45,n13,n03\} != \{n01,n13,n45,n03\}
 *
 *	It should be more efficient of equal(), so use it whenever possible.
 *
 * @param[in] 	other   The other term of the comparison
 * @retval bool
 */
bool SetArguments::operator==(const SetArguments &other) const
{
	if (this->cardinality() != other.cardinality())
		return false;
	for(SetArgumentsIterator it = this->begin(), it2 = other.begin(); it != this->end() and it2 != other.begin(); it++, it2++)
		if ((*it) != (*it2))
			return false;
	return true;
}

/**@brief TRUE if the 2 SetArguments called are not equal using == operator.
 *
 * For information go to the documentation of == operator
 *
 * @param other the set to compare with
 * @return TRUE if the sets are not equal in the == sense, FALSE otherwise
 */
bool SetArguments::operator!=(const SetArguments &other) const {
	return !(*this==other);
}

/**Destroy the current SetArgument
 *
 * \post
 *  \li All the structured pointed by this class will <b>not</b> be destroyed
 *  \li keyassoc structure itself will be erased;
 *  \li argument structure itself will be erase;
 *
 */
SetArguments::~SetArguments(){
	//keyassoc: nothing to free because the structures pointed by keyassoc->second must remain intact
	//arguments: nothing to free because the structures pointed by arguments->second muyst remain intact
}

/**@brief removes all the pointers of Arguments inside this set.
 *
 * The function removes all the pointers to Arguments inside this set; <b>no</b>
 * Arguments will be freed in this operation. You can use this function to
 * clean a SetArguments that later will be used again in other operations.
 *
 * \post
 *  \li all the pointer to Arguments in this set will be erased.
 *
 */
void SetArguments::clean() {
	this->remove_All_Arguments();
}

ostream& operator<<(ostream& out, const SetArguments& r)
{
	out << "{";
	SetArgumentsIterator it;
	for (it = r.begin(); it != r.end();)
	{
		out << (*it)->getName();
		if (++it != r.end())
			out << " ";
	}
	out << "}";
	return out;
}

