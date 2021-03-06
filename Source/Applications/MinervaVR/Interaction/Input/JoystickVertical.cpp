
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2002, John K. Grant and Perry L. Miller IV.
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Functor class for vertical joystick input.
//
///////////////////////////////////////////////////////////////////////////////

#include "Interaction/Input/JoystickVertical.h"


using namespace Usul::Functors::Interaction::Input;


///////////////////////////////////////////////////////////////////////////////
//
//  Default constructor.
//
///////////////////////////////////////////////////////////////////////////////

JoystickVertical::JoystickVertical ( Unknown *caller, const std::string &name ) : 
  BaseClass ( caller, name ),
  _j ( caller )
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Copy constructor.
//
///////////////////////////////////////////////////////////////////////////////

JoystickVertical::JoystickVertical ( const JoystickVertical &j ) : BaseClass ( j ),
  _j ( j._j )
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

JoystickVertical::~JoystickVertical()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the vertical analog input.
//
///////////////////////////////////////////////////////////////////////////////

void JoystickVertical::operator()()
{
  Guard guard ( this->mutex() );
  _value = ( ( _j.valid() ) ? _j->joystickVertical() : _value );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the caller.
//
///////////////////////////////////////////////////////////////////////////////

void JoystickVertical::caller ( Unknown* caller )
{
  // Call the base class.
  BaseClass::caller ( caller );

  // Set our internal query pointer to caller.
  Guard guard ( this->mutex() );
  _j = caller;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Clone.
//
///////////////////////////////////////////////////////////////////////////////

Usul::Functors::Interaction::Common::BaseFunctor* JoystickVertical::clone()
{
  return new JoystickVertical ( *this );
}
