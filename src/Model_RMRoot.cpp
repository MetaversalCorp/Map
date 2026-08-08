/*******************************************************************************************************************************
**                                                                                                                            **
**                                      MVRP_RP1_Map_cpp : Model_RMRoot.cpp                                                   **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2024 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

#include "pch.h"

using namespace RMAP::MAP;

/*******************************************************************************************************************************
**                                             CLASS (RMROOT::IREFERENCE)                                                  **
****************************************************************\**************************************************************/

RMROOT::IREFERENCE::IREFERENCE (std::string sID, uint64_t twRMRootIx) :
   RMAP::CORE::MEM::MODEL::IREFERENCE (sID, twRMRootIx, 0)
{
}

RMROOT::IREFERENCE::~IREFERENCE ()
{
}

RMAP::CORE::MODEL* RMROOT::IREFERENCE::Create (RMAP::CORE::SOURCE* pSource)
{
   return new RMROOT (this, dynamic_cast<RMAP::CORE::MEM::SOURCE*>(pSource));
}

/*******************************************************************************************************************************
**                                                 CLASS (RMROOT::FACTORY)                                                 **
*******************************************************************************************************************************/

RMROOT::FACTORY::FACTORY (std::string sID) :
   RMAP::CORE::MODEL::FACTORY (sID)
{
}

RMROOT::FACTORY::~FACTORY ()
{
}

RMAP::CORE::IREFERENCE<RMAP::CORE::MODEL*, RMAP::CORE::SOURCE*>* RMROOT::FACTORY::Reference (std::vector<std::string> asArgs)
{
   uint64_t twRMRootIx = atoi (asArgs[0].c_str ());

   return new RMROOT::IREFERENCE (sID (), twRMRootIx);
}

/*******************************************************************************************************************************
**                                                     CLASS (RMROOT)                                                      **
*******************************************************************************************************************************/

RMROOT::RMROOT (IREFERENCE* pReference, RMAP::CORE::MEM::SOURCE* pSource) :
   RMAP::CORE::MODEL_OBJECT (pReference, pSource),
   MAP_OBJECT (wClass_Parent (), twParentIx (), wClass_Object (), twObjectIx ())
{
}

RMROOT::~RMROOT ()
{
}

RMAP::CORE::MODEL::FACTORY* RMROOT::factory ()
{
   return new FACTORY ("RMRoot");
}

RMAP::CORE::CLIENT::IACTION* RMROOT::Request (std::string sAction)
{
   RMAP::CORE::CLIENT::IACTION* pIAction = RMAP::CORE::MODEL::Request (sAction);

   if (pIAction)
   {
      ordered_json& pRequest = pIAction->GetRequest ();

      if (pRequest.contains ("twRMRootIx"))
         pRequest["twRMRootIx"] = twObjectIx ();
   }

   return pIAction;
}

/******************************************************************************************************************************/
