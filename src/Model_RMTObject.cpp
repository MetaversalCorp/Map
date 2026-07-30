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
**                                             CLASS (RMPOBJECT::Impl)                                                        **
****************************************************************\**************************************************************/

class RMTOBJECT::Impl
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
   PROPERTIES              m_Properties;
   uint32_t                m_nChildren;
};

/*******************************************************************************************************************************
**                                                     CLASS (RMTOBJECT)                                                      **
*******************************************************************************************************************************/

RMTOBJECT::RMTOBJECT (IREFERENCE* pReference, RMAP::CORE::MEM::SOURCE* pSource) :
   RMAP::CORE::MODEL_OBJECT (pReference, pSource),
   m_pImpl (new Impl ())
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

RMTOBJECT::NAME const& RMTOBJECT::Name () const&
{
   return m_pImpl->m_Name;
}

TYPE const& RMTOBJECT::Type () const&
{
   return m_pImpl->m_Type;
}

OWNER const& RMTOBJECT::Owner () const&
{
   return m_pImpl->m_Owner;
}

RESOURCE const& RMTOBJECT::Resource () const&
{
   return m_pImpl->m_Resource;
}

TRANSFORM const& RMTOBJECT::Transform () const&
{
   return m_pImpl->m_Transform;
}

BOUND const& RMTOBJECT::Bound () const&
{
   return m_pImpl->m_Bound;
}

RMTOBJECT::PROPERTIES const& RMTOBJECT::Properties () const&
{
   return m_pImpl->m_Properties;
}

uint32_t const RMTOBJECT::Children () const &
{
   return m_pImpl->m_nChildren;
}

/*******************************************************************************
**  Modifiers
*******************************************************************************/

RMTOBJECT& RMTOBJECT::Name (const NAME& _Name) &
{
   m_pImpl->m_Name = _Name;

   return *this;
}

RMTOBJECT& RMTOBJECT::Type (const TYPE& _Type) &
{
   m_pImpl->m_Type = _Type;

    return *this;
 }

RMTOBJECT& RMTOBJECT::Owner (const OWNER& _Owner) &
{
   m_pImpl->m_Owner = _Owner;

   return *this;
}

RMTOBJECT& RMTOBJECT::Resource (const RESOURCE& _Resource) &
{
   m_pImpl->m_Resource = _Resource;

   return *this;
}

RMTOBJECT& RMTOBJECT::Transform (const TRANSFORM& _Transform) &
{
   m_pImpl->m_Transform = _Transform;

   return *this;
}

RMTOBJECT& RMTOBJECT::Bound (const BOUND& _Bound) &
{
   m_pImpl->m_Bound = _Bound;

   return *this;
}

RMTOBJECT& RMTOBJECT::Properties (const PROPERTIES& _Properties) &
{
   m_pImpl->m_Properties = _Properties;

   return *this;
}

RMTOBJECT& RMTOBJECT::Children (uint32_t _nChildren) &
{
   m_pImpl->m_nChildren = _nChildren;

   return *this;
}

/******************************************************************************************************************************/
