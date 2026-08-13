/*******************************************************************************************************************************
**                                                                                                                            **
**                                                   MVRP_cpp : Map_Object.cpp                                                **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2026 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

#include "pch.h"

using namespace RMAP::MAP;

/*******************************************************************************************************************************
**                                                     CLASS (VEC3)                                                           **
*******************************************************************************************************************************/

double MAP_OBJECT::VEC3::Length () const
{
   return std::sqrt (dX * dX + dY * dY + dZ * dZ);
}

MAP_OBJECT::VEC3 MAP_OBJECT::VEC3::operator* (double dScale) const
{
   return { dX * dScale, dY * dScale, dZ * dScale };
}

MAP_OBJECT::VEC3 MAP_OBJECT::VEC3::operator+ (const VEC3& vRhs) const
{
   return { dX + vRhs.dX, dY + vRhs.dY, dZ + vRhs.dZ };
}

/*******************************************************************************************************************************
**                                                     CLASS (MAP_OBJECT::Impl)                                               **
*******************************************************************************************************************************/

class MAP_OBJECT::Impl
{
public:
   Impl () :
      m_nTextureWidth (0),
      m_nTextureHeight (0),
      m_nTextureChannels (0),
      m_bTextureReady (false)
   {
   }

   ~Impl ()
   {
   }

   bool GetTexture (const uint8_t*& pTex, int& nTexW, int& nTexH)
   {
      bool bResult = false;

      if (m_bTextureReady.load ())
      {
         m_CS.lock ();
         {
            bResult = true;

            pTex = m_aTexturePixels.data ();
            nTexW = m_nTextureWidth;
            nTexH = m_nTextureHeight;
         }
         m_CS.unlock ();
      }

      return bResult;
   }

   void SetTexture (const uint8_t* pTex, int nTexW, int nTexH)
   {
      m_CS.lock ();
      {
         m_aTexturePixels.assign (pTex, pTex + nTexW * nTexH * 4);
         m_nTextureWidth = nTexW;
         m_nTextureHeight = nTexH;
         m_nTextureChannels = 4;
      }
      m_CS.unlock ();

      m_bTextureReady.store (true);
   }

private:
   mutable std::mutex            m_CS;
   std::vector<uint8_t>          m_aTexturePixels;
   int                           m_nTextureWidth;
   int                           m_nTextureHeight;
   int                           m_nTextureChannels;
   std::atomic<bool>             m_bTextureReady;
};

/*******************************************************************************************************************************
**                                                     CLASS (MAP_OBJECT)                                                     **
*******************************************************************************************************************************/

MAP_OBJECT* MAP_OBJECT::Create (uint16_t wClass, uint64_t twObjectIx, const MAP_OBJECT_POD& Pod)
{
   MAP_OBJECT* pMap_Object = NULL;

   switch (wClass)
   {
   case MAP_OBJECT_CLASS_ROOT:         pMap_Object = new MAP_OBJECT              (wClass, twObjectIx, Pod);    break;
   case MAP_OBJECT_CLASS_CELESTIAL:    pMap_Object = new MAP_OBJECT_CELESTIAL    (wClass, twObjectIx, Pod);    break;
   case MAP_OBJECT_CLASS_TERRESTRIAL:  pMap_Object = new MAP_OBJECT_TERRESTRIAL  (wClass, twObjectIx, Pod);    break;
   case MAP_OBJECT_CLASS_PHYSICAL:     pMap_Object = new MAP_OBJECT              (wClass, twObjectIx, Pod);    break;
   case MAP_OBJECT_CLASS_PANEL:        pMap_Object = new MAP_OBJECT              (wClass, twObjectIx, Pod);    break;
   case MAP_OBJECT_CLASS_LIGHT:        pMap_Object = new MAP_OBJECT_LIGHT        (wClass, twObjectIx, Pod);    break;
   }

   return pMap_Object;
}

