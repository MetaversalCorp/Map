/*******************************************************************************************************************************
**                                                                                                                            **
**                                      MVRP_RP1_Core_cpp : Model_RMCObject.cpp                                               **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2024 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

#include "pch.h"

using namespace RMAP::MAP;

/*******************************************************************************************************************************
**                                             CLASS (RMCOBJECT::IREFERENCE)                                                  **
****************************************************************\**************************************************************/

RMCOBJECT::IREFERENCE::IREFERENCE (std::string sID, uint64_t twRMCObjectIx) :
   RMAP::CORE::MEM::MODEL::IREFERENCE (sID, twRMCObjectIx, 0)
{
}

RMCOBJECT::IREFERENCE::~IREFERENCE ()
{
}

RMAP::CORE::MODEL* RMCOBJECT::IREFERENCE::Create (RMAP::CORE::SOURCE* pSource)
{
   return new RMCOBJECT (this, dynamic_cast<RMAP::CORE::MEM::SOURCE*>(pSource));
}

/*******************************************************************************************************************************
**                                                 CLASS (RMCOBJECT::FACTORY)                                                 **
*******************************************************************************************************************************/

RMCOBJECT::FACTORY::FACTORY (std::string sID) :
   RMAP::CORE::MODEL::FACTORY (sID)
{
}

RMCOBJECT::FACTORY::~FACTORY ()
{
}

RMAP::CORE::IREFERENCE<RMAP::CORE::MODEL*, RMAP::CORE::SOURCE*>* RMCOBJECT::FACTORY::Reference (std::vector<std::string> asArgs)
{
   uint64_t twRMCObjectIx = atoi (asArgs[0].c_str ());

   return new RMCOBJECT::IREFERENCE (sID (), twRMCObjectIx);
}

/*******************************************************************************************************************************
**                                                     CLASS (RMCOBJECT)                                                      **
*******************************************************************************************************************************/

RMCOBJECT::RMCOBJECT (IREFERENCE* pReference, RMAP::CORE::MEM::SOURCE* pSource) :
   RMAP::CORE::MODEL_OBJECT (pReference, pSource),
   MAP_OBJECT_CELESTIAL (wClass_Parent (), twParentIx (), wClass_Object (), twObjectIx ())
{
}

RMCOBJECT::~RMCOBJECT ()
{
}

RMAP::CORE::MODEL::FACTORY* RMCOBJECT::factory ()
{
   return new FACTORY ("RMCObject");
}

RMAP::CORE::CLIENT::IACTION* RMCOBJECT::Request (std::string sAction)
{
   RMAP::CORE::CLIENT::IACTION* pIAction = RMAP::CORE::MODEL::Request (sAction);

   if (pIAction)
   {
      ordered_json& pRequest = pIAction->GetRequest ();

      if (pRequest.contains ("twRMCObjectIx"))
         pRequest["twRMCObjectIx"] = twObjectIx ();
   }

   return pIAction;
}

/******************************************************************************************************************************/
