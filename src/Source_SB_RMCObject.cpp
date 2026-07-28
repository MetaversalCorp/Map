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

   return new FACTORY ("MVSB", "RMCObject", SBO_CLASS_RMCOBJECT, aAction, true, pMap);
}

void SB_RMCOBJECT::Read (ordered_json& jSrc, RMAP::CORE::MODEL* pModel)
{
   RMCOBJECT* pModelSB = dynamic_cast<RMCOBJECT*> (pModel);
   RMCOBJECT::NAME Name (RMAP::CORE::UTILS::UTF8_to_Wchar (jSrc["pName"]["wsRMCObjectId"].get<std::string> ().c_str ()));
   RMCOMMON::TYPE Type;
   RMCOMMON::OWNER Owner;
   RMCOMMON::RESOURCE Resource (jSrc["pResource"]["qwResource"], jSrc["pResource"]["sName"], jSrc["pResource"]["sReference"]);
   RMCOMMON::TRANSFORM Transform;
   RMCOMMON::ORBIT_SPIN Orbit_Spin;
   RMCOMMON::BOUND Bound;
   RMCOBJECT::PROPERTIES Properties;
//   RMCOBJECT::POD Pod;

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

   Orbit_Spin.tmPeriod     = jSrc["pOrbit_Spin"]["tmPeriod"];
   Orbit_Spin.tmOrigin     = jSrc["pOrbit_Spin"]["tmOrigin"];
   Orbit_Spin.dA           = jSrc["pOrbit_Spin"]["dA"];
   Orbit_Spin.dB           = jSrc["pOrbit_Spin"]["dB"];

   Bound.dX                = jSrc["pBound"]["dX"];
   Bound.dY                = jSrc["pBound"]["dY"];
   Bound.dZ                = jSrc["pBound"]["dZ"];

   Properties.fMass         = jSrc["pProperties"]["fMass"];
   Properties.fGravity      = jSrc["pProperties"]["fGravity"];
   Properties.fColor        = jSrc["pProperties"]["fColor"];
   Properties.fBrightness   = jSrc["pProperties"]["fBrightness"];
   Properties.fReflectivity = jSrc["pProperties"]["fReflectivity"];

//   Pod.nChildren = jSrc["nChildren"];

   pModelSB->pName (Name);
   pModelSB->pType (Type);
   pModelSB->pOwner (Owner);
   pModelSB->pResource (Resource);
   pModelSB->pTransform (Transform);
   pModelSB->pOrbit_Spin (Orbit_Spin);
   pModelSB->pBound (Bound);
   pModelSB->pProperties (Properties);
//   pModelSB->pPOD (Pod);
}

/******************************************************************************************************************************/
