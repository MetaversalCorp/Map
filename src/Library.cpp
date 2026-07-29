/*******************************************************************************************************************************
**                                                                                                                            **
**                                                   MVRP_cpp : LibraryMap.cpp                                           **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2026 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

#include "pch.h"

using namespace RMAP;

std::string LibraryMap::sModuleName = "Map";

LibraryMap::LibraryMap (std::string sID, std::string sCopyright, std::string sTitle, std::string sVersion) :
   RMAP::CORE::LIBRARY (sID, sCopyright, sTitle, sVersion),
   m_pRequire (nullptr)
{
}

LibraryMap::~LibraryMap ()
{
}

bool LibraryMap::Install (RMAP::CORE::PLUGIN* pPlugin)
{
   bool bResult = true;
   RMAP::CORE::APP* pCore = RMAP::CORE::APP::GetInstance ();

   if (m_pRequire = pCore->Require ("Socket.IO,Statabase", "", ""))
   {
      m_apFactory_Model.push_back (RMAP::MAP::RMROOT::factory ());
      m_apFactory_Model.push_back (RMAP::MAP::RMCOBJECT::factory ());
      m_apFactory_Model.push_back (RMAP::MAP::RMTOBJECT::factory ());
      m_apFactory_Model.push_back (RMAP::MAP::RMPOBJECT::factory ());

      m_apFactory_Source.push_back (RMAP::MAP::SB_RMROOT::factory ());
      m_apFactory_Source.push_back (RMAP::MAP::SB_RMCOBJECT::factory ());
      m_apFactory_Source.push_back (RMAP::MAP::SB_RMTOBJECT::factory ());
      m_apFactory_Source.push_back (RMAP::MAP::SB_RMPOBJECT::factory ());
//      m_apFactory_Source.push_back (RMAP::MAP::REST_RMROOT::factory ());
//      m_apFactory_Source.push_back (RMAP::MAP::REST_RMCOBJECT::factory ());
//      m_apFactory_Source.push_back (RMAP::MAP::REST_RMTOBJECT::factory ());
//      m_apFactory_Source.push_back (RMAP::MAP::REST_RMPOBJECT::factory ());
      m_apFactory_Source.push_back (RMAP::MAP::IO_RMROOT::factory ());
      m_apFactory_Source.push_back (RMAP::MAP::IO_RMCOBJECT::factory ());
      m_apFactory_Source.push_back (RMAP::MAP::IO_RMTOBJECT::factory ());
      m_apFactory_Source.push_back (RMAP::MAP::IO_RMPOBJECT::factory ());

      m_apFactory_Package.push_back (PACKAGE_MAP_SB::factory ());
//      m_apFactory_Package.push_back (RMAP::MAP::MAP_REST::factory ());
      m_apFactory_Package.push_back (PACKAGE_MAP_IO::factory ());

      pPlugin->Factory_Models   (m_apFactory_Model);
      pPlugin->Factory_Sources  (m_apFactory_Source);
      pPlugin->Factory_Packages (m_apFactory_Package);
   }
   else bResult = false;

   return bResult;
}

void LibraryMap::Unstall (RMAP::CORE::PLUGIN* pPlugin)
{
   int n;
   RMAP::CORE::APP* pCore = RMAP::CORE::APP::GetInstance ();

   if (m_pRequire)
   {
      for (n = 0; n < m_apFactory_Model.size (); n++)
         delete m_apFactory_Model[n];

      for (n = 0; n < m_apFactory_Source.size (); n++)
         delete m_apFactory_Source[n];

      for (n = 0; n < m_apFactory_Package.size (); n++)
         delete m_apFactory_Package[n];

      pCore->Release (m_pRequire);

      m_pRequire = NULL;
   }
}

/*******************************************************************************************************************************
**                                                     Startup/Shutdown                                                       **
*******************************************************************************************************************************/

void RMAP::MAP::Install ()
{
   RMAP::CORE::APP* pCore = RMAP::CORE::APP::GetInstance ();

   pCore->LibraryInstall (new LibraryMap (LibraryMap::sModuleName, "Copyright 2014 - 2026 Metaversal Corporation. All rights reserved.", "Map", ""));
}

void RMAP::MAP::Unstall ()
{
   RMAP::CORE::APP* pCore = RMAP::CORE::APP::GetInstance ();

   pCore->LibraryUnstall (LibraryMap::sModuleName);
}
