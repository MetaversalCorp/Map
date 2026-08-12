/*******************************************************************************************************************************
**                                                                                                                            **
**                                      MVRP_RP1_Map_cpp : Source_IO_RMTObject.cpp                                            **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2024 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

#include "pch.h"

using namespace RMAP::MAP;

/*******************************************************************************************************************************
**                                                     CLASS (Impl)                                                           **
*******************************************************************************************************************************/

class IO_RMTOBJECT::Impl : public RMAP::CORE::IRESPONSE
{
public:
   Impl (IO_RMTOBJECT* pRMTObject) :
      m_pRMTObject (pRMTObject)
   {
   }

   ~Impl ()
   {
   }

   void onResponse (RMAP::CORE::CLIENT::IACTION* pIAction, int nType, intptr_t pParam) override
   {
      m_pRMTObject->Response (pIAction);
   }

private:
   IO_RMTOBJECT* m_pRMTObject;
};

/*******************************************************************************************************************************
**                                                     CLASS (FACTORY)                                                      **
*******************************************************************************************************************************/

IO_RMTOBJECT::FACTORY::FACTORY (std::string sID_Service, std::string sID_Model, int wClass, std::map<std::string, const RMAP::CORE::CLIENT::ACTION*>& apAction, bool bIndependent) :
   RMAP::SVC_SOCKETIO::IO_OBJECT::FACTORY (sID_Service, sID_Model, wClass, apAction, bIndependent)
{
}

IO_RMTOBJECT::FACTORY::~FACTORY ()
{
}

RMAP::CORE::SOURCE* IO_RMTOBJECT::FACTORY::Create (RMAP::CORE::CLIENT* pClient)
{
   return new IO_RMTOBJECT (pReference, pClient);
}

/*******************************************************************************************************************************
**                                                   Convert                                                                  **
*******************************************************************************************************************************/

void Convert_RMTOBJECT_BOUNDX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMTObjectIx"] = jRequest_In["twRMTObjectIx"];

   Convert_RMCOMMON_BOUND (jRequest_Out, jRequest_In);
}

void Convert_RMTOBJECT_NAMEX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMTObjectIx"] = jRequest_In["twRMTObjectIx"];

   Convert_RMTOBJECT_NAME (jRequest_Out, jRequest_In);
}

void Convert_RMTOBJECT_ORBIT_SPINX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMTObjectIx"] = jRequest_In["twRMTObjectIx"];

   Convert_RMCOMMON_ORBIT_SPIN (jRequest_Out, jRequest_In);
}

void Convert_RMTOBJECT_OWNERX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMTObjectIx"] = jRequest_In["twRMTObjectIx"];

   Convert_RMCOMMON_OWNER (jRequest_Out, jRequest_In);
}

void Convert_RMTOBJECT_PROPERTIESX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMTObjectIx"] = jRequest_In["twRMTObjectIx"];

   Convert_RMTOBJECT_PROPERTIES (jRequest_Out, jRequest_In);
}

void Convert_RMTOBJECT_RESOURCEX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMTObjectIx"] = jRequest_In["twRMTObjectIx"];

   Convert_RMCOMMON_RESOURCE (jRequest_Out, jRequest_In);
}

