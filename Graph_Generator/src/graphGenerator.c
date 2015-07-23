#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <strings.h>

/**The label identifiyng every nodes. If this macro is set to "node" the nodes will be called:
 * \li node1
 * \li node2
 * \li ...
 * \li node 15
 *
 */
#define NODE_LABEL "n"

/**@brief get random number between 1 (included) and maxnumbe (included)
 *
 * @param maxnumber
 * @return
 */
int getRandomNumber(int maxnumber){
#ifdef __GRAPHGENERATOR_RANDOMIZE__
#define __GRAPHGENERATOR_RANDOMIZE__
	srand(time(NULL));
#endif
	return 1+(rand()%maxnumber);
}

/**@brief Returns a number between 1 (included) and maxnumber (included) except the excluded one
 *
 * @param excluded
 * @param maxnumber
 * @return
 */
int getRandomNumberExceptThisOne(int excluded,int maxnumber){
	int result;
	do{
		result=getRandomNumber(maxnumber);
	}while (result==excluded);
	return result;
}

/**
 *
 * @param argc
 * @param args
 * @return
 */
int main(int argc,const char** args){
	if (argc!=5){
		fprintf(stderr,"Number of params mismatch! Require exactly 4!\n"
				"param 1: number of nodes in the graph;\n"
				"param 2: maximus arc outgoing from a node (it will be clipped between 0 and param1-1);\n"
				"param 3: name of the ouput dot file (extension excluded!)\n"
				"param 4: \"graph\" if you want to generate the graph; \"dot\" if you want only a dot file; \"nograph\" if you don't want it\n"
		);
		return EXIT_FAILURE;
	}
	//represents the total number of nodes in the graph
	int nodeNumber = atoi(args[1]);
	//represents the maximum number of arcs out going from a single node
	int branchingAverage = atoi(args[2]);
	if(branchingAverage<0)
		branchingAverage = 0;
	else if(branchingAverage >= nodeNumber)
		branchingAverage = nodeNumber-1;
	//represents the name of the file dot (extension EXCLUDED!). The name can be absolute or relative
	const char* outputname = args[3];
	//2 if the dot graph should be generated; 1 if only the dot file should be generated; 0 otherwise; The default value is 0
	short graph;
	if (strcmp(args[4],"graph")==0){
		graph =  2;
	}else if (strcmp(args[4],"dot")==0){
		graph = 1;
	}else if (strcmp(args[4],"nograph")==0){
			graph = 0;
	}else {
		fprintf(stderr, "arguments #4 has a strange value. Only \"graph\", \"dot\" or \"nograph\" accepted. I will not generate the graph!\n");
		graph = 0;
	}
	//represents the node which is computated in a certain cycle of the for loop
	int i;
	//represents the number of outgoing arc that the currentnode has
	int currentNodeBranching;
	//represents the terminal node of a "in computing" arc
	int j;
	//represents the ending node of an arc
	int endNode;

	char dlname[100];
	char dotname[100];
	char dotcommand[100];
	char rmcommand[100];
	//represents the pointer to the dot file
	FILE* dotfile;

	if(graph) {
		sprintf(dotname,"%s.dot",outputname);
		sprintf(dotcommand,"dot -Tjpg %s.dot -o %s.jpg",outputname,outputname);
		sprintf(rmcommand,"rm %s.dot",outputname);
		dotfile = fopen(dotname,"w");
		if (dotfile==NULL){
			fprintf(stderr,"Cannot create the file %s! Who knows why!\n",dotname);
			return EXIT_FAILURE;
		}
		fprintf(dotfile, "digraph \"%s\" {\n", outputname);
	}

	sprintf(dlname,"%s.dl",outputname);
	//represents the pointer to the dl file
	FILE* dlfile=fopen(dlname,"w");
	if (dlfile==NULL){
		fprintf(stderr, "Cannot create the file %s! Who knows why!\n",dlname);
		return EXIT_FAILURE;
	}

	//generating the nodes...
	for (i=1; i<=nodeNumber; i++){
		if(graph)
			fprintf(dotfile,"%s%d;\n", NODE_LABEL, i);
		fprintf(dlfile,"arg(%s%d).\n", NODE_LABEL, i);
	}
	//generating the arcs...
	printf("Generating...    ");
	for (i=1; i<=nodeNumber; i++){
		if(!((i*10)%nodeNumber))
			printf(" \b\b\b\b%d0%%", (i*10)/nodeNumber);
		currentNodeBranching = getRandomNumber(branchingAverage);
		for (j=0; j<currentNodeBranching; j++){
			endNode = getRandomNumberExceptThisOne(i, nodeNumber);
			if(graph)
			fprintf(dotfile, "%s%d -> %s%d;\n", NODE_LABEL, i, NODE_LABEL, endNode);
			fprintf(dlfile, "att(%s%d,%s%d).\n", NODE_LABEL, i, NODE_LABEL, endNode);
		}
	}
	printf("\n");
	fclose(dlfile);

	if (graph){
		fprintf(dotfile, "}\n");
		fclose(dotfile);
		//generating the jpg image...
		if(graph>1) {
			if (system(dotcommand)!=0)
				fprintf(stderr, "cannot compile %s with dot compiler! Maybe the dot compiler is not present on this system!\n", dotname);
			if (system(rmcommand)!=0)
				fprintf(stderr, "cannot remove %s with rm command! Are you sure you are on linux? :D\n", dotname);
		}
	}
	return EXIT_SUCCESS;
}
