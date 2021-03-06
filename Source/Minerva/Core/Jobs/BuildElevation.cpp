
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2009, Adam Kubach
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Job to build elevation.
//
///////////////////////////////////////////////////////////////////////////////

#include "Minerva/Core/Jobs/BuildElevation.h"

#include "Usul/Threads/Safe.h"

using namespace Minerva::Core::Jobs;


///////////////////////////////////////////////////////////////////////////////
//
//  Job to cut the texture to correct extents.
//
///////////////////////////////////////////////////////////////////////////////

BuildElevation::BuildElevation ( Tile::RefPtr tile ) : BaseClass ( 0x0, false ),
  _tile ( tile )
{ 
  if ( _tile.valid() )
  {
    const unsigned int level ( _tile->level() );
    this->priority ( -1 * static_cast<int> ( level ) );
  
    const Minerva::Core::TileEngine::Extents extents ( _tile->extents() );
    this->name ( Usul::Strings::format ( "BuildElevation, Extents: [", extents.minimum()[0], ", ", extents.minimum()[1], ", ", extents.maximum()[0], ", ", extents.maximum()[1], "], level: ", level ) );
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

BuildElevation::~BuildElevation()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Load the texture.
//
///////////////////////////////////////////////////////////////////////////////

void BuildElevation::_started()
{
  // Make sure we have valid data.
  if ( false == _tile.valid() )
    return;
  
  // Have we been cancelled?
  if ( true == this->canceled() )
    this->cancel();
  
  // Ask the tile to split.
  _tile->buildElevationData ( Usul::Jobs::Job::RefPtr ( this ) );
}
