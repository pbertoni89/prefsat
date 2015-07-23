/**
 * \file SCCSEQ.cpp
 * \class SCCSEQ
 * \brief computes all the information about SCCs
 *
 * This function enables you to computes SCCs.
 * The main function is performSCCSEQ() which:
 * \li computes SCCs
 * \li order topologically the SCCs computes
 * \li stores them in the output parameter
 *
 * The class is important for the prefAlgorithm classes in its main algorithm
 *
 * \author Koldar
 * \date Aug 13 2013
 *
 */

#include "SCCSEQ.h"

using namespace std;

//TODO documentazione
void SCCSEQ::performSCCSEQ(SetArguments* graph, vector<SetArguments*>* setSCC) {
	
	SCC(graph, setSCC);
	
	#if DEBUG_SCCSEQ > 0
		cout << "OUTPUT OF SCC:" << endl;
		for (unsigned int i=0; i<setSCC->size(); i++)
			cout << "S"<<i<<" = " << *setSCC->at(i) << endl;
	#endif

	SEQ(setSCC);
}

/**@brief Computes the SCC algorithm.
 *
 *	This function computes the algorithm that finds SCC in a specific graph.
 *	For further information about this algorithm, please visit the web page of wikipedia
 *	http://en.wikipedia.org/wiki/Tarjan's_strongly_connected_components_algorithm
 *
 * \pre
 *  \li setSCC must be initialized correctly through a constructor
 *
 * @param[in] graph the input graph where some SCCs have to be found
 * @param[out] setSCC the list of SCC that has been found in the graph
 */
void SCCSEQ::SCC(SetArguments* graph, vector<SetArguments*>* setSCC){
	int index;

	unordered_map <int,ExtendedArgument*> nodesMap;
	vector<Argument*> stack;

	//inizializzazione dei dati di assistenza per tarjan
	for (SetArgumentsIterator it= graph->begin(); it!= graph->end(); it++)
		nodesMap.insert(make_pair((*it)->getNumber(),new ExtendedArgument()));

	index = 0;
	stack = vector<Argument*>();

	for (SetArgumentsIterator it = graph->begin(); it != graph->end(); it++)
		if (nodesMap[(*it)->getNumber()]->index == ExtendedArgument::INDEXDEFAULT)
			strongConnected(*it,graph, &index, &stack, setSCC, &nodesMap);

	for (auto it=nodesMap.begin();it!=nodesMap.end();it++){
		delete (*it).second;
	}
	nodesMap.clear();
}

//TODO documentazione
void SCCSEQ::SEQ(vector<SetArguments*>* setSCC){
	/* definiamo macrografo il grafo dove ogni scc è sintetizzato in un nodo,
		e i macroarchi sussistono ove sussistevano archi.
	   IMPORTANTE non serve memorizzare un collegamento tra nodi e macronodi:
		l'iesimo sccset è l'iesimo macronodo e descrive già i propri nodi */
	SetArguments macroGraph = SetArguments();
	AF macroAF = AF();

	/* Un SCC è da un punto di vista del macrografo visibile come un Argument;
	 * da un punto di vista del grafo, come un SetArguments. */

	//generate, for each scc, the corrispective node in the macroGraph
	for(unsigned int i=0; i<setSCC->size(); i++)
		macroGraph.add_Argument(new Argument(genName(i), i, &macroAF));

	SCCSEQ::linkMacroGraph(setSCC, &macroGraph);
	#if DEBUG_SCCSEQ > 1
		cout << "macrograph is now: " << endl;
		macroGraph.printNodeRelations();
	#endif

	vector<int> positions_toposorted = vector<int>();
	SCCSEQ::toposort(macroGraph, &positions_toposorted);
	#if DEBUG_SCCSEQ > 1
		cout << "position toposorted: ";
		for(unsigned int i=0; i<positions_toposorted.size(); i++)
			cout << positions_toposorted[i] << ", ";
		cout <<endl;
	#endif

	SCCSEQ::finalsorting(setSCC, positions_toposorted);

	#if DEBUG_SCCSEQ > 0
		cout << "OUTPUT OF SCCSEQ: " << endl;
		for(unsigned int i=0; i<setSCC->size(); i++)
			cout << "S"<<i<<" = " << *setSCC->at(i) << endl;
		cout <<endl;
	#endif

	//we need to free all the Arguments inside macroGraph because they are not longer needed
	for (auto it=macroGraph.begin();it!=macroGraph.end();it++){
		delete (*it);
	}

}

