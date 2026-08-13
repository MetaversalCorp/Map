/*******************************************************************************************************************************
**                                                                                                                            **
**                                      MVRP_RP1_Map_cpp : Source_SB_RMTOBJECT.cpp                                            **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2024 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

#include "pch.h"

using namespace RMAP::MAP;

/*******************************************************************************************************************************
**                                                     CLASS (Impl)                                                           **
*******************************************************************************************************************************/

class SB_RMTOBJECT::Impl
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

SB_RMTOBJECT::FACTORY::FACTORY (std::string sID_Service, std::string sID_Model, int wClass, std::map<std::string, const RMAP::CORE::CLIENT::ACTION*>& apAction, bool bIndependent, RMAP::SVC_SB::MAP* pMap) :
   RMAP::SVC_SB::SB_OBJECT::FACTORY (sID_Service, sID_Model, wClass, apAction, bIndependent, pMap)
{
}

SB_RMTOBJECT::FACTORY::~FACTORY ()
{
}

RMAP::CORE::SOURCE* SB_RMTOBJECT::FACTORY::Create (RMAP::CORE::CLIENT* pClient)
{
   return new SB_RMTOBJECT (pReference, m_pMap, pClient);
}

/*******************************************************************************************************************************
**                                                   CLASS (SB_RMTOBJECT)                                                     **
*******************************************************************************************************************************/

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMTOBJECT_CAPTUREX
(
   SBA_RMTOBJECT_CAPTURE,
   "{"
      "\"twRMTObjectIx\"                : \"TWORD8\","
      "\"abReserved_A\"                 : \"PAD (8)\","
      "\"twRPersonaIx\"                 : \"TWORD8\""
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMTOBJECT_RELEASEX
(
   SBA_RMTOBJECT_RELEASE,
   "{"
      "\"twRMTObjectIx\"                : \"TWORD8\","
      "\"abReserved_A\"                 : \"PAD (8)\","
      "\"twRPersonaIx\"                 : \"TWORD8\""
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMTOBJECT_BOUNDX
(
   SBA_RMTOBJECT_BOUND,
   "{"
      "\"twRMTObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      RMCOMMON_BOUND_SB
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMTOBJECT_NAMEX
(
   SBA_RMTOBJECT_NAME,
   "{"
      "\"twRMTObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      RMTOBJECT_NAME_SB
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMTOBJECT_OWNERX
(
   SBA_RMTOBJECT_OWNER,
   "{"
      "\"twRMTObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      RMCOMMON_OWNER_SB
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMTOBJECT_PROPERTIESX
(
   SBA_RMTOBJECT_PROPERTIES,
   "{"
      "\"twRMTObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      RMTOBJECT_PROPERTIES_SB
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMTOBJECT_RESOURCEX
(
   SBA_RMTOBJECT_RESOURCE,
   "{"
      "\"twRMTObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      RMCOMMON_RESOURCE_SB
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMTOBJECT_TRANSFORMX
(
   SBA_RMTOBJECT_TRANSFORM,
   "{"
      "\"twRMTObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      RMCOMMON_TRANSFORM_SB ","
      RMCOMMON_DCOORD_SB
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMTOBJECT_TYPEX
(
   SBA_RMTOBJECT_TYPE,
   "{"
      "\"twRMTObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      RMCOMMON_TYPE_SB
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMTOBJECT_RMTOBJECT_OPENX
(
   SBA_RMTOBJECT_RMTOBJECT_OPEN,
   "{"
      "\"twRMTObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (16)\","
      RMTOBJECT_NAME_SB ","
      RMCOMMON_TYPE_SB ","
      RMCOMMON_OWNER_SB ","
      RMCOMMON_RESOURCE_SB ","
      RMCOMMON_TRANSFORM_SB ","
      RMCOMMON_BOUND_SB ","
      RMTOBJECT_PROPERTIES_SB ","
      RMCOMMON_DCOORD_SB
   "}",
   "{"
      "\"twRMTObjectIx\"         : \"TWORD8\""
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMTOBJECT_RMTOBJECT_CLOSEX
(
   SBA_RMTOBJECT_RMTOBJECT_CLOSE,
   "{"
      "\"twRMTObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      "\"twRMTObjectIx_Close\"  : \"TWORD8\""
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMTOBJECT_RMPOBJECT_OPENX
(
   SBA_RMTOBJECT_RMPOBJECT_OPEN,
   "{"
      "\"twRMTObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (16)\","
      RMTOBJECT_NAME_SB ","
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

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMTOBJECT_RMPOBJECT_CLOSEX
(
   SBA_RMTOBJECT_RMPOBJECT_CLOSE,
   "{"
      "\"twRMTObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      "\"twRMPObjectIx\"        : \"TWORD8\""
   "}",
   "{"
   "}",
   true
);

std::map<std::string, const RMAP::CORE::CLIENT::ACTION*> SB_RMTOBJECT::aAction =
{
   { "CAPTURE",         &SBA_RMTOBJECT_CAPTUREX          },
   { "RELEASE",         &SBA_RMTOBJECT_RELEASEX          },
   { "BOUND",           &SBA_RMTOBJECT_BOUNDX            },
   { "NAME",            &SBA_RMTOBJECT_NAMEX             },
   { "OWNER",           &SBA_RMTOBJECT_OWNERX            },
   { "PROPERTIES",      &SBA_RMTOBJECT_PROPERTIESX       },
   { "RESOURCE",        &SBA_RMTOBJECT_RESOURCEX         },
   { "TRANSFORM",       &SBA_RMTOBJECT_TRANSFORMX        },
   { "TYPE",            &SBA_RMTOBJECT_TYPEX             },
   { "RMTOBJECT_CLOSE", &SBA_RMTOBJECT_RMTOBJECT_CLOSEX  },
   { "RMTOBJECT_OPEN",  &SBA_RMTOBJECT_RMTOBJECT_OPENX   },
   { "RMTOBJECT_OPEN",  &SBA_RMTOBJECT_RMTOBJECT_OPENX   },
   { "RMTOBJECT_CLOSE", &SBA_RMTOBJECT_RMTOBJECT_CLOSEX  },
};

SB_RMTOBJECT::SB_RMTOBJECT (RMAP::CORE::MEM::SOURCE::REFERENCE* pReference, RMAP::SVC_SB::MAP* pMap, RMAP::CORE::CLIENT* pClient) :
   RMAP::SVC_SB::SB_OBJECT (pReference, pMap, pClient)
{
   m_pImpl = new Impl ();
}

SB_RMTOBJECT::~SB_RMTOBJECT ()
{
   delete m_pImpl;
}

void SB_RMTOBJECT::init ()
{
}

SB_RMTOBJECT::FACTORY* SB_RMTOBJECT::factory ()
{
   RMAP::SVC_SB::MAP* pMap = new RMAP::SVC_SB::MAP
   (
      "{"
         RMTOBJECT_NAME_SB ","
         RMCOMMON_TYPE_SB ","
         RMCOMMON_OWNER_SB ","
         RMCOMMON_RESOURCE_SB ","
         RMCOMMON_TRANSFORM_SB ","
         RMCOMMON_ORBIT_SPIN_SB_PAD ","
         RMCOMMON_BOUND_SB ","
         RMTOBJECT_PROPERTIES_SB ","

         "\"PARTIAL\"               : \"SIZE\","

         "\"abReserved_A\"   : \"PAD (128)\""
      "}"
   );

   return new FACTORY ("Statabase", "RMTObject", MAP_OBJECT_CLASS_TERRESTRIAL, aAction, true, pMap);
}

void SB_RMTOBJECT::Read (ordered_json& jSrc, RMAP::CORE::MODEL* pModel)
{
   RMTOBJECT* pModelSB = dynamic_cast<RMTOBJECT*> (pModel);
   MAP_OBJECT_TYPE Type;
   MAP_OBJECT_OWNER Owner;
   MAP_OBJECT_TRANSFORM Transform;
   MAP_OBJECT_BOUND Bound;
   MAP_OBJECT_PROPERTIES_TERRESTIAL Properties;
   //   uint32_t nChildren;
   RMAP::CORE::MEM::OBJECTHEAD* pHead = pObjectHead ();

   Type.bType     = jSrc["pType"]["bType"];
   Type.bSubtype  = jSrc["pType"]["bSubtype"];
   Type.bFiction  = jSrc["pType"]["bFiction"];

   Owner.twOwner = jSrc["pOwner"]["twRPersonaIx"];

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

   Properties.bAdult          = jSrc["pProperties"]["bAdult"];
   Properties.bAvatar         = jSrc["pProperties"]["bAvatar"];
   Properties.bLockToGround   = jSrc["pProperties"]["bLockToGround"];
   Properties.bYouth          = jSrc["pProperties"]["bYouth"];

//   Pod.nChildren = jSrc["nChildren"];

   pModelSB->Head (pHead->Parent.Class (), pHead->Parent.ObjectIx (), pHead->Self.Class (), pHead->Self.ObjectIx ());
   pModelSB->Name (RMAP::CORE::UTILS::UTF8_to_Wchar (jSrc["pName"]["wsRMTObjectId"].get<std::string> ().c_str ()));
   pModelSB->Type (Type);
   pModelSB->Owner (Owner);
   pModelSB->Resource (jSrc["pResource"]["qwResource"], jSrc["pResource"]["sName"], jSrc["pResource"]["sReference"]);
   pModelSB->Transform (Transform);
   pModelSB->Bound (Bound);
   pModelSB->Properties (Properties);
//   pModelSB->Children (nChildren);
}

/******************************************************************************************************************************/
