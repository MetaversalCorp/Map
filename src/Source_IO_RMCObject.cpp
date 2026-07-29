/*******************************************************************************************************************************
**                                                                                                                            **
**                                      MVRP_RP1_Map_cpp : Source_IO_RMCObject.cpp                                            **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2024 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

#include "pch.h"

using namespace RMAP::MAP;

/*******************************************************************************************************************************
**                                                     CLASS (Impl)                                                           **
*******************************************************************************************************************************/

class IO_RMCOBJECT::Impl : public RMAP::CORE::IRESPONSE
{
public:
   Impl (IO_RMCOBJECT* pRMCObject) :
      m_pRMCObject (pRMCObject)
   {
   }

   ~Impl ()
   {
   }

   void onResponse (RMAP::CORE::CLIENT::IACTION* pIAction, int nType, intptr_t pParam) override
   {
      m_pRMCObject->Response (pIAction);
   }

private:
   IO_RMCOBJECT*         m_pRMCObject;
};

/*******************************************************************************************************************************
**                                                     CLASS (FACTORY)                                                      **
*******************************************************************************************************************************/

IO_RMCOBJECT::FACTORY::FACTORY (std::string sID_Service, std::string sID_Model, int wClass, std::map<std::string, const RMAP::CORE::CLIENT::ACTION*>& apAction, bool bIndependent) :
   RMAP::SVC_SOCKETIO::IO_OBJECT::FACTORY (sID_Service, sID_Model, wClass, apAction, bIndependent)
{
}

IO_RMCOBJECT::FACTORY::~FACTORY ()
{
}

RMAP::CORE::SOURCE* IO_RMCOBJECT::FACTORY::Create (RMAP::CORE::CLIENT* pClient)
{
   return new IO_RMCOBJECT (pReference, pClient);
}

/*******************************************************************************************************************************
**                                                   Convert                                                                  **
*******************************************************************************************************************************/

void Convert_RMCOBJECT_BOUNDX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMCObjectIx"] = jRequest_In["twRMCObjectIx"];

   Convert_RMCOMMON_BOUND (jRequest_Out, jRequest_In);
}

void Convert_RMCOBJECT_NAMEX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMCObjectIx"] = jRequest_In["twRMCObjectIx"];

   Convert_RMCOBJECT_NAME (jRequest_Out, jRequest_In);
}

void Convert_RMCOBJECT_ORBIT_SPINX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMCObjectIx"] = jRequest_In["twRMCObjectIx"];

   Convert_RMCOMMON_ORBIT_SPIN (jRequest_Out, jRequest_In);
}

void Convert_RMCOBJECT_OWNERX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMCObjectIx"] = jRequest_In["twRMCObjectIx"];

   Convert_RMCOMMON_OWNER (jRequest_Out, jRequest_In);
}

void Convert_RMCOBJECT_PROPERTIESX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMCObjectIx"] = jRequest_In["twRMCObjectIx"];

   Convert_RMCOBJECT_PROPERTIES (jRequest_Out, jRequest_In);
}

void Convert_RMCOBJECT_RESOURCEX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMCObjectIx"] = jRequest_In["twRMCObjectIx"];

   Convert_RMCOMMON_RESOURCE (jRequest_Out, jRequest_In);
}

