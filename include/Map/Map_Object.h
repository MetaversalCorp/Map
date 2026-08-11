/*******************************************************************************************************************************
**                                                                                                                            **
**                                                         MAP : Map_Object.h                                                 **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2024 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

#ifndef RMAP_MAP_OBJECT_H
#define RMAP_MAP_OBJECT_H

#define OBJECTIX_COMPOSE(eClass, twObjectIx)      ((static_cast<uint64_t> (eClass) << 48)  |  (static_cast<uint64_t> (twObjectIx) & 0x0000FFFFFFFFFFFFull))

namespace RMAP
{
   namespace MAP
   {
      enum MAP_OBJECT_CLASS : uint16_t
      {
         MAP_OBJECT_CLASS_ROOT            = 70,
         MAP_OBJECT_CLASS_CELESTIAL       = 71,
         MAP_OBJECT_CLASS_TERRESTRIAL     = 72,
         MAP_OBJECT_CLASS_PHYSICAL        = 73,
         MAP_OBJECT_CLASS_PANEL           = 74,
         MAP_OBJECT_CLASS_LIGHT           = 75,
      };

      struct OBJECTIX
      {
         uint64_t              qwComposed;

         uint64_t              ObjectIx () const { return qwComposed & 0x0000FFFFFFFFFFFFull; }
         MAP_OBJECT_CLASS      Class ()    const { return static_cast<MAP_OBJECT_CLASS> (qwComposed >> 48); }
      };

      struct OBJECT_HEAD
      {
         OBJECTIX              Parent;
         OBJECTIX              Self;
         uint64_t              qwEvent;
      };

      struct MAP_OBJECT_NAME
      {
         uint16_t              wsName[48];
      };

      struct MAP_OBJECT_TYPE
      {
         uint8_t               bType;
         uint8_t               bSubtype;
         uint8_t               bFiction;
         uint8_t               abReserved[5];
      };

      struct MAP_OBJECT_OWNER
      {
         uint64_t              twOwner;
      };

      struct MAP_OBJECT_RESOURCE
      {
         uint64_t              qwResource;
         char                  sName[64];
         char                  sReference[128];
      };

      struct MAP_OBJECT_TRANSFORM
      {
         double                d3Position[3];
         double                d4Rotation[4];
         double                d3Scale[3];
      };

      struct MAP_OBJECT_ORBIT_CELESTIAL
      {
         int64_t               tmPeriod;
         int64_t               tmOrigin;
         double                dA;
         double                dB;
      };

      // The 32-byte orbit region is class-tagged: only celestial objects use it.
      // Other classes leave it reserved. The active member is chosen by the node's
      // MAP_OBJECT_CLASS; the wire size never changes.
      union MAP_OBJECT_ORBIT
      {
         MAP_OBJECT_ORBIT_CELESTIAL   Celestial;
         uint8_t                      abReserved[32];
      };

      struct MAP_OBJECT_BOUND
      {
         uint8_t               abReserved[24];
         double                d3Max[3];
      };

      struct MAP_OBJECT_PROPERTIES_CELESTIAL
      {
         float                 fMass;
         float                 fGravity;
         float                 fColor;
         float                 fBrightness;
         float                 fReflectivity;
         uint8_t               abReserved[12];
      };

      struct MAP_OBJECT_PROPERTIES_TERRESTIAL
      {
         uint8_t                 bLockToGround;
         uint8_t                 bYouth;
         uint8_t                 bAdult;
         uint8_t                 bAvatar;
         uint8_t                 abReserved[28];
      };

      // A light keeps fColor (0xRRGGBB packed into the float's bits) and
      // fBrightness at the same offsets as the celestial fields, so the shared
      // ColorToU32 accessor works for any class. The leading 8 bytes -- fMass and
      // fGravity on a celestial object -- carry the spot-light cone angles instead
      // (degrees). Point/ambient/directional lights ignore both angles.
      struct MAP_OBJECT_PROPERTIES_LIGHT
      {
         float                 fOpeningAngle;
         float                 fFalloffAngle;
         float                 fColor;
         float                 fBrightness;
         uint8_t               abReserved[16];
      };

      // The 32-byte properties region is class-tagged. The active member is chosen
      // by the node's MAP_OBJECT_CLASS; the wire size never changes.
      union MAP_OBJECT_PROPERTIES
      {
         MAP_OBJECT_PROPERTIES_CELESTIAL  Celestial;
         MAP_OBJECT_PROPERTIES_LIGHT      Light;
         MAP_OBJECT_PROPERTIES_TERRESTIAL Terrestial;
         uint8_t                          abReserved[32];
      };

      struct MAP_OBJECT_POD
      {
         OBJECT_HEAD                   Head;
         MAP_OBJECT_NAME               Name;
         MAP_OBJECT_TYPE               Type;
         MAP_OBJECT_OWNER              Owner;
         MAP_OBJECT_RESOURCE           Resource;
         MAP_OBJECT_TRANSFORM          Transform;
         MAP_OBJECT_ORBIT              Orbit;
         MAP_OBJECT_BOUND              Bound;
         MAP_OBJECT_PROPERTIES         Properties;
      };

      /*******************************************************************************************************************************
      **                                                 Object: MAP_OBJECT                                                         **
      *******************************************************************************************************************************/

      constexpr double PI = 3.14159265358979323846;
      constexpr double TWO_PI = 2.0 * PI;
      constexpr double DEG_TO_RAD = PI / 180.0;

      class MAP_OBJECT
      {
      public:
         class VEC3
         {
         public:
            double dX;
            double dY;
            double dZ;

            double Length ()                    const;
            VEC3   operator* (double dScale)    const;
            VEC3   operator+ (const VEC3& vRhs) const;
         };

         struct QUAT
         {
            double dX;
            double dY;
            double dZ;
            double dW;
         };

      public:
         MAP_OBJECT (uint16_t wClass_Parent, uint64_t twParentIx, uint16_t wClass_Object, uint64_t twObjectIx);
         MAP_OBJECT (const MAP_OBJECT_POD& Pod);
         virtual ~MAP_OBJECT ();

         static MAP_OBJECT* Create (const MAP_OBJECT_POD& Pod);
         static const char* ClassName (MAP_OBJECT_CLASS eType);

         void        Scale            (double& dX, double& dY, double& dZ)   const;
         void        Scale            (VEC3& vScale)                         const;
         double      Radius           ()                                     const;
         uint32_t    ColorToU32       ()                                     const;
         uint32_t    ColorDimToU32    ()                                     const;
         uint32_t    ColorBrightToU32 ()                                     const;

         bool GetTexture (const uint8_t*& pTex, int& nTexW, int& nTexH); // WRONG, shouldn't return pointer to pTex
         void SetTexture (const uint8_t* pTex, int nTexW, int nTexH);

         virtual void Position (int64_t tmNow, double& dX, double& dY, double& dZ)                 const;
         virtual void Rotation (int64_t tmNow, double& dQx, double& dQy, double& dQz, double& dQw) const;

         void         Position (int64_t tmNow, VEC3& vPosition)                                    const;
         void         Rotation (int64_t tmNow, QUAT& qRotation)                                    const;

         // Accessors
         void     GetPOD   (MAP_OBJECT_POD& Pod)                                                   const &;
         uint32_t Children ()                                                                      const &;

         // Modifiers                                              
         void Head      (const OBJECT_HEAD& Head)                                                        &;
         void Name      (const std::wstring& sName)                                                      &;
         void Type      (const MAP_OBJECT_TYPE& Type)                                                    &;
         void Owner     (const MAP_OBJECT_OWNER& Owner)                                                  &;
         void Resource  (uint64_t qwResource, const std::string& sName, const std::string& sReference)   &;
         void Transform (const MAP_OBJECT_TRANSFORM& Transform)                                          &;
         void Bound     (const MAP_OBJECT_BOUND& Bound)                                                  &;
         void Children  (uint32_t nChildren)                                                             &;

      public:
         MAP_OBJECT_POD    m_POD;   // Available only for MAP_OBJECT USAGE

      protected:
         uint32_t          m_nChildren;

         VEC3   RotateByQuat (double qx, double qy, double qz, double qw, double vx, double vy, double vz) const;
         QUAT   QuatMultiply (const QUAT& q1, const QUAT& q2) const;
         double SolveKepler (double dM_rad, double dEcc) const;

      private:
         class Impl;
         Impl* m_pImpl;
      };

      class MAP_OBJECT_CELESTIAL : public MAP_OBJECT
      {
      public:
         struct ORBIT_POSITION
         {
            double dX;
            double dY;
            double dZ;
            double dE;
         };

         enum eTYPE
         {
            MAP_OBJECT_TYPE_CELESTIAL_NONE = 0,
            MAP_OBJECT_TYPE_CELESTIAL_UNIVERSE = 1,
            MAP_OBJECT_TYPE_CELESTIAL_SUPERCLUSTER = 2,
            MAP_OBJECT_TYPE_CELESTIAL_GALAXYCLUSTER = 3,
            MAP_OBJECT_TYPE_CELESTIAL_GALAXY = 4,
            MAP_OBJECT_TYPE_CELESTIAL_SECTOR = 5,
            MAP_OBJECT_TYPE_CELESTIAL_NEBULA = 6,
            MAP_OBJECT_TYPE_CELESTIAL_STARCLUSTER = 7,
            MAP_OBJECT_TYPE_CELESTIAL_BLACKHOLE = 8,
            MAP_OBJECT_TYPE_CELESTIAL_STARSYSTEM = 9,
            MAP_OBJECT_TYPE_CELESTIAL_STAR = 10,
            MAP_OBJECT_TYPE_CELESTIAL_PLANETSYSTEM = 11,
            MAP_OBJECT_TYPE_CELESTIAL_PLANET = 12,
            MAP_OBJECT_TYPE_CELESTIAL_MOONSYSTEM = 125,
            MAP_OBJECT_TYPE_CELESTIAL_MOON = 13,
            MAP_OBJECT_TYPE_CELESTIAL_DEBRISSYSTEM = 135,
            MAP_OBJECT_TYPE_CELESTIAL_DEBRIS = 14,
            MAP_OBJECT_TYPE_CELESTIAL_SATELLITE = 15,
            MAP_OBJECT_TYPE_CELESTIAL_TRANSPORT = 16,
            MAP_OBJECT_TYPE_CELESTIAL_SURFACE = 17,
         };

      public:
         MAP_OBJECT_CELESTIAL (uint16_t wClass_Parent, uint64_t twParentIx, uint16_t wClass_Object, uint64_t twObjectIx);
         MAP_OBJECT_CELESTIAL (const MAP_OBJECT_POD& Pod);
         virtual ~MAP_OBJECT_CELESTIAL ();

         bool HasOrbit () const;

         void Position (int64_t tmNow, double& dX, double& dY, double& dZ)                 const override;
         void Rotation (int64_t tmNow, double& dQx, double& dQy, double& dQz, double& dQw) const override;

         bool PositionAtTick (int64_t tmNow, ORBIT_POSITION& out) const;
         VEC3 OrbitTrailPoint (double dE, int64_t tmElapsed)      const;

         static const char* GetTypeName (eTYPE eType);

         // Modifiers                                              
         void Orbit_Spin (const MAP_OBJECT_ORBIT_CELESTIAL& _Orbit_Spin)&;
         void Properties (const MAP_OBJECT_PROPERTIES_CELESTIAL& _Properties)&;
      };

      class MAP_OBJECT_TERRESTRIAL : public MAP_OBJECT
      {
      public:
         enum eTYPE
         {
            _NULL          =  0,
            ROOT           =  1,
            WATER          =  2,
            LAND           =  3,
            COUNTRY        =  4,
            TERRITORY      =  5,
            STATE          =  6,
            COUNTY         =  7,
            CITY           =  8,
            COMMUNITY      =  9,
            SECTOR         = 10,
            PARCEL         = 11
         };

      public:
         MAP_OBJECT_TERRESTRIAL (uint16_t wClass_Parent, uint64_t twParentIx, uint16_t wClass_Object, uint64_t twObjectIx);
         MAP_OBJECT_TERRESTRIAL (const MAP_OBJECT_POD& Pod);
         virtual ~MAP_OBJECT_TERRESTRIAL ();

         // Modifiers                                              
         void Properties (const MAP_OBJECT_PROPERTIES_TERRESTIAL& _Properties)&;
      };
   }
}

#endif //RMAP_MAP_OBJECT_H
