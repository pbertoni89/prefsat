#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "Grounded.h"
#include "AF.h"
#include "SCCSEQ.h"
#include "SetArguments.h"
#include "PrefAlgorithm.h"
#include "Labelling.h"
#include "SetArgumentsVector.h"

using namespace std;

void test_AspartixImproved3(){
	PrefAlgorithm solver=PrefAlgorithm("test-input/example06.dl");

	SetArgumentsVector trueSolution=SetArgumentsVector();
	trueSolution.push_back(new SetArguments());

	SetArgumentsVector solution=solver.handlePref(true);
	cout << "solution:     "<<solution << endl;
	cout << "truesolution: "<<trueSolution<<endl;

	ASSERT_EQUALM("something is wrong in example06.dl!",solution,trueSolution);
}

void test_AspartixImproved2(){
	PrefAlgorithm solver=PrefAlgorithm("test-input/example05.dl");

	SetArgumentsVector trueSolution=SetArgumentsVector();
	trueSolution.push_back(new SetArguments(solver.framework,(string[]){"n1", "n3", "n14", "n15", "n22", "n23", "n26", "n29", "n30", "n33", "n39", "n40"},12));
	trueSolution.push_back(new SetArguments(solver.framework,(string[]){"n1", "n3", "n11", "n14", "n22", "n23", "n26", "n29", "n30", "n33", "n39", "n40"},12));

	SetArgumentsVector solution=solver.handlePref(true);
	cout << "solution:     "<<solution << endl;
	cout << "truesolution: "<<trueSolution<<endl;

	ASSERT_EQUALM("something is wrong in example05.dl!",solution,trueSolution);
}

void test_AspartixImproved1(){
	PrefAlgorithm solver=PrefAlgorithm("test-input/example04.dl");

	SetArgumentsVector trueSolution=SetArgumentsVector();
	trueSolution.push_back(new SetArguments(solver.framework,(string[]){"n5", "n9", "n10", "n12", "n14", "n16", "n20", "n23", "n25", "n26"},10));

	SetArgumentsVector solution=solver.handlePref(true);
	cout << "solution:     "<<solution << endl;
	cout << "truesolution: "<<trueSolution<<endl;

	ASSERT_EQUALM("something is wrong in example05.dl!",solution,trueSolution);
}

void test_ZanellaImproved3(){
	PrefAlgorithm solver=PrefAlgorithm("test-input/Zanellaesempio3.dl");

	SetArgumentsVector trueSolution=SetArgumentsVector();
	trueSolution.push_back(new SetArguments(solver.framework,(string[]){"n01","n02","n03","n04"},4));

	SetArgumentsVector solution=solver.handlePref(true);
	cout << "solution:     "<<solution << endl;
	cout << "truesolution: "<<trueSolution<<endl;

	ASSERT_EQUALM("something is wrong in Zanellaesempio2.dl!",solution,trueSolution);
}

void test_ZanellaImproved2(){
	PrefAlgorithm solver=PrefAlgorithm("test-input/Zanellaesempio2.dl");

	SetArgumentsVector trueSolution=SetArgumentsVector();
	trueSolution.push_back(new SetArguments(solver.framework,(string[]){"n01","n02","n03","n04"},4));
	trueSolution.push_back(new SetArguments(solver.framework,(string[]){"n02","n03","n04","n07"},4));

	SetArgumentsVector solution=solver.handlePref(true);
	cout << "solution:     "<<solution << endl;
	cout << "truesolution: "<<trueSolution<<endl;

	ASSERT_EQUALM("something is wrong in Zanellaesempio2.dl!",solution,trueSolution);
}

void test_ZanellaImproved1(){
	PrefAlgorithm solver=PrefAlgorithm("test-input/esempio1.dl");

	SetArgumentsVector trueSolution=SetArgumentsVector();
	trueSolution.push_back(new SetArguments(solver.framework,(string[]){"n01","n03","n06","n14"},4));
	trueSolution.push_back(new SetArguments(solver.framework,(string[]){"n01","n03","n13","n06"},4));

	SetArgumentsVector solution=solver.handlePref(true);
	cout << "solution:     "<<solution << endl;
	cout << "truesolution: "<<trueSolution<<endl;

	ASSERT_EQUALM("something is wrong in esempio1.dl!",solution,trueSolution);
}

void test_Aspartix3(){
	PrefAlgorithm solver=PrefAlgorithm("test-input/example06.dl");

	SetArgumentsVector trueSolution=SetArgumentsVector();
	trueSolution.push_back(new SetArguments());

	SetArgumentsVector solution=solver.handlePref(false);
	cout << "solution:     "<<solution << endl;
	cout << "truesolution: "<<trueSolution<<endl;

	ASSERT_EQUALM("something is wrong in example06.dl!",solution,trueSolution);
}

void test_Aspartix2(){
	PrefAlgorithm solver=PrefAlgorithm("test-input/example05.dl");

	SetArgumentsVector trueSolution=SetArgumentsVector();
	trueSolution.push_back(new SetArguments(solver.framework,(string[]){"n1", "n3", "n14", "n15", "n22", "n23", "n26", "n29", "n30", "n33", "n39", "n40"},12));
	trueSolution.push_back(new SetArguments(solver.framework,(string[]){"n1", "n3", "n11", "n14", "n22", "n23", "n26", "n29", "n30", "n33", "n39", "n40"},12));

	SetArgumentsVector solution=solver.handlePref(false);
	cout << "solution:     "<<solution << endl;
	cout << "truesolution: "<<trueSolution<<endl;

	ASSERT_EQUALM("something is wrong in example05.dl!",solution,trueSolution);
}