MAP_OBJECT::MAP_OBJECT (uint16_t wClass, uint64_t twObjectIx, const MAP_OBJECT_POD& Pod) :
   m_POD (Pod),
   m_nChildren (0),
   m_wClass (wClass),
   m_twObjectIx (twObjectIx),
   m_pImpl (new Impl ())
{
}

MAP_OBJECT::~MAP_OBJECT ()
{
   delete m_pImpl;
}

void MAP_OBJECT::GetPOD (MAP_OBJECT_POD& Pod) const&
{
   Pod = m_POD;
}

uint32_t MAP_OBJECT::Children () const &
{
   return m_nChildren;
}

// Modifiers                                              
void MAP_OBJECT::Name (const std::wstring& sName) &
{
   RMAP::CORE::UTILS::WString_to_Uint16 (sName, m_POD.Name.wsName, sizeof (m_POD.Name.wsName) / sizeof (uint16_t));
}

void MAP_OBJECT::Type (const MAP_OBJECT_TYPE& Type) &
{
   m_POD.Type = Type;
}

void MAP_OBJECT::Owner (const MAP_OBJECT_OWNER& Owner) &
{
   m_POD.Owner = Owner;
}

void MAP_OBJECT::Resource (uint64_t qwResource, const std::string& sName, const std::string& sReference) &
{
   m_POD.Resource.qwResource = qwResource;
   RMAP::CORE::UTILS::String_to_Uint8 (sName, reinterpret_cast<uint8_t*> (m_POD.Resource.sName), sizeof (m_POD.Resource.sName) / sizeof (uint8_t));
   RMAP::CORE::UTILS::String_to_Uint8 (sReference, reinterpret_cast<uint8_t*> (m_POD.Resource.sReference), sizeof (m_POD.Resource.sReference) / sizeof (uint8_t));
}

void MAP_OBJECT::Transform (const MAP_OBJECT_TRANSFORM& Transform) &
{
   m_POD.Transform = Transform;
}

void MAP_OBJECT::Bound (const MAP_OBJECT_BOUND& Bound) &
{
   m_POD.Bound = Bound;
}

void MAP_OBJECT::Children (uint32_t nChildren) &
{
   m_nChildren = nChildren;
}

void MAP_OBJECT::Position (int64_t tmNow, double& dX, double& dY, double& dZ) const
{
   (void)tmNow;
   dX = m_POD.Transform.d3Position[0];
   dY = m_POD.Transform.d3Position[1];
   dZ = m_POD.Transform.d3Position[2];
}

void MAP_OBJECT::Rotation (int64_t tmNow, double& dQx, double& dQy, double& dQz, double& dQw) const
{
   (void)tmNow;
   dQx = m_POD.Transform.d4Rotation[0];
   dQy = m_POD.Transform.d4Rotation[1];
   dQz = m_POD.Transform.d4Rotation[2];
   dQw = m_POD.Transform.d4Rotation[3];
}

void MAP_OBJECT::Scale (double& dX, double& dY, double& dZ) const
{
   dX = m_POD.Transform.d3Scale[0];
   dY = m_POD.Transform.d3Scale[1];
   dZ = m_POD.Transform.d3Scale[2];
}

void MAP_OBJECT::Position (int64_t tmNow, VEC3& vPosition) const
{
   Position (tmNow, vPosition.dX, vPosition.dY, vPosition.dZ);
}

void MAP_OBJECT::Rotation (int64_t tmNow, QUAT& qRotation) const
{
   Rotation (tmNow, qRotation.dX, qRotation.dY, qRotation.dZ, qRotation.dW);
}

void MAP_OBJECT::Scale (VEC3& vScale) const
{
   Scale (vScale.dX, vScale.dY, vScale.dZ);
}

double MAP_OBJECT::Radius () const
{
   return m_POD.Bound.d3Max[0];
}

uint32_t MAP_OBJECT::ColorToU32 () const
{
   uint32_t nColor;

   memcpy (&nColor, &m_POD.Properties.Celestial.fColor, 4);

   return nColor & 0x00FFFFFF;
}

