
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2006, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Adam Kubach
//
///////////////////////////////////////////////////////////////////////////////

#include "Minerva/Core/Data/MultiGeometry.h"

#include "osg/Group"

using namespace Minerva::Core::Data;


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

MultiGeometry::MultiGeometry() : BaseClass(),
  _geometries()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

MultiGeometry::~MultiGeometry()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Is this geometry transparent?
//
///////////////////////////////////////////////////////////////////////////////

bool MultiGeometry::isSemiTransparent() const
{
  return false;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Add a geometry.
//
///////////////////////////////////////////////////////////////////////////////

void MultiGeometry::addGeometry ( Geometry::RefPtr geometry )
{
  if ( true == geometry.valid() )
  {
    Guard guard ( this );
    _geometries.push_back ( geometry );

    Extents extents ( this->extents() );
    extents.expand ( geometry->extents() );
    this->extents ( extents );

    this->dirty ( true );
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the geometry.
//
///////////////////////////////////////////////////////////////////////////////

MultiGeometry::Geometries MultiGeometry::geometries() const
{
  Guard guard ( this );
  return _geometries;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Reserve geometry size.
//
///////////////////////////////////////////////////////////////////////////////

void MultiGeometry::reserveGeometry ( unsigned int size )
{
  Guard guard ( this );
  _geometries.reserve ( size );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Build the scene branch for the data object.
//
///////////////////////////////////////////////////////////////////////////////

osg::Node* MultiGeometry::_buildScene ( Style::RefPtr style, IPlanetCoordinates *planet, IElevationDatabase* elevation )
{
  Extents extents;

  osg::ref_ptr<osg::Group> group ( new osg::Group );
  Geometries geometries ( this->geometries() );
  for ( Geometries::iterator iter = geometries.begin(); iter != geometries.end(); ++iter )
  {
    Geometry::RefPtr geometry ( *iter );
    if ( geometry.valid() )
    {
      // Make sure the altitude modes match.
      geometry->altitudeMode ( this->altitudeMode() );

      group->addChild ( geometry->buildScene ( style, planet, elevation ) );
      extents.expand ( geometry->extents() );
    }
  }

  // Set the new extents.
  this->extents ( extents );

  return group.release();
}