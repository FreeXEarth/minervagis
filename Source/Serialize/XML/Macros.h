
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2002, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Author: Perry L Miller IV
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Convenient macros.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _SERIALIZE_XML_MACROS_H_
#define _SERIALIZE_XML_MACROS_H_

#include "Serialize/XML/DataMemberMap.h"

#include "XmlTree/Node.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Macro for declaring class name.
//
///////////////////////////////////////////////////////////////////////////////

#define SERIALIZE_XML_CLASS_NAME(the_class)\
public:\
  virtual const char *className() const { return #the_class; }\


///////////////////////////////////////////////////////////////////////////////
//
//  Macro for declaring serialize.
//
///////////////////////////////////////////////////////////////////////////////

#define SERIALIZE_XML_SERIALIZE_FUNCTION \
public:\
  virtual void serialize ( XmlTree::Node &parent ) const\
  {\
    _dataMemberMap.serialize ( parent );\
  }\


///////////////////////////////////////////////////////////////////////////////
//
//  Macro for declaring deserialize.
//
///////////////////////////////////////////////////////////////////////////////

#define SERIALIZE_XML_DESERIALIZE_FUNCTION \
public:\
  virtual void deserialize ( const XmlTree::Node &node )\
  {\
    _dataMemberMap.deserialize ( node );\
  }\


///////////////////////////////////////////////////////////////////////////////
//
//  Macro for declaring add member.
//
///////////////////////////////////////////////////////////////////////////////

#define SERIALIZE_XML_ADD_MEMBER_FUNCTION \
protected:\
  template < class T > void _addMember ( const std::string &name, T &value )\
  {\
    _dataMemberMap.addMember ( name, value );\
  }\
  void _addMember ( Serialize::XML::MemberBase *member )\
  {\
    _dataMemberMap.addMember ( member );\
  }


///////////////////////////////////////////////////////////////////////////////
//
//  Macro for declaring necessary members.
//
///////////////////////////////////////////////////////////////////////////////

#define SERIALIZE_XML_DEFINE_MEMBERS(the_class)\
  SERIALIZE_XML_CLASS_NAME(the_class) \
  SERIALIZE_XML_SERIALIZE_FUNCTION \
  SERIALIZE_XML_DESERIALIZE_FUNCTION \
  SERIALIZE_XML_ADD_MEMBER_FUNCTION


///////////////////////////////////////////////////////////////////////////////
//
//  Macro for declaring member map.
//
///////////////////////////////////////////////////////////////////////////////

#define SERIALIZE_XML_DEFINE_MAP\
  protected: \
    Serialize::XML::DataMemberMap _dataMemberMap


///////////////////////////////////////////////////////////////////////////////
//
//  Macro for initializing necessary members.
//
///////////////////////////////////////////////////////////////////////////////

#define SERIALIZE_XML_INITIALIZER_LIST _dataMemberMap()


///////////////////////////////////////////////////////////////////////////////
//
//  Macro for adding data members.
//
///////////////////////////////////////////////////////////////////////////////

#define SERIALIZE_XML_ADD_MEMBER(the_member)\
  this->_addMember ( #the_member, the_member )


#endif // _SERIALIZE_XML_MACROS_H_
