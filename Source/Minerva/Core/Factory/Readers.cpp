
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2008, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Adam Kubach
//
///////////////////////////////////////////////////////////////////////////////

#include "Minerva/Core/Factory/Readers.h"

#include "Usul/Threads/Safe.h"

#include "boost/filesystem.hpp"

using namespace Minerva::Core::Factory;


///////////////////////////////////////////////////////////////////////////////
//
//  Static member initialization.
//
///////////////////////////////////////////////////////////////////////////////

Readers* Readers::_instance ( 0x0 );


///////////////////////////////////////////////////////////////////////////////
//
//  Get the instance.
//
///////////////////////////////////////////////////////////////////////////////

Readers& Readers::instance()
{
  if ( 0x0 == _instance )
    _instance = new Readers;
  return *_instance;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

Readers::Readers() :
  _mutex    ( new Readers::Mutex ),
  _readers()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

Readers::~Readers()
{
  delete _mutex; _mutex = 0x0;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Add a creator.
//
///////////////////////////////////////////////////////////////////////////////

void Readers::add ( ReaderPtr reader )
{
  Guard guard ( *_mutex );
  
  if ( reader )
  {
    _readers.push_back ( reader );
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Remove a creator.
//
///////////////////////////////////////////////////////////////////////////////

void Readers::remove ( ReaderPtr reader )
{
  Guard guard ( *_mutex );

  _readers.erase ( 
                 std::remove_if ( _readers.begin(), 
                                  _readers.end(), 
                                 ReaderPtr::IsEqual ( reader ) ),
                 _readers.end() );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Create.
//
///////////////////////////////////////////////////////////////////////////////

Minerva::Core::Data::Feature * Readers::read ( const std::string &filename )
{
  FeatureReaders readers ( Usul::Threads::Safe::get ( *_mutex, _readers ) );
  
  for ( FeatureReaders::const_iterator iter = readers.begin(); iter != readers.end(); ++iter )
  {
    ReaderPtr reader ( *iter );
    if ( reader && reader->canHandle ( boost::filesystem::extension ( filename ) ) )
    {
      return reader->readFeature ( filename );
    }
  }
  
  return 0x0;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get all filters.
//
///////////////////////////////////////////////////////////////////////////////

Readers::Filters Readers::filters() const
{
  FeatureReaders readers ( Usul::Threads::Safe::get ( *_mutex, _readers ) );
  Filters filters;
  
  for ( FeatureReaders::const_iterator iter = readers.begin(); iter != readers.end(); ++iter )
  {
    ReaderPtr reader ( *iter );
    if ( reader )
    {
      Filters f ( reader->filters() );
      std::copy ( f.begin(), f.end(), std::back_inserter ( filters ) );
    }
  }
  
  return filters;
}