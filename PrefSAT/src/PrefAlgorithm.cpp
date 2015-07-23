#include "PrefAlgorithm.h"

/* utilizzati per la configurazione di semopt. NON elegante piazzarli qui, ma vabbè amen.
 	 WARNING: non togliere/spostare/nulla, ti prego!!! si incasina tutto e il make piange :( */

bool debug = false;
bool externalsat = true;
string satsolver;
int labellingconditions = 0;
bool manualopt = false;
string inputfile;
string semantics;
time_t start;

#define DEBUG_PREFEXT 0 // 0: no debug. 1: minimal. 2: verbose. >3: more verbose...
//#define DEBUG_IMPROVING

unsigned int PrefAlgorithm::calls[CALLING_TYPES] = {0, 0, 0, 0};

void PrefAlgorithm::pushCall(unsigned short type) {
	PrefAlgorithm::calls[type]++;
}

unsigned int PrefAlgorithm::getCalls(unsigned short type) {
	return PrefAlgorithm::calls[type];
}

//TODO documentation
PrefAlgorithm::PrefAlgorithm(string graphPath) {
	inputfile = string(graphPath);
	this->framework = AF();
	this->preferred=Preferred();
	if (!framework.readFile(inputfile)){
		cout << "cannot read the file" << endl;
		exit(1);
	}
}

//TODO migliorare la documentazione! non spiega nulla!
/** Modularizza la gestione della chiamata a Grounded. */
void callGrounded(SetArguments* G, SetArguments* C, SetArguments* temp_e, SetArguments* I) {

	#ifdef CHRONOPREF
		auto t1 = chrono::high_resolution_clock::now();
	#endif
		Grounded::doGrounded(*G, *C, temp_e, I);
	#ifdef CHRONOPREF
		auto t2 = chrono::high_resolution_clock::now();
		auto msecs = chrono::duration_cast<chrono::milliseconds>(t2-t1).count();
		if(msecs)
			cout << "\tGrounded call took " << msecs << " milliseconds." << endl;
		else
			cout << "\tGrounded call took less than 1 millisecond." << endl;
	#endif
	PrefAlgorithm::pushCall(GROUNDED_CALL);
}

//TODO migliorare la documentazione! non spiega nulla!
/** Modularizza la gestione della chiamata a Boundcond. */
void callBoundcond(SetArguments* G, SetArguments* S_i, SetArguments* e, SetArguments* O, SetArguments* I) {

	#ifdef CHRONOPREF
		auto t1 = chrono::high_resolution_clock::now();
	#endif
		Boundcond::doBoundcond(G, S_i, e, O, I);
	#ifdef CHRONOPREF
		auto t2 = chrono::high_resolution_clock::now();
		auto msecs = chrono::duration_cast<chrono::milliseconds>(t2-t1).count();
		if(msecs)
			cout << "\tBoundcond call took " << msecs << " milliseconds." << endl;
		else
			cout << "\tBoundcond call took less than 1 millisecond." << endl;
	#endif
	PrefAlgorithm::pushCall(BOUNDCOND_CALL);

	#if DEBUG_PREFEXT > 0
		cout << "calling boundcond with A = G = " << *G << endl; //G.printNodeRelations();
		cout << "calling boundcond with B = S[i] = " << *S_i << endl; //S_i->printNodeRelations();
		cout << "calling boundcond with C = Ep[j] = " << *e << endl;
		cout << "Boundcond returned: O= "<< *O <<"; I= "<< *I << endl;
	#endif
}

//TODO migliorare la documentazione! non spiega nulla!
/** Modularizza la gestione della chiamata a SCCSEQ. */
void callSCCSEQ(SetArguments *G, vector<SetArguments*>* sccSet) {

	#ifdef CHRONOPREF
		auto t1 = chrono::high_resolution_clock::now();
	#endif
		SCCSEQ::performSCCSEQ(G, sccSet);
	#ifdef CHRONOPREF
		auto t2 = chrono::high_resolution_clock::now();
		auto msecs = chrono::duration_cast<chrono::milliseconds>(t2-t1).count();
		if(msecs)
			cout << "\tSCCSEQ call took " << msecs << " milliseconds." << endl;
		else
			cout << "\tSCCSEQ call took less than 1 millisecond." << endl;
	#endif

	#if DEBUG_PREFEXT > 1
		cout << "*************** SCCSEQ ***************"<<endl;
		for (auto it=sccSet->begin();it!=sccSet->end();it++)
			cout << "set in SCCSET: " << **it << endl;
		cout << "--------------------------------------"<<endl;
	#endif
}

