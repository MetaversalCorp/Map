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
   MAP_OBJECT (wClass_Parent (), twParentIx (), wClass_Object (), twObjectIx ())
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

bool RMCOBJECT::HasOrbit () const
{
   return m_POD.Orbit.Celestial.dA != 0.0 && m_POD.Orbit.Celestial.tmPeriod != 0 && m_POD.Transform.d4Rotation[3] != 0.0;
}

void RMCOBJECT::Position (int64_t tmNow, double& dX, double& dY, double& dZ) const
{
   ORBIT_POSITION pos;

   if (PositionAtTick (tmNow, pos))
   {
      dX = pos.dX;
      dY = pos.dY;
      dZ = pos.dZ;
   }
   else
   {
      dX = m_POD.Transform.d3Position[0];
      dY = m_POD.Transform.d3Position[1];
      dZ = m_POD.Transform.d3Position[2];
   }
}

void RMCOBJECT::Rotation (int64_t tmNow, double& dQx, double& dQy, double& dQz, double& dQw) const
{
   uint8_t bType = m_POD.Type.bType;

   if (bType == MAP_OBJECT_TYPE_CELESTIAL_STAR
      || bType == MAP_OBJECT_TYPE_CELESTIAL_PLANET
      || bType == MAP_OBJECT_TYPE_CELESTIAL_MOON
      || bType == MAP_OBJECT_TYPE_CELESTIAL_DEBRIS)
   {
      double eX = m_POD.Transform.d4Rotation[0];
      double eY = m_POD.Transform.d4Rotation[1];
      double eZ = m_POD.Transform.d4Rotation[2];
      double eW = m_POD.Transform.d4Rotation[3];

      if (eW == 0.0 && eX == 0.0 && eY == 0.0 && eZ == 0.0)
      {
         dQx = 0.0;  dQy = 0.0;  dQz = 0.0;  dQw = 1.0;
      }
      else
      {
         double dPrecX = m_POD.Transform.d3Position[0];
         double dPrecY = m_POD.Transform.d3Position[1];
         double dPrecZ = m_POD.Transform.d3Position[2];
         double dRate = std::sqrt (dPrecX * dPrecX + dPrecY * dPrecY + dPrecZ * dPrecZ);

         if (dRate > 1e-30 && tmNow != 0)
         {
            double dAngle = dRate * static_cast<double> (tmNow);
            double dHalf = dAngle * 0.5;
            double dSinHalf = std::sin (dHalf) / dRate;

            QUAT qPrec = { dPrecX * dSinHalf, dPrecY * dSinHalf, dPrecZ * dSinHalf, std::cos (dHalf) };
            QUAT qRot = { eX, eY, eZ, eW };
            QUAT qComposed = QuatMultiply (qPrec, qRot);

            dQx = qComposed.dX;
            dQy = qComposed.dY;
            dQz = qComposed.dZ;
            dQw = qComposed.dW;
         }
         else
         {
            dQx = eX;  dQy = eY;  dQz = eZ;  dQw = eW;
         }
      }
   }
   else if (bType == MAP_OBJECT_TYPE_CELESTIAL_SURFACE)
   {
      int64_t tmSpinPeriod = m_POD.Orbit.Celestial.tmPeriod;

      if (tmSpinPeriod != 0)
      {
         double dW0Rad = m_POD.Orbit.Celestial.dA;
         double dAngle = dW0Rad + (static_cast<double> (tmNow) / static_cast<double> (tmSpinPeriod)) * TWO_PI;
         double dHalf = dAngle * 0.5;

         // Spin about the local polar axis = +Z (Z-up world).
         dQx = 0.0;
         dQy = 0.0;
         dQz = std::sin (dHalf);
         dQw = std::cos (dHalf);
      }
      else
      {
         dQx = 0.0;  dQy = 0.0;  dQz = 0.0;  dQw = 1.0;
      }
   }
   else
   {
      dQx = 0.0;  dQy = 0.0;  dQz = 0.0;  dQw = 1.0;
   }
}

