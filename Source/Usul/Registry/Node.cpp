
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2002, Perry L. Miller IV
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Node class for the registry.
//
///////////////////////////////////////////////////////////////////////////////

#include "Usul/Registry/Node.h"
#include "Usul/Registry/Visitor.h"

using namespace Usul::Registry;


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

Node::Node() : BaseClass(),
  _value(),
  _kids()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

Node::~Node()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Accept the visitor.
//
///////////////////////////////////////////////////////////////////////////////

void Node::accept ( Visitor *v )
{
  if ( 0x0 != v )
  {
    v->visit ( this );
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the value.
//
///////////////////////////////////////////////////////////////////////////////

void Node::set ( const std::string &s )
{
  Guard guard ( this );
  _value = s;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the value.
//
///////////////////////////////////////////////////////////////////////////////

std::string Node::get ( const std::string &defaultValue ) const
{
  Guard guard ( this );
  return ( ( true == _value.empty() ) ? defaultValue : _value );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the value.
//
///////////////////////////////////////////////////////////////////////////////

std::string Node::get ( const std::string &defaultValue, bool setValueIfEmpty )
{
  Guard guard ( this );

  if ( ( true == _value.empty() ) && ( true == setValueIfEmpty ) )
  {
    this->set ( defaultValue );
  }

  return this->get ( defaultValue );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Clear the database.
//
///////////////////////////////////////////////////////////////////////////////

void Node::clear()
{
  Guard guard ( this );
  _value.clear();
  _kids.clear();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return the child with the name. Creates child nodes as needed.
//
///////////////////////////////////////////////////////////////////////////////

Node::RefPtr Node::_getNode ( const std::string &name )
{
  Kids::iterator i ( _kids.find ( name ) );
  Node::RefPtr child ( ( _kids.end() == i ) ? 0x0 : i->second );
  if ( false == child.valid() )
  {
    child = new Node;
    child->name ( name );
    _kids.insert ( Kids::value_type ( name, child ) );
  }
  return child;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Operator to return the child with the name. Creates child nodes as needed.
//
///////////////////////////////////////////////////////////////////////////////

Node &Node::operator [] ( const std::string &name )
{
  Kids::iterator i ( _kids.find ( name ) );
  Node::RefPtr child ( this->_getNode ( name ) );
  return *child;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Operator to return the child with the path. Creates child nodes as needed.
//
///////////////////////////////////////////////////////////////////////////////

Node &Node::operator [] ( const Node::Path &path )
{
  Node::RefPtr child ( this );

  for ( Node::Path::const_iterator i = path.begin(); i != path.end(); ++i )
  {
    child = child->_getNode ( *i );
  }

  return *child;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the iterator.
//
///////////////////////////////////////////////////////////////////////////////

Node::Iterator Node::begin()
{
  Guard guard ( this );
  return _kids.begin();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the iterator.
//
///////////////////////////////////////////////////////////////////////////////

Node::ConstIterator Node::begin() const
{
  Guard guard ( this );
  return _kids.begin();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the iterator.
//
///////////////////////////////////////////////////////////////////////////////

Node::Iterator Node::end()
{
  Guard guard ( this );
  return _kids.end();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the iterator.
//
///////////////////////////////////////////////////////////////////////////////

Node::ConstIterator Node::end() const
{
  Guard guard ( this );
  return _kids.end();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return the child with the name. No new nodes are created.
//
///////////////////////////////////////////////////////////////////////////////

Node::RefPtr Node::find ( const std::string &name ) const
{
  Kids::const_iterator i ( _kids.find ( name ) );
  Node::RefPtr child ( ( _kids.end() == i ) ? 0x0 : i->second );
  return child;
}
