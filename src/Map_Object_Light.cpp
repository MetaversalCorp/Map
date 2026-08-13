/*******************************************************************************************************************************
**                                                                                                                            **
**                                              MVRP_cpp : Map_Object_Light.cpp                                               **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2026 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

#include "pch.h"

using namespace RMAP::MAP;

/*******************************************************************************************************************************
**                                                     CLASS (MAP_OBJECT_LIGHT)                                         **
*******************************************************************************************************************************/

MAP_OBJECT_LIGHT::MAP_OBJECT_LIGHT (uint16_t wClass_Parent, uint64_t twParentIx, uint16_t wClass_Object, uint64_t twObjectIx, const MAP_OBJECT_POD& Pod) :
   MAP_OBJECT (wClass_Parent, twParentIx, wClass_Object, twObjectIx, Pod)
{
}

MAP_OBJECT_LIGHT::~MAP_OBJECT_LIGHT ()
{
}

/*******************************************************************************
**  Modifiers
*******************************************************************************/

void MAP_OBJECT_LIGHT::Properties (const MAP_OBJECT_PROPERTIES_LIGHT& _Properties)&
{
   m_POD.Properties.Light = _Properties;
}
