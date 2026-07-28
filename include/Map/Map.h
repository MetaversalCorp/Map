/*******************************************************************************************************************************
**                                                                                                                            **
**                                                      MVRP_Map_cpp : MVRP_Map.h                                             **
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
      **                                                 COORDINATES                                                                **
      *******************************************************************************************************************************/

      class DOUBLE4
      {
      public:
         DOUBLE4 (double dX = 0.0, double dY = 0.0, double dZ = 0.0, double dW = 0.0);

         DOUBLE4& operator=(DOUBLE4    const& rhs)&;
         DOUBLE4& operator=(DOUBLE4&& rhs) & noexcept;
         DOUBLE4 (DOUBLE4    const& other);
         DOUBLE4 (DOUBLE4&& other)  noexcept;
         virtual ~DOUBLE4 ()                          noexcept;

         // Accessors
         double dX () const&;
         double dY () const&;
         double dZ () const&;
         double dW () const&;

         // Modifiers
         DOUBLE4& dX (double dX)&;
         DOUBLE4& dY (double dY)&;
         DOUBLE4& dZ (double dZ)&;
         DOUBLE4& dW (double dW)&;

      private:
         double m_dX;
         double m_dY;
         double m_dZ;
         double m_dW;
      };

      class DOUBLE3
      {
      public:
         DOUBLE3 (double dX = 0.0, double dY = 0.0, double dZ = 0.0);

         DOUBLE3& operator=(DOUBLE3    const& rhs)&;
         DOUBLE3& operator=(DOUBLE3&& rhs) & noexcept;
         DOUBLE3 (DOUBLE3    const& other);
         DOUBLE3 (DOUBLE3&& other)  noexcept;
         virtual ~DOUBLE3 ()                          noexcept;

         // Accessors
         double dX () const&;
         double dY () const&;
         double dZ () const&;

         // Modifiers
         DOUBLE3& dX (double dX)&;
         DOUBLE3& dY (double dY)&;
         DOUBLE3& dZ (double dZ)&;

      private:
         double m_dX;
         double m_dY;
         double m_dZ;
      };

      class PARENT
      {
      public:
         PARENT (uint16_t wClass = 0, uint64_t twObjectIx = 0);

         PARENT& operator=(PARENT    const& rhs)&;
         PARENT& operator=(PARENT&& rhs) & noexcept;
         PARENT (PARENT    const& other);
         PARENT (PARENT&& other)    noexcept;
         virtual ~PARENT ()                           noexcept;

         // Accessors
         uint16_t   wClass () const&;
         uint64_t   twObjectIx () const&;

         // Modifiers
         PARENT& wClass (uint16_t wClass)&;
         PARENT& twObjectIx (uint64_t twObjectIx)&;

      private:
         uint16_t   m_wClass;
         uint64_t   m_twObjectIx;
      };

      class RELATIVE
      {
      public:
         RELATIVE (DOUBLE3 vPosition = {});

         RELATIVE& operator=(RELATIVE    const& rhs)&;
         RELATIVE& operator=(RELATIVE&& rhs) & noexcept;
         RELATIVE (RELATIVE    const& other);
         RELATIVE (RELATIVE&& other)    noexcept;
         virtual ~RELATIVE ()                             noexcept;

         // Accessors
         DOUBLE3 const& vPosition () const&;

         // Modifiers   
         RELATIVE& vPosition (DOUBLE3 _vPosition)&;

      private:
         DOUBLE3 m_vPosition;
      };

      class POSITION_UNIVERSAL
      {
      public:
         POSITION_UNIVERSAL (PARENT pParent = {}, RELATIVE pRelative = {});

         POSITION_UNIVERSAL& operator=(POSITION_UNIVERSAL    const& rhs)&;
         POSITION_UNIVERSAL& operator=(POSITION_UNIVERSAL&& rhs) & noexcept;
         POSITION_UNIVERSAL (POSITION_UNIVERSAL    const& other);
         POSITION_UNIVERSAL (POSITION_UNIVERSAL&& other) noexcept;
         virtual ~POSITION_UNIVERSAL ()                      noexcept;

         // Accessors
         PARENT   const& Parent ()   const&;
         RELATIVE const& Relative () const&;

         // Modifiers   
         POSITION_UNIVERSAL& Parent (PARENT _Parent)&;
         POSITION_UNIVERSAL& Relative (RELATIVE _Relative)&;

      private:
         PARENT   m_Parent;
         RELATIVE m_Relative;
      };

      class RZONE_ROUTE
      {
      public:
         RZONE_ROUTE (uint32_t dwIPAddress_RHub = 0, uint32_t dwIPAddress_RProximity = 0);

         // Accessors
         uint32_t dwIPAddress_RHub ()       const&;
         uint32_t dwIPAddress_RProximity () const&;

         // Modifiers
         RZONE_ROUTE& dwIPAddress_RHub (uint32_t _dwIPAddress_RHub)&;
         RZONE_ROUTE& dwIPAddress_RProximity (uint32_t _dwIPAddress_RProximity)&;

      private:
         uint32_t m_dwIPAddress_RHub;
         uint32_t m_dwIPAddress_RProximity;
      };

      class RZONE_POSITION
      {
      public:
         RZONE_POSITION (PARENT pParent = {}, DOUBLE3 vPosition = {});

         RZONE_POSITION& operator=(RZONE_POSITION    const& rhs)&;
         RZONE_POSITION& operator=(RZONE_POSITION&& rhs) & noexcept;
         RZONE_POSITION (RZONE_POSITION    const& other);
         RZONE_POSITION (RZONE_POSITION&& other) noexcept;
         virtual ~RZONE_POSITION ()                                  noexcept;

         // Accessors
         PARENT   const& pParent ()   const&;
         DOUBLE3  const& vPosition () const&;

         // Modifiers   
         RZONE_POSITION& pParent (PARENT _pParent)&;
         RZONE_POSITION& vPosition (DOUBLE3 _vPosition)&;

      private:
         PARENT   m_pParent;
         DOUBLE3  m_vPosition;
      };

      namespace RMCOMMON
      {
         struct TYPE
         {
            uint8_t                 bType;
            uint8_t                 bSubtype;
            uint8_t                 bFiction;
            uint8_t                 bMovable;
         };

         struct OWNER
         {
            uint64_t                twRPersonaIx;
         };

         class RESOURCE
         {
         public:
            RESOURCE (uint64_t qwResource = 0,
                        std::string sName  = {}, 
                        std::string sReference  = {}  );

            RESOURCE& operator=(RESOURCE    const & rhs) &;
            RESOURCE& operator=(RESOURCE         && rhs) & noexcept;
            RESOURCE           (RESOURCE    const & other);
            RESOURCE           (RESOURCE         && other) noexcept;
            virtual ~RESOURCE ()                           noexcept;

            // Accessors
            std::string const & sName ()       const &;
            std::string const & sReference ()  const &;
            uint64_t            qwResource ()  const &;

            std::string         sName ()       &&;
            std::string         sReference ()  &&;

            // Modifiers                                              
            RESOURCE & qwResource (uint64_t     _qwResource) &;
            RESOURCE & sName      (std::string _wsForename)  &;
            RESOURCE & sReference (std::string _wsSurname )  &;

         private:
            class Impl;
            Impl* m_pImpl;
         };

         struct TRANSFORM
         {
            DOUBLE3                 vPosition;
            DOUBLE4                 qRotation;
            DOUBLE3                 vScale;
         };

         struct ORBIT_SPIN
         {
            TIME                    tmPeriod;
            TIME                    tmOrigin;
            double                  dA;
            double                  dB;
         };

         struct BOUND
         {
            double                  dX;
            double                  dY;
            double                  dZ;
         };
      }

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

      class RMCOBJECT : public RMAP::CORE::MODEL_OBJECT
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

         struct PROPERTIES
         {
            double                  fMass;
            double                  fGravity;
            double                  fColor;
            double                  fBrightness;
            double                  fReflectivity;
         };

         struct POD
         {
            uint32_t                nChildren;
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

      // Accessors 
         NAME                 const & pName ()                         const &;
         RMCOMMON::TYPE       const & pType ()                         const &;
         RMCOMMON::OWNER      const & pOwner ()                        const &;
         RMCOMMON::RESOURCE   const & pResource ()                     const &;
         RMCOMMON::TRANSFORM  const & pTransform ()                    const &;
         RMCOMMON::ORBIT_SPIN const & pOrbit_Spin ()                   const &;
         RMCOMMON::BOUND      const & pBound ()                        const &;
         PROPERTIES           const & pProperties ()                   const &;
         POD                  const & pPOD ()                          const &;

         // Modifiers                                              
         RMCOBJECT& pName        (NAME _pName)                          &;
         RMCOBJECT& pType        (RMCOMMON::TYPE       _pType)          &;
         RMCOBJECT& pOwner       (RMCOMMON::OWNER      _pOwner)         &;
         RMCOBJECT& pResource    (RMCOMMON::RESOURCE   _pResource)      &;
         RMCOBJECT& pTransform   (RMCOMMON::TRANSFORM  _pTransform)     &;
         RMCOBJECT& pOrbit_Spin  (RMCOMMON::ORBIT_SPIN _pOrbit_Spin)    &;
         RMCOBJECT& pBound       (RMCOMMON::BOUND      _pBound)         &;
         RMCOBJECT& pProperties  (PROPERTIES           _pProperties)    &;
         RMCOBJECT& pPOD         (POD                  _pPOD)           &;

      private:
         NAME*                   m_pName;
         RMCOMMON::TYPE*         m_pType;
         RMCOMMON::OWNER*        m_pOwner;
         RMCOMMON::RESOURCE*     m_pResource;
         RMCOMMON::TRANSFORM*    m_pTransform;
         RMCOMMON::ORBIT_SPIN*   m_pOrbit_Spin;
         RMCOMMON::BOUND*        m_pBound;
         PROPERTIES*             m_pProperties;
         POD*                    m_pPOD;
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

      class RMPOBJECT : public RMAP::CORE::MODEL_OBJECT
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

         struct POD
         {
            uint32_t                nChildren;
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

         RMAP::CORE::CLIENT::IACTION* Request (std::string sAction) override;

         // Accessors 
         NAME                 const & pName ()                         const &;
         RMCOMMON::TYPE       const & pType ()                         const &;
         RMCOMMON::OWNER      const & pOwner ()                        const &;
         RMCOMMON::RESOURCE   const & pResource ()                     const &;
         RMCOMMON::TRANSFORM  const & pTransform ()                    const &;
         RMCOMMON::BOUND      const & pBound ()                        const &;
         POD                  const & pPOD ()                          const &;

         // Modifiers                                              
         RMPOBJECT& pName        (NAME _pName)&;
         RMPOBJECT& pType        (RMCOMMON::TYPE       _pType)       &;
         RMPOBJECT& pOwner       (RMCOMMON::OWNER      _pOwner)      &;
         RMPOBJECT& pResource    (RMCOMMON::RESOURCE   _pResource)   &;
         RMPOBJECT& pTransform   (RMCOMMON::TRANSFORM  _pTransform)  &;
         RMPOBJECT& pBound       (RMCOMMON::BOUND      _pBound)      &;
         RMPOBJECT& pPOD         (POD                  _pPOD)        &;

      private:
         NAME*                m_pName;
         RMCOMMON::TYPE*      m_pType;
         RMCOMMON::OWNER*     m_pOwner;
         RMCOMMON::RESOURCE*  m_pResource;
         RMCOMMON::TRANSFORM* m_pTransform;
         RMCOMMON::BOUND*     m_pBound;
         POD*                 m_pPOD;
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

      class RMROOT : public RMAP::CORE::MODEL_OBJECT
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

         RMAP::CORE::CLIENT::IACTION* Request (std::string sAction) override;

      // Accessors 
         NAME                 const & pName ()                         const &;
         RMCOMMON::OWNER      const & pOwner ()                        const &;

         // Modifiers                                              
         RMROOT& pName        (NAME _pName)                          &;
         RMROOT& pOwner       (RMCOMMON::OWNER      _pOwner)         &;

      private:
         NAME*                   m_pName;
         RMCOMMON::OWNER*        m_pOwner;
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

      class RMTOBJECT : public RMAP::CORE::MODEL_OBJECT
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

         struct PROPERTIES
         {
            uint8_t                 bLockToGround;
            uint8_t                 bYouth;
            uint8_t                 bAdult;
            uint8_t                 bAvatar;
         };

         struct POD
         {
            uint32_t                nChildren;
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

      // Accessors 
         NAME                 const & pName ()                         const &;
         RMCOMMON::TYPE       const & pType ()                         const &;
         RMCOMMON::OWNER      const & pOwner ()                        const &;
         RMCOMMON::RESOURCE   const & pResource ()                     const &;
         RMCOMMON::TRANSFORM  const & pTransform ()                    const &;
         RMCOMMON::BOUND      const & pBound ()                        const &;
         PROPERTIES           const & pProperties ()                   const &;
         POD                  const & pPOD ()                          const &;

         // Modifiers                                              
         RMTOBJECT& pName        (NAME _pName)                          &;
         RMTOBJECT& pType        (RMCOMMON::TYPE       _pType)          &;
         RMTOBJECT& pOwner       (RMCOMMON::OWNER      _pOwner)         &;
         RMTOBJECT& pResource    (RMCOMMON::RESOURCE   _pResource)      &;
         RMTOBJECT& pTransform   (RMCOMMON::TRANSFORM  _pTransform)     &;
         RMTOBJECT& pBound       (RMCOMMON::BOUND      _pBound)         &;
         RMTOBJECT& pProperties  (PROPERTIES           _pProperties)    &;
         RMTOBJECT& pPOD         (POD                  _pPOD)           &;

      private:
         NAME*                   m_pName;
         RMCOMMON::TYPE*         m_pType;
         RMCOMMON::OWNER*        m_pOwner;
         RMCOMMON::RESOURCE*     m_pResource;
         RMCOMMON::TRANSFORM*    m_pTransform;
         RMCOMMON::BOUND*        m_pBound;
         PROPERTIES*             m_pProperties;
         POD*                    m_pPOD;
      };

      void Install ();
      void Unstall ();
   }
}

#include "Map_ClassTypes.h"

#endif //RMAP_MAP_H
