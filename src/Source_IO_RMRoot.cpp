/*******************************************************************************************************************************
**                                                                                                                            **
**                                      MVRP_RP1_Map_cpp : Source_IO_RMRoot.cpp                                            **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2024 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

#include "pch.h"

using namespace RMAP::MAP;

/*******************************************************************************************************************************
**                                                     CLASS (Impl)                                                           **
*******************************************************************************************************************************/

class IO_RMROOT::Impl : public RMAP::CORE::IRESPONSE
{
public:
   Impl (IO_RMROOT* pRMRoot) :
      m_pRMRoot (pRMRoot)
   {
   }

   ~Impl ()
   {
   }

   void onResponse (RMAP::CORE::CLIENT::IACTION* pIAction, int nType, intptr_t pParam) override
   {
      m_pRMRoot->Response (pIAction);
   }

private:
   IO_RMROOT* m_pRMRoot;
};

/*******************************************************************************************************************************
**                                                     CLASS (FACTORY)                                                      **
*******************************************************************************************************************************/

IO_RMROOT::FACTORY::FACTORY (std::string sID_Service, std::string sID_Model, int wClass, std::map<std::string, const RMAP::CORE::CLIENT::ACTION*>& apAction, bool bIndependent) :
   RMAP::SVC_SOCKETIO::IO_OBJECT::FACTORY (sID_Service, sID_Model, wClass, apAction, bIndependent)
{
}

IO_RMROOT::FACTORY::~FACTORY ()
{
}

RMAP::CORE::SOURCE* IO_RMROOT::FACTORY::Create (RMAP::CORE::CLIENT* pClient)
{
   return new IO_RMROOT (pReference, pClient);
}

/*******************************************************************************************************************************
**                                                   Convert                                                                  **
*******************************************************************************************************************************/

void Convert_RMROOT_NAMEX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMRootIx"] = jRequest_In["twRMRootIx"];

   Convert_RMROOT_NAME (jRequest_Out, jRequest_In);
}

void Convert_RMROOT_OWNERX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMRootIx"] = jRequest_In["twRMRootIx"];

   Convert_RMCOMMON_OWNER (jRequest_Out, jRequest_In);
}