//TODO documentazione
void SCCSEQ::finalsorting(vector<SetArguments*>* setSCC, vector<int> pos) {
	vector<SetArguments*>* tempSCC = new vector<SetArguments*>(); // cloning
	if(setSCC->size() != pos.size()) {
		cout << " Errore in SCCSEQ. Exiting " <<endl;
		exit(1);
	}
	for(unsigned int i=0; i<pos.size(); i++)
		tempSCC->push_back(setSCC->at(i));
	for(unsigned int i=0; i<pos.size(); i++)
		setSCC->at(i) = tempSCC->at(pos.at(i));
	delete tempSCC; //TODO testing
}

/**@brief create the connections between SCCs creating a macroGraph
 *
 * \dot
 * 	digraph {
 * 		subgraph cluster1 {
 * 			style="dashed";
 * 			color="red";
 * 			n01;
 * 		}
 * 		subgraph cluster3 {
 * 			style="dashed";
 * 			color="red";
 * 			n02;
 * 			n03;
 * 		}
 * 		subgraph cluster6 {
 * 			style="dashed";
 * 			color="red";
 * 			n04;
 * 		}
 * 		subgraph cluster4 {
 * 			style="dashed";
 * 			color="red";
 * 			n05;
 * 		}
 * 		subgraph cluster5 {
 * 			style="dashed";
 * 			color="red";
 * 			n06;
 * 			n07;
 * 			n08;
 * 			n09;
 * 		}
 * 		subgraph cluster2 {
 * 			style="dashed";
 * 			color="red";
 * 			n10;
 * 			n11;
 * 			n12;
 * 		}
 * 		subgraph cluster7 {
 * 			style="dashed";
 * 			color="red";
 * 			n13;
 * 			n14;
 * 		}
 *
 *		n01->n02 [color="red", lhead=cluster1, ltail=cluster3];
 *		n03->n04 [color="red", lhead=cluster3, ltail=cluster6];
 *		n01->n05 [color="red", lhead=cluster1, ltail=cluster4];
 *		n01->n07 [color="red", lhead=cluster1, ltail=cluster5];
 *		n05->n06 [color="red", lhead=cluster4, ltail=cluster5];
 *		n12->n09 [color="red", lhead=cluster2, ltail=cluster5];
 *		n08->n13 [color="red", lhead=cluster5, ltail=cluster7];
 *		n04->n14 [color="red", lhead=cluster6, ltail=cluster7];
 *
 * 		n01->n02;
 * 		n02->n03;
 * 		n03->n02;
 * 		n03->n04;
 * 		n01->n05;
 * 		n05->n06;
 * 		n06->n07;
 * 		n07->n08;
 * 		n08->n09;
 * 		n01->n07;
 * 		n10->n11;
 * 		n11->n12;
 * 		n12->n10;
 * 		n12->n09;
 * 		n08->n13;
 * 		n13->n14;
 * 		n14->n13;
 * 		n04->n04;
 * 	}
 * \enddot
 *
 * In the figure the black color indicates the original graph while the red indicates the new macro graph to create. The function
 * receives as input the set of macro nodes (red nodes) and must compute the red graph in figures.
 *
 * @param sccset a set of macro arguments (aka set of argument in relationship with eachother)
 * @param macroGraph a graph
 */
void SCCSEQ::linkMacroGraph(vector<SetArguments*>* setSCC, SetArguments* macroGraph) {
	/* occorre creare gli archi giusti nel macrografo, per ora composto di macronodi isolati.
	 * Siccome un SCC è un insieme minimale (slide 9), pat sostiene che,
	 * se esiste un attacco da n incluso in Si a m incluso in Sj, allora
	 * 	Si attacca Sj
	 * 	Sj non attacca sicuramente Si, altrimenti essi costituirebbero un SCC unico
	 */
	auto it_i = setSCC->begin(), it_end = setSCC->end();
	int ind_i = 0, ind_j = 0;
	while(it_i!=it_end-1){
		bool i_attacks_j = false;
		auto it_j = it_i+1;
		ind_j = ind_i+1;
		while(it_j!=it_end && !i_attacks_j){
				SetArguments* tempIJ = (*it_i)->getSubsetAttackedBy(*it_j);
				//se non c'è alcun nodo in "j" che attacca i nodi in "i" allora i due macro argomenti non hanno un arco che li collega.
				if(!tempIJ->empty()) {
					macroGraph->getArgumentByNumber(ind_i)->add_attackers(macroGraph->getArgumentByNumber(ind_j));
					macroGraph->getArgumentByNumber(ind_j)->add_attacks(macroGraph->getArgumentByNumber(ind_i));
					i_attacks_j = true;
				}
				delete tempIJ; // TODO testing
			it_j++;
			ind_j++;
		}
		it_i++;
		ind_i++;
	}
}

/**Generates a string numbered useful to be the name of new arguments.
 *
 * \pre
 *  \li No precedent argument name must have Sx as name (where S is rthe character itself while x is the number)
 *
 * @param i the number to be appended to the character "S"
 * @return a string composed as "S"+<number_i>
 */
