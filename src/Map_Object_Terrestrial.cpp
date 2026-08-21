/*******************************************************************************************************************************
**                                                                                                                            **
**                                           MVRP_cpp : Map_Object_Terrestrial.cpp                                            **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2026 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

#include "pch.h"

using namespace RMAP::MAP;

/*******************************************************************************************************************************
**                                                     CLASS (MAP_OBJECT_TERRESTRIAL)                                         **
*******************************************************************************************************************************/

MAP_OBJECT_TERRESTRIAL::MAP_OBJECT_TERRESTRIAL (uint16_t wClass, uint64_t twObjectIx, const MAP_OBJECT_POD& Pod) :
   MAP_OBJECT (wClass, twObjectIx, Pod)
{
}

MAP_OBJECT_TERRESTRIAL::~MAP_OBJECT_TERRESTRIAL ()
{
}

/*******************************************************************************
**  Modifiers
*******************************************************************************/

void MAP_OBJECT_TERRESTRIAL::Properties (const MAP_OBJECT_PROPERTIES_TERRESTIAL& _Properties)&
{
   m_POD.Properties.Terrestial = _Properties;
}
