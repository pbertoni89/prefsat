/**
 * @file 		semopt.h
 * @author 		Federico Cerutti <f.cerutti@abdn.ac.uk>
 * @copyright	GNU Public License v3
 */

#ifndef _SEMOPT_H
#define	_SEMOPT_H

#include <cmath>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <vector>
#include <time.h>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <cassert>
#include <set>

#define DIMBUFFER 100000

using namespace std;

#define HG(a) static const char *hgrev = a;

#define _PUBLIC_RELEASE "0.2alpha5-SCC"
#ifndef _PUBLIC_RELEASE
#include "hgversion.h"
#else
#define HG(a) static const char *hgrev = a;
HG("Version: "_PUBLIC_RELEASE);
#endif

#include "AF.h"
#include "OrClause.h"
#include "SATFormulae.h"
#include "SetArguments.h"
#include "Labelling.h"
#include "Argument.h"
#include "Preferred.h"

extern bool debug;
extern bool externalsat;
extern string satsolver;
extern int labellingconditions;
extern string inputfile;
extern string semantics;

extern bool manualopt;
extern time_t start;

bool parse_solution_aspartix(set<set<string> > *, const char *);

#endif	/* _SEMOPT_H */

int precosat_lib(stringstream *the_cnf, int num_var, int num_cl, vector<int> *result);
