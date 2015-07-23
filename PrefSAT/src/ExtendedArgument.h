
#ifndef EXTENDEDARGUMENT_H_
#define EXTENDEDARGUMENT_H_

#include "Argument.h"
using namespace std;

class ExtendedArgument{

public:
	/**@brief represents the default lowlink value field.
	 * Value that is associated to lowlink field when the node has not
	 * been explored yet. This value is set to the lowlink field at class
	 * construction time.
	 */
	static const int LOWLINKDEFAULT=-1;
	/**@brief represents the default index value field.
	 * Value that is associated to index field when the node has not
	 * been explored yet. This value is set to the index field at class
	 * construction time.
	 */
	static const int INDEXDEFAULT=-1;
	int index;
	int lowlink;
	ExtendedArgument();
	virtual ~ExtendedArgument();
};

ostream& operator<<(ostream& , const ExtendedArgument& );

#endif /* EXTENDEDARGUMENT_H_ */
