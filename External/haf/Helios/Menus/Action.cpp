
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2009, Perry L Miller IV
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Derived from earlier work by Adam Kubach and Perry Miller found here:
//  http://sourceforge.net/projects/cadkit/
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Action class.
//
///////////////////////////////////////////////////////////////////////////////

#include "Helios/Menus/Action.h"

#include "Usul/Functions/SafeCall.h"

#include <iostream>


using namespace Helios::Menus;


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor
//
///////////////////////////////////////////////////////////////////////////////

Action::Action ( const std::string &text, Command command, QObject *parent ) : BaseClass ( parent ),
  _command ( command ),
  _update()
{
  this->setText ( text.c_str() );
  QObject::connect ( this, SIGNAL ( triggered() ), this, SLOT ( _triggered() ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor
//
///////////////////////////////////////////////////////////////////////////////

Action::Action ( const std::string &text, 
                 const std::string &icon, 
                 const std::string &status,
                 Command command, 
                 Update update,
                 QObject *parent ) : 
  BaseClass ( ( true == text.empty() ) ? 
                QString() : QString ( text.c_str() ), parent ),
  _command ( command ),
  _update ( update )
{
  if ( false == status.empty() )
  {
    this->setStatusTip ( status.c_str() );
  }
  if ( false == icon.empty() )
  {
    this->setIcon ( QIcon ( icon.c_str() ) );
  }
  QObject::connect ( this, SIGNAL ( triggered() ), this, SLOT ( _triggered() ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor
//
///////////////////////////////////////////////////////////////////////////////

Action::~Action()
{
  USUL_TRY_BLOCK
  {
    this->clear();
  }
  USUL_DEFINE_CATCH_BLOCKS ( "3641481742" );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Clear commands.
//
///////////////////////////////////////////////////////////////////////////////

void Action::clear()
{
  _command = Command();
  _update  = Update();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Update the action now.
//
///////////////////////////////////////////////////////////////////////////////

void Action::updateState()
{
  if ( _update )
  {
    _update ( *this );
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Called when it's time to update.
//
///////////////////////////////////////////////////////////////////////////////

void Action::_updateNotify()
{
  this->updateState();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Called when the button is pressed.
//
///////////////////////////////////////////////////////////////////////////////

void Action::_triggered()
{
  if ( _command )
  {
    _command();
  }
  this->_updateNotify();
}