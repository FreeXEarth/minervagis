
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2008, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Author: Adam Kubach
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Program to test a Tile
//
///////////////////////////////////////////////////////////////////////////////

#include "Minerva/Core/TileEngine/Body.h"
#include "Minerva/Core/TileEngine/Tile.h"
#include "Minerva/Core/Functions/MakeBody.h"

#include "Usul/Factory/ObjectFactory.h"
#include "Usul/Jobs/Manager.h"
#include "Usul/Registry/Database.h"

#include "osgViewer/Viewer"
#include "osgGA/StateSetManipulator"

int main ( int argc, char** argv )
{
  // Initialize the thread pool.
  Usul::Jobs::Manager::init ( "Job Manager", 2 );

  // Make the viewer.
  osgViewer::Viewer viewer;
  viewer.setThreadingModel ( osgViewer::Viewer::DrawThreadPerContext );

  // This allows 'w' -> wireframe.
  viewer.addEventHandler( new osgGA::StateSetManipulator( viewer.getCamera()->getOrCreateStateSet() ) );

  // Make a body.
  Minerva::Core::TileEngine::Body::RefPtr body ( Minerva::Core::Functions::makeEarth ( &Usul::Jobs::Manager::instance() ) );

  // Make a tile.
  using Minerva::Core::TileEngine::Extents;
  using Minerva::Core::TileEngine::MeshSize;
  using Minerva::Core::TileEngine::ImageSize;
  using Minerva::Core::TileEngine::Tile;
  Tile::RefPtr tile ( new Tile ( 0x0, Tile::NONE, 0, Extents ( -90, -45, 0, 45 ), MeshSize ( 17, 17 ), ImageSize ( 512, 512 ), body->splitDistance(), body.get() ) );

  // Add the tile to the viewer.
  viewer.setSceneData ( tile.get() );

  // Run the viewer.
  const int result ( viewer.run() );

  // Clear the scene.
  viewer.setSceneData ( 0x0 );

  // Clear the tile.
  tile = 0x0;

  // Delete the body.
  body = 0x0;

  // Wait for all threads.
  Usul::Jobs::Manager::instance().cancel();
  Usul::Jobs::Manager::instance().wait();

  // Clear the registry.
  Usul::Registry::Database::destroy();

  // Clear the ObjectFactory.
  Usul::Factory::ObjectFactory::instance().clear();

  // Destroy the job manager.
  Usul::Jobs::Manager::destroy();

  // return the result.
  return result;
}