std::string SCCSEQ::genName(unsigned int i) {
	string name = "S";
	ostringstream convert;
	convert << i;
	name.append(convert.str());
	return name;
}

//TODO migliorare la documentazione
/**
 * The function run the Kahn algorithm to compute a topological sort of a graph. Fort further information about this algorithm, please
 * visit the page http://en.wikipedia.org/wiki/Topological_sorting#Algorithms
 *
 * @param G a SetArguments representing the macrograph of SCC. Macrograph is a graph where single arguments are none other than SCC computed by Tarjan Algorithm
 * 	(implmented by SCC() function)
 * @param L
 */
// passo (macro)grafo PER VALORE: ci opererò sopra infatti. Inutile: copi la struttura, non le strutture referenziate e quindi il danno lo fai comunque.
//Fortunatamente le informazioni che vengono perse non sono più utilizzate nell'algoritmo e quindi perderle non è rilevante ;D
void SCCSEQ::toposort(SetArguments macroGraph, vector<int>* L) {

	//stack representing the starting macroNodes which have NO attackers
	stack<Argument*> S = stack<Argument*>();

	for(SetArgumentsIterator it = macroGraph.begin(); it != macroGraph.end(); it++)
		//we can use Argument->get_attackers() because the graph where (*it) comes from is the macroGraph, not a subset of a larger graph
		if( (*it)->get_attackers()->empty() ) {
			S.push(*it);
			#ifdef DEBUG_SCCSEQ
				cout << "added "<< S.top()->print() << " to S."<<endl;
			#endif
		}

	while(!S.empty()) {
		Argument* n = S.top();
		S.pop();
		#ifdef DEBUG_SCCSEQ
			if(!S.empty())
				cout << endl <<"WHILE EXT. popped n = "<< n->print() <<"from S. S.top = " << S.top()->print()<< endl;
			else
				cout << endl <<"WHILE EXT. popped n = "<< n->print() <<"from S. S is empty."<< endl;
		#endif
		L->push_back(n->getNumber());
		#ifdef DEBUG_SCCSEQ
			cout <<" L = [";
			for(unsigned int i=0; i<L->size(); i++)
				cout << L->at(i) << ", ";
			cout <<" ]"<< endl;
		#endif

		//we can use Argument->get_attacks() because the graph where n comes from is the macroGraph, not a subset of a larger graph
		SetArguments* attackedByN = n->get_attacks();
		//IMPORTANT: we don't care wether or not the data about the attackers/attacks is lost after removing permanently an attacks/attackers:
		//this because that data is not useful anymore (according to Kahn algorithm, that information is no longer used after the consumption).

		//TODO test the removal
//		SetArguments* copyOfAttackedByN = new SetArguments();
//		attackedByN->clone(copyOfAttackedByN);

		#ifdef DEBUG_SCCSEQ
			cout << " creato attackedBy " << n->print() << endl;
			attackedByN->printNodeRelations();
		#endif

		SetArgumentsIterator it = attackedByN->begin();
		Argument* m = (*it);
		while(/*(it != 0) &&*/ it != attackedByN->end()) {
			m = (*it);
			#ifdef DEBUG_SCCSEQ
				cout <<" inizio while sui M, m " << m->print() << endl;
				cout <<" inizio while sui M, attackedByN " << endl;
				attackedByN->printNodeRelations();
				cout <<" inizio while sui M, copyOfAttackedByN " << endl;
				copyOfAttackedByN->printNodeRelations();
				cout <<" inizio while sui M, G " << endl;
				G.printNodeRelations();
				cout << "rimuovo (n,m) = "<< n->print() <<","<<m->print() <<" da G(?)"<<endl;
			#endif
			n->remove_attacks(m);
			m->remove_attackers(n);
			//we can use Argument->get_attacks() because the graph where n comes from is the macroGraph, not a subset of a larger graph
			attackedByN = n->get_attacks();
			#ifdef DEBUG_SCCSEQ
				cout <<" meta while sui M, attackedByN " << endl;
				attackedByN->printNodeRelations();
				cout <<" inizio while sui M, copyOfAttackedByN " << endl;
				copyOfAttackedByN->printNodeRelations();
				cout <<" meta while sui M, G " << endl;
				G.printNodeRelations();
			#endif

			//we can use Argument->get_attackers() because the graph where (*it) comes from is the macroGraph, not a subset of a larger graph
			if(m->get_attackers()->empty()) {
				S.push(m);
				#ifdef DEBUG_SCCSEQ
					cout << "aggiungo m= "<< m->print() <<" (no more attackers) in S." << endl;
					cout << "dopo aggiunta,  S.top = " << S.top()->print() << endl;
				#endif
			}

			#ifdef DEBUG_SCCSEQ
				cout <<"termine while sui M, S.top ="<< S.top()->print() << ", attackedByN"<<endl;
				attackedByN->printNodeRelations();
				cout <<" inizio while sui M, copyOfAttackedByN " << endl;
				copyOfAttackedByN->printNodeRelations();
				cout <<"termine while sui M, G " << endl;
				G.printNodeRelations();
			#endif
			it++;
		}
		#ifdef DEBUG_SCCSEQ
			if(!S.empty())
				cout <<"termine iterazione WHILE EXT, S.top ="<< S.top()->print() <<endl;
			else
				cout <<"termine iterazione WHILE EXT, S is empty"<<endl;
		#endif
	}
	#ifdef DEBUG_SCCSEQ
		cout << "final macroGraph" << endl;
		G.printNodeRelations();
		cout << "final list::: " <<  endl;
		for(unsigned int i=0; i<L->size(); i++)
			cout << L->at(i) << ", ";
	#endif
	if(macroGraph.graphHasEdges()) {
		cout << "Dopo toposort, il macrografo ha ancor edges. Probabilmente non è stato fornito un DAG. Errore, termino!" << endl;
		exit(1);
	}
}

