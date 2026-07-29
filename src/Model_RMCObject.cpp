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
**                                             CLASS (RMCOBJECT::NAME::Impl)                                                   **
****************************************************************\**************************************************************/

class RMCOBJECT::NAME::Impl
{
public:
   Impl (std::wstring wsRMCObjectId) :
      _wsRMCObjectId{ std::move (wsRMCObjectId) }
   {
   }

   ~Impl ()
   {
   }

public:
   std::wstring _wsRMCObjectId;
};


/*******************************************************************************************************************************
**                                             CLASS (RMCOBJECT::NAME)                                                         **
****************************************************************\**************************************************************/

RMCOBJECT::NAME::NAME (std::wstring wsRMCObjectId) :
   m_pImpl (new RMCOBJECT::NAME::Impl (std::move (wsRMCObjectId)))
{
}

// Copy Constructor
RMCOBJECT::NAME::NAME (NAME const& other) :
   m_pImpl (new RMCOBJECT::NAME::Impl (other.m_pImpl->_wsRMCObjectId))
{
}

// Move Constructor
RMCOBJECT::NAME::NAME (NAME&& other) noexcept :
   m_pImpl (new RMCOBJECT::NAME::Impl (std::move (other.m_pImpl->_wsRMCObjectId)))
{
}

// Copy Assignment Operator
RMCOBJECT::NAME& RMCOBJECT::NAME::operator=(NAME const& rhs)&
{
   if (this != &rhs)
   {
      m_pImpl->_wsRMCObjectId = rhs.m_pImpl->_wsRMCObjectId;
   }
   return *this;
}

// Move Assignment Operator
RMCOBJECT::NAME& RMCOBJECT::NAME::operator=(NAME&& rhs) & noexcept = default;

// Destructor
RMCOBJECT::NAME::~NAME () noexcept
{
   delete m_pImpl;
}

/*******************************************************************************
**  Accessors
*******************************************************************************/

std::wstring const& RMCOBJECT::NAME::wsRMCObjectId () const &
{
   return m_pImpl->_wsRMCObjectId;
}

std::wstring RMCOBJECT::NAME::wsRMCObjectId () &&
{
   return std::move (m_pImpl->_wsRMCObjectId);
}

/*******************************************************************************
**  Modifiers
*******************************************************************************/

RMCOBJECT::NAME& RMCOBJECT::NAME::wsRMCObjectId (std::wstring _wsRMCObjectId) &
{
   m_pImpl->_wsRMCObjectId = std::move (_wsRMCObjectId);

   return *this;
}

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
   m_pName        (new NAME),
   m_pType        (new TYPE),
   m_pOwner       (new OWNER),
   m_pResource    (new RESOURCE),
   m_pTransform   (new TRANSFORM),
   m_pOrbit_Spin  (new ORBIT_SPIN),
   m_pBound       (new BOUND),
   m_pProperties  (new PROPERTIES),
   m_pPOD         (new POD)
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

/*******************************************************************************
**  Accessors
*******************************************************************************/

RMCOBJECT::NAME const& RMCOBJECT::pName () const&
{
   return *m_pName;
}

TYPE const& RMCOBJECT::pType () const&
{
   return *m_pType;
}

OWNER const& RMCOBJECT::pOwner () const&
{
   return *m_pOwner;
}

RESOURCE const& RMCOBJECT::pResource () const&
{
   return *m_pResource;
}

TRANSFORM const& RMCOBJECT::pTransform () const&
{
   return *m_pTransform;
}

ORBIT_SPIN const& RMCOBJECT::pOrbit_Spin () const&
{
   return *m_pOrbit_Spin;
}

BOUND const& RMCOBJECT::pBound () const&
{
   return *m_pBound;
}

RMCOBJECT::PROPERTIES const& RMCOBJECT::pProperties () const&
{
   return *m_pProperties;
}

RMCOBJECT::POD const& RMCOBJECT::pPOD () const &
{
   return *m_pPOD;
}

/*******************************************************************************
**  Modifiers
*******************************************************************************/

RMCOBJECT& RMCOBJECT::pName (NAME _pName) &
{
   *m_pName = _pName;

   return *this;
}

RMCOBJECT& RMCOBJECT::pType (TYPE _pType) &
{
    *m_pType = _pType;

    return *this;
 }

RMCOBJECT& RMCOBJECT::pOwner (OWNER _pOwner) &
{
   *m_pOwner = _pOwner;

   return *this;
}

RMCOBJECT& RMCOBJECT::pResource (RESOURCE _pResource) &
{
   *m_pResource = _pResource;

   return *this;
}

RMCOBJECT& RMCOBJECT::pTransform (TRANSFORM _pTransform) &
{
   *m_pTransform = _pTransform;

   return *this;
}

RMCOBJECT& RMCOBJECT::pOrbit_Spin (ORBIT_SPIN _pOrbit_Spin) &
{
   *m_pOrbit_Spin = _pOrbit_Spin;

   return *this;
}

RMCOBJECT& RMCOBJECT::pBound (BOUND _pBound) &
{
   *m_pBound = _pBound;

   return *this;
}

RMCOBJECT& RMCOBJECT::pProperties (PROPERTIES _pProperties) &
{
   *m_pProperties = _pProperties;

   return *this;
}

RMCOBJECT& RMCOBJECT::pPOD (POD _pPOD) &
{
   *m_pPOD = _pPOD;

   return *this;
}

/******************************************************************************************************************************/