bool RMCOBJECT::PositionAtTick (int64_t tmNow, ORBIT_POSITION& out) const
{
   bool bResult = false;

   if (m_POD.Orbit.Celestial.dA != 0.0 && m_POD.Orbit.Celestial.tmPeriod != 0 && m_POD.Transform.d4Rotation[3] != 0.0)
   {
      double dA = m_POD.Orbit.Celestial.dA;
      double dB = m_POD.Orbit.Celestial.dB;
      double dEcc = std::sqrt (1.0 - (dB * dB) / (dA * dA));

      int64_t tmInOrbit = ((m_POD.Orbit.Celestial.tmOrigin + tmNow) % m_POD.Orbit.Celestial.tmPeriod + m_POD.Orbit.Celestial.tmPeriod) % m_POD.Orbit.Celestial.tmPeriod;
      double  dM = (static_cast<double> (tmInOrbit) / static_cast<double> (m_POD.Orbit.Celestial.tmPeriod)) * TWO_PI;
      double  dE = SolveKepler (dM, dEcc);

      double dRx = m_POD.Transform.d4Rotation[0];
      double dRy = m_POD.Transform.d4Rotation[1];
      double dRz = m_POD.Transform.d4Rotation[2];
      double dRw = m_POD.Transform.d4Rotation[3];

      if (tmNow != 0)
      {
         double dPrecX = m_POD.Transform.d3Position[0];
         double dPrecY = m_POD.Transform.d3Position[1];
         double dPrecZ = m_POD.Transform.d3Position[2];
         double dRate = std::sqrt (dPrecX * dPrecX + dPrecY * dPrecY + dPrecZ * dPrecZ);

         if (dRate > 1e-30)
         {
            double dAngle = dRate * static_cast<double> (tmNow);
            double dHalf = dAngle * 0.5;
            double dSinHalf = std::sin (dHalf) / dRate;

            QUAT pPrec = { dPrecX * dSinHalf, dPrecY * dSinHalf, dPrecZ * dSinHalf, std::cos (dHalf) };
            QUAT pComposed = QuatMultiply (pPrec, { dRx, dRy, dRz, dRw });
            dRx = pComposed.dX;
            dRy = pComposed.dY;
            dRz = pComposed.dZ;
            dRw = pComposed.dW;
         }
      }

      double dLX = dA * (std::cos (dE) - dEcc);
      double dLY = dB * std::sin (dE);

      // Orbit lies in the local XY plane (Z-up world): perihelion on +X, sweeping
      // toward +Y as E grows (prograde / counter-clockwise seen from +Z). The
      // orientation quaternion tilts this plane into the reference frame.
      VEC3 pPos = RotateByQuat (dRx, dRy, dRz, dRw, dLX, dLY, 0.0);

      out.dX = pPos.dX;
      out.dY = pPos.dY;
      out.dZ = pPos.dZ;
      out.dE = dE;

      bResult = true;
   }

   return bResult;
}

MAP_OBJECT::VEC3 RMCOBJECT::OrbitTrailPoint (double dE, int64_t tmElapsed) const
{
   double dRx = m_POD.Transform.d4Rotation[0];
   double dRy = m_POD.Transform.d4Rotation[1];
   double dRz = m_POD.Transform.d4Rotation[2];
   double dRw = m_POD.Transform.d4Rotation[3];

   if (tmElapsed != 0)
   {
      double dPrecX = m_POD.Transform.d3Position[0];
      double dPrecY = m_POD.Transform.d3Position[1];
      double dPrecZ = m_POD.Transform.d3Position[2];
      double dRate = std::sqrt (dPrecX * dPrecX + dPrecY * dPrecY + dPrecZ * dPrecZ);

      if (dRate > 1e-30)
      {
         double dAngle = dRate * static_cast<double> (tmElapsed);
         double dHalf = dAngle * 0.5;
         double dSinHalf = std::sin (dHalf) / dRate;

         QUAT pPrec = { dPrecX * dSinHalf, dPrecY * dSinHalf, dPrecZ * dSinHalf, std::cos (dHalf) };
         QUAT pComposed = QuatMultiply (pPrec, { dRx, dRy, dRz, dRw });
         dRx = pComposed.dX;
         dRy = pComposed.dY;
         dRz = pComposed.dZ;
         dRw = pComposed.dW;
      }
   }

   double dA = m_POD.Orbit.Celestial.dA;
   double dB = m_POD.Orbit.Celestial.dB;
   double dEcc = std::sqrt (1.0 - (dB * dB) / (dA * dA));
   double dLX = dA * (std::cos (dE) - dEcc);
   double dLY = dB * std::sin (dE);

   return RotateByQuat (dRx, dRy, dRz, dRw, dLX, dLY, 0.0);
}

