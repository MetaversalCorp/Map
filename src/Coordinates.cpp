/*******************************************************************************************************************************
**                                                                                                                            **
**                                      MVRP_RP1_Core_cpp : Coordinates.cpp                                                   **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2024 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

#include "pch.h"

using namespace RMAP::MAP;

/*******************************************************************************************************************************
**                                                     CLASS (DOUBLE4)                                                        **
*******************************************************************************************************************************/

DOUBLE4::DOUBLE4 (double dX, double dY, double dZ, double dW) :
   m_dX (dX),
   m_dY (dY),
   m_dZ (dZ),
   m_dW (dW)
{
}

DOUBLE4::DOUBLE4 (DOUBLE4 const& other) :             // Copy constructor
   m_dX { other.m_dX },
   m_dY { other.m_dY },
   m_dZ { other.m_dZ },
   m_dW { other.m_dW }
{
}


DOUBLE4::DOUBLE4 (DOUBLE4&& other) noexcept :         // Move constructor
   m_dX { other.m_dX },
   m_dY { other.m_dY },
   m_dZ { other.m_dZ },
   m_dW { other.m_dW }
{
}

DOUBLE4& DOUBLE4::operator=(DOUBLE4 const& rhs)&     // Copy Assignment Operator
{
   if (this != &rhs)
   {
      m_dX = rhs.m_dX;
      m_dY = rhs.m_dY;
      m_dZ = rhs.m_dZ;
      m_dW = rhs.m_dW;
   }

   return *this;
}

DOUBLE4& DOUBLE4::operator=(DOUBLE4&& rhs) & noexcept = default;  // Move Assignment Operator
DOUBLE4::~DOUBLE4 ()                         noexcept = default;  // Destructor

//==================================

double DOUBLE4::dX () const&
{
   return m_dX;
}

double DOUBLE4::dY () const&
{
   return m_dY;
}

double DOUBLE4::dZ () const&
{
   return m_dZ;
}

double DOUBLE4::dW () const&
{
   return m_dW;
}

//==================================

DOUBLE4& DOUBLE4::dX (double _dX)&
{
   m_dX = _dX;

   return *this;
}

DOUBLE4& DOUBLE4::dY (double _dY)&
{
   m_dY = _dY;

   return *this;
}

DOUBLE4& DOUBLE4::dZ (double _dZ)&
{
   m_dZ = _dZ;

   return *this;
}

DOUBLE4& DOUBLE4::dW (double _dW)&
{
   m_dW = _dW;

   return *this;
}

/*******************************************************************************************************************************
**                                                     CLASS (DOUBLE3)                                                        **
*******************************************************************************************************************************/

DOUBLE3::DOUBLE3 (double dX, double dY, double dZ) :
   m_dX (dX),
   m_dY (dY),
   m_dZ (dZ)
{
}

DOUBLE3::DOUBLE3 (DOUBLE3 const& other) :             // Copy constructor
   m_dX { other.m_dX },
   m_dY { other.m_dY },
   m_dZ { other.m_dZ }
{
}


DOUBLE3::DOUBLE3 (DOUBLE3&& other) noexcept :         // Move constructor
   m_dX{ other.m_dX },
   m_dY{ other.m_dY },
   m_dZ{ other.m_dZ }
{
}

DOUBLE3& DOUBLE3::operator=(DOUBLE3 const& rhs) &     // Copy Assignment Operator
{
   if (this != &rhs)
   {
      m_dX = rhs.m_dX;
      m_dY = rhs.m_dY;
      m_dZ = rhs.m_dZ;
   }

   return *this;
}

DOUBLE3& DOUBLE3::operator=(DOUBLE3&& rhs) & noexcept = default;  // Move Assignment Operator
DOUBLE3::~DOUBLE3 ()                         noexcept = default;  // Destructor

//==================================

double DOUBLE3::dX () const &
{
   return m_dX;
}

double DOUBLE3::dY () const &
{
   return m_dY;
}

double DOUBLE3::dZ () const &
{
   return m_dZ;
}

//==================================

DOUBLE3& DOUBLE3::dX (double newdX ) &
{
  m_dX = newdX;

  return *this;
}

DOUBLE3& DOUBLE3::dY (double newdY) &
{
   m_dY = newdY;

   return *this;
}

DOUBLE3& DOUBLE3::dZ (double newdZ) &
{
   m_dZ = newdZ;

   return *this;
}

/*******************************************************************************************************************************
**                                                     CLASS (PARENT)                                                        **
*******************************************************************************************************************************/

PARENT::PARENT (uint16_t wClass, uint64_t twObjectIx) :
   m_wClass (wClass),
   m_twObjectIx (twObjectIx)
{
}

