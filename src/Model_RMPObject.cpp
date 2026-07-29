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
**                                             CLASS (RMPOBJECT::NAME::Impl)                                                   **
****************************************************************\**************************************************************/

class RMPOBJECT::NAME::Impl
{
public:
   Impl (std::wstring wsRMPObjectId) :
      _wsRMPObjectId{ std::move (wsRMPObjectId) }
   {
   }

   ~Impl ()
   {
   }

public:
   std::wstring _wsRMPObjectId;
};


/*******************************************************************************************************************************
**                                             CLASS (RMPOBJECT::NAME)                                                         **
****************************************************************\**************************************************************/

RMPOBJECT::NAME::NAME (std::wstring wsRMPObjectId) :
   m_pImpl (new RMPOBJECT::NAME::Impl (std::move (wsRMPObjectId)))
{
}

// Copy Constructor
RMPOBJECT::NAME::NAME (NAME const& other) :
   m_pImpl (new RMPOBJECT::NAME::Impl (other.m_pImpl->_wsRMPObjectId))
{
}

// Move Constructor
RMPOBJECT::NAME::NAME (NAME&& other) noexcept :
   m_pImpl (new RMPOBJECT::NAME::Impl (std::move (other.m_pImpl->_wsRMPObjectId)))
{
}

// Copy Assignment Operator
RMPOBJECT::NAME& RMPOBJECT::NAME::operator=(NAME const& rhs)&
{
   if (this != &rhs)
   {
      m_pImpl->_wsRMPObjectId = rhs.m_pImpl->_wsRMPObjectId;
   }
   return *this;
}

// Move Assignment Operator
RMPOBJECT::NAME& RMPOBJECT::NAME::operator=(NAME&& rhs) & noexcept = default;

// Destructor
RMPOBJECT::NAME::~NAME () noexcept
{
   delete m_pImpl;
}

/*******************************************************************************
**  Accessors
*******************************************************************************/

std::wstring const& RMPOBJECT::NAME::wsRMPObjectId () const&
{
   return m_pImpl->_wsRMPObjectId;
}

std::wstring RMPOBJECT::NAME::wsRMPObjectId ()&&
{
   return std::move (m_pImpl->_wsRMPObjectId);
}

/*******************************************************************************
**  Modifiers
*******************************************************************************/

RMPOBJECT::NAME& RMPOBJECT::NAME::wsRMPObjectId (std::wstring _wsRMPObjectId) &
{
   m_pImpl->_wsRMPObjectId = std::move (_wsRMPObjectId);

   return *this;
}

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
   m_pName (new NAME),
   m_pType (new TYPE),
   m_pOwner (new OWNER),
   m_pResource (new RESOURCE),
   m_pTransform (new TRANSFORM),
   m_pBound (new BOUND),
   m_pPOD (new POD)
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

/*******************************************************************************
**  Accessors
*******************************************************************************/

RMPOBJECT::NAME const& RMPOBJECT::pName () const&
{
   return *m_pName;
}

TYPE const& RMPOBJECT::pType () const&
{
   return *m_pType;
}

OWNER const& RMPOBJECT::pOwner () const&
{
   return *m_pOwner;
}

RESOURCE const& RMPOBJECT::pResource () const&
{
   return *m_pResource;
}

TRANSFORM const& RMPOBJECT::pTransform () const&
{
   return *m_pTransform;
}

BOUND const& RMPOBJECT::pBound () const&
{
   return *m_pBound;
}

RMPOBJECT::POD const& RMPOBJECT::pPOD () const&
{
   return *m_pPOD;
}

/*******************************************************************************
**  Modifiers
*******************************************************************************/

RMPOBJECT& RMPOBJECT::pName (NAME _pName) &
{
   *m_pName = _pName;

   return *this;
}

RMPOBJECT& RMPOBJECT::pType (TYPE _pType) &
{
    *m_pType = _pType;

    return *this;
 }

RMPOBJECT& RMPOBJECT::pOwner (OWNER _pOwner) &
{
   *m_pOwner = _pOwner;

   return *this;
}

RMPOBJECT& RMPOBJECT::pResource (RESOURCE _pResource) &
{
   *m_pResource = _pResource;

   return *this;
}

RMPOBJECT& RMPOBJECT::pTransform (TRANSFORM _pTransform) &
{
   *m_pTransform = _pTransform;

   return *this;
}

RMPOBJECT& RMPOBJECT::pBound (BOUND _pBound) &
{
   *m_pBound = _pBound;

   return *this;
}

RMPOBJECT& RMPOBJECT::pPOD (POD _pPOD) &
{
   *m_pPOD = _pPOD;

   return *this;
}

/******************************************************************************************************************************/
