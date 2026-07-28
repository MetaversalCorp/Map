/*******************************************************************************************************************************
**                                                                                                                            **
**                                      MVRP_RP1_Core_cpp : Source_IO_Object.cpp                                              **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2024 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

#include "pch.h"

using namespace RMAP::MAP;

/*******************************************************************************************************************************
**                                                   Convert                                                                  **
*******************************************************************************************************************************/

void Convert_DCOORD (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["bCoord"]  = jRequest_In["pCoord"]["bCoord"];
   jRequest_Out["dA"]      = jRequest_In["pCoord"]["dA"];
   jRequest_Out["dB"]      = jRequest_In["pCoord"]["dB"];
   jRequest_Out["dC"]      = jRequest_In["pCoord"]["dC"];
}

// RMCOMMON =============================================================

void Convert_RMCOMMON_BOUND (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["Bound_dX"] = jRequest_In["pBound"]["dX"];
   jRequest_Out["Bound_dY"] = jRequest_In["pBound"]["dY"];
   jRequest_Out["Bound_dZ"] = jRequest_In["pBound"]["dZ"];
}

void Convert_RMCOMMON_ORBIT_SPIN (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["Orbit_Spin_tmPeriod"] = jRequest_In["pOrbit_Spin"]["tmPeriod"];
   jRequest_Out["Orbit_Spin_tmOrigin"] = jRequest_In["pOrbit_Spin"]["tmOrigin"];
   jRequest_Out["Orbit_Spin_dA"]       = jRequest_In["pOrbit_Spin"]["dA"];
   jRequest_Out["Orbit_Spin_dB"]       = jRequest_In["pOrbit_Spin"]["dB"];
}

void Convert_RMCOMMON_RESOURCE (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["Resource_qwResource"] = jRequest_In["pResource"]["qwResource"];
   jRequest_Out["Resource_sName"]      = jRequest_In["pResource"]["sName"];
   jRequest_Out["Resource_sReference"] = jRequest_In["pResource"]["sReference"];
}

void Convert_RMCOMMON_OWNER (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["Owner_twRPersonaIx"] = jRequest_In["pOwner"]["twRPersonaIx"];
}

void Convert_RMCOMMON_TYPE (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["Type_bType"] = jRequest_In["pType"]["bType"];
   jRequest_Out["Type_bSubtype"] = jRequest_In["pType"]["bSubtype"];
   jRequest_Out["Type_bFiction"] = jRequest_In["pType"]["bFiction"];
   jRequest_Out["Type_bMovable"] = jRequest_In["pType"]["bMovable"];
}

void Convert_RMCOMMON_TRANSFORM (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["Transform_Position_dX"] = jRequest_In["pTransform"]["vPosition"]["dX"];
   jRequest_Out["Transform_Position_dY"] = jRequest_In["pTransform"]["vPosition"]["dY"];
   jRequest_Out["Transform_Position_dZ"] = jRequest_In["pTransform"]["vPosition"]["dZ"];

   jRequest_Out["Transform_Rotation_dX"] = jRequest_In["pTransform"]["qRotation"]["dX"];
   jRequest_Out["Transform_Rotation_dY"] = jRequest_In["pTransform"]["qRotation"]["dY"];
   jRequest_Out["Transform_Rotation_dZ"] = jRequest_In["pTransform"]["qRotation"]["dZ"];
   jRequest_Out["Transform_Rotation_dW"] = jRequest_In["pTransform"]["qRotation"]["dW"];

   jRequest_Out["Transform_Scale_dX"] = jRequest_In["pTransform"]["vScale"]["dX"];
   jRequest_Out["Transform_Scale_dY"] = jRequest_In["pTransform"]["vScale"]["dY"];
   jRequest_Out["Transform_Scale_dZ"] = jRequest_In["pTransform"]["vScale"]["dZ"];
}

// RMCObject =============================================================

void Convert_RMCOBJECT_NAME (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["Name_wsRMCObjectId"] = jRequest_In["pName"]["wsRMCObjectId"];
}

