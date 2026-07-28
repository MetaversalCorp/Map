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
**                                             CLASS (RMCOMMON::RESOURCE::Impl)                                               **
****************************************************************\**************************************************************/

class RMCOMMON::RESOURCE::Impl
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
**                                             CLASS (RMCOMMON::RESOURCE)                                                     **
****************************************************************\**************************************************************/

RMCOMMON::RESOURCE::RESOURCE (uint64_t qwResource, std::string sName, std::string sReference) :
   m_pImpl (new RMCOMMON::RESOURCE::Impl (qwResource, std::move (sName), std::move (sReference)))
{
}

// Copy Constructor
RMCOMMON::RESOURCE::RESOURCE (RESOURCE const& other) :
   m_pImpl (new RMCOMMON::RESOURCE::Impl (other.m_pImpl->qwResource, other.m_pImpl->sName, other.m_pImpl->sReference))
{
}

// Move Constructor
RMCOMMON::RESOURCE::RESOURCE (RESOURCE&& other) noexcept :
   m_pImpl (new RMCOMMON::RESOURCE::Impl (std::move (other.m_pImpl->qwResource), std::move (other.m_pImpl->sName), other.m_pImpl->sReference))
{
}

// Copy Assignment Operator
RMCOMMON::RESOURCE& RMCOMMON::RESOURCE::operator=(RESOURCE const& rhs)&
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
RMCOMMON::RESOURCE& RMCOMMON::RESOURCE::operator=(RESOURCE&& rhs) & noexcept = default;

// Destructor
RMCOMMON::RESOURCE::~RESOURCE () noexcept
{
   delete m_pImpl;
}

/*******************************************************************************
**  Accessors
*******************************************************************************/

uint64_t RMCOMMON::RESOURCE::qwResource () const&
{
   return m_pImpl->qwResource;
}

std::string const& RMCOMMON::RESOURCE::sName () const&
{
   return m_pImpl->sName;
}

std::string const& RMCOMMON::RESOURCE::sReference () const&
{
   return m_pImpl->sReference;
}

std::string RMCOMMON::RESOURCE::sName () &&
{
   return std::move (m_pImpl->sName);
}

std::string RMCOMMON::RESOURCE::sReference () &&
{
   return std::move (m_pImpl->sReference);
}

/*******************************************************************************
**  Modifiers
*******************************************************************************/

RMCOMMON::RESOURCE& RMCOMMON::RESOURCE::qwResource (uint64_t _qwResource)&
{
   m_pImpl->qwResource = _qwResource;

   return *this;
}

RMCOMMON::RESOURCE& RMCOMMON::RESOURCE::sName (std::string _sName) &
{
   m_pImpl->sName = std::move (_sName);

   return *this;
}

RMCOMMON::RESOURCE& RMCOMMON::RESOURCE::sReference (std::string _sReference) &
{
   m_pImpl->sReference = std::move (_sReference);

   return *this;
}

/******************************************************************************************************************************/
