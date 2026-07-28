/*******************************************************************************************************************************
**                                                                                                                            **
**                                      MVRP_RP1_Core_cpp : Source_IO_Object.h                                                **
**                                                                                                                            **
********************************************************************************************************************************
**                              Copyright 2014-2024 Metaversal Corporation. All rights reserved.                              **
*******************************************************************************************************************************/

/*******************************************************************************************************************************
**                                                   Convert                                                                  **
*******************************************************************************************************************************/

#define RMCOMMON_BOUND_SB "\"pBound\":"                                             \
   "{"                                                                              \
      "\"abReserved_A\"      : \"PAD (24)\","                                       \
      "\"dX\"                : \"DOUBLE\","                                         \
      "\"dY\"                : \"DOUBLE\","                                         \
      "\"dZ\"                : \"DOUBLE\""                                          \
   "}"                                                                              

#define RMCOMMON_BOUND_SB_PAD "\"pBound\":"                                         \
   "{"                                                                              \
      "\"abReserved_A\"      : \"PAD (48)\""                                        \
   "}"                                                                              

#define RMCOMMON_ORBIT_SPIN_SB "\"pOrbit_Spin\":"                                   \
   "{"                                                                              \
      "\"tmPeriod\"          : \"TIME\","                                           \
      "\"tmOrigin\"          : \"TIME\","                                           \
      "\"dA\"                : \"DOUBLE\","                                         \
      "\"dB\"                : \"DOUBLE\""                                          \
   "}"                                                                              

#define RMCOMMON_ORBIT_SPIN_SB_PAD "\"pOrbit_Spin\":"                               \
   "{"                                                                              \
      "\"abReserved_A\"      : \"PAD (32)\""                                        \
   "}"                                                                              

#define RMCOMMON_OWNER_SB "\"pOwner\":"                                             \
   "{"                                                                              \
      "\"twRPersonaIx\"      : \"TWORD8\""                                          \
   "}"                                                                              

#define RMCOMMON_TRANSFORM_SB "\"pTransform\":"                                     \
   "{"                                                                              \
      "\"vPosition\"       :"                                                       \
      "{"                                                                           \
         "\"dX\"                : \"DOUBLE\","                                      \
         "\"dY\"                : \"DOUBLE\","                                      \
         "\"dZ\"                : \"DOUBLE\""                                       \
      "},"                                                                          \
      "\"qRotation\"       :"                                                       \
      "{"                                                                           \
         "\"dX\"                : \"DOUBLE\","                                      \
         "\"dY\"                : \"DOUBLE\","                                      \
         "\"dZ\"                : \"DOUBLE\","                                      \
         "\"dw\"                : \"DOUBLE\""                                       \
      "},"                                                                          \
      "\"vScale\"          :"                                                       \
      "{"                                                                           \
         "\"dX\"                : \"DOUBLE\","                                      \
         "\"dY\"                : \"DOUBLE\","                                      \
         "\"dZ\"                : \"DOUBLE\""                                       \
      "}"                                                                           \
   "}"                                                                              

#define RMCOMMON_TRANSFORM_SB_PAD "\"pTransform\":"                                 \
   "{"                                                                              \
      "\"abReserved_A\"      : \"PAD (80)\""                                        \
   "}"

#define RMCOMMON_TYPE_SB "\"pType\":"                                               \
   "{"                                                                              \
      "\"bType\"             : \"BYTE\","                                           \
      "\"bSubtype\"          : \"BYTE\","                                           \
      "\"bFiction\"          : \"BYTE\","                                           \
      "\"bMovable\"          : \"BYTE\","                                           \
      "\"abReserved_A\"      : \"PAD (4)\""                                         \
   "}"                                                                              

#define RMCOMMON_TYPE_SB_PAD "\"pType\":"                                           \
   "{"                                                                              \
      "\"abReserved_A\"      : \"PAD (8)\""                                         \
   "}"                                                                              

#define RMCOMMON_RESOURCE_SB "\"pResource\":"                                       \
   "{"                                                                              \
      "\"qwResource\"        : \"QWORD\","                                          \
      "\"sName\"             : \"STRING (" TO_STRING (MVO_SIZE_RMNAME) ")\","       \
      "\"sReference\"        : \"STRING (" TO_STRING (MVO_SIZE_RMREFERENCE) ")\""   \
   "}"                                                                              

#define RMCOMMON_RESOURCE_SB_PAD "\"pResource\":"                                   \
   "{"                                                                              \
      "\"abReserved_A\"      : \"PAD (104)\""                                       \
   "}"                                                                              

#define RMCOMMON_DCOORD_SB "\"pCoord\":"                                            \
   "{"                                                                              \
      "\"abReserved_A\"      : \"PAD (7)\","                                        \
      "\"bCoord\"            : \"BYTE\","                                           \
      "\"dA\"                : \"DOUBLE\","                                         \
      "\"dB\"                : \"DOUBLE\","                                         \
      "\"dC\"                : \"DOUBLE\""                                          \
   "}"                                                                              

////////////////////////////

#define RMCOBJECT_NAME_SB "\"pName\":"                                              \
   "{"                                                                              \
      "\"wsRMCObjectId\"     : \"STRING_W (" TO_STRING (MVO_SIZE_RMCOBJECTID) ")\"" \
   "}"                                                                              

#define RMCOBJECT_PROPERTIES_SB "\"pProperties\":"                                  \
   "{"                                                                              \
      "\"fMass\"             : \"FLOAT\","                                          \
      "\"fGravity\"          : \"FLOAT\","                                          \
      "\"fColor\"            : \"FLOAT\","                                          \
      "\"fBrightness\"       : \"FLOAT\","                                          \
      "\"fReflectivity\"     : \"FLOAT\","                                          \
      "\"abReserved_A\"      : \"PAD (12)\""                                        \
   "}"                                                                              

////////////////////////////

#define RMPOBJECT_NAME_SB "\"pName\":"                                              \
   "{"                                                                              \
      "\"wsRMPObjectId\"     : \"STRING_W (" TO_STRING (MVO_SIZE_RMPOBJECTID) ")\"" \
   "}"                                                                              

#define RMPOBJECT_PROPERTIES_SB "\"pProperties\":"                                  \
   "{"                                                                              \
      "\"abReserved_A\"      : \"PAD (32)\""                                        \
   "}"                                                                              

////////////////////////////

#define RMTOBJECT_NAME_SB "\"pName\":"                                              \
   "{"                                                                              \
      "\"wsRMTObjectId\"     : \"STRING_W (" TO_STRING (MVO_SIZE_RMTOBJECTID) ")\"" \
   "}"                                                                              

#define RMTOBJECT_PROPERTIES_SB "\"pProperties\":"                                  \
   "{"                                                                              \
      "\"bLockToGround\"     : \"BYTE\","                                           \
      "\"bYouth\"            : \"BYTE\","                                           \
      "\"bAdult\"            : \"BYTE\","                                           \
      "\"bAvatar\"           : \"BYTE\","                                           \
      "\"abReserved_A\"      : \"PAD (28)\""                                        \
   "}"                                                                              

/////////////////////////////////////////////

#define RMROOT_NAME_SB "\"pName\":"                                                 \
   "{"                                                                              \
      "\"wsRMRootId\"        : \"STRING_W (" TO_STRING (MVO_SIZE_RMROOTID) ")\""    \
   "}"                                                                              

/////////////////////////////////////////////

#define RMROOT_PROPERTIES_SB "\"pProperties\":"                                     \
   "{"                                                                              \
      "\"abReserved_A\"      : \"PAD (32)\""                                        \
   "}"                                                                              

/******************************************************************************************************************************/
