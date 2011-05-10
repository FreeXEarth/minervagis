
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Author: Perry L Miller IV
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Callbacks that determine tile splitting behavior.
//
///////////////////////////////////////////////////////////////////////////////

#include "Minerva/Core/TileEngine/SplitCallbacks.h"
#include "Minerva/Core/TileEngine/Tile.h"

#include "Usul/Factory/RegisterCreator.h"

using namespace Minerva::Core::TileEngine::Callbacks;

/////////////////////////////////////////////////////////////////////////////
//
//  Declare serialization wrappers.
//
/////////////////////////////////////////////////////////////////////////////

USUL_IO_TEXT_DEFINE_READER_TYPE_VECTOR_4 ( SplitToLevel::Extents );
USUL_IO_TEXT_DEFINE_WRITER_TYPE_VECTOR_4 ( SplitToLevel::Extents );
SERIALIZE_XML_DECLARE_VECTOR_4_WRAPPER ( SplitToLevel::Extents );


///////////////////////////////////////////////////////////////////////////////
//
//  Register factories.
//
///////////////////////////////////////////////////////////////////////////////

USUL_FACTORY_REGISTER_CREATOR ( PassThrough );
USUL_FACTORY_REGISTER_CREATOR ( SplitToLevel );
USUL_FACTORY_REGISTER_CREATOR ( SplitIfLess );


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

SplitCallback::SplitCallback() : BaseClass(),
  SERIALIZE_XML_INITIALIZER_LIST
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

SplitCallback::~SplitCallback()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

PassThrough::PassThrough() : BaseClass()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

PassThrough::~PassThrough()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return true if the tile should split.
//
///////////////////////////////////////////////////////////////////////////////

bool PassThrough::shouldSplit ( bool suggestion, Tile * )
{
  return suggestion;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

SplitToLevel::SplitToLevel ( unsigned int level, const Extents &extents, bool canGoDeeper ) : BaseClass(), 
  _level ( level ),
  _extents ( extents ),
  _canGoDeeper ( canGoDeeper )
{
  // Serialization glue.
  this->_addMember ( "level", _level );
  this->_addMember ( "extents", _extents );
  this->_addMember ( "allow_splitting_beyond_level", _canGoDeeper );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

SplitToLevel::~SplitToLevel()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return true if the tile's level is less than the max.
//
///////////////////////////////////////////////////////////////////////////////

bool SplitToLevel::shouldSplit ( bool suggestion, Tile *tile )
{
  if ( 0x0 == tile )
  {
    return suggestion;
  }

  if ( false == _extents.intersects ( tile->extents() ) )
  {
    return suggestion;
  }

  if ( ( true == suggestion ) && ( true == _canGoDeeper ) )
  {
    return true;
  }

  return ( tile->level() < _level );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

SplitIfLess::SplitIfLess ( unsigned int maxLevel ) : BaseClass(), 
  _maxLevel ( maxLevel )
{
  // Serialization glue.
  this->_addMember ( "max_level", _maxLevel );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

SplitIfLess::~SplitIfLess()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return true if the tile's level is less than the max.
//
///////////////////////////////////////////////////////////////////////////////

bool SplitIfLess::shouldSplit ( bool suggestion, Tile *tile )
{
  return ( ( 0x0 == tile ) ? suggestion : ( ( true == suggestion ) && ( tile->level() < _maxLevel ) ) );
}