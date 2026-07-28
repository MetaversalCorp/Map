/*******************************************************************************************************************************
**                                                                                                                            **
**                                      MVRP1_Core_cpp : LibraryMVRP_Map.h                                                    **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2024 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

class LibraryMap : public RMAP::CORE::LIBRARY
{
public:
   static std::string sModuleName;

public:
   LibraryMap (std::string sID, std::string sCopyright, std::string sTitle, std::string sVersion);
   ~LibraryMap ();

   bool Install (RMAP::CORE::PLUGIN* pPlugin) override;
   void Unstall (RMAP::CORE::PLUGIN* pPlugin) override;

private:
   RMAP::CORE::APP::REQUIRE* m_pRequire;

   std::vector<RMAP::CORE::SERVICE::FACTORY*>   m_apFactory_Service;
   std::vector<RMAP::CORE::MODEL::FACTORY*>     m_apFactory_Model;
   std::vector<RMAP::CORE::SOURCE::FACTORY*>    m_apFactory_Source;
   std::vector<RMAP::CORE::PACKAGE::FACTORY*>   m_apFactory_Package;
};