void test_Aspartix1(){
	PrefAlgorithm solver=PrefAlgorithm("test-input/example04.dl");

	SetArgumentsVector trueSolution=SetArgumentsVector();
	trueSolution.push_back(new SetArguments(solver.framework,(string[]){"n5", "n9", "n10", "n12", "n14", "n16", "n20", "n23", "n25", "n26"},10));

	SetArgumentsVector solution=solver.handlePref(false);
	cout << "solution:     "<<solution << endl;
	cout << "truesolution: "<<trueSolution<<endl;

	ASSERT_EQUALM("something is wrong in example05.dl!",solution,trueSolution);
}

void test_Zanella3(){
	PrefAlgorithm solver=PrefAlgorithm("test-input/Zanellaesempio3.dl");

	SetArgumentsVector trueSolution=SetArgumentsVector();
	trueSolution.push_back(new SetArguments(solver.framework,(string[]){"n01","n02","n03","n04"},4));

	SetArgumentsVector solution=solver.handlePref(false);
	cout << "solution:     "<<solution << endl;
	cout << "truesolution: "<<trueSolution<<endl;

	ASSERT_EQUALM("something is wrong in Zanellaesempio2.dl!",solution,trueSolution);
}

void test_Zanella2(){
	PrefAlgorithm solver=PrefAlgorithm("test-input/Zanellaesempio2.dl");

	SetArgumentsVector trueSolution=SetArgumentsVector();
	trueSolution.push_back(new SetArguments(solver.framework,(string[]){"n01","n02","n03","n04"},4));
	trueSolution.push_back(new SetArguments(solver.framework,(string[]){"n02","n03","n04","n07"},4));

	SetArgumentsVector solution=solver.handlePref(false);
	cout << "solution:     "<<solution << endl;
	cout << "truesolution: "<<trueSolution<<endl;

	ASSERT_EQUALM("something is wrong in Zanellaesempio2.dl!",solution,trueSolution);
}

void test_Zanella1(){
	PrefAlgorithm solver=PrefAlgorithm("test-input/esempio1.dl");

	SetArgumentsVector trueSolution=SetArgumentsVector();
	trueSolution.push_back(new SetArguments(solver.framework,(string[]){"n01","n03","n06","n14"},4));
	trueSolution.push_back(new SetArguments(solver.framework,(string[]){"n01","n03","n13","n06"},4));

	SetArgumentsVector solution=solver.handlePref(false);
	cout << "solution:     "<<solution << endl;
	cout << "truesolution: "<<trueSolution<<endl;

	ASSERT_EQUALM("something is wrong in esempio1.dl!",solution,trueSolution);
}

void test_SetArgumentsVector_operator_equal(){
	PrefAlgorithm solver=PrefAlgorithm("test-input/esempio1.dl");

	SetArgumentsVector trueSolution=SetArgumentsVector();
	trueSolution.push_back(new SetArguments(solver.framework,(string[]){"n01","n03","n06","n14"},4));
	trueSolution.push_back(new SetArguments(solver.framework,(string[]){"n01","n03","n13","n06"},4));

	SetArgumentsVector fakeSolution1=SetArgumentsVector();
	fakeSolution1.push_back(new SetArguments(solver.framework,(string[]){"n01","n03","n06"},3));
	fakeSolution1.push_back(new SetArguments(solver.framework,(string[]){"n01","n03","n06","n13"},4));

	SetArgumentsVector fakeSolution2=SetArgumentsVector();
		fakeSolution2.push_back(new SetArguments(solver.framework,(string[]){"n01","n03","n06","n14"},4));

	SetArgumentsVector solution=solver.handlePref(false);
	cout << "solution:      "<<solution << endl;
	cout << "true solution: "<<trueSolution<<endl;
	cout << "fake solution1:"<<fakeSolution1<<endl;
	cout << "fake solution2:"<<fakeSolution2<<endl;

	cout << "verifico che solution==trueSolution..."<<endl;
	ASSERT_EQUALM("SetArgumentsVector == is malfunctioning!",true,solution==trueSolution);
	cout << "verifico che solution!=fakeSolution1..."<<endl;
	ASSERT_EQUALM("something is wrong in the return false of ==!",false,solution==fakeSolution1);
	cout << "verifico che solution!=fakeSolution2..."<<endl;
	ASSERT_EQUALM("something is wrong in the return false of ==!",false,solution==fakeSolution2);

}

void test_SetArgumentsVector_addSetArgumentsToAll(){
	AF af=AF();
	ASSERTM("file cannot be read",af.readFile("test-input/esempio1.dl"));
	SetArgumentsVector truelablist=SetArgumentsVector();
	SetArgumentsVector lablist=SetArgumentsVector();
	cout << "creating the varoius sets..."<<endl;

	SetArguments setD=SetArguments(af,(string[]){"n02"},1);

	SetArguments setA=SetArguments(af,(string[]){"n01","n05","n03"},3);
	SetArguments setB=SetArguments(af,(string[]){"n02"},1);
	SetArguments setC=SetArguments(af,(string[]){"n10","n11","n12","n13","n14"},5);
	SetArguments setE=SetArguments(af,(string[]){"n02","n03","n01","n13"},4);

	SetArguments truesetA=SetArguments(af,(string[]){"n02","n01","n05","n03"},4);
	SetArguments truesetB=SetArguments(af,(string[]){"n02"},1);
	SetArguments truesetC=SetArguments(af,(string[]){"n02","n10","n14","n12","n13","n11"},6);
	SetArguments truesetE=SetArguments(af,(string[]){"n02","n03","n01","n13"},4);
	truelablist.push_back(&truesetA);
	truelablist.push_back(&truesetB);
	truelablist.push_back(&truesetC);
	truelablist.push_back(&truesetE);

	cout << "creating lablist..."<<endl;
	lablist.push_back(&setA);
	lablist.push_back(&setB);
	lablist.push_back(&setC);
	lablist.push_back(&setE);
	cout << "lablist before: "<< lablist<< endl;
	cout << "setD: "<<setD << endl;
	cout << "invoking lablist.addSetArgumentsToAll(&setD)..."<<endl;
	lablist.addSetArgumentsToAll(&setD);
	cout << "lablist:      " << lablist << endl;
	cout << "truelabllist: " << truelablist << endl;

	ASSERT_EQUALM("size of lablist is mismatching!",truelablist.size(),lablist.size());

	for (auto trueit=truelablist.begin();trueit!=truelablist.end();trueit++){
		cout << "checking " << **trueit << "..."<<endl;
		ASSERT_EQUALM("item not found!",true,lablist.exist(*trueit));
	}
}

