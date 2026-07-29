/*******************************************************************************************************************************
**                                                                                                                            **
**                                      MVRP_RP1_Core_cpp : Package.cpp                                                       **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2024 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

#include "pch.h"

using namespace RMAP;

/*******************************************************************************************************************************
**                                             CLASS (PACKAGE_MAP_SB::IREFERENCE)                                             **
****************************************************************\**************************************************************/

PACKAGE_MAP_SB::IREFERENCE::IREFERENCE (const std::string& sID, const std::string& sNamespace, const std::vector<std::string>& aService, const std::vector<std::string>& aModel, const std::vector<std::string>& aSource) :
   RMAP::CORE::PACKAGE::IREFERENCE (sID, sNamespace, aService, aModel, aSource)
{
}

PACKAGE_MAP_SB::IREFERENCE::~IREFERENCE ()
{
}

RMAP::CORE::PACKAGE* PACKAGE_MAP_SB::IREFERENCE::Create (RMAP::CORE::PACKAGE::PACKAGEPARAM* pParam)
{
   return new PACKAGE_MAP_SB (this, NULL);
}

/*******************************************************************************************************************************
**                                                 CLASS (PACKAGE_MAP_SB::FACTORY)                                            **
*******************************************************************************************************************************/

PACKAGE_MAP_SB::FACTORY::FACTORY (const std::string& sID_Service, const std::string& sID_Package, const std::vector<std::string>& aService, const std::vector<std::string>& aModel, const std::vector<std::string>& aSource) :
   RMAP::CORE::PACKAGE::FACTORY (sID_Service, sID_Package, aService, aModel, aSource)
{
}

PACKAGE_MAP_SB::FACTORY::~FACTORY ()
{
}

RMAP::CORE::PACKAGE::IREFERENCE* PACKAGE_MAP_SB::FACTORY::Reference (const std::string& sNamespace)
{
   return new PACKAGE_MAP_SB::IREFERENCE (sID (), sNamespace, aService (), aModel (), aSource ());
}

/*******************************************************************************************************************************
**                                                     CLASS (PACKAGE_MAP_SB)                                                 **
*******************************************************************************************************************************/

PACKAGE_MAP_SB::PACKAGE_MAP_SB (IREFERENCE* pReference, RMAP::CORE::PACKAGE::PACKAGEPARAM* pParam) :
   RMAP::CORE::PACKAGE (pReference, pParam)
{
}

PACKAGE_MAP_SB::~PACKAGE_MAP_SB ()
{
}

RMAP::CORE::PACKAGE::FACTORY* PACKAGE_MAP_SB::factory ()
{
   const std::vector<std::string> aService = {
      "Statabase/Statabase",
   };

   const std::vector<std::string> aModel = {
      "Map/RMRoot",
      "Map/RMCObject",
      "Map/RMTObject",
      "Map/RMPObject",
   };

   const std::vector<std::string> aSource = {
      "Map/Statabase:RMRoot",
      "Map/Statabase:RMCObject",
      "Map/Statabase:RMTObject",
      "Map/Statabase:RMPObject",
   };

   return new FACTORY ("Statabase", "Map", aService, aModel, aSource);
}

/******************************************************************************************************************************/
