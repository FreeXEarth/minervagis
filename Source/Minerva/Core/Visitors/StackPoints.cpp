
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2008, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Adam Kubach
//
///////////////////////////////////////////////////////////////////////////////

#include "Minerva/Core/Visitors/StackPoints.h"
#include "Minerva/Core/Data/DataObject.h"
#include "Minerva/Core/Data/Container.h"
#include "Minerva/Core/Data/Point.h"

using namespace Minerva::Core::Visitors;

///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

StackPoints::StackPoints( double multiplier ) : 
  BaseClass(),
  _counts( LessVector ( EqualPredicate() ) ),
  _multiplier ( multiplier )
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

StackPoints::~StackPoints()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Visit a point.
//
///////////////////////////////////////////////////////////////////////////////

void StackPoints::visit ( Minerva::Core::Data::DataObject &dataObject )
{
  typedef Minerva::Core::Data::Point Point;
  typedef Minerva::Core::Data::Geometry Geometry;
  Geometry::RefPtr geometry ( dataObject.geometry() );

  {
    if ( Point* point = dynamic_cast<Point*> ( geometry.get() ) )
    {
      Usul::Math::Vec3d p ( point->point() );

      const unsigned int multiplier ( 100000 );
      Usul::Math::Vec3ui center ( static_cast<unsigned int> ( p[0] * multiplier ),
                                  static_cast<unsigned int> ( p[1] * multiplier ),
                                  /*static_cast<unsigned int> ( p[2] * multiplier )*/ 0 );

      Counts::iterator countIter = _counts.find ( center );
      if ( _counts.end() == countIter )
      {
        _counts[center] = 1;
      }
      else
      {
        // Make sure it's using the right altitude mode.
        point->altitudeMode ( Minerva::Core::Data::ALTITUDE_MODE_RELATIVE_TO_GROUND );

        unsigned int count ( countIter->second );

        float size ( 5.0 );
        if ( dataObject.style() && dataObject.style()->pointstyle() )
        {
          size = dataObject.style()->pointstyle()->size();
        }

        Usul::Math::Vec3d location ( point->point() );
        const double distance ( count * _multiplier * size );
        point->point ( Usul::Math::Vec3d ( location[0], location[1], distance ) );
        dataObject.dirty ( true );

        countIter->second = count + 1;
      }
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Visit a point layer.
//
///////////////////////////////////////////////////////////////////////////////

void StackPoints::visit ( Minerva::Core::Data::Container &layer )
{
  if ( layer.visibility() )
  {
    layer.traverse ( *this );
    layer.dirtyScene ( true );
  }
}
