
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2008, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Adam Kubach
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MINERVA_CORE_DATA_NETWORK_LINK_H__
#define __MINERVA_CORE_DATA_NETWORK_LINK_H__

#include "Minerva/Core/Data/Feature.h"
#include "Minerva/Core/Data/Link.h"

namespace Minerva {
namespace Core {
namespace Data {
  

class MINERVA_EXPORT NetworkLink : public Minerva::Core::Data::Feature
{
public:
  // Typedefs.
  typedef Feature BaseClass;
  typedef Minerva::Core::Data::Link Link;
  
  // Declare pointers.
  USUL_DECLARE_REF_POINTERS ( NetworkLink );
  
  NetworkLink();
  
  virtual Feature* clone() const;

  /// Get/Set the link.
  Link*       link() const;
  void        link ( Link* );
  
protected:
  virtual ~NetworkLink();
  
private:
  Link::RefPtr _link;
};


}
}
}


#endif // __MINERVA_CORE_DATA_NETWORK_LINK_H__