/**@brief function needed by SCC
 *
 * This function is the recursive procedure to compile index and lowlink fields of an ExtendedArgument.
 *
 * @param v the argument which lowlink and index fields must be compiled
 * @param graph the graph in which all nodes handled by tarjan algorithm must be contained
 * @param globalIndex variable used by tarjan algorithm
 * @param stack a vector of Arguments needed by the tarjan algorthm
 * @param sccresult the location where put a new SCC when the algorithm reveals it
 * @param nodeMap a unordered_map that associate for each argument ID number the corrispective class storing lowlink and index values
 */
void SCCSEQ::strongConnected(Argument* v, SetArguments* graph,int* globalIndex, vector<Argument*>* stack, vector<SetArguments*>* sccresult,
		unordered_map <int,ExtendedArgument*>* nodeMap){
	(*nodeMap)[v->getNumber()]->index=*globalIndex;
	(*nodeMap)[v->getNumber()]->lowlink=*globalIndex;
	*globalIndex=*globalIndex+1;
	stack->push_back(v);


	for (SetArgumentsIterator w = graph->getArgumentAttacksInSet(v)->begin(); w != graph->getArgumentAttacksInSet(v)->end(); w++){
		if ((*nodeMap)[(*w)->getNumber()]->index == ExtendedArgument::INDEXDEFAULT) {
			strongConnected(*w, graph, globalIndex, stack, sccresult, nodeMap);
			(*nodeMap)[v->getNumber()]->lowlink = min((*nodeMap)[v->getNumber()]->lowlink, (*nodeMap)[(*w)->getNumber()]->lowlink);
		}
		else if (find(stack->begin(),stack->end(),*w) != stack->end())
			(*nodeMap)[v->getNumber()]->lowlink = min((*nodeMap)[v->getNumber()]->lowlink, (*nodeMap)[(*w)->getNumber()]->index);
	}

	if ((*nodeMap)[v->getNumber()]->lowlink == (*nodeMap)[v->getNumber()]->index) {
		Argument* w;
		SetArguments* scc = new SetArguments();
		do {
			w=stack->back();
			stack->pop_back();
			scc->add_Argument(w);
		}while (w!=v);
		sccresult->push_back(scc);
		//delete scc; NON SI PUÒ FARE. cercar di capire se si può distruggere a posteriori
	}
}

/** @return the set union of all SCCs who are fathers of s_i. An SCC s_j is a father of s_i if s_j attacks s_i.
 *  @pre setSCC is already toposorted, to improve speedness by searching only with 0<=j<i
 *  @pre i<= setSCC->size()
 *  TODO handle memory leak!!! */
vector<SetArguments*>* SCCSEQ::getFathersUnion(vector<SetArguments*>* setSCC, SetArguments* s_i) {
	vector<SetArguments*>* a_i = new vector<SetArguments*>();
	//cout << "started get fathers with s_i " << *s_i << " printing setSCC" << endl;
	//for(auto itt=setSCC->begin(); itt!=setSCC->end(); itt++)
	//	cout << "S: " << **itt << endl;
	for(auto it_j=setSCC->begin(); ((**it_j)!=(*s_i) and it_j!=setSCC->end()); it_j++) {
		SetArguments* s_j_attacks_s_i = (*it_j)->getSubsetAttacks(s_i);
		//cout << "s_j = " << **it_j << endl;
		if(!s_j_attacks_s_i->empty()) {
			//cout << "aggiungo s_j ad a_i = " << *a_i << endl;
			a_i->push_back(*it_j);
		}
	}
	//cout << "ritorno a_i = " << *a_i << endl;
	return a_i;
}
