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
      **                                                 Object: MAP_DATA                                                           **
      *******************************************************************************************************************************/

      class MAP_OBJECT
      {
      public:
         MAP_OBJECT (uint16_t wClass_Parent, uint64_t twParentIx, uint16_t wClass_Object, uint64_t twObjectIx);
         virtual ~MAP_OBJECT ();

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
            _NULL         =  0,
            UNIVERSE      =  1,
            SUPERCLUSTER  =  2,
            GALAXYCLUSTER =  3,
            GALAXY        =  4,
            SECTOR        =  5,
            NEBULA        =  6,
            STARCLUSTER   =  7,
            BLACKHOLE     =  8,
            STARSYSTEM    =  9,
            STAR          = 10,
            PLANETSYSTEM  = 11,
            PLANET        = 12,
            MOON          = 13,
            DEBRIS        = 14,
            SATELLITE     = 15,
            TRANSPORT     = 16,
            SURFACE       = 17,
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
