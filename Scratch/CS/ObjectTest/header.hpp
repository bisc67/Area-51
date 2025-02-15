///////////////////////////////////////////////////////////////////////////////
//
//	header.hpp
//
//
//		header.hpp is intended to be used as a precompiled header or, if
//		support for precompiled headers does not exist, just a preinclude file
//		that contains all declarations, header files, and cosntants that we 
//		think the majority of the files in the project might use.
//
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
//	Common defines
//
///////////////////////////////////////////////////////////////////////////////
#define bit(x)  (1 << (x))



///////////////////////////////////////////////////////////////////////////////
//
//	Universal Headers
//
///////////////////////////////////////////////////////////////////////////////

extern "C" 
{
    #include <lua.h>
}


#include "x_types.hpp"
#include "X_debug.hpp"