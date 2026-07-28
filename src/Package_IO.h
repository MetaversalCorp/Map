/*******************************************************************************************************************************
**                                                                                                                            **
**                                      MVRP1_Core_cpp : Package_SB_RP1.h                                                     **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2024 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

class PACKAGE_MAP_IO : public RMAP::CORE::PACKAGE
{
public:
   class FACTORY : public RMAP::CORE::PACKAGE::FACTORY
   {
   public:
      FACTORY (const std::string& sID_Service, const std::string& sID_Package, const std::vector<std::string>& aService, const std::vector<std::string>& aModel, const std::vector<std::string>& aSource);
      virtual ~FACTORY ();

      // ===== Public Properties ==================================================================================================

      virtual PACKAGE::IREFERENCE* Reference (const std::string& sNamespace) override;
   };

public:
   class IREFERENCE : public RMAP::CORE::PACKAGE::IREFERENCE
   {
   public:
      IREFERENCE (const std::string& sID, const std::string& sNamespace, const std::vector<std::string>& aService, const std::vector<std::string>& aModel, const std::vector<std::string>& aSource);
      virtual ~IREFERENCE ();

      virtual RMAP::CORE::PACKAGE* Create (RMAP::CORE::PACKAGE::PACKAGEPARAM* pParam) override;
   };

public:
   static RMAP::CORE::PACKAGE::FACTORY* factory ();

   PACKAGE_MAP_IO (IREFERENCE* pReference, RMAP::CORE::PACKAGE::PACKAGEPARAM* pParam);
   virtual ~PACKAGE_MAP_IO ();
};