void test_SetArgumentsVector_find(){
	AF af=AF();
	ASSERTM("file cannot be read",af.readFile("test-input/esempio1.dl"));
	SetArgumentsVector lablist1=SetArgumentsVector();
	cout << "creating the varoius sets..."<<endl;
	SetArguments setA=SetArguments(af,(string[]){"n01","n05","n03"},3);
	SetArguments setB=SetArguments(af,(string[]){"n02"},1);
	SetArguments setC=SetArguments(af,(string[]){"n10","n11","n12","n13","n14"},5);
	SetArguments setD=SetArguments(af,(string[]){"n02"},1);
	SetArguments setE=SetArguments(af,(string[]){"n05","n03","n01","n13"},4);

	lablist1.push_back(&setA);
	lablist1.push_back(&setB);
	lablist1.push_back(&setC);

	cout << "looking for " << setC << " (it exist inside lablist1)... "<< endl;;
	ASSERT_EQUALM("can't find labC!",true,lablist1.exist(&setC));
	cout << "looking for " << setE << " (it does not exist in lablist1)..."<< endl;
	ASSERT_EQUALM("you found labE, but you shouldn\'t",false,lablist1.exist(&setE));
}

void test_SetArgumentsVector_plus(){
	AF af=AF();
	ASSERTM("file cannot be read",af.readFile("test-input/esempio1.dl"));
	SetArgumentsVector lablist1=SetArgumentsVector();
	SetArgumentsVector lablist2=SetArgumentsVector();
	cout << "creating the varoius sets..."<<endl;
	SetArguments setA=SetArguments(af,(string[]){"n01","n05","n03"},3);
	SetArguments setB=SetArguments(af,(string[]){"n02"},1);
	SetArguments setC=SetArguments(af,(string[]){"n10","n11","n12","n13","n14"},5);
	SetArguments setD=SetArguments(af,(string[]){"n02"},1);
	SetArguments setE=SetArguments(af,(string[]){"n05","n03","n01","n13"},4);
	cout << "creating lablist1..."<<endl;
	lablist1.push_back(&setA);
	lablist1.push_back(&setB);
	lablist1.push_back(&setC);
	cout << "creating lablist2..."<<endl;
	lablist2.push_back(&setC);
	lablist2.push_back(&setD);
	lablist2.push_back(&setE);
	cout << "lablist1: "<< lablist1 << endl;
	cout << "lablist2: "<< lablist2 << endl;
	cout << "creating clones of lablist1 & lablist2..." << endl;
	SetArgumentsVector clonelablist1=SetArgumentsVector();
	lablist1.clone(&clonelablist1);
	SetArgumentsVector clonelablist2=SetArgumentsVector();
	lablist2.clone(&clonelablist2);
	cout << "using + operator to compute lablist3..." << endl;
	SetArgumentsVector lablist3;
	lablist3=lablist1+lablist2;
	cout << "recout all lablist!"<< endl;

	cout << "lablist1: "<< lablist1 << endl;
	cout << "lablist2: "<< lablist2 << endl;
	cout << "lablist2: "<< lablist3 << endl;

	bool found;

	ASSERT_EQUALM("lablist1 size has been modified!",clonelablist1.size(),lablist1.size());
	for (auto it1clone=clonelablist1.begin();it1clone!=clonelablist1.end();it1clone++){
		found=false;
		cout << "checking if "<< *it1clone << "is agiain stored in lablist1...";
		for (auto it1=lablist1.begin();it1!=lablist1.end(); it1++){
			if ((*it1clone)==(*it1)){
				found=true;
				cout << "YES";
				break;
			}
		}
		cout << endl;
		ASSERT_EQUALM("item not found!",true,found);
	}
	ASSERT_EQUALM("lablist2 size has been modified!",clonelablist2.size(),lablist2.size());
	for (auto it2clone=clonelablist2.begin();it2clone!=clonelablist2.end();it2clone++){
		found=false;
		cout << "checking if "<< *it2clone << "is agiain stored in lablist2...";
		for (auto it2=lablist2.begin();it2!=lablist2.end(); it2++){
			if ((*it2clone)==(*it2)){
				found=true;
				cout << "YES";
				break;
			}
		}
		cout << endl;
		ASSERT_EQUALM("item not found!",true,found);
	}

	for (auto it1=lablist1.begin();it1!=lablist1.end();it1++){
		cout << "checkin if "<< *it1 << "is stored in lablist3...";
		found=false;
		for (auto it3=lablist3.begin();it3!=lablist3.end();it3++){
			if ((*it1)==(*it3)){
				found=true;
				cout << " FOUND";
				break;
			}
		}
		cout << endl;
		ASSERT_EQUALM("item not found!",true,found);
	}

	for (auto it2=lablist2.begin();it2!=lablist2.end();it2++){
		cout << "checkin if "<< *it2 << "is stored in lablist3...";
		found=false;
		for (auto it3=lablist3.begin();it3!=lablist3.end();it3++){
			if ((*it2)==(*it3)){
				found=true;
				cout << " FOUND";
				break;
			}
		}
		cout << endl;
		ASSERT_EQUALM("item not found!",true,found);
	}
}

