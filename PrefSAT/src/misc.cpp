/**
 * @file 		misc.cpp
 * @brief 		Miscellanea functions
 * @author 		Federico Cerutti <f.cerutti@abdn.ac.uk>
 * @copyright	GNU Public License v2
 */

#include "semopt.h"

/**
 * @brief 				Function checking the existence of a file
 * @param[in] filename	Pointer to a `const char` containing the name of the file
 * @retval bool
 */
bool fexists(const char *filename)
{
	if (ifstream(filename))
		return true;
	else
		return false;
}

bool parse_solution_aspartix(set<set<string> > *preferred, const char *file)
{
	ifstream infile;
	infile.open(file);
	if (infile.good() == false)
		return false;

	string inLine;
	while (getline(infile, inLine))
	{
		int start = 0;
		int pos = 0;
		set<string> sol_asp = set<string>();

		while (((int) (pos = inLine.find("in(", start))) != ((int) string::npos))
		{
			string arg = inLine.substr(pos + 3,
					inLine.find(")", pos + 3) - (pos + 3));
			sol_asp.insert(arg);
			start = pos + 4;
		}
		(*preferred).insert(sol_asp);
	}
	set<set<string> >::iterator it;
	for (it = preferred->begin(); it != preferred->end(); it++)
	{
		set<string>::iterator inner;
		cout << "{";
		for (inner = (*it).begin(); inner != (*it).end(); inner++)
		{
			cout << (*inner) << " ";
		}
		cout << "}" << endl;
	}
	return true;
}
