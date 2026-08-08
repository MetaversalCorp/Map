/*******************************************************************************************************************************
**                                                                                                                            **
**                                                         MAP : Map.h                                                        **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2024 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

#ifndef RMAP_MAP_H
#define RMAP_MAP_H

namespace RMAP
{
   namespace MAP
   {
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
      **                                                 Object: MAP_DATA                                                           **
      *******************************************************************************************************************************/

      class MAP_DATA
      {
      public:
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
            uint8_t               abReserved[16];
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

      public:
         OBJECT_HEAD                   Head        = {};
         MAP_OBJECT_NAME               Name        = {};
         MAP_OBJECT_TYPE               Type        = {};
         MAP_OBJECT_OWNER              Owner       = {};
         MAP_OBJECT_RESOURCE           Resource    = {};
         MAP_OBJECT_TRANSFORM          Transform   = {};
         MAP_OBJECT_ORBIT              Orbit       = {};
         MAP_OBJECT_BOUND              Bound       = {};
         MAP_OBJECT_PROPERTIES         Properties  = {};
      };

      class MAP_OBJECT
      {
      public:
         virtual void GetData (MAP_DATA& Map_Data) = 0;
      };
      
      /*******************************************************************************************************************************
      **                                                 RESOURCE                                                                   **
      *******************************************************************************************************************************/

      class RESOURCE
      {
      public:
         RESOURCE (uint64_t qwResource = 0, std::string sName = {}, std::string sReference = {});

         RESOURCE& operator=(RESOURCE    const& rhs)&;
         RESOURCE& operator=(RESOURCE&& rhs) & noexcept;
         RESOURCE (RESOURCE    const& other);
         RESOURCE (RESOURCE&& other) noexcept;
         virtual ~RESOURCE ()                           noexcept;

         // Accessors
         std::string const&   sName ()                        const &;
         std::string const&   sReference ()                   const &;
         uint64_t             qwResource ()                   const &;

         std::string          sName ()                             &&;
         std::string          sReference ()                        &&;

         // Modifiers                                              
         RESOURCE&            qwResource (uint64_t    _qwResource)  &;
         RESOURCE&            sName      (std::string _wsForename)  &;
         RESOURCE&            sReference (std::string _wsSurname)   &;

         void GetData (MAP_DATA::MAP_OBJECT_RESOURCE& Map_Data);

      private:
         class Impl;
         Impl* m_pImpl;
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
         class NAME
         {
         public:
            NAME (std::wstring wsRMCObjectId = {});

            NAME& operator=(NAME    const & rhs) &;
            NAME& operator=(NAME         && rhs) & noexcept;
            NAME           (NAME    const & other);
            NAME           (NAME         && other) noexcept;
            virtual ~NAME  ()                      noexcept;

            // Accessors
            std::wstring const & wsRMCObjectId () const &;

            std::wstring         wsRMCObjectId ()       &&;

            // Modifiers                                              
            NAME & wsRMCObjectId (std::wstring _wsRMCObjectId) &;

         private:
            class Impl;
            Impl* m_pImpl;
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

         void GetData (MAP_DATA& Map_Data) override;

         RMAP::CORE::CLIENT::IACTION* Request (std::string sAction) override;

      // Accessors 
         NAME                                      const & Name ()                           const &;
         MAP_DATA::MAP_OBJECT_TYPE                 const & Type ()                           const &;
         MAP_DATA::MAP_OBJECT_OWNER                const & Owner ()                          const &;
         RESOURCE                                  const & Resource ()                       const &;
         MAP_DATA::MAP_OBJECT_TRANSFORM            const & Transform ()                      const &;
         MAP_DATA::MAP_OBJECT_ORBIT_CELESTIAL      const & Orbit_Spin ()                     const &;
         MAP_DATA::MAP_OBJECT_BOUND                const & Bound ()                          const &;
         MAP_DATA::MAP_OBJECT_PROPERTIES_CELESTIAL const & Properties ()                     const &;
         uint32_t                                  const   Children ()                       const &;

         // Modifiers                                              
         RMCOBJECT& Name        (const NAME& _Name)                                                &;
         RMCOBJECT& Type        (const MAP_DATA::MAP_OBJECT_TYPE& _Type)                           &;
         RMCOBJECT& Owner       (const MAP_DATA::MAP_OBJECT_OWNER& _Owner)                         &;
         RMCOBJECT& Resource    (const RESOURCE& _Resource)                                        &;
         RMCOBJECT& Transform   (const MAP_DATA::MAP_OBJECT_TRANSFORM& _Transform)                 &;
         RMCOBJECT& Orbit_Spin  (const MAP_DATA::MAP_OBJECT_ORBIT_CELESTIAL& _Orbit_Spin)          &;
         RMCOBJECT& Bound       (const MAP_DATA::MAP_OBJECT_BOUND& _Bound)                         &;
         RMCOBJECT& Properties  (const MAP_DATA::MAP_OBJECT_PROPERTIES_CELESTIAL& _Properties)     &;
         RMCOBJECT& Children    (uint32_t _nChildren)                                              &;

      private:
         class Impl;
         Impl* m_pImpl;
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
         class NAME
         {
         public:
            NAME (std::wstring wsRMPObjectId = {});

            NAME& operator=(NAME    const& rhs)&;
            NAME& operator=(NAME&& rhs) & noexcept;
            NAME (NAME    const& other);
            NAME (NAME&& other) noexcept;
            virtual ~NAME ()                      noexcept;

            // Accessors
            std::wstring const& wsRMPObjectId () const&;

            std::wstring         wsRMPObjectId ()&&;

            // Modifiers                                              
            NAME& wsRMPObjectId (std::wstring _wsRMPObjectId)&;

         private:
            class Impl;
            Impl* m_pImpl;
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

         RMPOBJECT (IREFERENCE* pReference, RMAP::CORE::MEM::SOURCE* pSource);
         virtual ~RMPOBJECT ();

         // ===== Public Methods =====================================================================================================

         void GetData (MAP_DATA& Map_Data) override;

         RMAP::CORE::CLIENT::IACTION* Request (std::string sAction) override;

         // Accessors 
         NAME                                      const & Name ()                        const &;
         MAP_DATA::MAP_OBJECT_TYPE                 const & Type ()                        const &;
         MAP_DATA::MAP_OBJECT_OWNER                const & Owner ()                       const &;
         RESOURCE                                  const & Resource ()                    const &;
         MAP_DATA::MAP_OBJECT_TRANSFORM            const & Transform ()                   const &;
         MAP_DATA::MAP_OBJECT_BOUND                const & Bound ()                       const &;
         uint32_t                                  const   Children ()                    const &;

         // Modifiers                                              
         RMPOBJECT& Name        (const NAME& _Name)                                             &;
         RMPOBJECT& Type        (const MAP_DATA::MAP_OBJECT_TYPE& _Type)                        &;
         RMPOBJECT& Owner       (const MAP_DATA::MAP_OBJECT_OWNER& _Owner)                      &;
         RMPOBJECT& Resource    (const RESOURCE& _Resource)                                     &;
         RMPOBJECT& Transform   (const MAP_DATA::MAP_OBJECT_TRANSFORM& _Transform)              &;
         RMPOBJECT& Bound       (const MAP_DATA::MAP_OBJECT_BOUND& _Bound)                      &;
         RMPOBJECT& Children    (uint32_t _nChildren)                                           &;

      private:
         class Impl;
         Impl* m_pImpl;
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
         class NAME
         {
         public:
            NAME (std::wstring wsRMRootId = {});

            NAME& operator=(NAME    const & rhs) &;
            NAME& operator=(NAME         && rhs) & noexcept;
            NAME           (NAME    const & other);
            NAME           (NAME         && other) noexcept;
            virtual ~NAME  ()                      noexcept;

            // Accessors
            std::wstring const & wsRMRootId () const &;

            std::wstring         wsRMRootId ()       &&;

            // Modifiers                                              
            NAME & wsRMRootId (std::wstring _wsRMRootId) &;

         private:
            class Impl;
            Impl* m_pImpl;
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

         RMROOT (IREFERENCE* pReference, RMAP::CORE::MEM::SOURCE* pSource);
         virtual ~RMROOT ();

         // ===== Public Methods =====================================================================================================

         void GetData (MAP_DATA& Map_Data) override;

         RMAP::CORE::CLIENT::IACTION* Request (std::string sAction) override;

      // Accessors 
         NAME                             const & Name ()                          const &;
         MAP_DATA::MAP_OBJECT_OWNER       const & Owner ()                         const &;

         // Modifiers                                              
         RMROOT& Name        (const NAME& _Name)                                          &;
         RMROOT& Owner       (const MAP_DATA::MAP_OBJECT_OWNER& _Owner)                   &;

      private:
         class Impl;
         Impl* m_pImpl;
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
         class NAME
         {
         public:
            NAME (std::wstring wsRMTObjectId = {});

            NAME& operator=(NAME    const & rhs) &;
            NAME& operator=(NAME         && rhs) & noexcept;
            NAME           (NAME    const & other);
            NAME           (NAME         && other) noexcept;
            virtual ~NAME  ()                      noexcept;

            // Accessors
            std::wstring const & wsRMTObjectId () const &;

            std::wstring         wsRMTObjectId ()       &&;

            // Modifiers                                              
            NAME & wsRMTObjectId (std::wstring _wsRMTObjectId) &;

         private:
            class Impl;
            Impl* m_pImpl;
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

         void GetData (MAP_DATA& Map_Data) override;

         RMAP::CORE::CLIENT::IACTION* Request (std::string sAction) override;

      // Accessors 
         NAME                                         const & Name ()                        const &;
         MAP_DATA::MAP_OBJECT_TYPE                    const & Type ()                        const &;
         MAP_DATA::MAP_OBJECT_OWNER                   const & Owner ()                       const &;
         RESOURCE                                     const & Resource ()                    const &;
         MAP_DATA::MAP_OBJECT_TRANSFORM               const & Transform ()                   const &;
         MAP_DATA::MAP_OBJECT_BOUND                   const & Bound ()                       const &;
         MAP_DATA::MAP_OBJECT_PROPERTIES_TERRESTIAL   const & Properties ()                  const &;
         uint32_t                                     const   Children ()                    const &;

         // Modifiers                                              
         RMTOBJECT& Name        (const NAME& _Name)                                                &;
         RMTOBJECT& Type        (const MAP_DATA::MAP_OBJECT_TYPE& _Type)                           &;
         RMTOBJECT& Owner       (const MAP_DATA::MAP_OBJECT_OWNER& _Owner)                         &;
         RMTOBJECT& Resource    (const RESOURCE& _Resource)                                        &;
         RMTOBJECT& Transform   (const MAP_DATA::MAP_OBJECT_TRANSFORM& _Transform)                 &;
         RMTOBJECT& Bound       (const MAP_DATA::MAP_OBJECT_BOUND& _Bound)                         &;
         RMTOBJECT& Properties  (const MAP_DATA::MAP_OBJECT_PROPERTIES_TERRESTIAL& _Properties)    &;
         RMTOBJECT& Children    (uint32_t _nChildren)                                              &;

      private:
         class Impl;
         Impl* m_pImpl;
      };

      void Install ();
      void Unstall ();
   }
}

#endif //RMAP_MAP_H