void test_SetArgumentsVector_at(){
	AF af=AF();
	ASSERTM("file cannot be read",af.readFile("test-input/esempio1.dl"));
	SetArgumentsVector lablist=SetArgumentsVector();
	SetArguments setA=SetArguments(af,(string[]){"n01","n05","n03"},3);
	SetArguments setB=SetArguments(af,(string[]){"n02"},1);
	SetArguments setC=SetArguments(af,(string[]){"n10","n11","n12","n13","n14"},5);
	lablist.push_back(&setA);
	lablist.push_back(&setB);
	lablist.push_back(&setC);
	cout << "lablist: " << lablist << endl;
	for (unsigned int i=0; i<lablist.size();i++){
		cout << i << "st/nd/rd/th set: " << lablist.at(i) << endl;
	}

	unsigned int i=0;
	for (auto it=lablist.begin();it!=lablist.end();it++){
		cout << "elements #" << i << "is equal to the element in iterator #" << i << "???" << lablist.at(i) << " == " << *it << endl;
		ASSERT_EQUALM("elements are not right!",*it,lablist.at(i));
		i++;
	}
}


void test_SetArgumentsVector_pushback(){
	AF af=AF();
	ASSERTM("file cannot be read",af.readFile("test-input/esempio1.dl"));
	vector<SetArguments*> result=vector<SetArguments*>();
	SetArgumentsVector setlist=SetArgumentsVector();
	SCCSEQ::performSCCSEQ(new SetArguments(af,(string[]){"n01","n03","n05"},3),&result);
	cout << "vector<setArguments*>: { ";
	for (auto it=result.begin();it!=result.end();it++){
		cout << **it << " ";
		setlist.push_back(*it);
	}
	cout << " }" << endl;
	cout << "setlist:               " << setlist << endl;

	bool found;
	for (auto it=setlist.begin(); it!=setlist.end();it++){
		found=false;
		cout << "checking " <<  *it << " ..." <<endl;
		for (auto it2=result.begin(); it2!=result.end();it2++){
			if ((*it2)->equal(**it)){
				found=true;
				break;
			}
		}
		ASSERT_EQUALM("element not found!",true,found);
	}
}

void test_constructorSetArgumentsVectorEmpty(){
	AF af=AF();
	ASSERTM("file cannot be read",af.readFile("test-input/esempio1.dl"));
	SetArgumentsVector lablist=SetArgumentsVector();
	cout << "lablist: "<<lablist << endl;
	ASSERT_EQUALM("lablist is not empty!",0,lablist.size());
}


void test_tillSEQ(){
	AF af=AF();
	SetArguments* G=new SetArguments();
	SetArguments* C=new SetArguments();
	SetArguments* e=new SetArguments();
	SetArguments* I=new SetArguments();
	SetArguments* O=new SetArguments();
	SetArguments* res=new SetArguments();
	vector<SetArguments> Ep= vector<SetArguments>();
	vector<SetArguments*> sccSet= vector<SetArguments*>();
	vector<SetArguments*> truesccSet= vector<SetArguments*>();

	ASSERTM("file cannot be read",af.readFile("test-input/esempio1.dl"));
	G=af.get_arguments_copy();
	C=af.get_arguments_copy();

	Grounded::doGrounded(*G,*C,e,I);
	Ep.push_back(*e);

	cout << "e= " << *e << endl;
	cout << "I= " << *I << endl;
	if (I->cardinality()==0){
		cout << "I={} -> ritorno {e}" << endl;
		return;
	}

	cout << "running setSafeRestrict..." << endl;
	G->setSafeRestrict(I,res);
	G=res;
	cout << "running SCCSEQ..." << endl;
	SCCSEQ::performSCCSEQ(G,&sccSet);

	cout << "computing true sccSset..." << endl;
	truesccSet.push_back(new SetArguments(af,(string[]){"n13","n14"},2));
	truesccSet.push_back(new SetArguments(af,(string[]){"n10","n11","n12"},3));
	truesccSet.push_back(new SetArguments(af,(string[]){"n09"},1));

	for (unsigned int i=0;i<sccSet.size();i++){
		cout << "verify that sccSet[i] (" << *sccSet[i] << ") is equal to truesccSet[i] (" << *truesccSet[i] <<")..." << endl;
		ASSERT_EQUALM("scc is not correct!",true,sccSet[i]->equal(*truesccSet[i]));
	}
}

void test_toposort(){
	AF af=AF();
	ASSERTM("file cannot be read",af.readFile("test-input/toposort.dl"));
	SetArguments* macroGraph=af.get_arguments_copy();
	vector<int> result=vector<int>();
	SCCSEQ::toposort(*macroGraph,&result);

	cout << "toposort result: ";
	for (auto it=result.begin(); it!=result.end();it++){
		cout << " " << *af.getArgumentByNumber(*it);
	}
	cout << endl;
}

