// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#include <RMAP/RMAP.h>
#include <RMAP_Svc_SB/RMAP_Svc_SB.h>
#include <RMAP_Svc_Rest/RMAP_Svc_Rest.h>
#include <RMAP_Svc_SocketIO/RMAP_Svc_SocketIO.h>
#include <Map/Map.h>
#include <mutex>

#define OBJECTIX_COMPOSE(eClass, twObjectIx)      ((static_cast<uint64_t> (eClass) << 48)  |  (static_cast<uint64_t> (twObjectIx) & 0x0000FFFFFFFFFFFFull))

#include "Library.h"
#include "Package_SB.h"
#include "Package_IO.h"

void Convert_DCOORD                 (ordered_json& jRequest_Out, const ordered_json& jRequest_In);

void Convert_RMCOMMON_BOUND         (ordered_json& jRequest_Out, const ordered_json& jRequest_In);
void Convert_RMCOMMON_ORBIT_SPIN    (ordered_json& jRequest_Out, const ordered_json& jRequest_In);
void Convert_RMCOMMON_RESOURCE      (ordered_json& jRequest_Out, const ordered_json& jRequest_In);
void Convert_RMCOMMON_OWNER         (ordered_json& jRequest_Out, const ordered_json& jRequest_In);
void Convert_RMCOMMON_TYPE          (ordered_json& jRequest_Out, const ordered_json& jRequest_In);
void Convert_RMCOMMON_TRANSFORM     (ordered_json& jRequest_Out, const ordered_json& jRequest_In);

void Convert_RMCOBJECT_NAME         (ordered_json& jRequest_Out, const ordered_json& jRequest_In);
void Convert_RMCOBJECT_PROPERTIES   (ordered_json& jRequest_Out, const ordered_json& jRequest_In);

void Convert_RMTOBJECT_NAME         (ordered_json& jRequest_Out, const ordered_json& jRequest_In);
void Convert_RMTOBJECT_PROPERTIES   (ordered_json& jRequest_Out, const ordered_json& jRequest_In);

void Convert_RMPOBJECT_NAME         (ordered_json& jRequest_Out, const ordered_json& jRequest_In);

void Convert_RMROOT_NAME            (ordered_json& jRequest_Out, const ordered_json& jRequest_In);

/////////////////////////////////////////////////////////////////////

#define MVO_SIZE_RMOBJECTID                               48
#define MVO_SIZE_RMROOTID                                  MVO_SIZE_RMOBJECTID // TBD
#define MVO_SIZE_RMCOBJECTID                               MVO_SIZE_RMOBJECTID // TBD
#define MVO_SIZE_RMTOBJECTID                               MVO_SIZE_RMOBJECTID // TBD
#define MVO_SIZE_RMPOBJECTID                               MVO_SIZE_RMOBJECTID // TBD
#define MVO_SIZE_RMNAME                                   32
#define MVO_SIZE_RMREFERENCE                              64

#define STRINGIFY(x)                                       #x
#define TO_STRING(x)                                       STRINGIFY(x)

#define MAKEACTION(n,o)                                   (n | ((o) << 16))

//#define SBA_RROOT_RMROOT_OPEN                              MAKEACTION ( 5, SBO_CLASS_RROOT)
//#define SBA_RROOT_RMROOT_CLOSE                             MAKEACTION ( 6, SBO_CLASS_RROOT)

#define SBA_RMROOT_NAME                                    MAKEACTION ( 1, MAP_OBJECT_CLASS_ROOT)
#define SBA_RMROOT_OWNER                                   MAKEACTION ( 2, MAP_OBJECT_CLASS_ROOT)
#define SBA_RMROOT_RMCOBJECT_OPEN                          MAKEACTION ( 3, MAP_OBJECT_CLASS_ROOT)
#define SBA_RMROOT_RMCOBJECT_CLOSE                         MAKEACTION ( 4, MAP_OBJECT_CLASS_ROOT)

