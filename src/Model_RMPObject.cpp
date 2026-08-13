/*******************************************************************************************************************************
**                                                                                                                            **
**                                      MVRP_RP1_Core_cpp : Model_RMPObject.cpp                                               **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2024 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

#include "pch.h"

using namespace RMAP::MAP;

/*******************************************************************************************************************************
**                                             CLASS (RMPOBJECT::IREFERENCE)                                                  **
****************************************************************\**************************************************************/

RMPOBJECT::IREFERENCE::IREFERENCE (std::string sID, uint64_t twRMPObjectIx) :
   RMAP::CORE::MEM::MODEL::IREFERENCE (sID, twRMPObjectIx, 0)
{
}

RMPOBJECT::IREFERENCE::~IREFERENCE ()
{
}

RMAP::CORE::MODEL* RMPOBJECT::IREFERENCE::Create (RMAP::CORE::SOURCE* pSource)
{
   return new RMPOBJECT (this, dynamic_cast<RMAP::CORE::MEM::SOURCE*>(pSource));
}

/*******************************************************************************************************************************
**                                                 CLASS (RMPOBJECT::FACTORY)                                                 **
*******************************************************************************************************************************/

RMPOBJECT::FACTORY::FACTORY (std::string sID) :
   RMAP::CORE::MODEL::FACTORY (sID)
{
}

RMPOBJECT::FACTORY::~FACTORY ()
{
}

RMAP::CORE::IREFERENCE<RMAP::CORE::MODEL*, RMAP::CORE::SOURCE*>* RMPOBJECT::FACTORY::Reference (std::vector<std::string> asArgs)
{
   uint64_t twRMPObjectIx = atoi (asArgs[0].c_str ());

   return new RMPOBJECT::IREFERENCE (sID (), twRMPObjectIx);
}

/*******************************************************************************************************************************
**                                                     CLASS (RMPOBJECT)                                                      **
*******************************************************************************************************************************/

RMPOBJECT::RMPOBJECT (IREFERENCE* pReference, RMAP::CORE::MEM::SOURCE* pSource) :
   RMAP::CORE::MODEL_OBJECT (pReference, pSource),
   MAP_OBJECT (wClass_Object (), twObjectIx ())
{
}

RMPOBJECT::~RMPOBJECT ()
{
}

RMAP::CORE::MODEL::FACTORY* RMPOBJECT::factory ()
{
   return new FACTORY ("RMPObject");
}

RMAP::CORE::CLIENT::IACTION* RMPOBJECT::Request (std::string sAction)
{
   RMAP::CORE::CLIENT::IACTION* pIAction = RMAP::CORE::MODEL::Request (sAction);

   if (pIAction)
   {
      ordered_json& pRequest = pIAction->GetRequest ();

      if (pRequest.contains ("twRMPObjectIx"))
         pRequest["twRMPObjectIx"] = twObjectIx ();
   }

   return pIAction;
}

/******************************************************************************************************************************/