PARENT::PARENT (PARENT const& other) :                // Copy constructor
   m_wClass    { other.m_wClass },
   m_twObjectIx{ other.m_twObjectIx }
{
}

PARENT::PARENT (PARENT&& other) noexcept :            // Move constructor
   m_wClass    { other.m_wClass },
   m_twObjectIx{ other.m_twObjectIx }
{
}

PARENT& PARENT::operator=(PARENT const& rhs)&         // Copy Assignment Operator
{
   if (this != &rhs)
   {
      m_wClass     = rhs.m_wClass;
      m_twObjectIx = rhs.m_twObjectIx;
   }

   return *this;
}

PARENT& PARENT::operator=(PARENT&& rhs) & noexcept = default;  // Move Assignment Operator
PARENT::~PARENT ()                        noexcept = default;  // Destructor

//==================================

uint16_t PARENT::wClass () const &
{
   return m_wClass;
}

uint64_t PARENT::twObjectIx () const &
{
   return m_twObjectIx;
}

//==================================

PARENT& PARENT::wClass (uint16_t newwClass) &
{
   m_wClass = newwClass;

   return *this;
}

PARENT& PARENT::twObjectIx (uint64_t newtwObjectIx) &
{
   m_twObjectIx = newtwObjectIx;

   return *this;
}

/*******************************************************************************************************************************
**                                                     CLASS (RELATIVE)                                                       **
*******************************************************************************************************************************/

RELATIVE::RELATIVE (DOUBLE3 vPosition) :
   m_vPosition (vPosition)
{
}

RELATIVE::RELATIVE (RELATIVE const& other) :          // Copy constructor
   m_vPosition    { other.m_vPosition }
{
}

RELATIVE::RELATIVE (RELATIVE&& other) noexcept :      // Move constructor
   m_vPosition    { std::move (other.m_vPosition) }
{
}

RELATIVE& RELATIVE::operator=(RELATIVE const& rhs)&   // Copy Assignment Operator
{
   if (this != &rhs)
   {
      m_vPosition = rhs.m_vPosition;
   }

   return *this;
}

RELATIVE& RELATIVE::operator=(RELATIVE&& rhs) & noexcept = default;  // Move Assignment Operator
RELATIVE::~RELATIVE ()                          noexcept = default;  // Destructor

//==================================

DOUBLE3 const& RELATIVE::vPosition () const&
{
   return m_vPosition;
}

//==================================

RELATIVE& RELATIVE::vPosition (DOUBLE3 newvPosition) &
{
   m_vPosition = std::move (newvPosition);

   return *this;
}

/*******************************************************************************************************************************
**                                                     CLASS (POSITION_UNIVERSAL)                                             **
*******************************************************************************************************************************/

POSITION_UNIVERSAL::POSITION_UNIVERSAL (PARENT Parent, RELATIVE Relative) :
   m_Parent (Parent),
   m_Relative (Relative)
{
}

POSITION_UNIVERSAL::POSITION_UNIVERSAL (POSITION_UNIVERSAL const& other) :          // Copy constructor
   m_Parent    { other.m_Parent   },
   m_Relative  { other.m_Relative }
{
}

POSITION_UNIVERSAL::POSITION_UNIVERSAL (POSITION_UNIVERSAL&& other) noexcept :      // Move constructor
   m_Parent    { std::move (other.m_Parent)   },
   m_Relative  { std::move (other.m_Relative) }
{
}

POSITION_UNIVERSAL& POSITION_UNIVERSAL::operator=(POSITION_UNIVERSAL const& rhs)&   // Copy Assignment Operator
{
   if (this != &rhs)
   {
      m_Parent    = rhs.m_Parent;
      m_Relative  = rhs.m_Relative;
   }

   return *this;
}

POSITION_UNIVERSAL& POSITION_UNIVERSAL::operator=(POSITION_UNIVERSAL&& rhs) & noexcept = default;  // Move Assignment Operator
POSITION_UNIVERSAL::~POSITION_UNIVERSAL ()                                    noexcept = default;  // Destructor

//==================================

PARENT const& POSITION_UNIVERSAL::Parent () const&
{
   return m_Parent;
}

RELATIVE const& POSITION_UNIVERSAL::Relative () const&
{
   return m_Relative;
}

//==================================

POSITION_UNIVERSAL& POSITION_UNIVERSAL::Parent (PARENT newParent) &
{
   m_Parent = std::move (newParent);

   return *this;
}

POSITION_UNIVERSAL& POSITION_UNIVERSAL::Relative (RELATIVE newRelative) &
{
   m_Relative = std::move (newRelative);

   return *this;
}

/******************************************************************************************************************************/
