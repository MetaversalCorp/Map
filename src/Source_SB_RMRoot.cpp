/*******************************************************************************************************************************
**                                                                                                                            **
**                                      MVRP_RP1_Map_cpp : Source_SB_RMROOT.cpp                                            **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2024 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

#include "pch.h"

using namespace RMAP::MAP;

/*******************************************************************************************************************************
**                                                     CLASS (Impl)                                                           **
*******************************************************************************************************************************/

class SB_RMROOT::Impl
{
public:
   Impl ()
   {
   }

   ~Impl ()
   {
   }
};

/*******************************************************************************************************************************
**                                                     CLASS (FACTORY)                                                      **
*******************************************************************************************************************************/

SB_RMROOT::FACTORY::FACTORY (std::string sID_Service, std::string sID_Model, int wClass, std::map<std::string, const RMAP::CORE::CLIENT::ACTION*>& apAction, bool bIndependent, RMAP::SVC_SB::MAP* pMap) :
   RMAP::SVC_SB::SB_OBJECT::FACTORY (sID_Service, sID_Model, wClass, apAction, bIndependent, pMap)
{
}

SB_RMROOT::FACTORY::~FACTORY ()
{
}

RMAP::CORE::SOURCE* SB_RMROOT::FACTORY::Create (RMAP::CORE::CLIENT* pClient)
{
   return new SB_RMROOT (pReference, m_pMap, pClient);
}

/*******************************************************************************************************************************
**                                                   CLASS (SB_RMROOT)                                                     **
*******************************************************************************************************************************/

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMROOT_NAMEX
(
   SBA_RMROOT_NAME,
   "{"
      "\"twRMRootIx\"            : \"TWORD8\","
      "\"abReserved_A\"          : \"PAD (8)\","
      RMCOBJECT_NAME_SB
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMROOT_OWNERX
(
   SBA_RMROOT_OWNER,
   "{"
      "\"twRMRootIx\"            : \"TWORD8\","
      "\"abReserved_A\"          : \"PAD (8)\","
      RMCOMMON_OWNER_SB
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMROOT_RMCOBJECT_OPENX
(
   SBA_RMROOT_RMCOBJECT_OPEN,
   "{"
      "\"twRMRootIx\"            : \"TWORD8\","
      "\"abReserved_A\"          : \"PAD (16)\","
      RMCOBJECT_NAME_SB ","
      RMCOMMON_TYPE_SB ","
      RMCOMMON_OWNER_SB ","
      RMCOMMON_RESOURCE_SB ","
      RMCOMMON_TRANSFORM_SB ","
      RMCOMMON_ORBIT_SPIN_SB ","
      RMCOMMON_BOUND_SB ","
      RMCOBJECT_PROPERTIES_SB ","
      RMCOMMON_DCOORD_SB
   "}",
   "{"
      "\"twRMCObjectIx\"         : \"TWORD8\""
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMROOT_RMCOBJECT_CLOSEX
(
   SBA_RMROOT_RMCOBJECT_CLOSE,
   "{"
      "\"twRMRootIx\"            : \"TWORD8\","
      "\"abReserved_A\"          : \"PAD (8)\","
      "\"twRMCObjectIx\"         : \"TWORD8\""
   "}",
   "{"
   "}",
   true
);

std::map<std::string, const RMAP::CORE::CLIENT::ACTION*> SB_RMROOT::aAction =
{
   { "NAME",            &SBA_RMROOT_NAMEX             },
   { "OWNER",           &SBA_RMROOT_OWNERX            },
   { "RMCOBJECT_OPEN",  &SBA_RMROOT_RMCOBJECT_OPENX   },
   { "RMCOBJECT_CLOSE", &SBA_RMROOT_RMCOBJECT_CLOSEX  },
};

SB_RMROOT::SB_RMROOT (RMAP::CORE::MEM::SOURCE::REFERENCE* pReference, RMAP::SVC_SB::MAP* pMap, RMAP::CORE::CLIENT* pClient) :
   RMAP::SVC_SB::SB_OBJECT (pReference, pMap, pClient)
{
   m_pImpl = new Impl ();
}

SB_RMROOT::~SB_RMROOT ()
{
   delete m_pImpl;
}

void SB_RMROOT::init ()
{
}

SB_RMROOT::FACTORY* SB_RMROOT::factory ()
{
   RMAP::SVC_SB::MAP* pMap = new RMAP::SVC_SB::MAP
   (
      "{"
         RMROOT_NAME_SB ","
         RMCOMMON_TYPE_SB_PAD ","
         RMCOMMON_OWNER_SB ","
         RMCOMMON_RESOURCE_SB_PAD ","
         RMCOMMON_TRANSFORM_SB_PAD ","
         RMCOMMON_ORBIT_SPIN_SB_PAD ","
         RMCOMMON_BOUND_SB_PAD ","
         RMROOT_PROPERTIES_SB ","

         "\"PARTIAL\"            : \"SIZE\""
      "}"
   );

   return new FACTORY ("Statabase", "RMRoot", SBO_CLASS_RMROOT, aAction, true, pMap);
}

void SB_RMROOT::Read (ordered_json& jSrc, RMAP::CORE::MODEL* pModel)
{
   RMROOT* pModelIO = dynamic_cast<RMROOT*> (pModel);
   RMROOT::NAME Name (RMAP::CORE::UTILS::UTF8_to_Wchar (jSrc["pName"]["wsRMRootId"].get<std::string> ().c_str ()));
   OWNER Owner;

   Owner.twRPersonaIx = jSrc["pOwner"]["twRPersonaIx"];

   pModelIO->Name (Name);
   pModelIO->Owner (Owner);
}

/******************************************************************************************************************************/