#define SBA_RMCOBJECT_CAPTURE                              MAKEACTION ( 1, MAP_OBJECT_CLASS_CELESTIAL)
#define SBA_RMCOBJECT_RELEASE                              MAKEACTION ( 2, MAP_OBJECT_CLASS_CELESTIAL)
#define SBA_RMCOBJECT_NAME                                 MAKEACTION ( 3, MAP_OBJECT_CLASS_CELESTIAL)
#define SBA_RMCOBJECT_TYPE                                 MAKEACTION ( 4, MAP_OBJECT_CLASS_CELESTIAL)
#define SBA_RMCOBJECT_OWNER                                MAKEACTION ( 5, MAP_OBJECT_CLASS_CELESTIAL)
#define SBA_RMCOBJECT_RESOURCE                             MAKEACTION ( 6, MAP_OBJECT_CLASS_CELESTIAL)
#define SBA_RMCOBJECT_TRANSFORM                            MAKEACTION ( 7, MAP_OBJECT_CLASS_CELESTIAL)
#define SBA_RMCOBJECT_ORBIT                                MAKEACTION ( 8, MAP_OBJECT_CLASS_CELESTIAL)
#define SBA_RMCOBJECT_SPIN                                 MAKEACTION ( 9, MAP_OBJECT_CLASS_CELESTIAL)
#define SBA_RMCOBJECT_BOUND                                MAKEACTION (10, MAP_OBJECT_CLASS_CELESTIAL)
#define SBA_RMCOBJECT_PROPERTIES                           MAKEACTION (11, MAP_OBJECT_CLASS_CELESTIAL)
#define SBA_RMCOBJECT_RMCOBJECT_OPEN                       MAKEACTION (12, MAP_OBJECT_CLASS_CELESTIAL)
#define SBA_RMCOBJECT_RMCOBJECT_CLOSE                      MAKEACTION (13, MAP_OBJECT_CLASS_CELESTIAL)
#define SBA_RMCOBJECT_RMTOBJECT_OPEN                       MAKEACTION (14, MAP_OBJECT_CLASS_CELESTIAL)
#define SBA_RMCOBJECT_RMTOBJECT_CLOSE                      MAKEACTION (15, MAP_OBJECT_CLASS_CELESTIAL)

#define SBA_RMTOBJECT_CAPTURE                              MAKEACTION ( 1, MAP_OBJECT_CLASS_TERRESTRIAL)
#define SBA_RMTOBJECT_RELEASE                              MAKEACTION ( 2, MAP_OBJECT_CLASS_TERRESTRIAL)
#define SBA_RMTOBJECT_NAME                                 MAKEACTION ( 3, MAP_OBJECT_CLASS_TERRESTRIAL)
#define SBA_RMTOBJECT_TYPE                                 MAKEACTION ( 4, MAP_OBJECT_CLASS_TERRESTRIAL)
#define SBA_RMTOBJECT_OWNER                                MAKEACTION ( 5, MAP_OBJECT_CLASS_TERRESTRIAL)
#define SBA_RMTOBJECT_RESOURCE                             MAKEACTION ( 6, MAP_OBJECT_CLASS_TERRESTRIAL)
#define SBA_RMTOBJECT_TRANSFORM                            MAKEACTION ( 7, MAP_OBJECT_CLASS_TERRESTRIAL)
#define SBA_RMTOBJECT_BOUND                                MAKEACTION ( 8, MAP_OBJECT_CLASS_TERRESTRIAL)
#define SBA_RMTOBJECT_PROPERTIES                           MAKEACTION ( 9, MAP_OBJECT_CLASS_TERRESTRIAL)
#define SBA_RMTOBJECT_RMTOBJECT_OPEN                       MAKEACTION (10, MAP_OBJECT_CLASS_TERRESTRIAL)
#define SBA_RMTOBJECT_RMTOBJECT_CLOSE                      MAKEACTION (11, MAP_OBJECT_CLASS_TERRESTRIAL)
#define SBA_RMTOBJECT_RMPOBJECT_OPEN                       MAKEACTION (12, MAP_OBJECT_CLASS_TERRESTRIAL)
#define SBA_RMTOBJECT_RMPOBJECT_CLOSE                      MAKEACTION (13, MAP_OBJECT_CLASS_TERRESTRIAL)

#define SBA_RMPOBJECT_CAPTURE                              MAKEACTION ( 1, MAP_OBJECT_CLASS_PHYSICAL)
#define SBA_RMPOBJECT_RELEASE                              MAKEACTION ( 2, MAP_OBJECT_CLASS_PHYSICAL)
#define SBA_RMPOBJECT_NAME                                 MAKEACTION ( 3, MAP_OBJECT_CLASS_PHYSICAL)
#define SBA_RMPOBJECT_TYPE                                 MAKEACTION ( 4, MAP_OBJECT_CLASS_PHYSICAL)
#define SBA_RMPOBJECT_OWNER                                MAKEACTION ( 5, MAP_OBJECT_CLASS_PHYSICAL)
#define SBA_RMPOBJECT_RESOURCE                             MAKEACTION ( 6, MAP_OBJECT_CLASS_PHYSICAL)
#define SBA_RMPOBJECT_TRANSFORM                            MAKEACTION ( 7, MAP_OBJECT_CLASS_PHYSICAL)
#define SBA_RMPOBJECT_BOUND                                MAKEACTION ( 8, MAP_OBJECT_CLASS_PHYSICAL)
//efine SBA_RMPOBJECT_PROPERTIES                           MAKEACTION ( 9, MAP_OBJECT_CLASS_PHYSICAL)
#define SBA_RMPOBJECT_RMPOBJECT_OPEN                       MAKEACTION (10, MAP_OBJECT_CLASS_PHYSICAL)
#define SBA_RMPOBJECT_RMPOBJECT_CLOSE                      MAKEACTION (11, MAP_OBJECT_CLASS_PHYSICAL)

#include "Source_SB_Object.h"

#endif //PCH_H