void test_linkMacroGraph_lookmanually(){
	AF af=AF();
	AF macroaf=AF();
	ASSERTM("file cannot be read",af.readFile("test-input/esempio1.dl"));
	SetArguments* graph=af.get_arguments_copy();
	vector<SetArguments*> scclist=vector<SetArguments*> ();
	SetArguments* macrograph=new SetArguments();

	cout << "eseguo SCC..."<<endl;
	SCCSEQ::SCC(graph,&scclist);
	cout << "scclist: ";
	for (auto it=scclist.begin();it!=scclist.end();it++){
		cout << **it << " ";
	}
	cout << endl;
	for(unsigned int i=0; i<scclist.size(); i++){
		cout << "scc "<< *scclist[i] << " = " << SCCSEQ::genName(i) << endl;
		macrograph->add_Argument(new Argument(SCCSEQ::genName(i), i,&macroaf));
	}
	cout << "eseguo il link graph..." << endl;
	SCCSEQ::linkMacroGraph(&scclist,macrograph);

	macrograph->printNodeRelations();
}

void test_getSubsetAttacksSet(){
	AF af=AF();
	ASSERTM("file cannot be read",af.readFile("test-input/getSubsetAttacksSet.dl"));

	cout << "costruisco l'insieme ABC..." << endl;
	SetArguments* setABC=new SetArguments(af,(string[]){"A","B","C"},3);
	cout << "costruisco l'attacked set..." << endl;
	SetArguments* setDE=new SetArguments(af,(string[]){"D","E"},2);
	cout << "costruisco la vera soluzione..."<<endl;
	SetArguments* trueResult=new SetArguments(af,(string[]){"A"},1);
	cout << "calcolo getSubsetAttacksSet..." << endl;
	SetArguments* result=setABC->getSubsetAttacks(setDE);
	cout << "result: " << *result << endl;
	cout << "true result: " << *trueResult << endl;
	ASSERTM("getSubsetAttacksBySet isn't working!",result->equal(*trueResult));
}

void test_getSubsetAttackedBySet(){
	AF af=AF();
	ASSERTM("file cannot be read",af.readFile("test-input/getSubsetAttackedBySet.dl"));

	cout << "costruisco l'insieme ABC..." << endl;
	SetArguments* setABC=new SetArguments(af,(string[]){"A","B","C"},3);
	cout << "costruisco l'attacking set..." << endl;
	SetArguments* setDE=new SetArguments(af,(string[]){"D","E"},2);
	cout << "costruisco la vera soluzione..."<<endl;
	SetArguments* trueResult=new SetArguments(af,(string[]){"A","C"},2);
	cout << "calcolo getSubsetAttackedBySet..." << endl;
	SetArguments* result=setABC->getSubsetAttackedBy(setDE);
	cout << "result: " << *result << endl;
	cout << "true result: " << *trueResult << endl;
	ASSERTM("getSubsetAttackedBySet isn't working!",result->equal(*trueResult));
}

void test_getAllAttacksInSet(){
	AF af=AF();
	ASSERTM("file cannot be read",af.readFile("test-input/getAllAttackersInSet.dl"));

	cout << "costruisco l'insieme ABC..." << endl;
	SetArguments* setABC=new SetArguments(af,(string[]){"A","B","C"},3);
	cout << "costruisco la vera soluzione..."<<endl;
	SetArguments* trueResult=new SetArguments(af,(string[]){"A","B"},2);
	cout << "calcolo getAllAttacksInSet..." << endl;
	SetArguments* result=setABC->getAllAttacksInSet();
	cout << "result: " << *result << endl;
	cout << "true result: " << *trueResult << endl;
	ASSERT_EQUALM("getAllAttacksInSet isn't working!",*trueResult,*result);
}

void test_getAllAttackersInSet(){
	AF af=AF();
	ASSERTM("file cannot be read",af.readFile("test-input/getAllAttackersInSet.dl"));

	cout << "costruisco l'insieme ABC..." << endl;
	SetArguments* setABC=new SetArguments(af,(string[]){"A","B","C"},3);
	cout << "costruisco la vera soluzione..."<<endl;
	SetArguments* trueResult=new SetArguments(af,(string[]){"A","B"},2);
	cout << "calcolo getAllAttackersInSet..." << endl;
	SetArguments* result=setABC->getAllAttackersInSet();
	cout << "result: " << *result << endl;
	cout << "true result: " << *trueResult << endl;
	ASSERT_EQUALM("getAllAttackersInSet isn't working!",*trueResult,*result);
}


void test_getAllAttackers(){
	AF af=AF();
	ASSERTM("file cannot be read",af.readFile("test-input/getAllAttackers.dl"));

	cout << "costruisco l'insieme ABC..." << endl;
	SetArguments* setABC=new SetArguments(af,(string[]){"A","B","C"},3);
	cout << "costruisco la vera soluzione..."<<endl;
	SetArguments* trueResult=new SetArguments(af,(string[]){"A","B","D","E"},4);
	cout << "calcolo getAllAttackers..." << endl;
	SetArguments* result=setABC->getAllAttackers();
	cout << "result: " << *result << endl;
	cout << "true result: " << *trueResult << endl;
	ASSERT_EQUALM("getAllAttackers isn't working!",*trueResult,*result);
}

void test_getAllAttacks(){
	AF af=AF();
	cout << "leggo il file..."<< endl;
	ASSERTM("file cannot be read",af.readFile("test-input/getAllAttacks.dl"));

	cout << "costruisco l'insieme ABC..." << endl;
	SetArguments* setABC=new SetArguments(af,(string[]){"A","B","C"},3);
	cout << "costruisco la vera soluzione..."<<endl;
	SetArguments* trueResult=new SetArguments(af,(string[]){"B","E","C"},3);
	cout << "true result: " << *trueResult << endl;
	cout << "calcolo getAllAttacks..." << endl;
	SetArguments* result=setABC->getAllAttacks();
	cout << "result: " << *result << endl;
	ASSERT_EQUALM("getAllAttacks isn't working!",*trueResult,*result);
}

