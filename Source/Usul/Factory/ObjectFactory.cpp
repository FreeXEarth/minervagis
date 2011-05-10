
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2002, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Author: Perry L Miller IV
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Factory class.
//
///////////////////////////////////////////////////////////////////////////////

#include "Usul/Factory/ObjectFactory.h"
#include "Usul/Base/Referenced.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Singelton instance.
//
///////////////////////////////////////////////////////////////////////////////

namespace Usul
{
  namespace Factory
  {
    USUL_INSTANTIATE_SINGLETON ( ObjectFactory );
  }
}