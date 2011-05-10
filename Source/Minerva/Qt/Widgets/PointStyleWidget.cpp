
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2010, Adam Kubach
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Widget to edit PointStyle
//
///////////////////////////////////////////////////////////////////////////////

#include "PointStyleWidget.h"
#include "ui_PointStyleWidget.h"

#include "Minerva/Core/Data/PointStyle.h"

#include "Minerva/Qt/Tools/Color.h"

using namespace Minerva::QtWidgets;

///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

PointStyleWidget::PointStyleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PointStyleWidget),
    _pointStyle ( new Minerva::Core::Data::PointStyle )
{
    ui->setupUi(this);
    ui->transparencySlider->setRange ( 0, 100 );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

PointStyleWidget::~PointStyleWidget()
{
    delete ui;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the point style.
//
///////////////////////////////////////////////////////////////////////////////

void PointStyleWidget::setPointStyle ( Minerva::Core::Data::PointStyle::RefPtr pointStyle )
{
  if ( pointStyle )
  {
    _pointStyle->color ( pointStyle->color() );

    QColor color ( Minerva::QtTools::Color<Usul::Math::Vec4f>::convert ( pointStyle->color() ) );
    ui->colorButton->color ( color );
    ui->transparencySlider->setValue ( color.alphaF() * 100 );
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the point style.
//
///////////////////////////////////////////////////////////////////////////////

Minerva::Core::Data::PointStyle::RefPtr PointStyleWidget::getPointStyle()
{
  Usul::Math::Vec4f color ( Minerva::QtTools::Color<Usul::Math::Vec4f>::convert ( ui->colorButton->color() ) );
  color[0] = static_cast<double> ( ui->transparencySlider->value() ) / 100;
  _pointStyle->color ( color );
  return _pointStyle;
}