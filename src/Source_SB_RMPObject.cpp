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

   return new FACTORY ("MVSB", "RMPObject", SBO_CLASS_RMPOBJECT, aAction, true, pMap);
}

void SB_RMPOBJECT::Read (ordered_json& jSrc, RMAP::CORE::MODEL* pModel)
{
   RMPOBJECT* pModelSB = dynamic_cast<RMPOBJECT*> (pModel);
   RMPOBJECT::NAME Name (RMAP::CORE::UTILS::UTF8_to_Wchar (jSrc["pName"]["wsRMCObjectId"].get<std::string> ().c_str ()));
   RMCOMMON::TYPE Type;
   RMCOMMON::OWNER Owner;
   RMCOMMON::RESOURCE Resource (jSrc["pResource"]["qwResource"], jSrc["pResource"]["sName"], jSrc["pResource"]["sReference"]);
   RMCOMMON::TRANSFORM Transform;
   RMCOMMON::BOUND Bound;
//   RMPOBJECT::POD Pod;

   Type.bType     = jSrc["pType"]["bType"];
   Type.bSubtype  = jSrc["pType"]["bSubtype"];
   Type.bFiction  = jSrc["pType"]["bFiction"];
   Type.bMovable  = 0;

   Owner.twRPersonaIx = jSrc["pOwner"]["twRPersonaIx"];

   Transform.vPosition.dX  = jSrc["pTransform"]["vPosition"]["dX"];
   Transform.vPosition.dY  = jSrc["pTransform"]["vPosition"]["dY"];
   Transform.vPosition.dZ  = jSrc["pTransform"]["vPosition"]["dZ"];

   Transform.qRotation.dX  = jSrc["pTransform"]["qRotation"]["dX"];
   Transform.qRotation.dY  = jSrc["pTransform"]["qRotation"]["dY"];
   Transform.qRotation.dZ  = jSrc["pTransform"]["qRotation"]["dZ"];
   Transform.qRotation.dW  = jSrc["pTransform"]["qRotation"]["dW"];

   Transform.vScale.dX     = jSrc["pTransform"]["vScale"]["dX"];
   Transform.vScale.dY     = jSrc["pTransform"]["vScale"]["dY"];
   Transform.vScale.dZ     = jSrc["pTransform"]["vScale"]["dZ"];

   Bound.dX                = jSrc["pBound"]["dX"];
   Bound.dY                = jSrc["pBound"]["dY"];
   Bound.dZ                = jSrc["pBound"]["dZ"];

//   Pod.nChildren = jSrc["nChildren"];

   pModelSB->pName (Name);
   pModelSB->pType (Type);
   pModelSB->pOwner (Owner);
   pModelSB->pResource (Resource);
   pModelSB->pTransform (Transform);
   pModelSB->pBound (Bound);
//   pModelSB->pPOD (Pod);
}

/******************************************************************************************************************************/
