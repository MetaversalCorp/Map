/*******************************************************************************************************************************
**                                                                                                                            **
**                                      MVRP_RP1_Map_cpp : Common.cpp                                                         **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2024 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

#include "pch.h"

using namespace RMAP::MAP;

/*******************************************************************************************************************************
**                                             CLASS (RESOURCE::Impl)                                               **
****************************************************************\**************************************************************/

class RESOURCE::Impl
{
public:
   Impl (uint64_t qwResource, std::string sName, std::string sReference) :
      qwResource  { qwResource },
      sName       { std::move (sName) },
      sReference  { std::move (sReference) }
   {
   }

   ~Impl ()
   {
   }

public:
   uint64_t    qwResource;
   std::string sName;
   std::string sReference;
};

/*******************************************************************************************************************************
**                                             CLASS (RESOURCE)                                                     **
****************************************************************\**************************************************************/

RESOURCE::RESOURCE (uint64_t qwResource, std::string sName, std::string sReference) :
   m_pImpl (new RESOURCE::Impl (qwResource, std::move (sName), std::move (sReference)))
{
}

// Copy Constructor
RESOURCE::RESOURCE (RESOURCE const& other) :
   m_pImpl (new RESOURCE::Impl (other.m_pImpl->qwResource, other.m_pImpl->sName, other.m_pImpl->sReference))
{
}

// Move Constructor
RESOURCE::RESOURCE (RESOURCE&& other) noexcept :
   m_pImpl (new RESOURCE::Impl (std::move (other.m_pImpl->qwResource), std::move (other.m_pImpl->sName), other.m_pImpl->sReference))
{
}

// Copy Assignment Operator
RESOURCE& RESOURCE::operator=(RESOURCE const& rhs)&
{
   if (this != &rhs)
   {
      m_pImpl->qwResource  = rhs.m_pImpl->qwResource;
      m_pImpl->sName       = rhs.m_pImpl->sName;
      m_pImpl->sReference  = rhs.m_pImpl->sReference;
   }
   return *this;
}

// Move Assignment Operator
RESOURCE& RESOURCE::operator=(RESOURCE&& rhs) & noexcept = default;

// Destructor
RESOURCE::~RESOURCE () noexcept
{
   delete m_pImpl;
}

/*******************************************************************************
**  Accessors
*******************************************************************************/

uint64_t RESOURCE::qwResource () const&
{
   return m_pImpl->qwResource;
}

std::string const& RESOURCE::sName () const&
{
   return m_pImpl->sName;
}

std::string const& RESOURCE::sReference () const&
{
   return m_pImpl->sReference;
}

std::string RESOURCE::sName () &&
{
   return std::move (m_pImpl->sName);
}

std::string RESOURCE::sReference () &&
{
   return std::move (m_pImpl->sReference);
}

/*******************************************************************************
**  Modifiers
*******************************************************************************/

RESOURCE& RESOURCE::qwResource (uint64_t _qwResource)&
{
   m_pImpl->qwResource = _qwResource;

   return *this;
}

RESOURCE& RESOURCE::sName (std::string _sName) &
{
   m_pImpl->sName = std::move (_sName);

   return *this;
}

RESOURCE& RESOURCE::sReference (std::string _sReference) &
{
   m_pImpl->sReference = std::move (_sReference);

   return *this;
}

/******************************************************************************************************************************/