const char* RMCOBJECT::GetTypeName (eTYPE eType)
{
   const char* pcszResult;

   switch (eType)
   {
   case MAP_OBJECT_TYPE_CELESTIAL_NONE:          pcszResult = "none";              break;
   case MAP_OBJECT_TYPE_CELESTIAL_UNIVERSE:      pcszResult = "universe";          break;
   case MAP_OBJECT_TYPE_CELESTIAL_SUPERCLUSTER:  pcszResult = "supercluster";      break;
   case MAP_OBJECT_TYPE_CELESTIAL_GALAXYCLUSTER: pcszResult = "galaxycluster";     break;
   case MAP_OBJECT_TYPE_CELESTIAL_GALAXY:        pcszResult = "galaxy";            break;
   case MAP_OBJECT_TYPE_CELESTIAL_SECTOR:        pcszResult = "sector";            break;
   case MAP_OBJECT_TYPE_CELESTIAL_NEBULA:        pcszResult = "nebula";            break;
   case MAP_OBJECT_TYPE_CELESTIAL_STARCLUSTER:   pcszResult = "starcluster";       break;
   case MAP_OBJECT_TYPE_CELESTIAL_BLACKHOLE:     pcszResult = "blackhole";         break;
   case MAP_OBJECT_TYPE_CELESTIAL_STARSYSTEM:    pcszResult = "starsystem";        break;
   case MAP_OBJECT_TYPE_CELESTIAL_STAR:          pcszResult = "star";              break;
   case MAP_OBJECT_TYPE_CELESTIAL_PLANETSYSTEM:  pcszResult = "planetsystem";      break;
   case MAP_OBJECT_TYPE_CELESTIAL_PLANET:        pcszResult = "planet";            break;
   case MAP_OBJECT_TYPE_CELESTIAL_MOONSYSTEM:    pcszResult = "moonsystem";        break;
   case MAP_OBJECT_TYPE_CELESTIAL_MOON:          pcszResult = "moon";              break;
   case MAP_OBJECT_TYPE_CELESTIAL_DEBRISSYSTEM:  pcszResult = "debrissystem";      break;
   case MAP_OBJECT_TYPE_CELESTIAL_DEBRIS:        pcszResult = "debris";            break;
   case MAP_OBJECT_TYPE_CELESTIAL_SATELLITE:     pcszResult = "satellite";         break;
   case MAP_OBJECT_TYPE_CELESTIAL_TRANSPORT:     pcszResult = "transport";         break;
   case MAP_OBJECT_TYPE_CELESTIAL_SURFACE:       pcszResult = "surface";           break;

   default:
      pcszResult = "";
   }

   return pcszResult;
}

/*******************************************************************************
**  Modifiers
*******************************************************************************/

void RMCOBJECT::Orbit_Spin (const MAP_OBJECT_ORBIT_CELESTIAL& _Orbit_Spin) &
{
   m_POD.Orbit.Celestial = _Orbit_Spin;
}

void RMCOBJECT::Properties (const MAP_OBJECT_PROPERTIES_CELESTIAL& _Properties) &
{
   m_POD.Properties.Celestial = _Properties;
}

/******************************************************************************************************************************/
