/*******************************************************************************************************************************
**                                                                                                                            **
**                                      MVRP_RP1_Map_cpp : Source_IO_RMPObject.cpp                                            **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2024 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

#include "pch.h"

using namespace RMAP::MAP;

/*******************************************************************************************************************************
**                                                     CLASS (Impl)                                                           **
*******************************************************************************************************************************/

class IO_RMPOBJECT::Impl : public RMAP::CORE::IRESPONSE
{
public:
   Impl (IO_RMPOBJECT* pRMPObject) :
      m_pRMPObject (pRMPObject)
   {
   }

   ~Impl ()
   {
   }

   void onResponse (RMAP::CORE::CLIENT::IACTION* pIAction, int nType, intptr_t pParam) override
   {
      m_pRMPObject->Response (pIAction);
   }

private:
   IO_RMPOBJECT* m_pRMPObject;
};

/*******************************************************************************************************************************
**                                                     CLASS (FACTORY)                                                      **
*******************************************************************************************************************************/

IO_RMPOBJECT::FACTORY::FACTORY (std::string sID_Service, std::string sID_Model, int wClass, std::map<std::string, const RMAP::CORE::CLIENT::ACTION*>& apAction, bool bIndependent) :
   RMAP::SVC_SOCKETIO::IO_OBJECT::FACTORY (sID_Service, sID_Model, wClass, apAction, bIndependent)
{
}

IO_RMPOBJECT::FACTORY::~FACTORY ()
{
}

RMAP::CORE::SOURCE* IO_RMPOBJECT::FACTORY::Create (RMAP::CORE::CLIENT* pClient)
{
   return new IO_RMPOBJECT (pReference, pClient);
}

/*******************************************************************************************************************************
**                                                   Convert                                                                  **
*******************************************************************************************************************************/

void Convert_RMPOBJECT_BOUNDX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMPObjectIx"] = jRequest_In["twRMPObjectIx"];

   Convert_RMCOMMON_BOUND (jRequest_Out, jRequest_In);
}

void Convert_RMPOBJECT_NAMEX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMPObjectIx"] = jRequest_In["twRMPObjectIx"];

   Convert_RMPOBJECT_NAME (jRequest_Out, jRequest_In);
}

void Convert_RMPOBJECT_RESOURCEX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMPObjectIx"] = jRequest_In["twRMPObjectIx"];

   Convert_RMCOMMON_RESOURCE (jRequest_Out, jRequest_In);
}

