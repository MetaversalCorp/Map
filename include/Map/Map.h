/*******************************************************************************************************************************
**                                                                                                                            **
**                                                         MAP : Map.h                                                        **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2024 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

#ifndef RMAP_MAP_H
#define RMAP_MAP_H

#include "Map_Object.h"

namespace RMAP
{
   namespace MAP
   {
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
         virtual ~MAP_OBJECT ();

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
         void Name      (const std::wstring& sName)                                                      &;
         void Type      (const MAP_OBJECT_TYPE& Type)                                                    &;
         void Owner     (const MAP_OBJECT_OWNER& Owner)                                                  &;
         void Resource  (uint64_t qwResource, const std::string& sName, const std::string& sReference)   &;
         void Transform (const MAP_OBJECT_TRANSFORM& Transform)                                          &;
         void Bound     (const MAP_OBJECT_BOUND& Bound)                                                  &;
         void Children  (uint32_t nChildren)                                                             &;

      protected:
         MAP_OBJECT_POD    m_POD;
         uint32_t          m_nChildren;

         VEC3   RotateByQuat (double qx, double qy, double qz, double qw, double vx, double vy, double vz) const;
         QUAT   QuatMultiply (const QUAT& q1, const QUAT& q2) const;
         double SolveKepler (double dM_rad, double dEcc) const;

      private:
         class Impl;
         Impl* m_pImpl;
      };

      /*******************************************************************************************************************************
      **                                                 Object: SOURCE_IO_OBJECT                                                   **
      *******************************************************************************************************************************/

      class IO_OBJECT : public RMAP::SVC_SOCKETIO::IO_OBJECT
      {
      public:
         IO_OBJECT (RMAP::CORE::MEM::SOURCE::REFERENCE* pReference, RMAP::CORE::CLIENT* pClient);
         virtual ~IO_OBJECT ();

         void Response (RMAP::CORE::CLIENT::IACTION* pIAction);

      private:
         void ParseResponse (ordered_json& jResponse, ordered_json& jResult);
      };

      /*******************************************************************************************************************************
      **                                                 Object: RMCOBJECT                                                          **
      *******************************************************************************************************************************/

      class IO_RMCOBJECT : public IO_OBJECT
      {
      public:
         class FACTORY : public RMAP::SVC_SOCKETIO::IO_OBJECT::FACTORY
         {
         public:
            FACTORY (std::string sID_Service, std::string sID_Model, int wClass, std::map<std::string, const RMAP::CORE::CLIENT::ACTION*> &apAction, bool bIndependent);
            virtual ~FACTORY ();

            RMAP::CORE::SOURCE* Create (RMAP::CORE::CLIENT* pClient) override;
         };

      public:
         IO_RMCOBJECT (RMAP::CORE::MEM::SOURCE::REFERENCE* pReference, RMAP::CORE::CLIENT* pClient);
         virtual ~IO_RMCOBJECT ();

         static void init ();
         static FACTORY* factory ();

         void Read (ordered_json& jSrc, RMAP::CORE::MODEL* pModel) override;
         bool Attach () override;

         static std::map<std::string, const RMAP::CORE::CLIENT::ACTION*> aAction;

      private:
         class Impl;
         Impl* m_pImpl;
      };

      class SB_RMCOBJECT : public RMAP::SVC_SB::SB_OBJECT
      {
      public:
         class FACTORY : public RMAP::SVC_SB::SB_OBJECT::FACTORY
         {
         public:
            FACTORY (std::string sID_Service, std::string sID_Model, int wClass, std::map<std::string, const RMAP::CORE::CLIENT::ACTION*>& apAction, bool bIndependent, RMAP::SVC_SB::MAP* pMap);
            virtual ~FACTORY ();

            RMAP::CORE::SOURCE* Create (RMAP::CORE::CLIENT* pClient) override;
         };

      public:
         SB_RMCOBJECT (RMAP::CORE::MEM::SOURCE::REFERENCE* pReference, RMAP::SVC_SB::MAP* pMap, RMAP::CORE::CLIENT* pClient);
         virtual ~SB_RMCOBJECT ();

         static void init ();
         static FACTORY* factory ();

         void Read (ordered_json& jSrc, RMAP::CORE::MODEL* pModel) override;

         static std::map<std::string, const RMAP::CORE::CLIENT::ACTION*> aAction;

      private:
         class Impl;
         Impl* m_pImpl;
      };

      class RMCOBJECT : public RMAP::CORE::MODEL_OBJECT, public MAP_OBJECT
      {
      public:
         enum eTYPE
         {
            MAP_OBJECT_TYPE_CELESTIAL_NONE           = 0,
            MAP_OBJECT_TYPE_CELESTIAL_UNIVERSE       = 1,
            MAP_OBJECT_TYPE_CELESTIAL_SUPERCLUSTER   = 2,
            MAP_OBJECT_TYPE_CELESTIAL_GALAXYCLUSTER  = 3,
            MAP_OBJECT_TYPE_CELESTIAL_GALAXY         = 4,
            MAP_OBJECT_TYPE_CELESTIAL_SECTOR         = 5,
            MAP_OBJECT_TYPE_CELESTIAL_NEBULA         = 6,
            MAP_OBJECT_TYPE_CELESTIAL_STARCLUSTER    = 7,
            MAP_OBJECT_TYPE_CELESTIAL_BLACKHOLE      = 8,
            MAP_OBJECT_TYPE_CELESTIAL_STARSYSTEM     = 9,
            MAP_OBJECT_TYPE_CELESTIAL_STAR           = 10,
            MAP_OBJECT_TYPE_CELESTIAL_PLANETSYSTEM   = 11,
            MAP_OBJECT_TYPE_CELESTIAL_PLANET         = 12,
            MAP_OBJECT_TYPE_CELESTIAL_MOONSYSTEM     = 125,
            MAP_OBJECT_TYPE_CELESTIAL_MOON           = 13,
            MAP_OBJECT_TYPE_CELESTIAL_DEBRISSYSTEM   = 135,
            MAP_OBJECT_TYPE_CELESTIAL_DEBRIS         = 14,
            MAP_OBJECT_TYPE_CELESTIAL_SATELLITE      = 15,
            MAP_OBJECT_TYPE_CELESTIAL_TRANSPORT      = 16,
            MAP_OBJECT_TYPE_CELESTIAL_SURFACE        = 17,
         };

         struct ORBIT_POSITION
         {
            double dX;
            double dY;
            double dZ;
            double dE;
         };

      public:
         class FACTORY : public RMAP::CORE::MODEL_OBJECT::FACTORY
         {
         public:
            FACTORY (std::string sID);
            virtual ~FACTORY ();

            // ===== Public Properties ==================================================================================================

            virtual RMAP::CORE::IREFERENCE<RMAP::CORE::MODEL*, RMAP::CORE::SOURCE*>* Reference (std::vector<std::string> asArgs) override;
         };

      public:
         class IREFERENCE : public RMAP::CORE::MODEL_OBJECT::IREFERENCE
         {
         public:
            IREFERENCE (std::string sID, uint64_t twRDRootIx);
            virtual ~IREFERENCE ();

            RMAP::CORE::MODEL* Create (RMAP::CORE::SOURCE* pParam) override;
         };

      public:
         static RMAP::CORE::MODEL::FACTORY* factory ();

         RMCOBJECT (IREFERENCE* pReference, RMAP::CORE::MEM::SOURCE* pSource);
         virtual ~RMCOBJECT ();

         // ===== Public Methods =====================================================================================================

         static const char* GetTypeName (eTYPE eType);

         bool HasOrbit () const;

         void Position (int64_t tmNow, double& dX, double& dY, double& dZ)                 const override;
         void Rotation (int64_t tmNow, double& dQx, double& dQy, double& dQz, double& dQw) const override;

         bool PositionAtTick (int64_t tmNow, ORBIT_POSITION& out) const;
         VEC3 OrbitTrailPoint (double dE, int64_t tmElapsed)      const;

         RMAP::CORE::CLIENT::IACTION* Request (std::string sAction) override;

         // Modifiers                                              
         void Orbit_Spin  (const MAP_OBJECT_ORBIT_CELESTIAL& _Orbit_Spin)          &;
         void Properties  (const MAP_OBJECT_PROPERTIES_CELESTIAL& _Properties)     &;
      };

      /*******************************************************************************************************************************
      **                                                 Object: RMPOBJECT                                                          **
      *******************************************************************************************************************************/

      class IO_RMPOBJECT : public IO_OBJECT
      {
      public:
         class FACTORY : public RMAP::SVC_SOCKETIO::IO_OBJECT::FACTORY
         {
         public:
            FACTORY (std::string sID_Service, std::string sID_Model, int wClass, std::map<std::string, const RMAP::CORE::CLIENT::ACTION*>& apAction, bool bIndependent);
            virtual ~FACTORY ();

            RMAP::CORE::SOURCE* Create (RMAP::CORE::CLIENT* pClient) override;
         };

      public:
         IO_RMPOBJECT (RMAP::CORE::MEM::SOURCE::REFERENCE* pReference, RMAP::CORE::CLIENT* pClient);
         virtual ~IO_RMPOBJECT ();

         static void init ();
         static FACTORY* factory ();

         void Read (ordered_json& jSrc, RMAP::CORE::MODEL* pModel) override;
         bool Attach () override;

         static std::map<std::string, const RMAP::CORE::CLIENT::ACTION*> aAction;

      private:
         class Impl;
         Impl* m_pImpl;
      };

      class SB_RMPOBJECT : public RMAP::SVC_SB::SB_OBJECT
      {
      public:
         class FACTORY : public RMAP::SVC_SB::SB_OBJECT::FACTORY
         {
         public:
            FACTORY (std::string sID_Service, std::string sID_Model, int wClass, std::map<std::string, const RMAP::CORE::CLIENT::ACTION*>& apAction, bool bIndependent, RMAP::SVC_SB::MAP* pMap);
            virtual ~FACTORY ();

            RMAP::CORE::SOURCE* Create (RMAP::CORE::CLIENT* pClient) override;
         };

      public:
         SB_RMPOBJECT (RMAP::CORE::MEM::SOURCE::REFERENCE* pReference, RMAP::SVC_SB::MAP* pMap, RMAP::CORE::CLIENT* pClient);
         virtual ~SB_RMPOBJECT ();

         static void init ();
         static FACTORY* factory ();

         void Read (ordered_json& jSrc, RMAP::CORE::MODEL* pModel) override;

         static std::map<std::string, const RMAP::CORE::CLIENT::ACTION*> aAction;

      private:
         class Impl;
         Impl* m_pImpl;
      };

      class RMPOBJECT : public RMAP::CORE::MODEL_OBJECT, public MAP_OBJECT
      {
      public:
         class FACTORY : public RMAP::CORE::MODEL_OBJECT::FACTORY
         {
         public:
            FACTORY (std::string sID);
            virtual ~FACTORY ();

            // ===== Public Properties ==================================================================================================

            virtual RMAP::CORE::IREFERENCE<RMAP::CORE::MODEL*, RMAP::CORE::SOURCE*>* Reference (std::vector<std::string> asArgs) override;
         };

      public:
         class IREFERENCE : public RMAP::CORE::MODEL_OBJECT::IREFERENCE
         {
         public:
            IREFERENCE (std::string sID, uint64_t twRDRootIx);
            virtual ~IREFERENCE ();

            RMAP::CORE::MODEL* Create (RMAP::CORE::SOURCE* pParam) override;
         };

      public:
         static RMAP::CORE::MODEL::FACTORY* factory ();

         RMPOBJECT (IREFERENCE* pReference, RMAP::CORE::MEM::SOURCE* pSource);
         virtual ~RMPOBJECT ();

         // ===== Public Methods =====================================================================================================

         RMAP::CORE::CLIENT::IACTION* Request (std::string sAction) override;
      };

      /*******************************************************************************************************************************
      **                                                 Object: RMRoot                                                             **
      *******************************************************************************************************************************/

      class IO_RMROOT : public IO_OBJECT
      {
      public:
         class FACTORY : public RMAP::SVC_SOCKETIO::IO_OBJECT::FACTORY
         {
         public:
            FACTORY (std::string sID_Service, std::string sID_Model, int wClass, std::map<std::string, const RMAP::CORE::CLIENT::ACTION*>& apAction, bool bIndependent);
            virtual ~FACTORY ();

            RMAP::CORE::SOURCE* Create (RMAP::CORE::CLIENT* pClient) override;
         };

      public:
         IO_RMROOT (RMAP::CORE::MEM::SOURCE::REFERENCE* pReference, RMAP::CORE::CLIENT* pClient);
         virtual ~IO_RMROOT ();

         static void init ();
         static FACTORY* factory ();

         void Read (ordered_json& jSrc, RMAP::CORE::MODEL* pModel) override;
         bool Attach () override;

         static std::map<std::string, const RMAP::CORE::CLIENT::ACTION*> aAction;

      private:
         class Impl;
         Impl* m_pImpl;
      };

      class SB_RMROOT : public RMAP::SVC_SB::SB_OBJECT
      {
      public:
         class FACTORY : public RMAP::SVC_SB::SB_OBJECT::FACTORY
         {
         public:
            FACTORY (std::string sID_Service, std::string sID_Model, int wClass, std::map<std::string, const RMAP::CORE::CLIENT::ACTION*>& apAction, bool bIndependent, RMAP::SVC_SB::MAP* pMap);
            virtual ~FACTORY ();

            RMAP::CORE::SOURCE* Create (RMAP::CORE::CLIENT* pClient) override;
         };

      public:
         SB_RMROOT (RMAP::CORE::MEM::SOURCE::REFERENCE* pReference, RMAP::SVC_SB::MAP* pMap, RMAP::CORE::CLIENT* pClient);
         virtual ~SB_RMROOT ();

         static void init ();
         static FACTORY* factory ();

         void Read (ordered_json& jSrc, RMAP::CORE::MODEL* pModel) override;

         static std::map<std::string, const RMAP::CORE::CLIENT::ACTION*> aAction;

      private:
         class Impl;
         Impl* m_pImpl;
      };

      class RMROOT : public RMAP::CORE::MODEL_OBJECT, public MAP_OBJECT
      {
      public:
         class FACTORY : public RMAP::CORE::MODEL_OBJECT::FACTORY
         {
         public:
            FACTORY (std::string sID);
            virtual ~FACTORY ();

            // ===== Public Properties ==================================================================================================

            virtual RMAP::CORE::IREFERENCE<RMAP::CORE::MODEL*, RMAP::CORE::SOURCE*>* Reference (std::vector<std::string> asArgs) override;
         };

      public:
         class IREFERENCE : public RMAP::CORE::MODEL_OBJECT::IREFERENCE
         {
         public:
            IREFERENCE (std::string sID, uint64_t twRDRootIx);
            virtual ~IREFERENCE ();

            RMAP::CORE::MODEL* Create (RMAP::CORE::SOURCE* pParam) override;
         };

      public:
         static RMAP::CORE::MODEL::FACTORY* factory ();

         RMROOT (IREFERENCE* pReference, RMAP::CORE::MEM::SOURCE* pSource);
         virtual ~RMROOT ();

         // ===== Public Methods =====================================================================================================

         RMAP::CORE::CLIENT::IACTION* Request (std::string sAction) override;
      };

      /*******************************************************************************************************************************
      **                                                 Object: RMTOBJECT                                                          **
      *******************************************************************************************************************************/

      class IO_RMTOBJECT : public IO_OBJECT
      {
      public:
         class FACTORY : public RMAP::SVC_SOCKETIO::IO_OBJECT::FACTORY
         {
         public:
            FACTORY (std::string sID_Service, std::string sID_Model, int wClass, std::map<std::string, const RMAP::CORE::CLIENT::ACTION*> &apAction, bool bIndependent);
            virtual ~FACTORY ();

            RMAP::CORE::SOURCE* Create (RMAP::CORE::CLIENT* pClient) override;
         };

      public:
         IO_RMTOBJECT (RMAP::CORE::MEM::SOURCE::REFERENCE* pReference, RMAP::CORE::CLIENT* pClient);
         virtual ~IO_RMTOBJECT ();

         static void init ();
         static FACTORY* factory ();

         void Read (ordered_json& jSrc, RMAP::CORE::MODEL* pModel) override;
         bool Attach () override;

         static std::map<std::string, const RMAP::CORE::CLIENT::ACTION*> aAction;

      private:
         class Impl;
         Impl* m_pImpl;
      };

      class SB_RMTOBJECT : public RMAP::SVC_SB::SB_OBJECT
      {
      public:
         class FACTORY : public RMAP::SVC_SB::SB_OBJECT::FACTORY
         {
         public:
            FACTORY (std::string sID_Service, std::string sID_Model, int wClass, std::map<std::string, const RMAP::CORE::CLIENT::ACTION*>& apAction, bool bIndependent, RMAP::SVC_SB::MAP* pMap);
            virtual ~FACTORY ();

            RMAP::CORE::SOURCE* Create (RMAP::CORE::CLIENT* pClient) override;
         };

      public:
         SB_RMTOBJECT (RMAP::CORE::MEM::SOURCE::REFERENCE* pReference, RMAP::SVC_SB::MAP* pMap, RMAP::CORE::CLIENT* pClient);
         virtual ~SB_RMTOBJECT ();

         static void init ();
         static FACTORY* factory ();

         void Read (ordered_json& jSrc, RMAP::CORE::MODEL* pModel) override;

         static std::map<std::string, const RMAP::CORE::CLIENT::ACTION*> aAction;

      private:
         class Impl;
         Impl* m_pImpl;
      };

      class RMTOBJECT : public RMAP::CORE::MODEL_OBJECT, public MAP_OBJECT
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
         class FACTORY : public RMAP::CORE::MODEL_OBJECT::FACTORY
         {
         public:
            FACTORY (std::string sID);
            virtual ~FACTORY ();

            // ===== Public Properties ==================================================================================================

            virtual RMAP::CORE::IREFERENCE<RMAP::CORE::MODEL*, RMAP::CORE::SOURCE*>* Reference (std::vector<std::string> asArgs) override;
         };

      public:
         class IREFERENCE : public RMAP::CORE::MODEL_OBJECT::IREFERENCE
         {
         public:
            IREFERENCE (std::string sID, uint64_t twRDRootIx);
            virtual ~IREFERENCE ();

            RMAP::CORE::MODEL* Create (RMAP::CORE::SOURCE* pParam) override;
         };

      public:
         static RMAP::CORE::MODEL::FACTORY* factory ();

         RMTOBJECT (IREFERENCE* pReference, RMAP::CORE::MEM::SOURCE* pSource);
         virtual ~RMTOBJECT ();

         // ===== Public Methods =====================================================================================================

         RMAP::CORE::CLIENT::IACTION* Request (std::string sAction) override;

         // Modifiers                                              
         void Properties  (const MAP_OBJECT_PROPERTIES_TERRESTIAL& _Properties)    &;
      };

      void Install ();
      void Unstall ();
   }
}

#endif //RMAP_MAP_H