void testSEQ(){
	AF af=AF();
	vector<SetArguments*> scclist=vector<SetArguments*>();
	vector<SetArguments*> truescclist=vector<SetArguments*>();
	ASSERTM("file cannot be read",af.readFile("test-input/esempio1.dl"));

	cout << "costruisco gli insiemi {n10,n11,n12} {n09} {n13,n14}"  << endl;
	SetArguments* Gamma_1=new SetArguments(af,(string[]){"n10","n11","n12"},3);
	SetArguments* Gamma_2=new SetArguments(af,(string[]){"n09"},1);
	SetArguments* Gamma_3=new SetArguments(af,(string[]){"n13","n14"},2);
	SetArguments* trueGamma_1=new SetArguments(af,(string[]){"n10","n11","n12"},3);
	SetArguments* trueGamma_2=new SetArguments(af,(string[]){"n09"},1);
	SetArguments* trueGamma_3=new SetArguments(af,(string[]){"n13","n14"},2);

	cout << "costruisco il vettore di insieme sccList..." << endl;
	scclist.push_back(Gamma_1);
	scclist.push_back(Gamma_2);
	scclist.push_back(Gamma_3);
	cout << "costuirsco il vettore soluzione del test..." << endl;
	truescclist.push_back(trueGamma_3);
	truescclist.push_back(trueGamma_1);
	truescclist.push_back(trueGamma_2);

	cout << "scclist (prima di SEQ): ";
	for (auto it=scclist.begin();it!=scclist.end();it++){
		cout << **it;
	}
	cout << endl;
	cout << "eseguo SEQ" << endl;
	SCCSEQ::SEQ(&scclist);
	cout << "scclist (prima di SEQ): ";
	for (auto it=scclist.begin();it!=scclist.end();it++){
		cout << **it;
	}
	cout << endl;

	ASSERT_EQUALM("le cardinalita' sono diverse!",truescclist.size(),scclist.size());
	cout << "verifico che tutti gli elementi siano presenti..." << endl;
	bool found;
	for (auto it=scclist.begin();it!=scclist.end();it++){
		cout << "verifico " << **it << " ..." << endl;
		found=false;
		for (auto it2=truescclist.begin();it2!=truescclist.end();it2++){
			if ((**it)==(**it2)){
				found=true;
				break;
			}
		}
		ASSERT_EQUALM("SCC not found!",true,found);
	}
}

void testTillSCC(){
	AF af=AF();
	SetArguments* G=new SetArguments();
	SetArguments* C=new SetArguments();
	SetArguments* e=new SetArguments();
	SetArguments* I=new SetArguments();
	SetArguments* O=new SetArguments();
	SetArguments* res=new SetArguments();
	vector<SetArguments> Ep= vector<SetArguments>();
	vector<SetArguments*> sccSet= vector<SetArguments*>();
	vector<SetArguments*> truesccSet= vector<SetArguments*>();

	ASSERTM("file cannot be read",af.readFile("test-input/esempio1.dl"));
	G=af.get_arguments_copy();
	C=af.get_arguments_copy();

	Grounded::doGrounded(*G,*C,e,I);
	Ep.push_back(*e);

	cout << "e= " << *e << endl;
	cout << "I= " << *I << endl;
	if (I->cardinality()==0){
		cout << "I={} -> ritorno {e}" << endl;
		return;
	}

	cout << "running setSafeRestrict..." << endl;
	G->setSafeRestrict(I,res);
	G=res;
	cout << "running SCCSEQ..." << endl;
	SCCSEQ::performSCCSEQ(G,&sccSet);

	cout << "computing true sccSset..." << endl;
	truesccSet.push_back(new SetArguments(af,(string[]){"n10","n11","n12"},3));
	truesccSet.push_back(new SetArguments(af,(string[]){"n09"},1));
	truesccSet.push_back(new SetArguments(af,(string[]){"n13","n14"},2));

	bool found;
	for (auto it=sccSet.begin();it!=sccSet.end();it++){
		cout << "verify that " << **it << "is present in the real solution..." << endl;
		found=false;
		for (auto it2=truesccSet.begin();it2!=truesccSet.end();it2++){
			//using **it because *it is a SetArguments* so **it is a SetArgument!
			if (**it==**it2){
				found=true;
				break;
			}
		}
		ASSERT_EQUALM("SCC not correct!",found,true);
	}
}


void testAF_get_arguments_copy(){
	AF af=AF();
	AF oldaf=AF();
	SetArguments* a=new SetArguments();
	SetArguments* b=new SetArguments();

	ASSERTM("file cannot be read",af.readFile("test-input/esempio1.dl"));
	ASSERTM("file cannot be read",oldaf.readFile("test-input/esempio1.dl"));
	af.get_arguments()->clone(b);
	a=af.get_arguments_copy();

	cout << "trying to remove Argument from a (set as get_arguments_copy)" << endl;
	cout << "af: " << *af.get_arguments() << endl;
	a->remove(af.getArgumentByName("n01"));
	cout << "a: " << *a << endl;
	cout << "af: " << *af.get_arguments() << endl;
	ASSERT_EQUALM("af has been changed!",*oldaf.get_arguments(),*af.get_arguments());
}