void Convert_RMTOBJECT_RMTOBJECT_OPENX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMTObjectIx"] = jRequest_In["twRMTObjectIx"];

   Convert_RMTOBJECT_NAME        (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_TYPE         (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_OWNER        (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_RESOURCE     (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_TRANSFORM    (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_BOUND        (jRequest_Out, jRequest_In);
   Convert_RMTOBJECT_PROPERTIES  (jRequest_Out, jRequest_In);
   Convert_DCOORD                (jRequest_Out, jRequest_In);
}

void Convert_RMTOBJECT_RMPOBJECT_OPENX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMTObjectIx"] = jRequest_In["twRMTObjectIx"];

   Convert_RMPOBJECT_NAME     (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_TYPE      (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_OWNER     (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_RESOURCE  (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_TRANSFORM (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_BOUND     (jRequest_Out, jRequest_In);
}

void Convert_RMTOBJECT_TRANSFORMX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMTObjectIx"] = jRequest_In["twRMTObjectIx"];

   Convert_RMCOMMON_TRANSFORM (jRequest_Out, jRequest_In);
   Convert_DCOORD (jRequest_Out, jRequest_In);
}

void Convert_RMTOBJECT_TYPEX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMTObjectIx"] = jRequest_In["twRMTObjectIx"];

   Convert_RMCOMMON_TYPE (jRequest_Out, jRequest_In);
}

/*******************************************************************************************************************************
**                                                   CLASS (IO_RMTOBJECT)                                                     **
*******************************************************************************************************************************/

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMTOBJECT_UPDATEX
(
   "RMTObject:update",
   "{"
      "\"twRMTObjectIx\"                     : 0"
   "}",
   NULL
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMTOBJECT_SEARCHX
(
   "RMTObject:search",
   "{"
      "\"twRMTObjectIx\"                     : 0,"
      "\"dX\"                                : 0,"
      "\"dY\"                                : 0,"
      "\"dZ\"                                : 0,"
      "\"sText\"                             : \"\""
   "}",
   NULL
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMTOBJECT_INFOX
(
   "RMTObject:info",
   "{"
      "\"twRMTObjectIx\"                     : 0,"
      "\"sType\"                             : \"\""
   "}",
   NULL
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMTOBJECT_NAMEX
(
   "RMTObject:name",
   "{"
      "\"twRMTObjectIx\"                     : 0,"
      "\"pName\"                             :"
      "{"
         "\"wsRMTObjectId\"                  : \"\""
      "}"
   "}",
   Convert_RMTOBJECT_NAMEX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMTOBJECT_TYPEX
(
   "RMTObject:",
   "{"
      "\"twRMTObjectIx\"                     : 0,"
      "\"pType\"                             :"
      "{"
         "\"bType\"                          : 0,"
         "\"bSubtype\"                       : 0,"
         "\"bFiction\"                       : 0,"
         "\"bMovable\"                       : 0"
      "}"
   "}",
   Convert_RMTOBJECT_TYPEX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMTOBJECT_OWNERX
(
   "RMTObject:owner",
   "{"
      "\"twRMTObjectIx\"                     : 0,"
      "\"pOwner\"                            :"
      "{"
         "\"twRPersonaIx\"                   : 0"
      "}"
   "}",
   Convert_RMTOBJECT_OWNERX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMTOBJECT_RESOURCEX
(
   "RMTObject:resource",
   "{"
      "\"twRMTObjectIx\"                     : 0,"
      "\"pResource\"                         :"
      "{"
         "\"qwResource\"                     : 0,"
         "\"sName\"                          : \"\","
         "\"sReference\"                     : \"\""
      "}"
   "}",
   Convert_RMTOBJECT_RESOURCEX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMTOBJECT_TRANSFORMX
(
   "RMTObject:transform",
   "{"
      "\"twRMTObjectIx\"                     : 0,"
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
   Convert_RMTOBJECT_TRANSFORMX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMTOBJECT_BOUNDX
(
   "RMTObject:bound",
   "{"
      "\"twRMTObjectIx\"                     : 0,"
      "\"pBound\"                            :"
      "{"
         "\"dX\"                             : 0," 
         "\"dY\"                             : 0," 
         "\"dZ\"                             : 0"
      "}"
   "}",
   Convert_RMTOBJECT_BOUNDX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMTOBJECT_PROPERTIESX
(
   "RMTObject:properties",
   "{"
      "\"twRMTObjectIx\"                     : 0,"
      "\"pProperties\"                       :"
      "{"
         "\"bLockToGround\"                  : 0,"
         "\"bYouth\"                         : 0,"
         "\"bAdult\"                         : 0,"
         "\"bAvatar\"                        : 0"
      "}"
   "}",
   Convert_RMTOBJECT_PROPERTIESX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMTOBJECT_RMTOBJECT_OPENX
(
   "RMTObject:rmcobject_open",
   "{"
      "\"twRMTObjectIx\"                     : 0,"
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
         "\"bLockToGround\"                  : 0,"
         "\"bYouth\"                         : 0,"
         "\"bAdult\"                         : 0,"
         "\"bAvatar\"                        : 0"
      "},"
      "\"pCoord\"                            :"
      "{"
         "\"bCoord\"                         : 0,"
         "\"dA\"                             : 0,"
         "\"dB\"                             : 0,"
         "\"dC\"                             : 0"
      "}"
   "}",
   Convert_RMTOBJECT_RMTOBJECT_OPENX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMTOBJECT_RMTOBJECT_CLOSEX
(
   "RMTObject:rmcobject_close",
   "{"
      "\"twRMTObjectIx\"                     : 0,"
      "\"twRMTObjectIx_Close\"               : 0,"
      "\"bDeleteAll\"                        : 0"
   "}",
   NULL
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMTOBJECT_RMPOBJECT_OPENX
(
   "RMTObject:rmtobject_open",
   "{"
      "\"twRMTObjectIx\"                     : 0,"
      "\"pName\"                             :"
      "{"
         "\"wsRMPObjectId\"                  : \"\""
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
      "}"
   "}",
   Convert_RMTOBJECT_RMPOBJECT_OPENX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMTOBJECT_RMPOBJECT_CLOSEX
(
   "RMTObject:rmtobject_close",
   "{"
      "\"twRMTObjectIx\"                     : 0,"
      "\"twRMPObjectIx_Close\"               : 0,"
      "\"bDeleteAll\"                        : 0"
   "}",
   NULL
);

std::map<std::string, const RMAP::CORE::CLIENT::ACTION*> IO_RMTOBJECT::aAction =
{
   { "UPDATE",             &IO_RMTOBJECT_UPDATEX          },
   { "SEARCH",             &IO_RMTOBJECT_SEARCHX          },
   { "INFO",               &IO_RMTOBJECT_INFOX            },
   { "NAME",               &IO_RMTOBJECT_NAMEX            },
   { "TYPE",               &IO_RMTOBJECT_TYPEX            },
   { "OWNER",              &IO_RMTOBJECT_OWNERX           },
   { "RESOURCE",           &IO_RMTOBJECT_RESOURCEX        },
   { "TRANSFORM",          &IO_RMTOBJECT_TRANSFORMX       },
   { "BOUND",              &IO_RMTOBJECT_BOUNDX           },
   { "PROPERTIES",         &IO_RMTOBJECT_PROPERTIESX      },
   { "RMTOBJECT_OPEN",     &IO_RMTOBJECT_RMTOBJECT_OPENX  },
   { "RMTOBJECT_CLOSE",    &IO_RMTOBJECT_RMTOBJECT_CLOSEX },
   { "RMPOBJECT_OPEN",     &IO_RMTOBJECT_RMPOBJECT_OPENX  },
   { "RMPOBJECT_CLOSE",    &IO_RMTOBJECT_RMPOBJECT_CLOSEX },
};

IO_RMTOBJECT::IO_RMTOBJECT (RMAP::CORE::MEM::SOURCE::REFERENCE* pReference, RMAP::CORE::CLIENT* pClient) :
   IO_OBJECT (pReference, pClient),
   m_pImpl (new Impl (this))
{
}

IO_RMTOBJECT::~IO_RMTOBJECT ()
{
   delete m_pImpl;
}

void IO_RMTOBJECT::init ()
{
}

IO_RMTOBJECT::FACTORY* IO_RMTOBJECT::factory ()
{
   return new FACTORY ("Socket.IO", "RMTObject", MAP_OBJECT_CLASS_TERRESTRIAL, aAction, true);
}

void IO_RMTOBJECT::Read (ordered_json& jSrc, RMAP::CORE::MODEL* pModel)
{
   RMTOBJECT* pModelIO = dynamic_cast<RMTOBJECT*> (pModel);
   MAP_OBJECT_TYPE Type;
   MAP_OBJECT_OWNER Owner;
   MAP_OBJECT_TRANSFORM Transform;
   MAP_OBJECT_BOUND Bound;
   MAP_OBJECT_PROPERTIES_TERRESTIAL Properties;
   uint32_t nChildren;
   RMAP::CORE::MEM::OBJECTHEAD* pHead = pObjectHead ();

   pModelIO->m_POD.Head.Parent.qwComposed = OBJECTIX_COMPOSE (pHead->twObjectIx, pHead->twParentIx);
   pModelIO->m_POD.Head.Self.qwComposed = OBJECTIX_COMPOSE (pHead->wClass_Object, pHead->twObjectIx);

   Type.bType     = jSrc["pType"]["bType"];
   Type.bSubtype  = jSrc["pType"]["bSubtype"];
   Type.bFiction  = jSrc["pType"]["bFiction"];

   Owner.twOwner  = jSrc["pOwner"]["twRPersonaIx"];

   Transform.d3Position[0] = jSrc["pTransform"]["Position"][0];
   Transform.d3Position[1] = jSrc["pTransform"]["Position"][1];
   Transform.d3Position[2] = jSrc["pTransform"]["Position"][2];

   Transform.d4Rotation[0] = jSrc["pTransform"]["Rotation"][0];
   Transform.d4Rotation[1] = jSrc["pTransform"]["Rotation"][1];
   Transform.d4Rotation[2] = jSrc["pTransform"]["Rotation"][2];
   Transform.d4Rotation[3] = jSrc["pTransform"]["Rotation"][3];

   Transform.d3Scale[0]    = jSrc["pTransform"]["Scale"][0];
   Transform.d3Scale[1]    = jSrc["pTransform"]["Scale"][1];
   Transform.d3Scale[2]    = jSrc["pTransform"]["Scale"][2];

   Bound.d3Max[0]          = jSrc["pBound"]["Max"][0];
   Bound.d3Max[1]          = jSrc["pBound"]["Max"][1];
   Bound.d3Max[2]          = jSrc["pBound"]["Max"][2];

   Properties.bLockToGround   = jSrc["pProperties"]["bLockToGround"];
   Properties.bYouth          = jSrc["pProperties"]["bYouth"];
   Properties.bAdult          = jSrc["pProperties"]["bAdult"];
   Properties.bAvatar         = jSrc["pProperties"]["bAvatar"];

   nChildren = jSrc["nChildren"];

   pModelIO->Name (RMAP::CORE::UTILS::UTF8_to_Wchar (jSrc["pName"]["wsRMTObjectId"].template get<std::string> ().c_str ()));
   pModelIO->Type (Type);
   pModelIO->Owner (Owner);
   pModelIO->Resource (jSrc["pResource"]["qwResource"], jSrc["pResource"]["sName"], jSrc["pResource"]["sReference"]);
   pModelIO->Transform (Transform);
   pModelIO->Bound (Bound);
   pModelIO->Properties (Properties);
   pModelIO->Children (nChildren);
}

bool IO_RMTOBJECT::Attach ()
{
   bool bResult = IO_OBJECT::Attach ();

   if (bResult)
   {
      RMTOBJECT* pModelIO = dynamic_cast<RMTOBJECT*> (pModel ());
      RMAP::SVC_SOCKETIO::CLIENT::IACTION* pIAction = dynamic_cast<RMAP::SVC_SOCKETIO::CLIENT::IACTION*> (Request ("UPDATE"));
      ordered_json& pRequest = pIAction->GetRequest ();

      pRequest["twRMTObjectIx"] = pModelIO->twObjectIx ();

      pIAction->Send (this->m_pImpl, 0, 0);
   }

   return bResult;
}

/******************************************************************************************************************************/
