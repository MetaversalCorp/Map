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
**                                             CLASS (RMTOBJECT::NAME::Impl)                                                   **
****************************************************************\**************************************************************/

class RMTOBJECT::NAME::Impl
{
public:
   Impl (std::wstring wsRMTObjectId) :
      _wsRMTObjectId{ std::move (wsRMTObjectId) }
   {
   }

   ~Impl ()
   {
   }

public:
   std::wstring _wsRMTObjectId;
};


/*******************************************************************************************************************************
**                                             CLASS (RMTOBJECT::NAME)                                                         **
****************************************************************\**************************************************************/

RMTOBJECT::NAME::NAME (std::wstring wsRMTObjectId) :
   m_pImpl (new RMTOBJECT::NAME::Impl (std::move (wsRMTObjectId)))
{
}

// Copy Constructor
RMTOBJECT::NAME::NAME (NAME const& other) :
   m_pImpl (new RMTOBJECT::NAME::Impl (other.m_pImpl->_wsRMTObjectId))
{
}

// Move Constructor
RMTOBJECT::NAME::NAME (NAME&& other) noexcept :
   m_pImpl (new RMTOBJECT::NAME::Impl (std::move (other.m_pImpl->_wsRMTObjectId)))
{
}

// Copy Assignment Operator
RMTOBJECT::NAME& RMTOBJECT::NAME::operator=(NAME const& rhs)&
{
   if (this != &rhs)
   {
      m_pImpl->_wsRMTObjectId = rhs.m_pImpl->_wsRMTObjectId;
   }
   return *this;
}

// Move Assignment Operator
RMTOBJECT::NAME& RMTOBJECT::NAME::operator=(NAME&& rhs) & noexcept = default;

// Destructor
RMTOBJECT::NAME::~NAME () noexcept
{
   delete m_pImpl;
}

/*******************************************************************************
**  Accessors
*******************************************************************************/

std::wstring const& RMTOBJECT::NAME::wsRMTObjectId () const&
{
   return m_pImpl->_wsRMTObjectId;
}

std::wstring RMTOBJECT::NAME::wsRMTObjectId ()&&
{
   return std::move (m_pImpl->_wsRMTObjectId);
}

/*******************************************************************************
**  Modifiers
*******************************************************************************/

RMTOBJECT::NAME& RMTOBJECT::NAME::wsRMTObjectId (std::wstring _wsRMTObjectId) &
{
   m_pImpl->_wsRMTObjectId = std::move (_wsRMTObjectId);

   return *this;
}

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
   m_pName (new NAME),
   m_pType (new TYPE),
   m_pOwner (new OWNER),
   m_pResource (new RESOURCE),
   m_pTransform (new TRANSFORM),
   m_pBound (new BOUND),
   m_pProperties (new PROPERTIES),
   m_pPOD (new POD)
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

/*******************************************************************************
**  Accessors
*******************************************************************************/

RMTOBJECT::NAME const& RMTOBJECT::pName () const&
{
   return *m_pName;
}

TYPE const& RMTOBJECT::pType () const&
{
   return *m_pType;
}

OWNER const& RMTOBJECT::pOwner () const&
{
   return *m_pOwner;
}

RESOURCE const& RMTOBJECT::pResource () const&
{
   return *m_pResource;
}

TRANSFORM const& RMTOBJECT::pTransform () const&
{
   return *m_pTransform;
}

BOUND const& RMTOBJECT::pBound () const&
{
   return *m_pBound;
}

RMTOBJECT::PROPERTIES const& RMTOBJECT::pProperties () const&
{
   return *m_pProperties;
}

RMTOBJECT::POD const& RMTOBJECT::pPOD () const &
{
   return *m_pPOD;
}

/*******************************************************************************
**  Modifiers
*******************************************************************************/

RMTOBJECT& RMTOBJECT::pName (NAME _pName) &
{
   *m_pName = _pName;

   return *this;
}

RMTOBJECT& RMTOBJECT::pType (TYPE _pType) &
{
    *m_pType = _pType;

    return *this;
 }

RMTOBJECT& RMTOBJECT::pOwner (OWNER _pOwner) &
{
   *m_pOwner = _pOwner;

   return *this;
}

RMTOBJECT& RMTOBJECT::pResource (RESOURCE _pResource) &
{
   *m_pResource = _pResource;

   return *this;
}

RMTOBJECT& RMTOBJECT::pTransform (TRANSFORM _pTransform) &
{
   *m_pTransform = _pTransform;

   return *this;
}

RMTOBJECT& RMTOBJECT::pBound (BOUND _pBound) &
{
   *m_pBound = _pBound;

   return *this;
}

RMTOBJECT& RMTOBJECT::pProperties (PROPERTIES _pProperties) &
{
   *m_pProperties = _pProperties;

   return *this;
}

RMTOBJECT& RMTOBJECT::pPOD (POD _pPOD) &
{
   *m_pPOD = _pPOD;

   return *this;
}

/******************************************************************************************************************************/