//TODO complete this test scenario
void testPrefAlgorithm(){
	PrefAlgorithm* solver = new PrefAlgorithm("test-input/esempio1.dl");
	cout << "computing solution..." << endl;
	SetArgumentsVector solution = solver->handlePref(false);
	cout << "computed!" << endl;
	cout << solution;
}


void testSetRestrict(){

	AF af=AF();
	ASSERTM("file cannot be read",af.readFile("test-input/esempio1.dl"));
	SetArguments* gamma;
	SetArguments* I;
	SetArguments* gammaDownI=new SetArguments();
	SetArguments* setAttackedByN01InI;

	cout << "computing gamma" << endl;
	gamma=af.get_arguments();
	cout << "computing I" << endl;
	I=new SetArguments(af,(string[]){"n06","n07","n08","n09"},4);
	cout << "computing gamma down I" << endl;
	gamma->setSafeRestrict(I,gammaDownI);
	cout << "computing set attackintestTillSCCg n07 in gamma down I" << endl;
	setAttackedByN01InI=gammaDownI->getArgumentAttackersInSet(af.getArgumentByName("n07"));
	cout << "done" << endl;

	SetArguments* truesetAttackedByN01InI=new SetArguments();
	truesetAttackedByN01InI->add_Argument(af.getArgumentByName("n09"));

	ASSERT_EQUALM("setRestrict isn't working",*truesetAttackedByN01InI,*setAttackedByN01InI);
}

void test_getArgumentAttacksInSet_getArgumentAttackersInSet(){
	AF af=AF();
	ASSERTM("file cannot be read",af.readFile("test-input/esempio1.dl"));
	SetArguments argset=SetArguments();
	SetArguments* actual;
	Argument* n=af.getArgumentByName("n01");
	argset.add_Argument(af.getArgumentByName("n01"));
	argset.add_Argument(af.getArgumentByName("n05"));
	argset.add_Argument(af.getArgumentByName("n10"));
	argset.add_Argument(af.getArgumentByName("n11"));
	argset.add_Argument(af.getArgumentByName("n12"));
	argset.add_Argument(af.getArgumentByName("n07"));
	SetArguments trueSet=SetArguments();
	trueSet.add_Argument(af.getArgumentByName("n05"));
	trueSet.add_Argument(af.getArgumentByName("n07"));

	cout << "eseguo " << argset << "->getArgumentAttacksInSet(n01);" << endl;
	actual=argset.getArgumentAttacksInSet(n);
	ASSERT_EQUALM("getArgumentAttacksInSet doesn\'t work correctly",trueSet,*actual);

	actual->remove_All_Arguments();
	trueSet.remove_All_Arguments();
	trueSet.add_Argument(af.getArgumentByName("n01"));

	n=af.getArgumentByName("n07");
	cout << "eseguo" << argset << "->getArgumentAttackersInSet(n07);" << endl;
	actual=argset.getArgumentAttackersInSet(n);
	ASSERT_EQUALM("getArgumentAttackersInSet doesn't work correctly",trueSet,*actual);

}

void testSCC(){
	AF af=AF();
	vector<SetArguments*> scclist=vector<SetArguments*>();
	vector<SetArguments*> truescclist=vector<SetArguments*>();

	if (!af.readFile("test-input/esempio1.dl")){
		ASSERTM("file cannot be read",false);
	}
	SetArguments* a1=new SetArguments();
	a1->add_Argument(af.getArgumentByName("n11"));
	a1->add_Argument(af.getArgumentByName("n10"));
	a1->add_Argument(af.getArgumentByName("n12"));
	SetArguments* a2=new SetArguments();
	a2->add_Argument(af.getArgumentByName("n06"));
	a2->add_Argument(af.getArgumentByName("n07"));
	a2->add_Argument(af.getArgumentByName("n08"));
	a2->add_Argument(af.getArgumentByName("n09"));
	SetArguments* a3=new SetArguments();
	a3->add_Argument(af.getArgumentByName("n14"));
	a3->add_Argument(af.getArgumentByName("n13"));
	SetArguments* a4=new SetArguments();
	a4->add_Argument(af.getArgumentByName("n01"));
	SetArguments* a5=new SetArguments();
	a5->add_Argument(af.getArgumentByName("n05"));
	SetArguments* a6=new SetArguments();
	a6->add_Argument(af.getArgumentByName("n04"));
	SetArguments* a7=new SetArguments();
	a7->add_Argument(af.getArgumentByName("n03"));
	a7->add_Argument(af.getArgumentByName("n02"));

	cout << "costruisco la vera lista scc" << endl;
	truescclist.push_back(a3);
	truescclist.push_back(a6);
	truescclist.push_back(a2);
	truescclist.push_back(a5);
	truescclist.push_back(a7);
	truescclist.push_back(a4);
	truescclist.push_back(a1);

	cout << "eseguo SCC" << endl;
	SCCSEQ::SCC(af.get_arguments(),&scclist);
	cout << "eseguito" << endl;

	bool found;
	ASSERT_EQUALM("SCC set numbers is mismatch!",7,scclist.size());
	for (unsigned int i=0; i<truescclist.size();i++){
		cout << "checking if " << *truescclist[i] << " was in the solution: ";
		found=false;
		for (unsigned int j=0; j<scclist.size();j++){
			if (*truescclist[i]==*scclist[j]){
				found=true;
				cout << "found!";
				break;
			}
		}
		cout << endl;
		ASSERT_EQUALM("manca un SCC!",true,found);
	}
}

