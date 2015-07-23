/**
 *	\file Grounded.cpp
 *	\class Grounded
 *	\brief The class compute the Grounded Algorithm
 *
 *	The class allows the developer to compute the Grounded Algorithm.
 *	This Algorithm is mainly used in the Pref() method of the class PrefAlgorithm.
 *	The main mathod of this class, as the developer can imagine, is doGrounded() that
 *	compute the grounded outputs: see the documentation of doGrounded() to understand the grounded Algorithm.
 *
 * 	\date Aug 25, 2013
 * 	\author koldar
 */

#include "Grounded.h"

/**@brief Computes the Grounded Algorithm
 *
 * The grounded algorithm can be synthetized as this pseudo-code:
 *
 *	\code
 * 	e <- emptySet
 *	I <- A
 *	while (exists N subset or equal to C containing only nodes which are not attacked by nodes in I) do
 *		e <- e union N
 *		ANC <- C subset containing  all nodes which are attacked by nodes in N
 *		ANI <- I subset containing all nodes which are attacked by nodes in N
 *		C <- C\(N union ANC)
 *		I <- I\(N union ANI)
 *	return (e,I)
 *	\endcode
 *
 * \pre
 *  \li C must be a subset of G;
 *  \li e must be already be initialized through a constructor;
 *  \li I must be already be initialized through a constructor;
 * \post
 *  \li in e some nodes have been added;
 *  \li in I some nodes have been added;
 *
 * @param[in] G represents the graph where grounded algorithm must be computed;
 * @param[in] C the graph to be groundized. C has to be a subset of G: $C \subseteq G$;
 * @param[out] e an output of the function
 * @param[out] I an output of the function
 */
void Grounded::doGrounded(SetArguments G, SetArguments C, SetArguments* e, SetArguments* I){

	*e = SetArguments();
	*I = G;

	SetArguments N = SetArguments();
	SetArguments* ANC;
	SetArguments* ANI;
	SetArguments Cunion;
	SetArguments Iunion;

	while (!isNempty(&C, I, &N)) {

		Cunion = SetArguments();
		Iunion = SetArguments();

		e->merge(&N, e);
		ANC = C.getSubsetAttackedBy(&N);
		ANI = I->getSubsetAttackedBy(&N);

		N.merge(ANC, &Cunion);
		N.merge(ANI, &Iunion);
		//ANC must be freed
		delete ANC;
		delete ANI;
		C.setminus(&Cunion, &C);
		I->setminus(&Iunion, I);

		#ifdef DEBUG_GROUNDED
			cout << "************FINE ITERAZIONE GROUNDED************" << endl;
			cout << "e dopo merge: "<< *e << endl;
			cout << "ANC: " << ANC << endl;
			cout << "ANI: " << ANI << endl;
			cout << "nuovo C" << C << endl;
			cout << "nuovo I" << *I<< endl;
		#endif
	}
	#ifdef DEBUG_GROUNDED
		cout << "alla fine di grounded:e:\t" << *e << endl;
		cout << "alla fine di grounded:I:\t" << *I << endl;
	#endif
}

/**@brief computes N and verify that it is empty
 *
 * Function used in the algorithm doGrounded() to compute easily N and test wether or
 * not it is empty.
 *
 * \pre
 *  \li N must be initialized through a constructor successfully;
 * \post
 *  \li N is filled.
 *
 * @param[in] C The set C
 * @param[in] I the set I
 * @param[out] N the subset of C which is attacked by any nodes present in I
 * @return TRUE if N is empty, FALSE otherwise
 */
bool Grounded::isNempty(SetArguments* C, SetArguments* I, SetArguments* N) {
	//N= tutti e soli i nodi di C che non sono attaccati da alcun nodo in I

	*N = SetArguments();

	Grounded::computeNSet(C, I, N);
	#ifdef DEBUG_GROUNDED
		cout << "N: " << N << endl;
	#endif
	return N->empty();
}
// subset dei soli nodi di C NON attaccati da nodi in I

/**@brief computes the set where all the nodes in it are in C and are not attacked by no nodes in I
 *
 * The function retrieve all the nodes in C which are not attacked by any nodes in I. This function
 * is useful in the function isNempty().
 * The figure makes the mechanism of the function clearer:
 *  \li red are nodes in C;
 *  \li yellow are nodes in I;
 *  \li orange are nodes both in C and in I;
 *
 * The solution N in this case would be {a,b,c,d,h,j,k,l}
 *
 * \dot
 * 	digraph {
 *		a [style="filled" fillcolor="red"];
 *		b [style="filled" fillcolor="red"];
 *		c [style="filled" fillcolor="red"];
 *		d [style="filled" fillcolor="orange"];
 *		e [style="filled" fillcolor="orange"];
 *		f [style="filled" fillcolor="orange"];
 *		g [style="filled" fillcolor="red"];
 *		h [style="filled" fillcolor="red"];
 *		i [style="filled" fillcolor="red"];
 *		j [style="filled" fillcolor="red"];
 *		k [style="filled" fillcolor="orange"];
 *		l [style="filled" fillcolor="red"];
 *		m [style="filled" fillcolor="yellow"];
 *
 *		a->d;
 *		b->d;
 *		c->d;
 *		d->f;
 *		e->f;
 *		f->e;
 *		h->i;
 *		i->d;
 *		j->h;
 *		k->g;
 *		k->i;
 *		l->j;
 * 	}
 * \enddot
 *
 * \pre
 *  \li N initialized correctly through a constructor;
 * \post
 *  \li N is storing all the solution nodes
 *
 * @param[in] C the set containing all the nodes in the output
 * @param[in] I the set that attacks some nodes in C
 * @param[out] N all the nodes in C which are not attacked by any nodes in I
 */
void Grounded::computeNSet(SetArguments* C, SetArguments* I, SetArguments* N) {
	SetArguments* nodeAttackers;

	/* for each node in C, computes the nodes which attack it:
	   	   if there are none, add the node analysed in N
	   	   continue otherwise */
	for (SetArgumentsIterator it=C->begin(); it!=C->end(); it++){
		nodeAttackers= new SetArguments();
		(*it)->get_attackers()->intersect(I,nodeAttackers);
		if (nodeAttackers->empty()==true)
			N->add_Argument(*it);
		delete nodeAttackers;
	}
}

Grounded::~Grounded() {
}

