
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2008, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Author: Adam Kubach
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MINERVA_LAYERS_CONTAINER_H__
#define __MINERVA_LAYERS_CONTAINER_H__

#include "Minerva/Core/Export.h"
#include "Minerva/Core/Data/Feature.h"
#include "Minerva/Core/Data/DataObject.h"

#include "Minerva/Common/IBuildScene.h"
#include "Minerva/Common/IElevationChangedListener.h"
#include "Minerva/Common/ITileVectorData.h"
#include "Minerva/Common/IWithinExtents.h"

#include "Usul/Math/Vector2.h"

#include "Serialize/XML/Macros.h"

#include "osg/Group"

#include <map>
#include <string>
#include <vector>

namespace Minerva {
namespace Core { 

class Visitor;

namespace Data {

class MINERVA_EXPORT Container : 
  public Minerva::Core::Data::Feature,
  public Minerva::Common::IElevationChangedListener,
  public Minerva::Common::ITileVectorData,
  public Minerva::Common::IBuildScene
{
public:

  /// Typedefs.
  typedef Minerva::Core::Data::Feature              BaseClass;
  typedef BaseClass::Extents                        Extents;
  typedef Usul::Interfaces::IUnknown                IUnknown;
  typedef std::vector<Feature::RefPtr>              Features;
  typedef Minerva::Common::ITileVectorData          ITileVectorData;
  typedef ITileVectorData::Jobs                     TileVectorJobs;
  typedef Minerva::Common::IWithinExtents           IWithinExtents;
  typedef std::vector<std::string> Comments;

  /// Smart-pointer definitions.
  USUL_DECLARE_QUERY_POINTERS ( Container );
  USUL_DECLARE_IUNKNOWN_MEMBERS;

  enum Flags
  {
    DATA_DIRTY    = 0x00000001,
    EXTENTS_DIRTY = 0x00000002,
    SCENE_DIRTY   = 0x00000004,
    ALL           = DATA_DIRTY | EXTENTS_DIRTY | SCENE_DIRTY
  };
  
  Container();
  
  /// Accept the visitor.
  virtual void                accept ( Minerva::Core::Visitor& visitor );
  
  /// Get this as a container.
  virtual Container*          asContainer() { return this; }

  /// Add an object.
  void                        add ( Feature* layer, bool notify = true );

  osg::Node*                  getScene();
  
  /// Build the scene (IBuildScene).
  virtual osg::Node *         buildScene ( Minerva::Common::IPlanetCoordinates *planet, Minerva::Common::IElevationDatabase *elevation );

  /// Get the extents.
  virtual Extents             calculateExtents() const;
  
  /// Clear objects.
  void                        clear();
  
  /// Clone this container.
  virtual Feature*            clone() const { return new Container ( *this ); }

  /// Deserialize.
  virtual void                deserialize ( const XmlTree::Node &node );

  /// Get/Set the data dirty flag.
  bool                        dirtyData() const;
  void                        dirtyData( bool );
  
  /// Get/Set the extents dirty flag.
  bool                        dirtyExtents() const;
  void                        dirtyExtents ( bool );
  
  /// Get/Set dirty scene flag (IDirtyScene).
  virtual bool                dirtyScene() const;
  virtual void                dirtyScene ( bool b );

  /// Elevation has changed within given extents (IElevationChangeListener).
  virtual bool                elevationChangedNotify ( const Extents& extents, unsigned int level, ElevationDataPtr elevationData, Usul::Interfaces::IUnknown * caller = 0x0 );
  
  /// Get the feature.
  Feature::RefPtr             feature ( unsigned int i );
  
  /// Find unknown with given id.  The function will return null if not found.
  Feature::RefPtr             find ( const ObjectID& id ) const;
  
  /// Get/Set the flags.
  unsigned int                flags() const;
  void                        flags ( unsigned int );

  /// See if the given level falls within this layer's range of levels.
  bool                        isInLevelRange ( unsigned int level ) const;

  /// Launch the jobs to fetch vector data.
  virtual TileVectorJobs      launchVectorJobs ( double minLon, double minLat, double maxLon, double maxLat, unsigned int level, Usul::Jobs::Manager *manager, Usul::Interfaces::IUnknown::RefPtr caller );

  /// Get the number of data objects in this layer.
  virtual unsigned int        size() const;

  /// Remove an object.
  void                        remove ( Feature* layer );

  /// Get/Set show layer.
  virtual void                visibilitySet ( bool b );

  // Swap two features.
  void                        swap ( Feature* layer0, Feature* layer1 );
  
  /// Traverse all DataObjects.
  virtual void                traverse ( Minerva::Core::Visitor& visitor );
  
  /// Update.
  virtual void                updateNotify ( CameraState* camera, Minerva::Common::IPlanetCoordinates *planet, Minerva::Common::IElevationDatabase *elevation );

  /// Minerva::Common::IWithinExtents
  Feature::RefPtr             getItemsWithinExtents ( double minLon, double minLat, double maxLon, double maxLat, IUnknown::RefPtr caller = IUnknown::RefPtr ( 0x0 ) ) const;

  void                        reserve ( unsigned int size );

protected:

  virtual ~Container();
  
  Container ( const Container& rhs );
  
  // Build the scene.
  void                        _buildScene ( Minerva::Common::IPlanetCoordinates *planet, Minerva::Common::IElevationDatabase *elevation );
  
  // Get the number of children.
  virtual unsigned int        getNumChildNodes() const;
  
  // Get the child node.
  virtual Feature::RefPtr     getChildNode ( unsigned int which );

private:

  // Do not use.
  Container& operator= ( const Container& rhs );

  // Register members for serialization.
  void                        _registerMembers();

  typedef Minerva::Common::IBuildScene IBuildScene;
  typedef std::vector<IBuildScene::RefPtr> Builders;
  typedef std::map<ObjectID,Feature::RefPtr>      FeatureMap;
  
  Features _layers;
  Builders _builders;
  unsigned int _flags;
  osg::ref_ptr<osg::Group> _root;
  FeatureMap _unknownMap;
  Comments _comments;
  
  SERIALIZE_XML_CLASS_NAME( Container )
};


}
}
}

#endif // __MINERVA_LAYERS_CONTAINER_H__
