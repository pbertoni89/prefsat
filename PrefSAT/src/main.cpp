#include "PrefAlgorithm.h"

void uncorrectSintaxExit() {
	cout << "SINTAX: AlgoritmiStruttureDati GRAPH_PATH [--improved]" << endl <<
			"Program exited." << endl;
	exit(-1);
}

void printCalls() {
	cout << "During the execution, there has been " << PrefAlgorithm::getCalls(PREF_CALL) << " calls to Pref,"
													  << PrefAlgorithm::getCalls(GROUNDED_CALL) << " to Grounded, "
													  << PrefAlgorithm::getCalls(BOUNDCOND_CALL) << " to Boundcond and "
													  << PrefAlgorithm::getCalls(SATPREF_CALL) << " to SATPref." << endl;
	cout << "Pref correctly terminated. Goodbye!" << endl << endl;
}

int main(int argc, char *argv[])
{
	if(argc<2 or argc>3)
		uncorrectSintaxExit();

	bool improved = false;
	if (argc==3) {
		if (strcmp(argv[2], "--improved")==0)
			improved = true;
		else
			uncorrectSintaxExit();
	}

	#ifdef CHRONOPREF
		auto t1 = std::chrono::high_resolution_clock::now();
	#endif

	PrefAlgorithm* solver = new PrefAlgorithm(argv[1]);
	SetArgumentsVector solution = solver->handlePref(improved);

	#ifdef CHRONOPREF
		auto t2 = std::chrono::high_resolution_clock::now();
		auto msecs = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
		cout << "\n\nFinal solution obtained after " << msecs << " milliseconds:\n\n" << solution << endl << endl;
	#else
		cout << "\n\nFinal solution:" << solution << endl << endl;
	#endif

	printCalls();

	//deallocates solution
	//delete &solution;

	#ifdef CHRONOPREF
		cout << "(You can now grep elapsed milliseconds with \"echo $?\")" <<endl;
		return msecs;
	#else
		return 0;
	#endif
}
