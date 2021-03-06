
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Perry L Miller IV
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Timer server.
//
///////////////////////////////////////////////////////////////////////////////

#include "TimerFactory.h"

#include "Usul/Functions/SafeCall.h"
#include "Usul/Threads/Named.h"

#include "boost/bind.hpp"

USUL_IMPLEMENT_IUNKNOWN_MEMBERS ( TimerServer, TimerServer::BaseClass );


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

TimerServer::TimerServer() : BaseClass()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor. Qt deletes child widgets.
//
///////////////////////////////////////////////////////////////////////////////

TimerServer::~TimerServer()
{
  Usul::Functions::safeCall ( boost::bind ( &TimerServer::_destroy, this ), "1498464868" );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor contents.
//
///////////////////////////////////////////////////////////////////////////////

void TimerServer::_destroy()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Query for the interface.
//
///////////////////////////////////////////////////////////////////////////////

Usul::Interfaces::IUnknown *TimerServer::queryInterface ( unsigned long iid )
{
  // No need to guard, should be re-entrant.
  
  switch ( iid )
  {
    case Usul::Interfaces::IUnknown::IID:
    case Minerva::Common::ITimerFactory::IID:
      return static_cast < Minerva::Common::ITimerFactory * > ( this );
    default:
      return 0x0;
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Create the timer.
//
///////////////////////////////////////////////////////////////////////////////

Minerva::Common::ITimer::RefPtr TimerServer::createTimer ( unsigned int milliseconds, ITimer::TimerCallback callback, bool singleShot )
{
  Timer::RefPtr timer ( new Timer ( milliseconds, callback, singleShot ) );
  return Minerva::Common::ITimer::RefPtr ( timer );
}
