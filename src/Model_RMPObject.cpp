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
**                                             CLASS (RMPOBJECT::Impl)                                                        **
****************************************************************\**************************************************************/

class RMPOBJECT::Impl
{
public:
   Impl () :
      m_nChildren (0)
   {
   }

   ~Impl ()
   {
   }

public:
   NAME                    m_Name;
   TYPE                    m_Type;
   OWNER                   m_Owner;
   RESOURCE                m_Resource;
   TRANSFORM               m_Transform;
   BOUND                   m_Bound;
   uint32_t                m_nChildren;
};

/*******************************************************************************************************************************
**                                                     CLASS (RMPOBJECT)                                                      **
*******************************************************************************************************************************/

RMPOBJECT::RMPOBJECT (IREFERENCE* pReference, RMAP::CORE::MEM::SOURCE* pSource) :
   RMAP::CORE::MODEL_OBJECT (pReference, pSource),
   m_pImpl (new Impl ())
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

RMPOBJECT::NAME const& RMPOBJECT::Name () const&
{
   return m_pImpl->m_Name;
}

TYPE const& RMPOBJECT::Type () const&
{
   return m_pImpl->m_Type;
}

OWNER const& RMPOBJECT::Owner () const&
{
   return m_pImpl->m_Owner;
}

RESOURCE const& RMPOBJECT::Resource () const&
{
   return m_pImpl->m_Resource;
}

TRANSFORM const& RMPOBJECT::Transform () const&
{
   return m_pImpl->m_Transform;
}

BOUND const& RMPOBJECT::Bound () const&
{
   return m_pImpl->m_Bound;
}

uint32_t const RMPOBJECT::Children () const &
{
   return m_pImpl->m_nChildren;
}

/*******************************************************************************
**  Modifiers
*******************************************************************************/

RMPOBJECT& RMPOBJECT::Name (const NAME& _Name) &
{
   m_pImpl->m_Name = _Name;

   return *this;
}

RMPOBJECT& RMPOBJECT::Type (const TYPE& _Type) &
{
   m_pImpl->m_Type = _Type;

    return *this;
 }

RMPOBJECT& RMPOBJECT::Owner (const OWNER& _Owner) &
{
   m_pImpl->m_Owner = _Owner;

   return *this;
}

RMPOBJECT& RMPOBJECT::Resource (const RESOURCE& _Resource) &
{
   m_pImpl->m_Resource = _Resource;

   return *this;
}

RMPOBJECT& RMPOBJECT::Transform (const TRANSFORM& _Transform) &
{
   m_pImpl->m_Transform = _Transform;

   return *this;
}

RMPOBJECT& RMPOBJECT::Bound (const BOUND& _Bound) &
{
   m_pImpl->m_Bound = _Bound;

   return *this;
}

RMPOBJECT& RMPOBJECT::Children (uint32_t _nChildren) &
{
   m_pImpl->m_nChildren = _nChildren;

   return *this;
}

/******************************************************************************************************************************/
