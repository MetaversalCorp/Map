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
   RMCOBJECT* pModelIO = dynamic_cast<RMCOBJECT*> (pModel);
   RMCOBJECT::NAME Name (RMAP::CORE::UTILS::UTF8_to_Wchar (jSrc["pName"]["wsRMCObjectId"].get<std::string> ().c_str ()));
   TYPE Type;
   OWNER Owner;
   RESOURCE Resource (jSrc["pResource"]["qwResource"], jSrc["pResource"]["sName"], jSrc["pResource"]["sReference"]);
   TRANSFORM Transform;
   ORBIT_SPIN Orbit_Spin;
   BOUND Bound;
   RMCOBJECT::PROPERTIES Properties;
   RMCOBJECT::POD Pod;

   Type.bType     = jSrc["pType"]["bType"];
   Type.bSubtype  = jSrc["pType"]["bSubtype"];
   Type.bFiction  = jSrc["pType"]["bFiction"];
   Type.bMovable  = 0;

   Owner.twRPersonaIx = jSrc["pOwner"]["twRPersonaIx"];

   Transform.vPosition.dX     = jSrc["pTransform"]["Position"][0];
   Transform.vPosition.dY     = jSrc["pTransform"]["Position"][1];
   Transform.vPosition.dZ     = jSrc["pTransform"]["Position"][2];

   Transform.qRotation.dX     = jSrc["pTransform"]["Rotation"][0];
   Transform.qRotation.dY     = jSrc["pTransform"]["Rotation"][1];
   Transform.qRotation.dZ     = jSrc["pTransform"]["Rotation"][2];
   Transform.qRotation.dW     = jSrc["pTransform"]["Rotation"][3];

   Transform.vScale.dX        = jSrc["pTransform"]["Scale"][0];
   Transform.vScale.dY        = jSrc["pTransform"]["Scale"][1];
   Transform.vScale.dZ        = jSrc["pTransform"]["Scale"][2];

   Orbit_Spin.tmPeriod        = jSrc["pOrbit_Spin"]["tmPeriod"];
   Orbit_Spin.tmOrigin        = jSrc["pOrbit_Spin"]["tmOrigin"];
   Orbit_Spin.dA              = jSrc["pOrbit_Spin"]["dA"];
   Orbit_Spin.dB              = jSrc["pOrbit_Spin"]["dB"];

   Bound.dX                   = jSrc["pBound"]["Max"][0];
   Bound.dY                   = jSrc["pBound"]["Max"][1];
   Bound.dZ                   = jSrc["pBound"]["Max"][2];

   Properties.fMass           = jSrc["pProperties"]["fMass"];
   Properties.fGravity        = jSrc["pProperties"]["fGravity"];
   Properties.fColor          = jSrc["pProperties"]["fColor"];
   Properties.fBrightness     = jSrc["pProperties"]["fBrightness"];
   Properties.fReflectivity   = jSrc["pProperties"]["fReflectivity"];

   Pod.nChildren = jSrc["nChildren"];

   pModelIO->pName (Name);
   pModelIO->pType (Type);
   pModelIO->pOwner (Owner);
   pModelIO->pResource (Resource);
   pModelIO->pTransform (Transform);
   pModelIO->pOrbit_Spin (Orbit_Spin);
   pModelIO->pBound (Bound);
   pModelIO->pProperties (Properties);
   pModelIO->pPOD (Pod);
}

/******************************************************************************************************************************/
