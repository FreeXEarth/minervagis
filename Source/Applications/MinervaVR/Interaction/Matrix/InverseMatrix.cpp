
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2002, John K. Grant and Perry L. Miller IV.
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Inverse matrix functor.
//
///////////////////////////////////////////////////////////////////////////////

#include "Interaction/Matrix/InverseMatrix.h"

using namespace Usul::Functors::Interaction::Matrix;


///////////////////////////////////////////////////////////////////////////////
//
//  Default constructors.
//
///////////////////////////////////////////////////////////////////////////////

InverseMatrix::InverseMatrix ( Unknown *caller, const std::string &name, BaseClass *mf ) : 
  BaseClass ( caller, name ), 
  _mf ( mf )
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Copy constructors.
//
///////////////////////////////////////////////////////////////////////////////

InverseMatrix::InverseMatrix ( const InverseMatrix &cb ) : 
  BaseClass ( cb ), 
  _mf ( cb._mf )
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructors.
//
///////////////////////////////////////////////////////////////////////////////

InverseMatrix::~InverseMatrix()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the inverse of the contained matrix.
//
///////////////////////////////////////////////////////////////////////////////

void InverseMatrix::operator()()
{
  Guard guard ( this->mutex() );

  if ( true == _mf.valid() )
  {
    (*_mf)();
    _matrix = _mf->matrix();
    _matrix.invert();
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Clone.
//
///////////////////////////////////////////////////////////////////////////////

Usul::Functors::Interaction::Common::BaseFunctor* InverseMatrix::clone()
{
  return new InverseMatrix ( *this );
}