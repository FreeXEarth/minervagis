
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2002, Perry L. Miller IV
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Job class.
//
///////////////////////////////////////////////////////////////////////////////

#include "Usul/Jobs/Job.h"
#include "Usul/Functions/SafeCall.h"
#include "Usul/Scope/Caller.h"
#include "Usul/Strings/Format.h"
#include "Usul/System/Sleep.h"
#include "Usul/Threads/ThreadId.h"

#include "boost/bind.hpp"

#include <stdexcept>

using namespace Usul::Jobs;

USUL_IMPLEMENT_IUNKNOWN_MEMBERS ( Job, Job::BaseClass );


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

Job::Job() : BaseClass(),
  _id          ( 0 ),
  _done        ( false ),
  _canceled    ( false ),
  _priority    ( 0 )
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor
//
///////////////////////////////////////////////////////////////////////////////

Job::~Job()
{
  Usul::Functions::safeCall ( boost::bind ( &Job::_destroy, this ), "3574964895" );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destroy
//
///////////////////////////////////////////////////////////////////////////////

void Job::_destroy()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Query for the interface.
//
///////////////////////////////////////////////////////////////////////////////

Usul::Interfaces::IUnknown *Job::queryInterface ( unsigned long iid )
{
  switch ( iid )
  {
  case Usul::Interfaces::IUnknown::IID:
  case Usul::Interfaces::ICancel::IID:
    return static_cast < Usul::Interfaces::ICancel * > ( this );
  case Usul::Interfaces::ICanceledStateGet::IID:
    return static_cast < Usul::Interfaces::ICanceledStateGet * > ( this );
  default:
    return 0x0;
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Helper class to set the done flag.
//
///////////////////////////////////////////////////////////////////////////////

namespace Usul
{
  namespace Jobs
  {
    namespace Helper
    {
      class ScopedDone
      {
      public:
        ScopedDone ( Job &job, bool done ) : _job ( job ), _done ( done )
        {
        }
        ~ScopedDone()
        {
          _job._setDone ( _done );
        }
      private:
        Job &_job;
        bool _done;
      };
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Called when the thread is cancelled.
//
///////////////////////////////////////////////////////////////////////////////

void Job::_threadCancelled()
{
  ScopedDone done ( *this, true );
  this->_cancelled();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Called when the job is cancelled.
//
///////////////////////////////////////////////////////////////////////////////

void Job::_cancelled()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Called when the thread encounters an error.
//
///////////////////////////////////////////////////////////////////////////////

void Job::_threadError()
{
  ScopedDone done ( *this, true );
  this->_error();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Called when the job encounters an error.
//
///////////////////////////////////////////////////////////////////////////////

void Job::_error()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Called when the thread finishes normally.
//
///////////////////////////////////////////////////////////////////////////////

void Job::_threadFinished()
{

  // Declare up here.
  ScopedDone done ( *this, true );

  // See if we've been cancelled.
  if ( true == this->canceled() )
    this->cancel();

  // Call finish callback.
  this->_finished();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Called when the job finishes normally.
//
///////////////////////////////////////////////////////////////////////////////

void Job::_finished()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Called when the thread starts.
//
///////////////////////////////////////////////////////////////////////////////

void Job::_threadStarted()
{
  if ( true == this->canceled() )
    this->cancel();

  this->_started();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Called when the job starts.
//
///////////////////////////////////////////////////////////////////////////////

void Job::_started()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the done flag.
//
///////////////////////////////////////////////////////////////////////////////

void Job::_setDone ( bool done )
{
  Guard guard ( this );
  _done = done;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Cancel this job.
//
///////////////////////////////////////////////////////////////////////////////

void Job::cancel()
{
  Guard guard ( this );

  _canceled = true;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Was the job canceled?
//
///////////////////////////////////////////////////////////////////////////////

bool Job::canceled() const
{
  Guard guard ( this );
  return _canceled;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return this job's id.
//
///////////////////////////////////////////////////////////////////////////////

unsigned long Job::id() const
{
  Guard guard ( this );
  return _id;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set this job's id.
//
///////////////////////////////////////////////////////////////////////////////

void Job::_setId ( unsigned int value )
{
  Guard guard ( this );
  _id = value;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Is this job done?
//
///////////////////////////////////////////////////////////////////////////////

bool Job::isDone() const
{
  Guard guard ( this );
  return _done;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the priority.
//
///////////////////////////////////////////////////////////////////////////////

void Job::priority ( int value )
{
  Guard guard ( this );
  _priority = value;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the priority.
//
///////////////////////////////////////////////////////////////////////////////

int Job::priority() const
{
  Guard guard ( this );
  return _priority;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Overload to return an accurate indication of success.
//
///////////////////////////////////////////////////////////////////////////////

bool Job::success() const
{
  return true;
}