void Convert_RMPOBJECT_RMPOBJECT_OPENX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMPObjectIx"] = jRequest_In["twRMPObjectIx"];

   Convert_RMPOBJECT_NAME (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_TYPE (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_OWNER (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_RESOURCE (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_TRANSFORM (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_BOUND (jRequest_Out, jRequest_In);
}

void Convert_RMPOBJECT_TRANSFORMX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMPObjectIx"] = jRequest_In["twRMPObjectIx"];

   Convert_RMCOMMON_TRANSFORM (jRequest_Out, jRequest_In);
}

void Convert_RMPOBJECT_TYPEX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMPObjectIx"] = jRequest_In["twRMPObjectIx"];

   Convert_RMCOMMON_TYPE (jRequest_Out, jRequest_In);
}

void Convert_RMPOBJECT_OWNERX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMPObjectIx"] = jRequest_In["twRMPObjectIx"];

   Convert_RMCOMMON_OWNER (jRequest_Out, jRequest_In);
}

/*******************************************************************************************************************************
**                                                   CLASS (IO_RMPOBJECT)                                                     **
*******************************************************************************************************************************/

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMPOBJECT_UPDATEX
(
   "RMPObject:update",
   "{"
      "\"twRMPObjectIx\"                     : 0"
   "}",
   NULL
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMPOBJECT_INFOX
(
   "RMPObject:info",
   "{"
      "\"twRMPObjectIx\"                     : 0,"
      "\"sType\"                             : \"\""
   "}",
   NULL
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMPOBJECT_BOUNDX
(
   "RMPObject:bound",
   "{"
      "\"twRMPObjectIx\"                     : 0,"
      "\"pBound\"                            :"
      "{"
         "\"dX\"                             : 0," 
         "\"dY\"                             : 0," 
         "\"dZ\"                             : 0"
      "}"
   "}",
   Convert_RMPOBJECT_BOUNDX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMPOBJECT_NAMEX
(
   "RMPObject:name",
   "{"
      "\"twRMPObjectIx\"                     : 0,"
      "\"pName\"                             :"
      "{"
         "\"wsRMPObjectId\"                  : \"\""
      "}"
   "}",
   Convert_RMPOBJECT_NAMEX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMPOBJECT_TYPEX
(
   "RMPObject:",
   "{"
      "\"twRMPObjectIx\"                     : 0,"
      "\"pType\"                             :"
      "{"
         "\"bType\"                          : 0,"
         "\"bSubtype\"                       : 0,"
         "\"bFiction\"                       : 0,"
         "\"bMovable\"                       : 0"
      "}"
   "}",
   Convert_RMPOBJECT_TYPEX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMPOBJECT_OWNERX
(
   "RMPObject:owner",
   "{"
      "\"twRMPObjectIx\"                     : 0,"
      "\"pOwner\"                            :"
      "{"
         "\"twRPersonaIx\"                   : 0"
      "}"
   "}",
   Convert_RMPOBJECT_OWNERX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMPOBJECT_RESOURCEX
(
   "RMPObject:resource",
   "{"
      "\"twRMPObjectIx\"                     : 0,"
      "\"pResource\"                         :"
      "{"
         "\"qwResource\"                     : 0,"
         "\"sName\"                          : \"\","
         "\"sReference\"                     : \"\""
      "}"
   "}",
   Convert_RMPOBJECT_RESOURCEX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMPOBJECT_TRANSFORMX
(
   "RMPObject:transform",
   "{"
      "\"twRMPObjectIx\"                     : 0,"
      "\"pTransform\"                        :"
      "{"
         "\"vPosition\"                      : { \"dX\": 0, \"dY\": 0, \"dZ\": 0             },"
         "\"qRotation\"                      : { \"dX\": 0, \"dY\": 0, \"dZ\": 0, \"dW\": 0  },"
         "\"vScale\"                         : { \"dX\": 0, \"dY\": 0, \"dZ\": 0             }"
      "}"
   "}",
   Convert_RMPOBJECT_TRANSFORMX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMPOBJECT_RMPOBJECT_OPENX
(
   "RMPObject:rmcobject_open",
   "{"
      "\"twRMPObjectIx\"                     : 0,"
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
   Convert_RMPOBJECT_RMPOBJECT_OPENX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMPOBJECT_RMPOBJECT_CLOSEX
(
   "RMPObject:rmcobject_close",
   "{"
      "\"twRMPObjectIx\"                     : 0,"
      "\"twRMPObjectIx_Close\"               : 0,"
      "\"bDeleteAll\"                        : 0"
   "}",
   NULL
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMPOBJECT_PARENTX
(
   "RMPObject:parent",
   "{"
      "\"twRMPObjectIx\"                     : 0,"
      "\"wClass\"                            : 0,"
      "\"twObjectIx\"                        : 0"
   "}",
   NULL
);

std::map<std::string, const RMAP::CORE::CLIENT::ACTION*> IO_RMPOBJECT::aAction =
{
   { "UPDATE",             &IO_RMPOBJECT_UPDATEX            },
   { "INFO",               &IO_RMPOBJECT_INFOX              },
   { "BOUND",              &IO_RMPOBJECT_BOUNDX             },
   { "NAME",               &IO_RMPOBJECT_NAMEX              },
   { "OWNER",              &IO_RMPOBJECT_OWNERX             },
   { "TYPE",               &IO_RMPOBJECT_TYPEX              },
   { "RESOURCE",           &IO_RMPOBJECT_RESOURCEX          },
   { "TRANSFORM",          &IO_RMPOBJECT_TRANSFORMX         },
   { "RMPOBJECT_OPEN",     &IO_RMPOBJECT_RMPOBJECT_OPENX    },
   { "RMPOBJECT_CLOSE",    &IO_RMPOBJECT_RMPOBJECT_CLOSEX   },
   { "PARENT",             &IO_RMPOBJECT_PARENTX            },
};

IO_RMPOBJECT::IO_RMPOBJECT (RMAP::CORE::MEM::SOURCE::REFERENCE* pReference, RMAP::CORE::CLIENT* pClient) :
   IO_OBJECT (pReference, pClient),
   m_pImpl (new Impl (this))
{
}

IO_RMPOBJECT::~IO_RMPOBJECT ()
{
   delete m_pImpl;
}

void IO_RMPOBJECT::init ()
{
}

IO_RMPOBJECT::FACTORY* IO_RMPOBJECT::factory ()
{
   return new FACTORY ("Socket.IO", "RMPObject", MAP_OBJECT_CLASS_PHYSICAL, aAction, true);
}

void IO_RMPOBJECT::Read (ordered_json& jSrc, RMAP::CORE::MODEL* pModel)
{
   RMPOBJECT* pModelIO = dynamic_cast<RMPOBJECT*> (pModel);
   MAP_OBJECT_TYPE Type;
   MAP_OBJECT_OWNER Owner;
   MAP_OBJECT_TRANSFORM Transform;
   MAP_OBJECT_BOUND Bound;
   uint32_t nChildren;
   RMAP::CORE::MEM::OBJECTHEAD* pHead = pObjectHead ();

   Type.bType     = jSrc["pType"]["bType"];
   Type.bSubtype  = jSrc["pType"]["bSubtype"];
   Type.bFiction  = jSrc["pType"]["bFiction"];

   Owner.twOwner = jSrc["pOwner"]["twRPersonaIx"];

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

   nChildren = jSrc["nChildren"];

   pModelIO->Head (pHead->Parent.Class (), pHead->Parent.ObjectIx (), pHead->Self.Class (), pHead->Self.ObjectIx ());
   pModelIO->Name (RMAP::CORE::UTILS::UTF8_to_Wchar (jSrc["pName"]["wsRMPObjectId"].template get<std::string> ().c_str ()));
   pModelIO->Type (Type);
   pModelIO->Owner (Owner);
   pModelIO->Resource (jSrc["pResource"]["qwResource"], jSrc["pResource"]["sName"], jSrc["pResource"]["sReference"]);
   pModelIO->Transform (Transform);
   pModelIO->Bound (Bound);
   pModelIO->Children (nChildren);
}

bool IO_RMPOBJECT::Attach ()
{
   bool bResult = IO_OBJECT::Attach ();

   if (bResult)
   {
      RMPOBJECT* pModelIO = dynamic_cast<RMPOBJECT*> (pModel ());
      RMAP::SVC_SOCKETIO::CLIENT::IACTION* pIAction = dynamic_cast<RMAP::SVC_SOCKETIO::CLIENT::IACTION*> (Request ("UPDATE"));
      ordered_json& pRequest = pIAction->GetRequest ();

      pRequest["twRMPObjectIx"] = pModelIO->twObjectIx ();

      pIAction->Send (this->m_pImpl, 0, 0);
   }

   return bResult;
}

/******************************************************************************************************************************/