//TODO migliorare la documentazione! non spiega nulla!
/** Modularizza la gestione della chiamata a PrefSAT. */
void callPrefSAT(Preferred* pref, SetArguments* Gamma_Down_Si, SetArguments* I_Intersect_C, SetArgumentsVector* E_star) {

	#ifdef CHRONOPREF
		auto t1 = chrono::high_resolution_clock::now();
	#endif
		pref->prefSAT(Gamma_Down_Si, I_Intersect_C);
	#ifdef CHRONOPREF
		auto t2 = chrono::high_resolution_clock::now();
		auto msecs = chrono::duration_cast<chrono::milliseconds>(t2-t1).count();
		if(msecs)
			cout << "\tPrefSAT call took " << msecs << " milliseconds." << endl;
		else
			cout << "\tPrefSAT call took less than 1 millisecond." << endl;
	#endif
	PrefAlgorithm::pushCall(SATPREF_CALL);
	*E_star = *(pref->getSolution());
}

/**\brief The function offer a easy interface for the PreferredExtension algorithm.
 *
 * This function solves the preferred algorithm problem.
 *
 * You can use this function like in this example:
 * \code
 * int main(){
 *	PrefAlgorithm solver=PrefAlgorithm("test-input/example06.dl");
 *	SetArgumentsVector solution=solver.handlePref();
 *	cout << "the solution is "<<solution << endl;
 *	return 0;
 * }
 * \endcode
 *
 * @param improved TRUE if you want to execute the performance focus algorithm, FALSE if you want to run the standard one
 * @return set of preferred Extensions
 */
SetArgumentsVector PrefAlgorithm::handlePref(bool improved) {
	if(improved)
		return PrefImproved(*framework.get_arguments(), *framework.get_arguments());
	else
		return Pref(*framework.get_arguments(), *framework.get_arguments());
}

