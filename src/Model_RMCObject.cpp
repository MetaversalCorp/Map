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
**                                             CLASS (RMCOBJECT::Impl)                                                        **
****************************************************************\**************************************************************/

class RMCOBJECT::Impl
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
   NAME                                      m_Name;
   MAP_DATA::MAP_OBJECT_TYPE                 m_Type;
   MAP_DATA::MAP_OBJECT_OWNER                m_Owner;
   RESOURCE                                  m_Resource;
   MAP_DATA::MAP_OBJECT_TRANSFORM            m_Transform;
   MAP_DATA::MAP_OBJECT_ORBIT_CELESTIAL      m_Orbit_Spin;
   MAP_DATA::MAP_OBJECT_BOUND                m_Bound;
   MAP_DATA::MAP_OBJECT_PROPERTIES_CELESTIAL m_Properties;
   uint32_t                                  m_nChildren;
};

/*******************************************************************************************************************************
**                                                     CLASS (RMCOBJECT)                                                      **
*******************************************************************************************************************************/

RMCOBJECT::RMCOBJECT (IREFERENCE* pReference, RMAP::CORE::MEM::SOURCE* pSource) :
   RMAP::CORE::MODEL_OBJECT (pReference, pSource),
   m_pImpl (new Impl ())
{
}

RMCOBJECT::~RMCOBJECT ()
{
   delete m_pImpl;
}

RMAP::CORE::MODEL::FACTORY* RMCOBJECT::factory ()
{
   return new FACTORY ("RMCObject");
}

void RMCOBJECT::GetData (MAP_DATA& Map_Data)
{
   Map_Data.Head.Parent.qwComposed  = OBJECTIX_COMPOSE (wClass_Parent (), twParentIx ());
   Map_Data.Head.Self.qwComposed    = OBJECTIX_COMPOSE (wClass_Object (), twObjectIx ());
   Map_Data.Head.qwEvent            = 0;

   RMAP::CORE::UTILS::WString_to_Uint16 (m_pImpl->m_Name.wsRMCObjectId (), Map_Data.Name.wsName, sizeof (Map_Data.Name.wsName) / sizeof (uint16_t));

   Map_Data.Type              = m_pImpl->m_Type;
   Map_Data.Owner             = m_pImpl->m_Owner;

   m_pImpl->m_Resource.GetData (Map_Data.Resource);

   Map_Data.Transform            = m_pImpl->m_Transform;
   Map_Data.Orbit.Celestial      = m_pImpl->m_Orbit_Spin;
   Map_Data.Bound                = m_pImpl->m_Bound;
   Map_Data.Properties.Celestial = m_pImpl->m_Properties;
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

RMCOBJECT::NAME const& RMCOBJECT::Name () const&
{
   return m_pImpl->m_Name;
}

MAP_DATA::MAP_OBJECT_TYPE const& RMCOBJECT::Type () const&
{
   return m_pImpl->m_Type;
}

MAP_DATA::MAP_OBJECT_OWNER const& RMCOBJECT::Owner () const&
{
   return m_pImpl->m_Owner;
}

RESOURCE const& RMCOBJECT::Resource () const&
{
   return m_pImpl->m_Resource;
}

MAP_DATA::MAP_OBJECT_TRANSFORM const& RMCOBJECT::Transform () const&
{
   return m_pImpl->m_Transform;
}

MAP_DATA::MAP_OBJECT_ORBIT_CELESTIAL const& RMCOBJECT::Orbit_Spin () const&
{
   return m_pImpl->m_Orbit_Spin;
}

MAP_DATA::MAP_OBJECT_BOUND const& RMCOBJECT::Bound () const&
{
   return m_pImpl->m_Bound;
}

MAP_DATA::MAP_OBJECT_PROPERTIES_CELESTIAL const& RMCOBJECT::Properties () const&
{
   return m_pImpl->m_Properties;
}

uint32_t const RMCOBJECT::Children () const &
{
   return m_pImpl->m_nChildren;
}

/*******************************************************************************
**  Modifiers
*******************************************************************************/

RMCOBJECT& RMCOBJECT::Name (const NAME& _Name) &
{
   m_pImpl->m_Name = _Name;

   return *this;
}

RMCOBJECT& RMCOBJECT::Type (const MAP_DATA::MAP_OBJECT_TYPE& _Type) &
{
   m_pImpl->m_Type = _Type;

    return *this;
 }

RMCOBJECT& RMCOBJECT::Owner (const MAP_DATA::MAP_OBJECT_OWNER& _Owner) &
{
   m_pImpl->m_Owner = _Owner;

   return *this;
}

RMCOBJECT& RMCOBJECT::Resource (const RESOURCE& _Resource) &
{
   m_pImpl->m_Resource = _Resource;

   return *this;
}

RMCOBJECT& RMCOBJECT::Transform (const MAP_DATA::MAP_OBJECT_TRANSFORM& _Transform) &
{
   m_pImpl->m_Transform = _Transform;

   return *this;
}

RMCOBJECT& RMCOBJECT::Orbit_Spin (const MAP_DATA::MAP_OBJECT_ORBIT_CELESTIAL& _Orbit_Spin) &
{
   m_pImpl->m_Orbit_Spin = _Orbit_Spin;

   return *this;
}

RMCOBJECT& RMCOBJECT::Bound (const MAP_DATA::MAP_OBJECT_BOUND& _Bound) &
{
   m_pImpl->m_Bound = _Bound;

   return *this;
}

RMCOBJECT& RMCOBJECT::Properties (const MAP_DATA::MAP_OBJECT_PROPERTIES_CELESTIAL& _Properties) &
{
   m_pImpl->m_Properties = _Properties;

   return *this;
}

RMCOBJECT& RMCOBJECT::Children (uint32_t nChildren) &
{
   m_pImpl->m_nChildren = nChildren;

   return *this;
}

/******************************************************************************************************************************/
