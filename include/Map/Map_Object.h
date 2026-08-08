/*******************************************************************************************************************************
**                                                                                                                            **
**                                                         MAP : Map_Object.h                                                 **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2024 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

#ifndef RMAP_MAP_OBJECT_H
#define RMAP_MAP_OBJECT_H

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
   }
}

#endif //RMAP_MAP_OBJECT_H