void Convert_RMCOBJECT_PROPERTIES (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["Properties_fMass"]          = jRequest_In["pProperties"]["fMass"];
   jRequest_Out["Properties_fGravity"]       = jRequest_In["pProperties"]["fGravity"];
   jRequest_Out["Properties_fColor"]         = jRequest_In["pProperties"]["fColor"];
   jRequest_Out["Properties_fBrightness"]    = jRequest_In["pProperties"]["fBrightness"];
   jRequest_Out["Properties_fReflectivity"]  = jRequest_In["pProperties"]["fReflectivity"];
}

// RMTObject =============================================================

void Convert_RMTOBJECT_NAME (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["Name_wsRMTObjectId"] = jRequest_In["pName"]["wsRMTObjectId"];
}

void Convert_RMTOBJECT_PROPERTIES (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["Properties_bLockToGround"]  = jRequest_In["pProperties"]["bLockToGround"];
   jRequest_Out["Properties_bYouth"]         = jRequest_In["pProperties"]["bYouth"];
   jRequest_Out["Properties_bAdult"]         = jRequest_In["pProperties"]["bAdult"];
   jRequest_Out["Properties_bAvatar"]        = jRequest_In["pProperties"]["bAvatar"];
}

// RMPObject =============================================================

void Convert_RMPOBJECT_NAME (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["Name_wsRMPObjectId"] = jRequest_In["pName"]["wsRMPObjectId"];
}

// RMRoot =============================================================

void Convert_RMROOT_NAME (ordered_json& jRequest_Out, const ordered_json& jRequest_In)
{
   jRequest_Out["Name_wsRMRootId"] = jRequest_In["pName"]["wsRMRootId"];
}

/*******************************************************************************************************************************
**                                                   CLASS (IO_OBJECT)                                                        **
*******************************************************************************************************************************/

IO_OBJECT::IO_OBJECT (RMAP::CORE::MEM::SOURCE::REFERENCE* pReference, RMAP::CORE::CLIENT* pClient) :
   RMAP::SVC_SOCKETIO::IO_OBJECT (pReference, pClient)
{
}

IO_OBJECT::~IO_OBJECT ()
{
}

void IO_OBJECT::ParseResponse (ordered_json& jResponse, ordered_json& jResult)
{
   jResult["Parent"] = ordered_json::parse (jResponse["aResultSet"][0][0]["Object"].get<std::string> ());
   jResult["aChild"] = ordered_json::array ();
   for (size_t i = 1; i < jResponse["aResultSet"].size (); i++)
   {
      ordered_json jChildRow = ordered_json::array ();

      for (size_t j = 0; j < jResponse["aResultSet"][i].size (); j++)
      {
         jChildRow.push_back (ordered_json::parse (jResponse["aResultSet"][i][j]["Object"].get<std::string> ()));
      }

      jResult["aChild"].push_back (jChildRow);
   }
}

void IO_OBJECT::Response (RMAP::CORE::CLIENT::IACTION* pIAction)
{
   OBJECTHEAD ObjectHead;
   RMAP::SVC_SOCKETIO::CLIENT::IACTION* pIActionIO = dynamic_cast<RMAP::SVC_SOCKETIO::CLIENT::IACTION*> (pIAction);
   RMAP::SVC_SOCKETIO::CLIENT* pClientIO = dynamic_cast<RMAP::SVC_SOCKETIO::CLIENT*> (pClient ());

   ordered_json& jResponse = pIActionIO->GetResponse ();

   if (pIActionIO->IsSuccess ())
   {
      ordered_json jResult;

      ParseResponse (jResponse, jResult);

      ordered_json jObjectHead = jResult["Parent"]["pObjectHead"];

      RMAP::CORE::MEM::OBJECTBANK* pObjectBank = pClientIO->pMem ()->ObjectBank (jObjectHead["wClass_Object"]);
      SOURCE* pObject;

      if (pObjectBank != NULL)
      {
         if ((pObject = pObjectBank->Get (NULL, jObjectHead["twObjectIx"])) != NULL)
         {
            pObject->Recovering ();

            pClientIO->Object_Recover (jResult["Parent"]);

            for (const auto& item : jResult["aChild"])
            {
               if (item.is_array () && item.size ())
               {
                  for (const auto& itemObj : item)
                  {
                     ordered_json jItem = itemObj;

                     pClientIO->Object_Recover (jItem);
                  }
               }
            }

            pObject->Recovered ();
         }
      }
   }

   // This is deleted in MVIO after Response is processed.
   //delete pIAction;
}

/******************************************************************************************************************************/
