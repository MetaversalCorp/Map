/*******************************************************************************************************************************
**                                                                                                                            **
**                                      MVRP_RP1_Map_cpp : Source_SB_RMPOBJECT.cpp                                            **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2024 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

#include "pch.h"

using namespace RMAP::MAP;

/*******************************************************************************************************************************
**                                                     CLASS (Impl)                                                           **
*******************************************************************************************************************************/

class SB_RMPOBJECT::Impl
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

SB_RMPOBJECT::FACTORY::FACTORY (std::string sID_Service, std::string sID_Model, int wClass, std::map<std::string, const RMAP::CORE::CLIENT::ACTION*>& apAction, bool bIndependent, RMAP::SVC_SB::MAP* pMap) :
   RMAP::SVC_SB::SB_OBJECT::FACTORY (sID_Service, sID_Model, wClass, apAction, bIndependent, pMap)
{
}

SB_RMPOBJECT::FACTORY::~FACTORY ()
{
}

RMAP::CORE::SOURCE* SB_RMPOBJECT::FACTORY::Create (RMAP::CORE::CLIENT* pClient)
{
   return new SB_RMPOBJECT (pReference, m_pMap, pClient);
}

/*******************************************************************************************************************************
**                                                   CLASS (SB_RMPOBJECT)                                                     **
*******************************************************************************************************************************/

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMPOBJECT_CAPTUREX
(
   SBA_RMPOBJECT_CAPTURE,
   "{"
      "\"twRMPObjectIx\"                : \"TWORD8\","
      "\"abReserved_A\"                 : \"PAD (8)\","
      "\"twRPersonaIx\"                 : \"TWORD8\""
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMPOBJECT_RELEASEX
(
   SBA_RMPOBJECT_RELEASE,
   "{"
      "\"twRMPObjectIx\"                : \"TWORD8\","
      "\"abReserved_A\"                 : \"PAD (8)\","
      "\"twRPersonaIx\"                 : \"TWORD8\""
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMPOBJECT_BOUNDX
(
   SBA_RMPOBJECT_BOUND,
   "{"
      "\"twRMPObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      RMCOMMON_BOUND_SB
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMPOBJECT_NAMEX
(
   SBA_RMPOBJECT_NAME,
   "{"
      "\"twRMPObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      RMPOBJECT_NAME_SB
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMPOBJECT_OWNERX
(
   SBA_RMPOBJECT_OWNER,
   "{"
      "\"twRMPObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      RMCOMMON_OWNER_SB
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMPOBJECT_RESOURCEX
(
   SBA_RMPOBJECT_RESOURCE,
   "{"
      "\"twRMPObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      RMCOMMON_RESOURCE_SB
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMPOBJECT_TRANSFORMX
(
   SBA_RMPOBJECT_TRANSFORM,
   "{"
      "\"twRMPObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      RMCOMMON_TRANSFORM_SB
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMPOBJECT_TYPEX
(
   SBA_RMPOBJECT_TYPE,
   "{"
      "\"twRMPObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      RMCOMMON_TYPE_SB
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMPOBJECT_RMPOBJECT_OPENX
(
   SBA_RMPOBJECT_RMPOBJECT_OPEN,
   "{"
      "\"twRMPObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (16)\","
      RMPOBJECT_NAME_SB ","
      RMCOMMON_TYPE_SB ","
      RMCOMMON_OWNER_SB ","
      RMCOMMON_RESOURCE_SB ","
      RMCOMMON_TRANSFORM_SB ","
      RMCOMMON_BOUND_SB
   "}",
   "{"
      "\"twRMPObjectIx\"         : \"TWORD8\""
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMPOBJECT_RMPOBJECT_CLOSEX
(
   SBA_RMPOBJECT_RMPOBJECT_CLOSE,
   "{"
      "\"twRMPObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      "\"twRMPObjectIx_Close\"  : \"TWORD8\""
   "}",
   "{"
   "}",
   true
);

std::map<std::string, const RMAP::CORE::CLIENT::ACTION*> SB_RMPOBJECT::aAction =
{
   { "CAPTURE",         &SBA_RMPOBJECT_CAPTUREX          },
   { "RELEASE",         &SBA_RMPOBJECT_RELEASEX          },
   { "BOUND",           &SBA_RMPOBJECT_BOUNDX            },
   { "NAME",            &SBA_RMPOBJECT_NAMEX             },
   { "OWNER",           &SBA_RMPOBJECT_OWNERX            },
   { "RESOURCE",        &SBA_RMPOBJECT_RESOURCEX         },
   { "TRANSFORM",       &SBA_RMPOBJECT_TRANSFORMX        },
   { "TYPE",            &SBA_RMPOBJECT_TYPEX             },
   { "RMPOBJECT_OPEN",  &SBA_RMPOBJECT_RMPOBJECT_OPENX   },
   { "RMPOBJECT_CLOSE", &SBA_RMPOBJECT_RMPOBJECT_CLOSEX  },
};

SB_RMPOBJECT::SB_RMPOBJECT (RMAP::CORE::MEM::SOURCE::REFERENCE* pReference, RMAP::SVC_SB::MAP* pMap, RMAP::CORE::CLIENT* pClient) :
   RMAP::SVC_SB::SB_OBJECT (pReference, pMap, pClient)
{
   m_pImpl = new Impl ();
}

SB_RMPOBJECT::~SB_RMPOBJECT ()
{
   delete m_pImpl;
}

void SB_RMPOBJECT::init ()
{
}

SB_RMPOBJECT::FACTORY* SB_RMPOBJECT::factory ()
{
   RMAP::SVC_SB::MAP* pMap = new RMAP::SVC_SB::MAP
   (
      "{"
         RMPOBJECT_NAME_SB ","
         RMCOMMON_TYPE_SB ","
         RMCOMMON_OWNER_SB ","
         RMCOMMON_RESOURCE_SB ","
         RMCOMMON_TRANSFORM_SB ","
         RMCOMMON_ORBIT_SPIN_SB_PAD ","
         RMCOMMON_BOUND_SB ","
         RMPOBJECT_PROPERTIES_SB ","

         "\"PARTIAL\"               : \"SIZE\""
      "}"
   );

   return new FACTORY ("Statabase", "RMPObject", MAP_OBJECT_CLASS_PHYSICAL, aAction, true, pMap);
}

void SB_RMPOBJECT::Read (ordered_json& jSrc, RMAP::CORE::MODEL* pModel)
{
   RMPOBJECT* pModelSB = dynamic_cast<RMPOBJECT*> (pModel);
   MAP_OBJECT_TYPE Type;
   MAP_OBJECT_OWNER Owner;
   MAP_OBJECT_TRANSFORM Transform;
   MAP_OBJECT_BOUND Bound;
   RMAP::CORE::MEM::OBJECTHEAD* pHead = pObjectHead ();

   Type.bType     = jSrc["pType"]["bType"];
   Type.bSubtype  = jSrc["pType"]["bSubtype"];
   Type.bFiction  = jSrc["pType"]["bFiction"];

   Owner.twOwner  = jSrc["pOwner"]["twRPersonaIx"];

   Transform.d3Position[0] = jSrc["pTransform"]["vPosition"]["dX"];
   Transform.d3Position[1] = jSrc["pTransform"]["vPosition"]["dY"];
   Transform.d3Position[2] = jSrc["pTransform"]["vPosition"]["dZ"];

   Transform.d4Rotation[0] = jSrc["pTransform"]["qRotation"]["dX"];
   Transform.d4Rotation[1] = jSrc["pTransform"]["qRotation"]["dY"];
   Transform.d4Rotation[2] = jSrc["pTransform"]["qRotation"]["dZ"];
   Transform.d4Rotation[3] = jSrc["pTransform"]["qRotation"]["dW"];

   Transform.d3Scale[0]    = jSrc["pTransform"]["vScale"]["dX"];
   Transform.d3Scale[1]    = jSrc["pTransform"]["vScale"]["dY"];
   Transform.d3Scale[2]    = jSrc["pTransform"]["vScale"]["dZ"];

   Bound.d3Max[0]          = jSrc["pBound"]["dX"];
   Bound.d3Max[1]          = jSrc["pBound"]["dY"];
   Bound.d3Max[2]          = jSrc["pBound"]["dZ"];

//   Pod.nChildren = jSrc["nChildren"];

   pModelSB->Head (pHead->Parent.Class (), pHead->Parent.ObjectIx (), pHead->Self.Class (), pHead->Self.ObjectIx ());
   pModelSB->Name (RMAP::CORE::UTILS::UTF8_to_Wchar (jSrc["pName"]["wsRMCObjectId"].get<std::string> ().c_str ()));
   pModelSB->Type (Type);
   pModelSB->Owner (Owner);
   pModelSB->Resource (jSrc["pResource"]["qwResource"], jSrc["pResource"]["sName"], jSrc["pResource"]["sReference"]);
   pModelSB->Transform (Transform);
   pModelSB->Bound (Bound);
//   pModelSB->pPOD (Pod);
}

/******************************************************************************************************************************/