void Convert_RMCOBJECT_RMCOBJECT_OPENX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMCObjectIx"] = jRequest_In["twRMCObjectIx"];

   Convert_RMCOBJECT_NAME (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_TYPE (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_OWNER (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_RESOURCE (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_TRANSFORM (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_ORBIT_SPIN (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_BOUND (jRequest_Out, jRequest_In);
   Convert_RMCOBJECT_PROPERTIES (jRequest_Out, jRequest_In);
}

void Convert_RMCOBJECT_RMTOBJECT_OPENX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMCObjectIx"] = jRequest_In["twRMCObjectIx"];

   Convert_RMTOBJECT_NAME (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_TYPE (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_OWNER (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_RESOURCE (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_TRANSFORM (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_BOUND (jRequest_Out, jRequest_In);
   Convert_RMTOBJECT_PROPERTIES (jRequest_Out, jRequest_In);
   Convert_DCOORD (jRequest_Out, jRequest_In);
}

void Convert_RMCOBJECT_TRANSFORMX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMCObjectIx"] = jRequest_In["twRMCObjectIx"];

   Convert_RMCOMMON_TRANSFORM (jRequest_Out, jRequest_In);
   Convert_DCOORD (jRequest_Out, jRequest_In);
}

void Convert_RMCOBJECT_TYPEX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMCObjectIx"] = jRequest_In["twRMCObjectIx"];

   Convert_RMCOMMON_TYPE (jRequest_Out, jRequest_In);
}

/*******************************************************************************************************************************
**                                                   CLASS (IO_RMCOBJECT)                                                     **
*******************************************************************************************************************************/

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMCOBJECT_UPDATEX
(
   "RMCObject:update",
   "{"
      "\"twRMCObjectIx\"                     : 0"
   "}",
   NULL
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMCOBJECT_SEARCHX
(
   "RMCObject:search",
   "{"
      "\"twRMCObjectIx\"                     : 0,"
      "\"dX\"                                : 0,"
      "\"dY\"                                : 0,"
      "\"dZ\"                                : 0,"
      "\"sText\"                             : \"\""
   "}",
   NULL
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMCOBJECT_INFOX
(
   "RMCObject:info",
   "{"
      "\"twRMCObjectIx\"                     : 0,"
      "\"sType\"                             : \"\""
   "}",
   NULL
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMCOBJECT_BOUNDX
(
   "RMCObject:bound",
   "{"
      "\"twRMCObjectIx\"                     : 0,"
      "\"pBound\"                            :"
      "{"
         "\"dX\"                             : 0," 
         "\"dY\"                             : 0," 
         "\"dZ\"                             : 0"
      "}"
   "}",
   Convert_RMCOBJECT_BOUNDX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMCOBJECT_NAMEX
(
   "RMCObject:name",
   "{"
      "\"twRMCObjectIx\"                     : 0,"
      "\"pName\"                             :"
      "{"
         "\"wsRMCObjectId\"                  : \"\""
      "}"
   "}",
   Convert_RMCOBJECT_NAMEX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMCOBJECT_ORBIT_SPINX
(
   "RMCObject:orbit_spin",
   "{"
      "\"twRMCObjectIx\"                     : 0,"
      "\"pOrbit_Spin\"                       :"
      "{"
         "\"tmPeriod\"                       : 0,"
         "\"tmOrigin\"                       : 0,"
         "\"dA\"                             : 0,"
         "\"dB\"                             : 0"
      "}"
   "}",
   Convert_RMCOBJECT_ORBIT_SPINX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMCOBJECT_OWNERX
(
   "RMCObject:owner",
   "{"
      "\"twRMCObjectIx\"                     : 0,"
      "\"pOwner\"                            :"
      "{"
         "\"twRPersonaIx\"                   : 0"
      "}"
   "}",
   Convert_RMCOBJECT_OWNERX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMCOBJECT_PROPERTIESX
(
   "RMCObject:properties",
   "{"
      "\"twRMCObjectIx\"                     : 0,"
      "\"pProperties\"                       :"
      "{"
         "\"fMass\"                          : 0.0,"
         "\"fGravity\"                       : 0.0,"
         "\"fColor\"                         : 0.0,"
         "\"fBrightness\"                    : 0.0,"
         "\"fReflectivity\"                  : 0.0"
      "}"
   "}",
   Convert_RMCOBJECT_PROPERTIESX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMCOBJECT_RESOURCEX
(
   "RMCObject:resource",
   "{"
      "\"twRMCObjectIx\"                     : 0,"
      "\"pResource\"                         :"
      "{"
         "\"qwResource\"                     : 0,"
         "\"sName\"                          : \"\","
         "\"sReference\"                     : \"\""
      "}"
   "}",
   Convert_RMCOBJECT_RESOURCEX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMCOBJECT_RMCOBJECT_OPENX
(
   "RMCObject:rmcobject_open",
   "{"
      "\"twRMCObjectIx\"                     : 0,"
      "\"pName\"                             :"
      "{"
         "\"wsRMCObjectId\"                  : \"\""
      "},"
      "\"pType\"                             :"
      "{"
         "\"bType\"                          : 0,"
         "\"bSubtype\"                       : 0,"
         "\"bFiction\"                       : 0,"
         "\"bMovable\"                       : 0"
      "},"
      "\"pOwner\"                            :"
      "{"
         "\"twRPersonaIx\"                   : 0"
      "},"
      "\"pResource\"                         :"
      "{"
         "\"qwResource\"                     : 0,"
         "\"sName\"                          : \"\","
         "\"sReference\"                     : \"\""
      "},"
      "\"pTransform\"                        :"
      "{"
         "\"vPosition\"                      : { \"dX\": 0, \"dY\": 0, \"dZ\": 0             },"
         "\"qRotation\"                      : { \"dX\": 0, \"dY\": 0, \"dZ\": 0, \"dW\": 0  },"
         "\"vScale\"                         : { \"dX\": 0, \"dY\": 0, \"dZ\": 0             }"
      "},"
      "\"pOrbit_Spin\"                       :"
      "{"
         "\"tmPeriod\"                       : 0,"
         "\"tmOrigin\"                       : 0,"
         "\"dA\"                             : 0,"
         "\"dB\"                             : 0"
      "},"
      "\"pBound\"                            :"
      "{"
         "\"dX\"                             : 0," 
         "\"dY\"                             : 0," 
         "\"dZ\"                             : 0"
      "},"
      "\"pProperties\"                       :"
      "{"
         "\"fMass\"                          : 0.0,"
         "\"fGravity\"                       : 0.0,"
         "\"fColor\"                         : 0.0,"
         "\"fBrightness\"                    : 0.0,"
         "\"fReflectivity\"                  : 0.0"
      "}"
   "}",
   Convert_RMCOBJECT_RMCOBJECT_OPENX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMCOBJECT_RMCOBJECT_CLOSEX
(
   "RMCObject:rmcobject_close",
   "{"
      "\"twRMCObjectIx\"                     : 0,"
      "\"twRMCObjectIx_Close\"               : 0,"
      "\"bDeleteAll\"                        : 0"
   "}",
   NULL
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMCOBJECT_RMTOBJECT_OPENX
(
   "RMCObject:rmtobject_open",
   "{"
      "\"twRMCObjectIx\"                     : 0,"
      "\"pName\"                             :"
      "{"
         "\"wsRMTObjectId\"                  : \"\""
      "},"
      "\"pType\"                             :"
      "{"
         "\"bType\"                          : 0,"
         "\"bSubtype\"                       : 0,"
         "\"bFiction\"                       : 0,"
         "\"bMovable\"                       : 0"
      "},"
      "\"pOwner\"                            :"
      "{"
         "\"twRPersonaIx\"                   : 0"
      "},"
      "\"pResource\"                         :"
      "{"
         "\"qwResource\"                     : 0,"
         "\"sName\"                          : \"\","
         "\"sReference\"                     : \"\""
      "},"
      "\"pTransform\"                        :"
      "{"
         "\"vPosition\"                      : { \"dX\": 0, \"dY\": 0, \"dZ\": 0             },"
         "\"qRotation\"                      : { \"dX\": 0, \"dY\": 0, \"dZ\": 0, \"dW\": 0  },"
         "\"vScale\"                         : { \"dX\": 0, \"dY\": 0, \"dZ\": 0             }"
      "},"
      "\"pBound\"                            :"
      "{"
         "\"dX\"                             : 0," 
         "\"dY\"                             : 0," 
         "\"dZ\"                             : 0"
      "},"
      "\"pProperties\"                       :"
      "{"
         "\"bLockToGround\"                  : 0.0,"
         "\"bYouth\"                         : 0.0,"
         "\"bAdult\"                         : 0.0,"
         "\"bAvatar\"                        : 0.0"
      "},"
      "\"pCoord\"                            :"
      "{"
         "\"bCoord\"                         : 0,"
         "\"dA\"                             : 0,"
         "\"dB\"                             : 0,"
         "\"dC\"                             : 0"
      "}"
   "}",
   Convert_RMCOBJECT_RMTOBJECT_OPENX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMCOBJECT_RMTOBJECT_CLOSEX
(
   "RMCObject:rmtobject_close",
   "{"
      "\"twRMCObjectIx\"                     : 0,"
      "\"twRMTObjectIx_Close\"               : 0,"
      "\"bDeleteAll\"                        : 0"
   "}",
   NULL
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMCOBJECT_TRANSFORMX
(
   "RMCObject:transform",
   "{"
      "\"twRMCObjectIx\"                     : 0,"
      "\"pTransform\"                        :"
      "{"
         "\"vPosition\"                      : { \"dX\": 0, \"dY\": 0, \"dZ\": 0             },"
         "\"qRotation\"                      : { \"dX\": 0, \"dY\": 0, \"dZ\": 0, \"dW\": 0  },"
         "\"vScale\"                         : { \"dX\": 0, \"dY\": 0, \"dZ\": 0             }"
      "},"
      "\"pCoord\"                            :"
      "{"
         "\"bCoord\"                         : 0,"
         "\"dA\"                             : 0,"
         "\"dB\"                             : 0,"
         "\"dC\"                             : 0"
      "}"
   "}",
   Convert_RMCOBJECT_TRANSFORMX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMCOBJECT_TYPEX
(
   "RMCObject:",
   "{"
      "\"twRMCObjectIx\"                     : 0,"
      "\"pType\"                             :"
      "{"
         "\"bType\"                          : 0,"
         "\"bSubtype\"                       : 0,"
         "\"bFiction\"                       : 0,"
         "\"bMovable\"                       : 0"
      "}"
   "}",
   Convert_RMCOBJECT_TYPEX
);


std::map<std::string, const RMAP::CORE::CLIENT::ACTION*> IO_RMCOBJECT::aAction =
{
   { "UPDATE",             &IO_RMCOBJECT_UPDATEX            },
   { "SEARCH",             &IO_RMCOBJECT_SEARCHX            },
   { "INFO",               &IO_RMCOBJECT_INFOX              },
   { "BOUND",              &IO_RMCOBJECT_BOUNDX             },
   { "NAME",               &IO_RMCOBJECT_NAMEX              },
   { "ORBIT_SPIN",         &IO_RMCOBJECT_ORBIT_SPINX        },
   { "OWNER",              &IO_RMCOBJECT_OWNERX             },
   { "PROPERTIES",         &IO_RMCOBJECT_PROPERTIESX        },
   { "RESOURCE",           &IO_RMCOBJECT_RESOURCEX          },
   { "RMCOBJECT_OPEN",     &IO_RMCOBJECT_RMCOBJECT_OPENX    },
   { "RMCOBJECT_CLOSE",    &IO_RMCOBJECT_RMCOBJECT_CLOSEX   },
   { "RMTOBJECT_OPEN",     &IO_RMCOBJECT_RMTOBJECT_OPENX    },
   { "RMTOBJECT_CLOSE",    &IO_RMCOBJECT_RMTOBJECT_CLOSEX   },
   { "TRANSFORM",          &IO_RMCOBJECT_TRANSFORMX         },
   { "TYPE",               &IO_RMCOBJECT_TYPEX              },
};

IO_RMCOBJECT::IO_RMCOBJECT (RMAP::CORE::MEM::SOURCE::REFERENCE* pReference, RMAP::CORE::CLIENT* pClient) :
   IO_OBJECT (pReference, pClient),
   m_pImpl (new Impl (this))
{
}

IO_RMCOBJECT::~IO_RMCOBJECT ()
{
   delete m_pImpl;
}

void IO_RMCOBJECT::init ()
{
}

IO_RMCOBJECT::FACTORY* IO_RMCOBJECT::factory ()
{
   return new FACTORY ("MVIO", "RMCObject", SBO_CLASS_RMCOBJECT, aAction, true);
}

void IO_RMCOBJECT::Read (ordered_json& jSrc, RMAP::CORE::MODEL* pModel)
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

   Transform.vPosition.dX  = jSrc["pTransform"]["Position"][0];
   Transform.vPosition.dY  = jSrc["pTransform"]["Position"][1];
   Transform.vPosition.dZ  = jSrc["pTransform"]["Position"][2];

   Transform.qRotation.dX  = jSrc["pTransform"]["Rotation"][0];
   Transform.qRotation.dY  = jSrc["pTransform"]["Rotation"][1];
   Transform.qRotation.dZ  = jSrc["pTransform"]["Rotation"][2];
   Transform.qRotation.dW  = jSrc["pTransform"]["Rotation"][3];

   Transform.vScale.dX     = jSrc["pTransform"]["Scale"][0];
   Transform.vScale.dY     = jSrc["pTransform"]["Scale"][1];
   Transform.vScale.dZ     = jSrc["pTransform"]["Scale"][2];

   Orbit_Spin.tmPeriod     = jSrc["pOrbit_Spin"]["tmPeriod"];
   Orbit_Spin.tmOrigin     = jSrc["pOrbit_Spin"]["tmOrigin"];
   Orbit_Spin.dA           = jSrc["pOrbit_Spin"]["dA"];
   Orbit_Spin.dB           = jSrc["pOrbit_Spin"]["dB"];

   Bound.dX = jSrc["pBound"]["Max"][0];
   Bound.dY = jSrc["pBound"]["Max"][1];
   Bound.dZ = jSrc["pBound"]["Max"][2];

   Properties.fMass         = jSrc["pProperties"]["fMass"];
   Properties.fGravity      = jSrc["pProperties"]["fGravity"];
   Properties.fColor        = jSrc["pProperties"]["fColor"];
   Properties.fBrightness   = jSrc["pProperties"]["fBrightness"];
   Properties.fReflectivity = jSrc["pProperties"]["fReflectivity"];

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

bool IO_RMCOBJECT::Attach ()
{
   bool bResult = IO_OBJECT::Attach ();

   if (bResult)
   {
      RMCOBJECT* pModelIO = dynamic_cast<RMCOBJECT*> (pModel ());
      RMAP::SVC_SOCKETIO::CLIENT::IACTION* pIAction = dynamic_cast<RMAP::SVC_SOCKETIO::CLIENT::IACTION*> (Request ("UPDATE"));
      ordered_json& pRequest = pIAction->GetRequest ();

      pRequest["twRMCObjectIx"] = pModelIO->twObjectIx ();

      pIAction->Send (this->m_pImpl, 0, 0);
   }

   return bResult;
}

/******************************************************************************************************************************/