void Convert_RMROOT_RMCOBJECT_OPENX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMRootIx"] = jRequest_In["twRMRootIx"];

   Convert_RMCOBJECT_NAME (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_TYPE (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_OWNER (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_RESOURCE (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_TRANSFORM (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_ORBIT_SPIN (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_BOUND (jRequest_Out, jRequest_In);
   Convert_RMCOBJECT_PROPERTIES (jRequest_Out, jRequest_In);
}

void Convert_RMROOT_RMTOBJECT_OPENX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMRootIx"] = jRequest_In["twRMRootIx"];

   Convert_RMTOBJECT_NAME (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_TYPE (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_OWNER (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_RESOURCE (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_TRANSFORM (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_BOUND (jRequest_Out, jRequest_In);
   Convert_RMTOBJECT_PROPERTIES (jRequest_Out, jRequest_In);
   Convert_DCOORD (jRequest_Out, jRequest_In);
}

void Convert_RMROOT_RMPOBJECT_OPENX (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["twRMRootIx"] = jRequest_In["twRMRootIx"];

   Convert_RMPOBJECT_NAME (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_TYPE (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_OWNER (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_RESOURCE (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_TRANSFORM (jRequest_Out, jRequest_In);
   Convert_RMCOMMON_BOUND (jRequest_Out, jRequest_In);
}

/*******************************************************************************************************************************
**                                                   CLASS (IO_RMROOT)                                                     **
*******************************************************************************************************************************/

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMROOT_UPDATEX
(
   "RMRoot:update",
   "{"
      "\"twRMRootIx\"                     : 0"
   "}",
   NULL
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMROOT_NAMEX
(
   "RMRoot:name",
   "{"
      "\"twRMRootIx\"                     : 0,"
      "\"pName\"                             :"
      "{"
         "\"wsRMRootId\"                  : \"\""
      "}"
   "}",
   Convert_RMROOT_NAMEX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMROOT_OWNERX
(
   "RMRoot:owner",
   "{"
      "\"twRMRootIx\"                     : 0,"
      "\"pOwner\"                            :"
      "{"
         "\"twRPersonaIx\"                   : 0"
      "}"
   "}",
   Convert_RMROOT_OWNERX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMROOT_RMCOBJECT_OPENX
(
   "RMRoot:rmcobject_open",
   "{"
      "\"twRMRootIx\"                     : 0,"
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
   Convert_RMROOT_RMCOBJECT_OPENX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMROOT_RMCOBJECT_CLOSEX
(
   "RMRoot:rmcobject_close",
   "{"
      "\"twRMRootIx\"                        : 0,"
      "\"twRMCObjectIx_Close\"               : 0,"
      "\"bDeleteAll\"                        : 0"
   "}",
   NULL
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMROOT_RMTOBJECT_OPENX
(
   "RMRoot:rmtobject_open",
   "{"
      "\"twRMRootIx\"                     : 0,"
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
   Convert_RMROOT_RMTOBJECT_OPENX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMROOT_RMTOBJECT_CLOSEX
(
   "RMRoot:rmtobject_close",
   "{"
      "\"twRMRootIx\"                     : 0,"
      "\"twRMTObjectIx_Close\"               : 0,"
      "\"bDeleteAll\"                        : 0"
   "}",
   NULL
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMROOT_RMPOBJECT_OPENX
(
   "RMRoot:rmpobject_open",
   "{"
      "\"twRMRootIx\"                     : 0,"
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
   Convert_RMROOT_RMTOBJECT_OPENX
);

static const RMAP::SVC_SOCKETIO::CLIENT::ACTION IO_RMROOT_RMPOBJECT_CLOSEX
(
   "RMRoot:rmpobject_close",
   "{"
      "\"twRMRootIx\"                     : 0,"
      "\"twRMTObjectIx_Close\"               : 0,"
      "\"bDeleteAll\"                        : 0"
   "}",
   NULL
);

std::map<std::string, const RMAP::CORE::CLIENT::ACTION*> IO_RMROOT::aAction =
{
   { "UPDATE",          &IO_RMROOT_UPDATEX          },
   { "NAME",            &IO_RMROOT_NAMEX            },
   { "OWNER",           &IO_RMROOT_OWNERX           },
   { "RMCOBJECT_OPEN",  &IO_RMROOT_RMCOBJECT_OPENX  },
   { "RMCOBJECT_CLOSE", &IO_RMROOT_RMCOBJECT_CLOSEX },
   { "RMTOBJECT_OPEN",  &IO_RMROOT_RMTOBJECT_OPENX  },
   { "RMTOBJECT_CLOSE", &IO_RMROOT_RMTOBJECT_CLOSEX },
   { "RMPOBJECT_OPEN",  &IO_RMROOT_RMPOBJECT_OPENX  },
   { "RMPOBJECT_CLOSE", &IO_RMROOT_RMPOBJECT_CLOSEX },
};

IO_RMROOT::IO_RMROOT (RMAP::CORE::MEM::SOURCE::REFERENCE* pReference, RMAP::CORE::CLIENT* pClient) :
   IO_OBJECT (pReference, pClient),
   m_pImpl (new Impl (this))
{
}

IO_RMROOT::~IO_RMROOT ()
{
   delete m_pImpl;
}

void IO_RMROOT::init ()
{
}

IO_RMROOT::FACTORY* IO_RMROOT::factory ()
{
   return new FACTORY ("Socket.IO", "RMRoot", MAP_OBJECT_CLASS_ROOT, aAction, true);
}

void IO_RMROOT::Read (ordered_json& jSrc, RMAP::CORE::MODEL* pModel)
{
   RMROOT* pModelIO = dynamic_cast<RMROOT*> (pModel);
   MAP_OBJECT_OWNER Owner;

   Owner.twOwner = jSrc["pOwner"]["twRPersonaIx"];

   pModelIO->Name (RMAP::CORE::UTILS::UTF8_to_Wchar (jSrc["pName"]["wsRMRootId"].template get<std::string> ().c_str ()));
   pModelIO->Owner (Owner);
}

bool IO_RMROOT::Attach ()
{
   bool bResult = IO_OBJECT::Attach ();

   if (bResult)
   {
      RMROOT* pModelIO = dynamic_cast<RMROOT*> (pModel ());
      RMAP::SVC_SOCKETIO::CLIENT::IACTION* pIAction = dynamic_cast<RMAP::SVC_SOCKETIO::CLIENT::IACTION*> (Request ("UPDATE"));
      ordered_json& pRequest = pIAction->GetRequest ();

      pRequest["twRMRootIx"] = pModelIO->twObjectIx ();

      pIAction->Send (this->m_pImpl, 0, 0);
   }

   return bResult;
}

/******************************************************************************************************************************/