uint32_t MAP_OBJECT::ColorDimToU32 () const
{
   uint32_t nC = ColorToU32 ();
   int r = (nC >> 16) & 0xFF;
   int g = (nC >> 8) & 0xFF;
   int b = nC & 0xFF;
   return static_cast<uint32_t> (((r / 2) << 16) | ((g / 2) << 8) | (b / 2));
}

uint32_t MAP_OBJECT::ColorBrightToU32 () const
{
   uint32_t nC = ColorToU32 ();
   int r = (nC >> 16) & 0xFF;
   int g = (nC >> 8) & 0xFF;
   int b = nC & 0xFF;
   auto clamp = [](int v) { return v > 255 ? 255 : v; };
   return static_cast<uint32_t> ((clamp (r + 64) << 16) | (clamp (g + 64) << 8) | clamp (b + 64));
}

bool MAP_OBJECT::GetTexture (const uint8_t*& pTex, int& nTexW, int& nTexH)
{
   return m_pImpl->GetTexture (pTex, nTexW, nTexH);
}

void MAP_OBJECT::SetTexture (const uint8_t* pTex, int nTexW, int nTexH)
{
   m_pImpl->SetTexture (pTex, nTexW, nTexH);
}

const char* MAP_OBJECT::ClassName (MAP_OBJECT_CLASS eType)
{
   const char* pcszResult;

   switch (eType)
   {
   case MAP_OBJECT_CLASS_ROOT:         pcszResult = "root";         break;
   case MAP_OBJECT_CLASS_CELESTIAL:    pcszResult = "celestial";    break;
   case MAP_OBJECT_CLASS_TERRESTRIAL:  pcszResult = "terrestrial";  break;
   case MAP_OBJECT_CLASS_PHYSICAL:     pcszResult = "physical";     break;
   case MAP_OBJECT_CLASS_PANEL:        pcszResult = "panel";        break;
   case MAP_OBJECT_CLASS_LIGHT:        pcszResult = "light";        break;
   default:                            pcszResult = "";             break;
   }

   return pcszResult;
}

MAP_OBJECT::VEC3 MAP_OBJECT::RotateByQuat (double qx, double qy, double qz, double qw, double vx, double vy, double vz) const
{
   double cx1 = qy * vz - qz * vy;
   double cy1 = qz * vx - qx * vz;
   double cz1 = qx * vy - qy * vx;
   double cx2 = qy * cz1 - qz * cy1;
   double cy2 = qz * cx1 - qx * cz1;
   double cz2 = qx * cy1 - qy * cx1;

   return {
      vx + 2.0 * (qw * cx1 + cx2),
      vy + 2.0 * (qw * cy1 + cy2),
      vz + 2.0 * (qw * cz1 + cz2),
   };
}

MAP_OBJECT::QUAT MAP_OBJECT::QuatMultiply (const QUAT& q1, const QUAT& q2) const
{
   QUAT r;

   r.dX = q1.dW * q2.dX + q1.dX * q2.dW + q1.dY * q2.dZ - q1.dZ * q2.dY;
   r.dY = q1.dW * q2.dY - q1.dX * q2.dZ + q1.dY * q2.dW + q1.dZ * q2.dX;
   r.dZ = q1.dW * q2.dZ + q1.dX * q2.dY - q1.dY * q2.dX + q1.dZ * q2.dW;
   r.dW = q1.dW * q2.dW - q1.dX * q2.dX - q1.dY * q2.dY - q1.dZ * q2.dZ;

   return r;
}

double MAP_OBJECT::SolveKepler (double dM_rad, double dEcc) const
{
   double dE = dEcc > 0.8 ? PI : dM_rad;

   for (int i = 0; i < 50; i++)
   {
      double dDelta = dE - dEcc * std::sin (dE) - dM_rad;
      if (std::abs (dDelta) < 1e-15) break;
      dE -= dDelta / (1.0 - dEcc * std::cos (dE));
   }

   return dE;
}

