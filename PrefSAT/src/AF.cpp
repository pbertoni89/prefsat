/**
 * @file 		AF.cpp
 * @class 		AF
 * @brief 		Class encompassing an Argumentation Framework
 * @author 		Mauro Vallati <m.vallati@hud.ac.uk>
 * @copyright	GNU Public License v2
 */


#include "AF.h"

/**
 * @brief 	Simple constructor
 */
AF::AF()
{
	//FIXME valgrind here reports a memory leak of 104 bytes per call. Number of calls: 2
	this->arguments = new SetArguments();
	//this->raw_attacks = map<int, int >();
	//this->attacks = map<Argument *, SetArguments *>();
	//this->attackers = map<Argument *, SetArguments *>();
}


AF::~AF()
{
	// TODO bisogna deallocare il setArguments principale
}

/**
 * @brief 		Method for parsing a ASPARTIX compliant file
 * @details		It uses part of the code from Samer Nofal's, University of Liverpool
 * @param[in] file A string representing the (relative/absolute) path to the ASPARTIX compliant file
 * @retval bool It returns `True` if it can correctly parse the file, `False` otherwise
 */
bool AF::readFile(string file)
{
	Argument* newarg;
	string inLine;
	ifstream infile;
	infile.open(file.c_str());
	if (!infile.good())
		return false;
	infile >> inLine;

	while (inLine.find("arg") != string::npos && !infile.eof())
	{
		newarg=new Argument(
				inLine.substr(4, inLine.find_last_of(")") - 4),
				this->numArgs(),
				this
				);
		this->arguments->add_Argument(newarg);

		infile >> inLine;
	}

	while (!infile.eof())
	{
		if (inLine.find("att") != string::npos)
		{
			Argument *source = this->getArgumentByName(
					(inLine.substr(4,
							inLine.find_last_of(",") - 4)));
			Argument *target = this->getArgumentByName(
					(inLine.substr(inLine.find_last_of(",") + 1,
							inLine.find_last_of(")")
									- inLine.find_last_of(",")
									- 1)));

			source->add_attacks(target);
			target->add_attackers(source);
//			this->raw_attacks.push_back(
//					pair<int, int>(
//							this->argNameToCode(
//									(inLine.substr(4,
//											inLine.find_last_of(",") - 4))),
//							this->argNameToCode(
//									(inLine.substr(inLine.find_last_of(",") + 1,
//											inLine.find_last_of(")")
//													- inLine.find_last_of(",")
//													- 1)))));
		}
		infile >> inLine;
	}
	infile.close();
	return true;
}

/**
 * @brief		This method returns the pointer to the Argument whose name is given as parameter
 * @param[in] name	 The name of the argument
 * @retval Argument* The pointer to the Argument object, or NULL if not found
 */
Argument *AF::getArgumentByName(string name)
{
	return this->arguments->getArgumentByName(name);
}

/**
 * @brief 	Returns the number of arguments
 * @retval int
 */
int AF::numArgs()
{
	return this->arguments->cardinality();
}


/**
 * @brief		This method returns the pointer to the Argument whose identification number is given as parameter
 * @param[in] num	 The name of the argument
 * @retval Argument* The pointer to the Argument object, or NULL if not found
 */
Argument *AF::getArgumentByNumber(int num)
{
	return this->arguments->getArgumentByNumber(num);
}

/**
 * @brief 	Begin of the iterator for the set of arguments
 * @retval SetArgumentsIterator An iterator pointing at the first of the elements of the set of arguments
 */
SetArgumentsIterator AF::begin()
{
	return this->arguments->begin();
}

/**
 * @brief 	End of the iterator for the set of arguments
 * @retval SetArgumentsIterator An iterator pointing at the last of the elements of the set of arguments
 */
SetArgumentsIterator AF::end()
{
	return this->arguments->end();
}

/**@brief Return a pointer to the set of arguments
 *
 * this funtion return a copy editable of the AF set of Argument.
 *
 * \post
 *  \li a new instance of SetArguments is created in the heap and must be free manually
 *
 * @return a changable version of the graph in AF class.
 */
SetArguments* AF::get_arguments_copy(){
	SetArguments* result=new SetArguments();
	this->get_arguments()->clone(result);
	return result;
}

/**
 * @brief	Returns a pointer to the set of arguments
 *
 * The function return the very structure used by the AF class as a constant: this mean that
 * changes to that SetArgument <b>may</b> change the AF instance itself provoking unexpected behaviour.
 * Use this function <b>carefully</b>.
 * If you want a SetArguments that can be changed safely (aka a simple copy of the set of AF, not the real handle)
 * you can use the function get_arguments_copy() or use the following code:
 * \code
 * 	SetArguments* clone_instance=new SetArguments();
 * 	af_instance->get_arguments()->clone(clone_instance);
 * \endcode
 *
 * For further information about what "const" reserved word mean at the end of a function, you can
 * read the link http://duramecho.com/ComputerInformation/WhyHowCppConst.html
 *
 * @return SetArguments* the very set used by the AF instance itself, output as a constant
 */
SetArguments *AF::get_arguments() const
{
	return this->arguments;
}
