
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Adam Kubach
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Component for ArcIMS GUI.
//
///////////////////////////////////////////////////////////////////////////////

#include "MinervaQt/Plugins/QtArcIMS/QtArcIMSComponent.h"
#include "Minerva/Qt/Widgets/AddNetworkLayerWidget.h"

#include "Usul/Components/Factory.h"


USUL_DECLARE_COMPONENT_FACTORY ( QtArcIMSComponent );
USUL_IMPLEMENT_IUNKNOWN_MEMBERS ( QtArcIMSComponent, QtArcIMSComponent::BaseClass );


///////////////////////////////////////////////////////////////////////////////
//
// Constructor
//
///////////////////////////////////////////////////////////////////////////////

QtArcIMSComponent::QtArcIMSComponent() : BaseClass(),
  _widget ( 0x0 )
{
}


///////////////////////////////////////////////////////////////////////////////
//
// Destructor
//
///////////////////////////////////////////////////////////////////////////////

QtArcIMSComponent::~QtArcIMSComponent() 
{
//  delete _widget;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Query for the interface.
//
///////////////////////////////////////////////////////////////////////////////

Usul::Interfaces::IUnknown *QtArcIMSComponent::queryInterface ( unsigned long iid )
{
  switch ( iid )
  {
  case Usul::Interfaces::IUnknown::IID:
  case Usul::Interfaces::IPlugin::IID:
    return static_cast < Usul::Interfaces::IPlugin* > ( this );
  case Minerva::Common::ILayerAddGUIQt::IID:
    return static_cast < Minerva::Common::ILayerAddGUIQt * > ( this );
  default:
    return 0x0;
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Usul::Interfaces::IPlugin implementation
//
///////////////////////////////////////////////////////////////////////////////

std::string QtArcIMSComponent::getPluginName() const 
{
  return "ArcIMS Qt GUI";
}


///////////////////////////////////////////////////////////////////////////////
//
//  Widget to add a gui for wms servers.
//
///////////////////////////////////////////////////////////////////////////////

QWidget* QtArcIMSComponent::layerAddGUI()
{
  _widget = new AddArcIMSLayerWidget;
  return _widget;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the name of widget.  This will go on a tab.
//
///////////////////////////////////////////////////////////////////////////////

std::string QtArcIMSComponent::name() const 
{
  return "ArcIMS";
}


///////////////////////////////////////////////////////////////////////////////
//
//  Apply any selections the user made.
//
///////////////////////////////////////////////////////////////////////////////

void QtArcIMSComponent::apply ( Minerva::Core::Data::Feature* parent, DataLoadedCallback dataLoadedCallback )
{
  if ( 0x0 != _widget )
    _widget->apply ( parent );

  _widget = 0x0;
}
