
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2008, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Adam Kubach
//
///////////////////////////////////////////////////////////////////////////////

#include "Minerva/Core/Data/LookAt.h"

using namespace Minerva::Core::Data;


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

LookAt::LookAt() : 
  BaseClass(),
  _longitude ( 0.0 ),
  _latitude ( 0.0 ),
  _altitude ( 0.0 ),
  _range ( 0.0 ),
  _heading ( 0.0 )
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

LookAt::~LookAt()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the longitude.
//
///////////////////////////////////////////////////////////////////////////////

void LookAt::longitude ( double longitude )
{
  Guard guard ( this->mutex() );
  _longitude = longitude;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the longitude.
//
///////////////////////////////////////////////////////////////////////////////

double LookAt::longitude() const
{
  Guard guard ( this->mutex() );
  return _longitude;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the latitude.
//
///////////////////////////////////////////////////////////////////////////////

void LookAt::latitude ( double latitude )
{
  Guard guard ( this->mutex() );
  _latitude = latitude;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the latitude.
//
///////////////////////////////////////////////////////////////////////////////

double LookAt::latitude() const
{
  Guard guard ( this->mutex() );
  return _latitude;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the altitude.
//
///////////////////////////////////////////////////////////////////////////////

void LookAt::altitude ( double altitude )
{
  Guard guard ( this->mutex() );
  _altitude = altitude;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the altitude.
//
///////////////////////////////////////////////////////////////////////////////

double LookAt::altitude() const
{
  Guard guard ( this->mutex() );
  return _altitude;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the range.
//
///////////////////////////////////////////////////////////////////////////////

void LookAt::range ( double range )
{
  Guard guard ( this->mutex() );
  _range = range;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the range.
//
///////////////////////////////////////////////////////////////////////////////

double LookAt::range() const
{
  Guard guard ( this->mutex() );
  return _range;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the heading.
//
///////////////////////////////////////////////////////////////////////////////

void LookAt::heading ( double heading )
{
  Guard guard ( this->mutex() );
  _heading = heading;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the heading.
//
///////////////////////////////////////////////////////////////////////////////

double LookAt::heading() const
{
  Guard guard ( this->mutex() );
  return _heading;
}
