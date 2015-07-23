#include "Boundcond.h"

Boundcond::Boundcond() {}
Boundcond::~Boundcond() {}

/*	Nella chiamata si ha A = G; B = S[i]; C = {e}
	O è il sottoinsieme dei nodi di B attaccati da nodi in C
	I è il sottoinsieme dei nodi di B\O che
		non subiscono attacchi da parte di nodi in A esterni a B
		_xor_
		subiscono eventuali attacchi solo da parte di nodi che
			sono contenuti in A ma non in (B join C)
			_and_
			sono attaccati da nodi in C
*/
void Boundcond::doBoundcond( SetArguments* A, SetArguments* B, SetArguments* C, SetArguments* O, SetArguments* I) {

	// O è il sottoinsieme dei nodi di B attaccati da nodi in C
	O = B->getSubsetAttackedBy(C);
	B->setminus(O, I);
	#ifdef DEBUG_BOUNDCOND
		cout << "init: O = "<<endl; O->printNodeRelations();
		cout << "init: I = "<<endl; I->printNodeRelations();
	#endif
	// I = { n in B\O | n notin (A\B).attacks xor n notin (A\((A\(BorC))and C.attacks)).attacks = X.attacks }
	SetArguments* firstConditionSet;  // (A\B).attacks
	SetArguments* secondConditionSet; // (A\((A\(BorC))and C.attacks)).attacks
	SetArguments* temp1 = new SetArguments(), * temp2 = new SetArguments(), * temp3 = new SetArguments();

	A->setminus(B, temp1);
	#ifdef DEBUG_BOUNDCOND
		cout << "0:temp1 = A\\B = " << *temp1 << endl;
	#endif

	firstConditionSet = temp1->getAllAttacks();
	#ifdef DEBUG_BOUNDCOND
		cout << "FIRST | nodi(anche di A\\B) attaccati da A\\B: " << *firstConditionSet << endl;
	#endif

	temp1->clean(); //TODO qua van forse dei delete temp1 ?
	#ifdef DEBUG_BOUNDCOND
		cout << "CLEAN: A = " << *A << ", B = " << *B << ", A\\B = temp1 = " << *temp1 << ": " << endl;
	#endif
	B->merge(C, temp1);				// temp1 = B or C
	#ifdef DEBUG_BOUNDCOND
		cout << "1:temp1 = B or C = " << *temp1 << endl;
	#endif
	A->setminus(temp1, temp2);		// temp2 = A \ (B or C)
	#ifdef DEBUG_BOUNDCOND
		cout << "2:temp2 = A \\ (B or C) = " << *temp2 << endl;
	#endif
	temp1->clean();
	temp1 = C->getAllAttacks();			// temp1 = C.attacks
	#ifdef DEBUG_BOUNDCOND
		cout << "3:temp1 = C.attacks " << *temp1 << endl;
	#endif

	temp1->intersect(temp2, temp3);	// temp3 = temp1 and temp2   QUI MUORE
	#ifdef DEBUG_BOUNDCOND
		cout << "4:temp3 = temp1 and temp2 = " << *temp3 << endl;
	#endif
	temp1->clean();

	A->setminus(temp3, temp1);		// temp1 = A \ temp3
	#ifdef DEBUG_BOUNDCOND
		cout << "5:temp1 = X = A \\ temp3 = " << *temp1 << endl;
	#endif

	secondConditionSet = temp1->getAllAttacks();
	#ifdef DEBUG_BOUNDCOND
		cout << "SECOND | nodi(anche di X) attaccati da X: " << *secondConditionSet << endl;
	#endif

	for(SetArgumentsIterator it=I->begin(); it!=I->end(); it++) {
		#ifdef DEBUG_BOUNDCOND
			cout << endl << "for su I di boundcond: nodo = " << (*it)->print() << endl;
		#endif
		if( firstConditionSet->exists(*it)/* nodo non subisce attacchi da nodi di A\B */)
			continue;
		if( secondConditionSet->exists(*it)/* nodo.attaccanti sono SOLO in A\(BorC)andC */)
			continue;
		#ifdef DEBUG_BOUNDCOND
			cout << "removing node from I." << endl;
		#endif
		I->remove(*it);
	}
	#ifdef DEBUG_BOUNDCOND
		cout<< "FINAL BOUNDCOND: I = " << *I << endl;
	#endif
	delete temp1;
	delete temp2;
	delete temp3;
	delete firstConditionSet;
	delete secondConditionSet;
}

