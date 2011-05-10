
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2008, Adam Kubach
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////

#include "Minerva/Core/Data/LineStyle.h"

#include "Usul/Factory/RegisterCreator.h"

using namespace Minerva::Core::Data;

USUL_FACTORY_REGISTER_CREATOR ( LineStyle );

///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

LineStyle::LineStyle() : BaseClass(),
	_width ( 1.0f )
{
  this->_addMember ( "width", _width );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Create.
//
///////////////////////////////////////////////////////////////////////////////

LineStyle* LineStyle::create ( const Color& color, float width )
{
  LineStyle::RefPtr lineStyle ( new LineStyle );
  lineStyle->color ( color );
  lineStyle->width ( width );

  return lineStyle.release();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

LineStyle::~LineStyle()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the width.
//
///////////////////////////////////////////////////////////////////////////////

void LineStyle::width ( float w )
{
  Guard guard ( this->mutex() );
  _width = w;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the width.
//
///////////////////////////////////////////////////////////////////////////////

float LineStyle::width() const
{
  Guard guard ( this->mutex() );
  return _width;
}