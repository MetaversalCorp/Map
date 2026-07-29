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
**                                             CLASS (RMROOT::NAME::Impl)                                                   **
****************************************************************\**************************************************************/

class RMROOT::NAME::Impl
{
public:
   Impl (std::wstring wsRMRootId) :
      _wsRMRootId{ std::move (wsRMRootId) }
   {
   }

   ~Impl ()
   {
   }

public:
   std::wstring _wsRMRootId;
};


/*******************************************************************************************************************************
**                                             CLASS (RMROOT::NAME)                                                         **
****************************************************************\**************************************************************/

RMROOT::NAME::NAME (std::wstring wsRMRootId) :
   m_pImpl (new RMROOT::NAME::Impl (std::move (wsRMRootId)))
{
}

// Copy Constructor
RMROOT::NAME::NAME (NAME const& other) :
   m_pImpl (new RMROOT::NAME::Impl (other.m_pImpl->_wsRMRootId))
{
}

// Move Constructor
RMROOT::NAME::NAME (NAME&& other) noexcept :
   m_pImpl (new RMROOT::NAME::Impl (std::move (other.m_pImpl->_wsRMRootId)))
{
}

// Copy Assignment Operator
RMROOT::NAME& RMROOT::NAME::operator=(NAME const& rhs)&
{
   if (this != &rhs)
   {
      m_pImpl->_wsRMRootId = rhs.m_pImpl->_wsRMRootId;
   }
   return *this;
}

// Move Assignment Operator
RMROOT::NAME& RMROOT::NAME::operator=(NAME&& rhs) & noexcept = default;

// Destructor
RMROOT::NAME::~NAME () noexcept
{
   delete m_pImpl;
}

/*******************************************************************************
**  Accessors
*******************************************************************************/

std::wstring const& RMROOT::NAME::wsRMRootId () const&
{
   return m_pImpl->_wsRMRootId;
}

std::wstring RMROOT::NAME::wsRMRootId () &&
{
   return std::move (m_pImpl->_wsRMRootId);
}

/*******************************************************************************
**  Modifiers
*******************************************************************************/

RMROOT::NAME& RMROOT::NAME::wsRMRootId (std::wstring _wsRMRootId) &
{
   m_pImpl->_wsRMRootId = std::move (_wsRMRootId);

   return *this;
}

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
   m_pName (new NAME),
   m_pOwner (new OWNER)
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

/*******************************************************************************
**  Accessors
*******************************************************************************/

RMROOT::NAME const& RMROOT::pName () const&
{
   return *m_pName;
}

OWNER const& RMROOT::pOwner () const&
{
   return *m_pOwner;
}

/*******************************************************************************
**  Modifiers
*******************************************************************************/

RMROOT& RMROOT::pName (NAME _pName) &
{
   *m_pName = _pName;

   return *this;
}

RMROOT& RMROOT::pOwner (OWNER _pOwner) &
{
   *m_pOwner = _pOwner;

   return *this;
}

/******************************************************************************************************************************/
