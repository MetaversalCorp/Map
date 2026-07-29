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

      struct DOUBLE4
      {
         double                        dX;
         double                        dY;
         double                        dZ;
         double                        dW;
      };

      struct DOUBLE3
      {
         double                        dX;
         double                        dY;
         double                        dZ;
      };

      struct PARENT
      {
         uint16_t                      wClass;
         uint64_t                      twObjectIx;
      };

      struct RELATIVEX
      {
         DOUBLE3                       vPosition;
      };

      struct POSITION_UNIVERSAL
      {
         PARENT                        Parent;
         RELATIVEX                     Relative;
      };

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

      class RESOURCE
      {
      public:
         RESOURCE (uint64_t qwResource = 0, std::string sName  = {}, std::string sReference  = {});

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
         RESOURCE & qwResource (uint64_t    _qwResource) &;
         RESOURCE & sName      (std::string _wsForename) &;
         RESOURCE & sReference (std::string _wsSurname ) &;

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
         TYPE                 const & pType ()                         const &;
         OWNER                const & pOwner ()                        const &;
         RESOURCE             const & pResource ()                     const &;
         TRANSFORM            const & pTransform ()                    const &;
         ORBIT_SPIN           const & pOrbit_Spin ()                   const &;
         BOUND                const & pBound ()                        const &;
         PROPERTIES           const & pProperties ()                   const &;
         POD                  const & pPOD ()                          const &;

         // Modifiers                                              
         RMCOBJECT& pName        (NAME       _pName)          &;
         RMCOBJECT& pType        (TYPE       _pType)          &;
         RMCOBJECT& pOwner       (OWNER      _pOwner)         &;
         RMCOBJECT& pResource    (RESOURCE   _pResource)      &;
         RMCOBJECT& pTransform   (TRANSFORM  _pTransform)     &;
         RMCOBJECT& pOrbit_Spin  (ORBIT_SPIN _pOrbit_Spin)    &;
         RMCOBJECT& pBound       (BOUND      _pBound)         &;
         RMCOBJECT& pProperties  (PROPERTIES _pProperties)    &;
         RMCOBJECT& pPOD         (POD        _pPOD)           &;

      private:
         NAME*                   m_pName;
         TYPE*                   m_pType;
         OWNER*                  m_pOwner;
         RESOURCE*               m_pResource;
         TRANSFORM*              m_pTransform;
         ORBIT_SPIN*             m_pOrbit_Spin;
         BOUND*                  m_pBound;
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
         NAME       const & pName ()                         const &;
         TYPE       const & pType ()                         const &;
         OWNER      const & pOwner ()                        const &;
         RESOURCE   const & pResource ()                     const &;
         TRANSFORM  const & pTransform ()                    const &;
         BOUND      const & pBound ()                        const &;
         POD                  const & pPOD ()                          const &;

         // Modifiers                                              
         RMPOBJECT& pName        (NAME _pName)              &;
         RMPOBJECT& pType        (TYPE       _pType)        &;
         RMPOBJECT& pOwner       (OWNER      _pOwner)       &;
         RMPOBJECT& pResource    (RESOURCE   _pResource)    &;
         RMPOBJECT& pTransform   (TRANSFORM  _pTransform)   &;
         RMPOBJECT& pBound       (BOUND      _pBound)       &;
         RMPOBJECT& pPOD         (POD        _pPOD)         &;

      private:
         NAME*      m_pName;
         TYPE*      m_pType;
         OWNER*     m_pOwner;
         RESOURCE*  m_pResource;
         TRANSFORM* m_pTransform;
         BOUND*     m_pBound;
         POD*       m_pPOD;
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
         NAME                 const & pName ()                          const &;
         OWNER                const & pOwner ()                         const &;

         // Modifiers                                              
         RMROOT& pName        (NAME _pName)                                   &;
         RMROOT& pOwner       (OWNER _pOwner)                                 &;

      private:
         NAME*         m_pName;
         OWNER*        m_pOwner;
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
         NAME           const & pName ()                         const &;
         TYPE           const & pType ()                         const &;
         OWNER          const & pOwner ()                        const &;
         RESOURCE       const & pResource ()                     const &;
         TRANSFORM      const & pTransform ()                    const &;
         BOUND          const & pBound ()                        const &;
         PROPERTIES     const & pProperties ()                   const &;
         POD            const & pPOD ()                          const &;

         // Modifiers                                              
         RMTOBJECT& pName        (NAME       _pName)          &;
         RMTOBJECT& pType        (TYPE       _pType)          &;
         RMTOBJECT& pOwner       (OWNER      _pOwner)         &;
         RMTOBJECT& pResource    (RESOURCE   _pResource)      &;
         RMTOBJECT& pTransform   (TRANSFORM  _pTransform)     &;
         RMTOBJECT& pBound       (BOUND      _pBound)         &;
         RMTOBJECT& pProperties  (PROPERTIES _pProperties)    &;
         RMTOBJECT& pPOD         (POD        _pPOD)           &;

      private:
         NAME*          m_pName;
         TYPE*          m_pType;
         OWNER*         m_pOwner;
         RESOURCE*      m_pResource;
         TRANSFORM*     m_pTransform;
         BOUND*         m_pBound;
         PROPERTIES*    m_pProperties;
         POD*           m_pPOD;
      };

      void Install ();
      void Unstall ();
   }
}

#include "Map_ClassTypes.h"

#endif //RMAP_MAP_H