//TODO migliorare la documentazione! non spiega nulla!
/** Algoritmo ricorsivo per il computo delle Preferred Extensions. */
SetArgumentsVector PrefAlgorithm::Pref(SetArguments G, SetArguments C) {

	#if DEBUG_PREFEXT > 0
		cout << "PREF starts with G = " << G << ", C = " << C << endl;
	#endif
	PrefAlgorithm::pushCall(PREF_CALL);

	//represents the initial area where to store the results of Grounded. After that, tempe will be added to Ep
	SetArguments temp_e;
	SetArgumentsVector Ep;
	SetArguments O;
	SetArguments I;
	SetArguments e;
	vector<SetArguments*> sccSet;
	SetArguments* S_i;
	SetArgumentsVector Ep_new, E_star;

	/* **************** GROUNDED *********************/

	callGrounded(&G, &C, &temp_e, &I);

	Ep = SetArgumentsVector();
	Ep.push_back(&temp_e);  // Ep <- {e}
	#if DEBUG_PREFEXT > 1
		cout << "Dopo Grounded, Ep = " << e <<endl;
	#endif
	if (!I.cardinality()) {
		#if DEBUG_PREFEXT > 1
			cout << "Pref si arresta correttamente dopo Grounded. Ep = {e}" << endl <<"e:\t" << e << endl;
		#endif
		return Ep;
	}
	/* **************** RESTRICT TO  *****************/

	SetArguments res;
	G.setSafeRestrict(&I, &res);
	G = res;

	/* **************** SCCSEQ ***********************/

	sccSet = vector<SetArguments*>();
	callSCCSEQ(&G, &sccSet);

	/* **************** PREF'S FOR **********************/

	for(auto it_sccSet=sccSet.begin(); it_sccSet!=sccSet.end(); it_sccSet++) {

		S_i = *it_sccSet;
		Ep_new = SetArgumentsVector();
		E_star = SetArgumentsVector();

		for(auto it_Ep=Ep.begin(); it_Ep!=Ep.end(); it_Ep++) {

			I = SetArguments();
			O = SetArguments();
			e = **it_Ep;

			callBoundcond(&G, S_i, &e, &O, &I);

			SetArguments Gamma_Down_Si;
			SetArguments Gamma_Down_Si_Minus_O;
			SetArguments I_Intersect_C;
			SetArguments Si_Minus_O;

			if (O.empty()) {
				//in this part of the if O is useless --> we can free it now
				//delete O;
				if (!I.empty()) {

					Gamma_Down_Si = SetArguments();
					I_Intersect_C = SetArguments();
					G.setSafeRestrict(S_i, &Gamma_Down_Si);
					I.intersect(&C, &I_Intersect_C);
					callPrefSAT(&(this->preferred), &Gamma_Down_Si, &I_Intersect_C, &E_star);
				}
				// else, E* <- emptySet is implicit from initialization
			}
			else {
				Gamma_Down_Si_Minus_O = SetArguments();
				Si_Minus_O = SetArguments();
				I_Intersect_C = SetArguments();
				I.intersect(&C, &I_Intersect_C);
				S_i->setminus(&O, &Si_Minus_O);
				//in this part of the if only now O is useless
				//delete O;
				G.setSafeRestrict(&Si_Minus_O, &Gamma_Down_Si_Minus_O);
				E_star = this->Pref(Gamma_Down_Si_Minus_O, I_Intersect_C);
			}
			E_star.addSetArgumentsToAll(&e);
			Ep_new = Ep_new + E_star;
		}
		Ep = Ep_new;
	}

	//scc must be deallocated
	for (auto it=sccSet.begin();it!=sccSet.end();it++){
		delete (*it);
	}

	return Ep;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//TODO migliorare la documentazione! non spiega nulla!
/** Algoritmo ricorsivo per il computo delle Preferred Extensions, con i miglioramenti suggeriti. */
SetArgumentsVector PrefAlgorithm::PrefImproved(SetArguments G, SetArguments C) {

	#if DEBUG_PREFEXT > 0
		cout << "PREF starts with G = " << G << ", C = " << C << endl;
	#endif
	PrefAlgorithm::pushCall(PREF_CALL);

	//represents the initial area where to store the results of Grounded. After that, tempe will be added to Ep
	SetArguments temp_e;
	SetArgumentsVector Ep;
	SetArguments O;
	SetArguments I;
	SetArguments e;
	vector<SetArguments*> sccSet;
	SetArgumentsVector Ep_new, E_star;
	SetArguments *S_i, *S_i_prec;

	// stored now for optimization. A later comparison would be corrupted since G changes when set restricted to I
	bool isGequalToC = G.equal(C);

	/* **************** GROUNDED *********************/

	if(isGequalToC and G.cardinality()==1) {
		#ifdef DEBUG_IMPROVING
			cout << "°°°°°°°°° I should not call Grounded!!!"<< endl;
		#endif
		temp_e = G;
		I = SetArguments();
	}
	else
		callGrounded(&G, &C, &temp_e, &I);

	Ep = SetArgumentsVector();
	Ep.push_back(&temp_e);
	#if DEBUG_PREFEXT > 1
		cout << "Dopo Grounded, Ep = " << e <<endl;
	#endif
	if (!I.cardinality()) {
		#if DEBUG_PREFEXT > 1
			cout << "Pref si arresta correttamente dopo Grounded. Ep = {e}" << endl <<"e:\t" << e << endl;
		#endif
		return Ep;
	}
	/* **************** RESTRICT TO  *****************/

	SetArguments res;
	G.setSafeRestrict(&I, &res);
	G = res;

	/* **************** SCCSEQ ***********************/

	sccSet = vector<SetArguments*>();
	callSCCSEQ(&G, &sccSet);

	/* **************** PREF'S FOR **********************/
	S_i = new SetArguments();
	S_i_prec = new SetArguments();

	for(auto it_sccSet=sccSet.begin(); it_sccSet!=sccSet.end(); it_sccSet++) {

		Ep_new = SetArgumentsVector();
		E_star = SetArgumentsVector();

		S_i_prec = S_i;
		S_i = *it_sccSet;

		vector<SetArguments*>* a_i = SCCSEQ::getFathersUnion(&sccSet, S_i);

		#if DEBUG_PREFEXT > 0
			cout << "************************* sccSet: "<< *S_i <<" *******************************"<<endl;
			cout << "Ep: "<< Ep << endl;
			cout << "a_i = " << *a_i << endl;
			cout << "S_i_prec = " << *S_i_prec << endl;
		#endif

		bool a_i_empty = a_i->empty();
		bool S_i_prec_is_father = true;

		#ifdef DEBUG_IMPROVING
			if(isGequalToC) {
				if(a_i_empty) {
					cout << "alpha(i) is empty, G=C. For all e in Ep, expecting Boundcond O to be {}, and I always equal to S_i = " << endl;
				}
				else if(it_sccSet!=sccSet.begin() and std::find(a_i->begin(), a_i->end(), S_i_prec) == a_i->end()) {
					S_i_prec_is_father = false;
					cout << "S_i_prec is not a father of S_i. For all e in Ep, expecting Boundcond O to be equal. which I ? maybe S_i = " << *S_i << endl;
				}
			}
		#endif

		for(auto it_Ep=Ep.begin(); it_Ep!=Ep.end(); it_Ep++) {
			#if DEBUG_PREFEXT > 0
				cout << "-------------- e: "<< **it_Ep <<" --------------"<<endl;
			#endif

			I = SetArguments();
			O = SetArguments();
			e = **it_Ep;

			if(a_i_empty && isGequalToC)
				I = SetArguments(*S_i); // and O = SetArguments() from before
			else
				callBoundcond(&G, S_i, &e, &O, &I);

			SetArguments Gamma_Down_Si;
			SetArguments Gamma_Down_Si_Minus_O;
			SetArguments I_Intersect_C;
			SetArguments Si_Minus_O;

			if (O.empty()) {
				if (!I.empty()) {

					Gamma_Down_Si = SetArguments();
					I_Intersect_C = SetArguments();
					G.setSafeRestrict(S_i, &Gamma_Down_Si);
					I.intersect(&C, &I_Intersect_C);

					int card_S_i = S_i->cardinality();
					if(card_S_i < 3 and card_S_i > 0 and Gamma_Down_Si.equal(I_Intersect_C)) {
						if(card_S_i==1) { // qua discrepanza con quanto sostenuto nelle slide. CHIAMO PREFSAT
							/*cout << "expecting a singleton, because |S_i|=1. S_i = " << *S_i << endl;
							vector<SetArguments*> singletons = S_i->getSingletons();
							E_star = SetArgumentsList(singletons);
							cout << "and NOW, E_star = " << E_star << endl;*/
							callPrefSAT(&(this->preferred), &Gamma_Down_Si, &I_Intersect_C, &E_star);
						}
						else {
							#ifdef DEBUG_IMPROVING
								cout << ">>>>> I should not call prefSAT!" << endl;
								cout << "expecting two singletons, because |S_i|=2. S_i = " << *S_i << endl;
							#endif
							vector<SetArguments*> singletons = S_i->getSingletons();
							E_star = SetArgumentsVector(singletons);
						}
					}
					else
						callPrefSAT(&(this->preferred), &Gamma_Down_Si, &I_Intersect_C, &E_star);

					#if DEBUG_PREFEXT > 0
						cout << "prefSAT("<< Gamma_Down_Si << ", " << I_Intersect_C <<" ) returns E_star = "<< E_star << endl;
					#endif
				}
				// else, E* <- emptySet is implicit from initialization
			}
			else {
				Gamma_Down_Si_Minus_O = SetArguments();
				Si_Minus_O = SetArguments();
				S_i->setminus(&O, &Si_Minus_O);
				I_Intersect_C = SetArguments();
				I.intersect(&C, &I_Intersect_C);
				G.setSafeRestrict(&Si_Minus_O, &Gamma_Down_Si_Minus_O);

				if(Gamma_Down_Si_Minus_O.equal(I_Intersect_C) and Gamma_Down_Si_Minus_O.cardinality()==1) {
					#ifdef DEBUG_IMPROVING
						cout << "°°°°°°°°° I should not call Pref!!!"<< endl;
					#endif
					vector<SetArguments*> singleton = Gamma_Down_Si_Minus_O.getSingletons();
					E_star = SetArgumentsVector(singleton);
				}
				else {
					#if DEBUG_PREFEXT > 0
						cout << "calling recursion: Pref("<< Gamma_Down_Si_Minus_O << ", " << I_Intersect_C<<")"<< endl;
					#endif
					E_star = this->PrefImproved(Gamma_Down_Si_Minus_O, I_Intersect_C);
				}
			}
			#if DEBUG_PREFEXT > 1
				cout << "*************** Ep_new computation *******************"<<endl;
				cout << "E_star: "<< E_star << endl;
				cout << "e:      "<< e << endl;
				cout << "Ep_new: "<< Ep_new << endl;
			#endif
			E_star.addSetArgumentsToAll(&e);
			Ep_new = Ep_new + E_star;
			#if DEBUG_PREFEXT > 1
				cout << "e (dopo):"<< e <<endl;
				cout << "e cross E_star: "<< E_star << endl;
				cout << "new Ep_new: " << Ep_new << endl;
				cout << "Ep: "<< Ep << endl;
			#endif
		}
		Ep = Ep_new;
	}
	delete S_i;
	delete S_i_prec;
	return Ep;
}

