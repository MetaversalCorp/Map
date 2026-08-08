/*******************************************************************************************************************************
**                                                                                                                            **
**                                                   MVRP_cpp : Map_Object.cpp                                                **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2026 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

#include "pch.h"

using namespace RMAP::MAP;

/*******************************************************************************************************************************
**                                                     CLASS (RMCOBJECT)                                                      **
*******************************************************************************************************************************/

MAP_OBJECT::MAP_OBJECT (uint16_t wClass_Parent, uint64_t twParentIx, uint16_t wClass_Object, uint64_t twObjectIx) :
   m_POD ({}),
   m_nChildren (0)
{
   m_POD.Head.Parent.qwComposed  = OBJECTIX_COMPOSE (wClass_Parent, twParentIx);
   m_POD.Head.Self.qwComposed    = OBJECTIX_COMPOSE (wClass_Object, twObjectIx);
}

MAP_OBJECT::~MAP_OBJECT ()
{
}

void MAP_OBJECT::GetPOD (MAP_OBJECT_POD& Pod) const&
{
   Pod = m_POD;
}

uint32_t MAP_OBJECT::Children () const &
{
   return m_nChildren;
}

// Modifiers                                              
void MAP_OBJECT::Name (const std::wstring& sName) &
{
   RMAP::CORE::UTILS::WString_to_Uint16 (sName, m_POD.Name.wsName, sizeof (m_POD.Name.wsName) / sizeof (uint16_t));
}

void MAP_OBJECT::Type (const MAP_OBJECT_TYPE& Type) &
{
   m_POD.Type = Type;
}

void MAP_OBJECT::Owner (const MAP_OBJECT_OWNER& Owner) &
{
   m_POD.Owner = Owner;
}

void MAP_OBJECT::Resource (uint64_t qwResource, const std::string& sName, const std::string& sReference) &
{
   m_POD.Resource.qwResource = qwResource;
   RMAP::CORE::UTILS::String_to_Uint8 (sName, reinterpret_cast<uint8_t*> (m_POD.Resource.sName), sizeof (m_POD.Resource.sName) / sizeof (uint8_t));
   RMAP::CORE::UTILS::String_to_Uint8 (sReference, reinterpret_cast<uint8_t*> (m_POD.Resource.sReference), sizeof (m_POD.Resource.sReference) / sizeof (uint8_t));
}

void MAP_OBJECT::Transform (const MAP_OBJECT_TRANSFORM& Transform) &
{
   m_POD.Transform = Transform;
}

void MAP_OBJECT::Bound (const MAP_OBJECT_BOUND& Bound) &
{
   m_POD.Bound = Bound;
}

void MAP_OBJECT::Children (uint32_t nChildren) &
{
   m_nChildren = nChildren;
}
