
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2008, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Author: Adam Kubach
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MINERVA_INTERFACES_ELEVATION_DATABASE_H__
#define __MINERVA_INTERFACES_ELEVATION_DATABASE_H__

#include "Usul/Interfaces/IUnknown.h"

namespace Minerva {
namespace Common {


struct IElevationDatabase : public Usul::Interfaces::IUnknown
{
  /// Smart-pointer definitions.
  USUL_DECLARE_QUERY_POINTERS ( IElevationDatabase );
  
  /// Id for this interface.
  enum { IID = 1417816400u };
  
  // Get the elevation at a lat, lon.
  virtual double             elevationAtLatLong ( double lat, double lon ) const = 0;
};


}
}

#endif // __MINERVA_INTERFACES_ELEVATION_DATABASE_H__
