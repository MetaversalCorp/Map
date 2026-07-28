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
**                                             CLASS (PACKAGE_MAP_IO::IREFERENCE)                                             **
****************************************************************\**************************************************************/

PACKAGE_MAP_IO::IREFERENCE::IREFERENCE (const std::string& sID, const std::string& sNamespace, const std::vector<std::string>& aService, const std::vector<std::string>& aModel, const std::vector<std::string>& aSource) :
   RMAP::CORE::PACKAGE::IREFERENCE (sID, sNamespace, aService, aModel, aSource)
{
}

PACKAGE_MAP_IO::IREFERENCE::~IREFERENCE ()
{
}

RMAP::CORE::PACKAGE* PACKAGE_MAP_IO::IREFERENCE::Create (RMAP::CORE::PACKAGE::PACKAGEPARAM* pParam)
{
   return new PACKAGE_MAP_IO (this, NULL);
}

/*******************************************************************************************************************************
**                                                 CLASS (PACKAGE_MAP_IO::FACTORY)                                            **
*******************************************************************************************************************************/

PACKAGE_MAP_IO::FACTORY::FACTORY (const std::string& sID_Service, const std::string& sID_Package, const std::vector<std::string>& aService, const std::vector<std::string>& aModel, const std::vector<std::string>& aSource) :
   RMAP::CORE::PACKAGE::FACTORY (sID_Service, sID_Package, aService, aModel, aSource)
{
}

PACKAGE_MAP_IO::FACTORY::~FACTORY ()
{
}

RMAP::CORE::PACKAGE::IREFERENCE* PACKAGE_MAP_IO::FACTORY::Reference (const std::string& sNamespace)
{
   return new PACKAGE_MAP_IO::IREFERENCE (sID (), sNamespace, aService (), aModel (), aSource ());
}

/*******************************************************************************************************************************
**                                                     CLASS (PACKAGE_MAP_IO)                                                 **
*******************************************************************************************************************************/

PACKAGE_MAP_IO::PACKAGE_MAP_IO (IREFERENCE* pReference, RMAP::CORE::PACKAGE::PACKAGEPARAM* pParam) :
   RMAP::CORE::PACKAGE (pReference, pParam)
{
}

PACKAGE_MAP_IO::~PACKAGE_MAP_IO ()
{
}

RMAP::CORE::PACKAGE::FACTORY* PACKAGE_MAP_IO::factory ()
{
   const std::vector<std::string> aService = {
      "MVIO/MVIO",
   };

   const std::vector<std::string> aModel = {
      "MVRP_Map/RMRoot",
      "MVRP_Map/RMCObject",
      "MVRP_Map/RMTObject",
      "MVRP_Map/RMPObject",
   };

   const std::vector<std::string> aSource = {
      "MVRP_Map/MVIO:RMRoot",
      "MVRP_Map/MVIO:RMCObject",
      "MVRP_Map/MVIO:RMTObject",
      "MVRP_Map/MVIO:RMPObject",
   };

   return new FACTORY ("MVIO", "Map", aService, aModel, aSource);
}

/******************************************************************************************************************************/
