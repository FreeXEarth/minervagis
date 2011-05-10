
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2008, Adam Kubach
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////

#include "Minerva/Core/Data/PolyStyle.h"

#include "Usul/Factory/RegisterCreator.h"

using namespace Minerva::Core::Data;

USUL_FACTORY_REGISTER_CREATOR ( PolyStyle );

///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

PolyStyle::PolyStyle() : BaseClass(),
	_fill ( true ),
	_outline ( true )
{
  // Default color.
  this->color ( Usul::Math::Vec4f ( 0.8f, 0.8f, 0.8f, 1.0f ) );

  this->_addMember ( "fill", _fill );
  this->_addMember ( "outline", _outline );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

PolyStyle::~PolyStyle()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the fill flag.
//
///////////////////////////////////////////////////////////////////////////////

void PolyStyle::fill ( bool b )
{
  Guard guard ( this->mutex() );
  _fill = b;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the fill flag.
//
///////////////////////////////////////////////////////////////////////////////

bool PolyStyle::fill() const
{
  Guard guard ( this->mutex() );
  return _fill;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the outline flag.
//
///////////////////////////////////////////////////////////////////////////////

void PolyStyle::outline ( bool b )
{
  Guard guard ( this->mutex() );
  _outline = b;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the outline flag.
//
///////////////////////////////////////////////////////////////////////////////

bool PolyStyle::outline() const
{
  Guard guard ( this->mutex() );
  return _outline;
}