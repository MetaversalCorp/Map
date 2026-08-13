/*******************************************************************************************************************************
**                                                                                                                            **
**                                      MVRP_RP1_Map_cpp : Source_SB_RMCOBJECT.cpp                                            **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2024 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

#include "pch.h"

using namespace RMAP::MAP;

/*******************************************************************************************************************************
**                                                     CLASS (Impl)                                                           **
*******************************************************************************************************************************/

class SB_RMCOBJECT::Impl
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

SB_RMCOBJECT::FACTORY::FACTORY (std::string sID_Service, std::string sID_Model, int wClass, std::map<std::string, const RMAP::CORE::CLIENT::ACTION*>& apAction, bool bIndependent, RMAP::SVC_SB::MAP* pMap) :
   RMAP::SVC_SB::SB_OBJECT::FACTORY (sID_Service, sID_Model, wClass, apAction, bIndependent, pMap)
{
}

SB_RMCOBJECT::FACTORY::~FACTORY ()
{
}

RMAP::CORE::SOURCE* SB_RMCOBJECT::FACTORY::Create (RMAP::CORE::CLIENT* pClient)
{
   return new SB_RMCOBJECT (pReference, m_pMap, pClient);
}

/*******************************************************************************************************************************
**                                                   CLASS (SB_RMCOBJECT)                                                     **
*******************************************************************************************************************************/

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMCOBJECT_CAPTUREX
(
   SBA_RMCOBJECT_CAPTURE,
   "{"
      "\"twRMCObjectIx\"                : \"TWORD8\","
      "\"abReserved_A\"                 : \"PAD (8)\","
      "\"twRPersonaIx\"                 : \"TWORD8\""
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMCOBJECT_RELEASEX
(
   SBA_RMCOBJECT_RELEASE,
   "{"
      "\"twRMCObjectIx\"                : \"TWORD8\","
      "\"abReserved_A\"                 : \"PAD (8)\","
      "\"twRPersonaIx\"                 : \"TWORD8\""
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMCOBJECT_BOUNDX
(
   SBA_RMCOBJECT_BOUND,
   "{"
      "\"twRMCObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      RMCOMMON_BOUND_SB
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMCOBJECT_NAMEX
(
   SBA_RMCOBJECT_NAME,
   "{"
      "\"twRMCObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      RMCOBJECT_NAME_SB
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMCOBJECT_ORBITX
(
   SBA_RMCOBJECT_ORBIT,
   "{"
      "\"twRMCObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      RMCOMMON_ORBIT_SPIN_SB
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMCOBJECT_OWNERX
(
   SBA_RMCOBJECT_OWNER,
   "{"
      "\"twRMCObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      RMCOMMON_OWNER_SB
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMCOBJECT_PROPERTIESX
(
   SBA_RMCOBJECT_PROPERTIES,
   "{"
      "\"twRMCObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      RMCOBJECT_PROPERTIES_SB
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMCOBJECT_RESOURCEX
(
   SBA_RMCOBJECT_RESOURCE,
   "{"
      "\"twRMCObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      RMCOMMON_RESOURCE_SB
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMCOBJECT_RMCOBJECT_CLOSEX
(
   SBA_RMCOBJECT_RMCOBJECT_CLOSE,
   "{"
      "\"twRMCObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      "\"twRMCObjectIx_Close\"  : \"TWORD8\""
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMCOBJECT_RMCOBJECT_OPENX
(
   SBA_RMCOBJECT_RMCOBJECT_OPEN,
   "{"
      "\"twRMCObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (16)\","
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

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMCOBJECT_RMTOBJECT_OPENX
(
   SBA_RMCOBJECT_RMTOBJECT_OPEN,
   "{"
      "\"twRMCObjectIx\"        : \"TWORD8\","
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
      "\"twRMtObjectIx\"         : \"TWORD8\""
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMCOBJECT_RMTOBJECT_CLOSEX
(
   SBA_RMCOBJECT_RMTOBJECT_CLOSE,
   "{"
      "\"twRMCObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      "\"twRMTObjectIx_Close\"  : \"TWORD8\""
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMCOBJECT_SPINX
(
   SBA_RMCOBJECT_SPIN,
   "{"
      "\"twRMCObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      RMCOMMON_ORBIT_SPIN_SB
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMCOBJECT_TRANSFORMX
(
   SBA_RMCOBJECT_TRANSFORM,
   "{"
      "\"twRMCObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      RMCOMMON_TRANSFORM_SB ","
      RMCOMMON_DCOORD_SB
   "}",
   "{"
   "}",
   true
);

static const RMAP::SVC_SB::CLIENT::ACTION SBA_RMCOBJECT_TYPEX
(
   SBA_RMCOBJECT_TYPE,
   "{"
      "\"twRMCObjectIx\"        : \"TWORD8\","
      "\"abReserved_A\"         : \"PAD (8)\","
      RMCOMMON_TYPE_SB
   "}",
   "{"
   "}",
   true
);

std::map<std::string, const RMAP::CORE::CLIENT::ACTION*> SB_RMCOBJECT::aAction =
{
   { "CAPTURE",         &SBA_RMCOBJECT_CAPTUREX          },
   { "RELEASE",         &SBA_RMCOBJECT_RELEASEX          },
   { "BOUND",           &SBA_RMCOBJECT_BOUNDX            },
   { "NAME",            &SBA_RMCOBJECT_NAMEX             },
   { "ORBIT",           &SBA_RMCOBJECT_ORBITX            },
   { "OWNER",           &SBA_RMCOBJECT_OWNERX            },
   { "PROPERTIES",      &SBA_RMCOBJECT_PROPERTIESX       },
   { "RESOURCE",        &SBA_RMCOBJECT_RESOURCEX         },
   { "RMCOBJECT_CLOSE", &SBA_RMCOBJECT_RMCOBJECT_CLOSEX  },
   { "RMCOBJECT_OPEN",  &SBA_RMCOBJECT_RMCOBJECT_OPENX   },
   { "RMTOBJECT_OPEN",  &SBA_RMCOBJECT_RMTOBJECT_OPENX   },
   { "RMTOBJECT_CLOSE", &SBA_RMCOBJECT_RMTOBJECT_CLOSEX  },
   { "SPIN",            &SBA_RMCOBJECT_SPINX             },
   { "TRANSFORM",       &SBA_RMCOBJECT_TRANSFORMX        },
   { "TYPE",            &SBA_RMCOBJECT_TYPEX             },
};

SB_RMCOBJECT::SB_RMCOBJECT (RMAP::CORE::MEM::SOURCE::REFERENCE* pReference, RMAP::SVC_SB::MAP* pMap, RMAP::CORE::CLIENT* pClient) :
   RMAP::SVC_SB::SB_OBJECT (pReference, pMap, pClient)
{
   m_pImpl = new Impl ();
}

SB_RMCOBJECT::~SB_RMCOBJECT ()
{
   delete m_pImpl;
}

void SB_RMCOBJECT::init ()
{
}

SB_RMCOBJECT::FACTORY* SB_RMCOBJECT::factory ()
{
   RMAP::SVC_SB::MAP* pMap = new RMAP::SVC_SB::MAP
   (
      "{"
         RMCOBJECT_NAME_SB ","
         RMCOMMON_TYPE_SB ","
         RMCOMMON_OWNER_SB ","
         RMCOMMON_RESOURCE_SB ","
         RMCOMMON_TRANSFORM_SB ","
         RMCOMMON_ORBIT_SPIN_SB ","
         RMCOMMON_BOUND_SB ","
         RMCOBJECT_PROPERTIES_SB ","

         "\"PARTIAL\"               : \"SIZE\","

         "\"abReserved_A\"   : \"PAD (56)\""
      "}"
   );

   return new FACTORY ("Statabase", "RMCObject", MAP_OBJECT_CLASS_CELESTIAL, aAction, true, pMap);
}

void SB_RMCOBJECT::Read (ordered_json& jSrc, RMAP::CORE::MODEL* pModel)
{
   RMCOBJECT* pModelSB = dynamic_cast<RMCOBJECT*> (pModel);
   MAP_OBJECT_TYPE Type;
   MAP_OBJECT_OWNER Owner;
   MAP_OBJECT_TRANSFORM Transform;
   MAP_OBJECT_ORBIT_CELESTIAL Orbit_Spin;
   MAP_OBJECT_BOUND Bound;
   MAP_OBJECT_PROPERTIES_CELESTIAL Properties;
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

   Orbit_Spin.tmPeriod     = jSrc["pOrbit_Spin"]["tmPeriod"];
   Orbit_Spin.tmOrigin     = jSrc["pOrbit_Spin"]["tmOrigin"];
   Orbit_Spin.dA           = jSrc["pOrbit_Spin"]["dA"];
   Orbit_Spin.dB           = jSrc["pOrbit_Spin"]["dB"];

   Bound.d3Max[0]          = jSrc["pBound"]["dX"];
   Bound.d3Max[1]          = jSrc["pBound"]["dY"];
   Bound.d3Max[2]          = jSrc["pBound"]["dZ"];

   Properties.fMass         = jSrc["pProperties"]["fMass"];
   Properties.fGravity      = jSrc["pProperties"]["fGravity"];
   Properties.fColor        = jSrc["pProperties"]["fColor"];
   Properties.fBrightness   = jSrc["pProperties"]["fBrightness"];
   Properties.fReflectivity = jSrc["pProperties"]["fReflectivity"];

//   nChildren = jSrc["nChildren"];

   pModelSB->m_wClass      = pHead->Self.Class ();
   pModelSB->m_twObjectIx  = pHead->Self.ObjectIx ();
   pModelSB->Name (RMAP::CORE::UTILS::UTF8_to_Wchar (jSrc["pName"]["wsRMCObjectId"].get<std::string> ().c_str ()));
   pModelSB->Type (Type);
   pModelSB->Owner (Owner);
   pModelSB->Resource (jSrc["pResource"]["qwResource"], jSrc["pResource"]["sName"], jSrc["pResource"]["sReference"]);
   pModelSB->Transform (Transform);
   pModelSB->Orbit_Spin (Orbit_Spin);
   pModelSB->Bound (Bound);
   pModelSB->Properties (Properties);
//   pModelSB->Children (nChildren);
}

/******************************************************************************************************************************/
