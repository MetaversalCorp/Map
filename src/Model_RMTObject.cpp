/*******************************************************************************************************************************
**                                                                                                                            **
**                                      MVRP_RP1_Map_cpp : Model_RMTObject.cpp                                                **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2024 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

#include "pch.h"

using namespace RMAP::MAP;

/*******************************************************************************************************************************
**                                             CLASS (RMTOBJECT::IREFERENCE)                                                  **
****************************************************************\**************************************************************/

RMTOBJECT::IREFERENCE::IREFERENCE (std::string sID, uint64_t twRMTObjectIx) :
   RMAP::CORE::MEM::MODEL::IREFERENCE (sID, twRMTObjectIx, 0)
{
}

RMTOBJECT::IREFERENCE::~IREFERENCE ()
{
}

RMAP::CORE::MODEL* RMTOBJECT::IREFERENCE::Create (RMAP::CORE::SOURCE* pSource)
{
   return new RMTOBJECT (this, dynamic_cast<RMAP::CORE::MEM::SOURCE*>(pSource));
}

/*******************************************************************************************************************************
**                                                 CLASS (RMTOBJECT::FACTORY)                                                 **
*******************************************************************************************************************************/

RMTOBJECT::FACTORY::FACTORY (std::string sID) :
   RMAP::CORE::MODEL::FACTORY (sID)
{
}

RMTOBJECT::FACTORY::~FACTORY ()
{
}

RMAP::CORE::IREFERENCE<RMAP::CORE::MODEL*, RMAP::CORE::SOURCE*>* RMTOBJECT::FACTORY::Reference (std::vector<std::string> asArgs)
{
   uint64_t twRMTObjectIx = atoi (asArgs[0].c_str ());

   return new RMTOBJECT::IREFERENCE (sID (), twRMTObjectIx);
}

/*******************************************************************************************************************************
**                                                     CLASS (RMTOBJECT)                                                      **
*******************************************************************************************************************************/

RMTOBJECT::RMTOBJECT (IREFERENCE* pReference, RMAP::CORE::MEM::SOURCE* pSource) :
   RMAP::CORE::MODEL_OBJECT (pReference, pSource),
   MAP_OBJECT_TERRESTRIAL (wClass_Object (), twObjectIx ())
{
}

RMTOBJECT::~RMTOBJECT ()
{
}

RMAP::CORE::MODEL::FACTORY* RMTOBJECT::factory ()
{
   return new FACTORY ("RMTObject");
}

RMAP::CORE::CLIENT::IACTION* RMTOBJECT::Request (std::string sAction)
{
   RMAP::CORE::CLIENT::IACTION* pIAction = RMAP::CORE::MODEL::Request (sAction);

   if (pIAction)
   {
      ordered_json& pRequest = pIAction->GetRequest ();

      if (pRequest.contains ("twRMTObjectIx"))
         pRequest["twRMTObjectIx"] = twObjectIx ();
   }

   return pIAction;
}

/******************************************************************************************************************************/
