
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2004, Perry L. Miller IV
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Convenient macro that inserts the filename and line number.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GENERIC_NURBS_LIBRARY_MACRO_ERROR_CHECK_H_
#define _GENERIC_NURBS_LIBRARY_MACRO_ERROR_CHECK_H_


#ifndef GN_ERROR_CHECK
#define GN_ERROR_CHECK(state) ErrorCheckerType ( __FILE__, __LINE__, state, #state );
#endif


#endif // _GENERIC_NURBS_LIBRARY_CONFIGURATIONS_H_
