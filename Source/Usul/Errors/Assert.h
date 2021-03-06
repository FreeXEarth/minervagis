
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2002, Perry L. Miller IV
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Defines assert.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_ASSERT_H_
#define _USUL_ASSERT_H_


namespace Usul {
namespace Errors {


///////////////////////////////////////////////////////////////////////////////
//
//  Function to handle assert in debug.
//
///////////////////////////////////////////////////////////////////////////////

void _assert_debug ( bool state, const char *exp, const char *file, int line );


///////////////////////////////////////////////////////////////////////////////
//
//  Function to handle assert in release.
//
///////////////////////////////////////////////////////////////////////////////

inline void _assert_release ( bool state, const char *, const char *, int )
{
  // Banking on this being compiled away.
}


} // namespace Errors
} // namespace Usul


///////////////////////////////////////////////////////////////////////////////
//
//  Macros for easy use of assert.
//
///////////////////////////////////////////////////////////////////////////////

#ifdef _MSC_VER
# ifdef __CLR_VER
#  define USUL_ASSERT System::Diagnostics::Debug::Assert
# else
#  include <crtdbg.h>
#  define USUL_ASSERT _ASSERT
# endif
#else
# ifdef assert
#  undef assert
# endif
# ifdef _DEBUG
#  define assert(exp) Usul::Errors::_assert_debug ( exp, #exp, __FILE__, __LINE__ )
# else
#  define assert(exp) Usul::Errors::_assert_release ( exp, #exp, __FILE__, __LINE__ )
# endif
# define USUL_ASSERT assert
#endif

#endif // _USUL_ASSERT_H_