void testSynchWithSet(){
	AF framework=AF();
	SetArguments e=SetArguments();
	SetArguments i=SetArguments();
	SetArguments copy=SetArguments();

	if (!framework.readFile("test-input/esempio1.dl")){
		ASSERTM("file cannot be read",false);
	}
	Grounded::doGrounded(*framework.get_arguments(),*framework.get_arguments(),&e,&i);
	cout << "Insieme norma: "<< e << endl;
	framework.get_arguments()->clone(&copy);
	cout << "Insieme da normalizzare: " << copy << endl;
	copy.synchWithSet(&e);
	cout << "Insieme normalizzato: " << copy << endl;
	ASSERT_EQUALM("SynchWithSet non funziona come dovrebbe",e,copy);
}

void testSetArgumentByNames(){
	AF framework=AF();
	if (!framework.readFile("test-input/esempio1.dl")){
		ASSERTM("file cannot be read",false);
	}

	SetArguments x;
	SetArguments y;

	cout << "creating SetArguments..."<<endl;
	x=SetArguments(framework,(string[]){"n01","n13","n07","n04"},4);
	y=SetArguments();

	cout << "creating second SetArguments..."<<endl;
	cout << "adding first node..."<<endl;
	y.add_Argument(framework.getArgumentByName("n01"));
	cout << "adding second node..."<<endl;
	y.add_Argument(framework.getArgumentByName("n13"));
	cout << "adding third node..."<<endl;
	y.add_Argument(framework.getArgumentByName("n07"));
	cout << "adding fourth node..."<<endl;
	y.add_Argument(framework.getArgumentByName("n04"));

	cout << "X="<<endl;
	x.printGraph();
	cout << "Y="<<endl;
	y.printGraph();

	ASSERT_EQUALM("constructor SetArgument(AF,string[]) is malfunctioning!",y,x);
}

void testGrounded() {

	AF framework=AF();
	SetArguments e=SetArguments();
	SetArguments I=SetArguments();
	SetArguments trueE=SetArguments();
	SetArguments trueI=SetArguments();

	cout << "leggo il file..." <<endl;
	string inputfile = string("test-input/esempio1.dl");
	if (!framework.readFile(inputfile)){
		ASSERTM("file cannot be read", false);
	}
	cout << "file letto"<< endl;

	trueE.add_Argument(framework.getArgumentByName("n01"));
	trueE.add_Argument(framework.getArgumentByName("n03"));
	trueE.add_Argument(framework.getArgumentByName("n06"));

	trueI.add_Argument(framework.getArgumentByName("n09"));
	trueI.add_Argument(framework.getArgumentByName("n10"));
	trueI.add_Argument(framework.getArgumentByName("n11"));
	trueI.add_Argument(framework.getArgumentByName("n12"));
	trueI.add_Argument(framework.getArgumentByName("n13"));
	trueI.add_Argument(framework.getArgumentByName("n14"));

	printf("eseguo grounded...\n");
	Grounded::doGrounded(*framework.get_arguments(),*framework.get_arguments(),&e,&I);
	cout << "E:" <<endl;
	cout << e << endl;
	cout << "I:" <<endl;
	cout << I << endl;
	printf("fatto\n");
	ASSERTM("grounded good",true);
	ASSERT_EQUALM("e != from expected",trueE,e);
	ASSERT_EQUALM("I != from expected",trueI,I);
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;

	s.push_back(CUTE(testGrounded));
	s.push_back(CUTE(testSetArgumentByNames));
	s.push_back(CUTE(testSynchWithSet));
	s.push_back(CUTE(testSCC));
	s.push_back(CUTE(test_getArgumentAttacksInSet_getArgumentAttackersInSet));
	s.push_back(CUTE(testSetRestrict));
	s.push_back(CUTE(testAF_get_arguments_copy));
	s.push_back(CUTE(testTillSCC));
	s.push_back(CUTE(testSEQ));
	s.push_back(CUTE(test_getAllAttackers));
	s.push_back(CUTE(test_getAllAttacks));
	s.push_back(CUTE(test_getAllAttackersInSet));
	s.push_back(CUTE(test_getAllAttacksInSet));
	s.push_back(CUTE(test_getSubsetAttackedBySet));
	s.push_back(CUTE(test_getSubsetAttacksSet));
	s.push_back(CUTE(test_linkMacroGraph_lookmanually));
	s.push_back(CUTE(test_toposort));
	s.push_back(CUTE(test_tillSEQ));
	s.push_back(CUTE(test_constructorSetArgumentsVectorEmpty));
	s.push_back(CUTE(test_SetArgumentsVector_pushback));
	s.push_back(CUTE(test_SetArgumentsVector_at));
	s.push_back(CUTE(test_SetArgumentsVector_plus));
	s.push_back(CUTE(test_SetArgumentsVector_find));
	s.push_back(CUTE(test_SetArgumentsVector_addSetArgumentsToAll));
	s.push_back(CUTE(test_SetArgumentsVector_operator_equal));
	s.push_back(CUTE(test_Zanella1));
	s.push_back(CUTE(test_Zanella2));
	s.push_back(CUTE(test_Zanella3));
	s.push_back(CUTE(test_Aspartix1));
	s.push_back(CUTE(test_Aspartix2));
	s.push_back(CUTE(test_Aspartix3));
	s.push_back(CUTE(test_ZanellaImproved1));
	s.push_back(CUTE(test_ZanellaImproved2));
	s.push_back(CUTE(test_ZanellaImproved3));
	s.push_back(CUTE(test_AspartixImproved1));
	s.push_back(CUTE(test_AspartixImproved2));
	s.push_back(CUTE(test_AspartixImproved3));
	//s.push_back(CUTE());
	//s.push_back(CUTE(testPrefAlgorithm));

	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



