cmake_minimum_required(VERSION 3.20)

project(Map
   VERSION 0.1.0
   LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Default to a Release build for single-config generators when none is given.
if(NOT CMAKE_BUILD_TYPE  AND  NOT CMAKE_CONFIGURATION_TYPES)
   set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# ---------------------------------------------------------------------------
# Map is a cross-platform C++17 STATIC library, Map.lib (libMap.a on Unix-like
# platforms). CMake is the single source of truth: it generates the Visual
# Studio solution on Windows (and Makefiles/Ninja/Xcode elsewhere), so there are
# no committed IDE project files.
#
# Headers are listed alongside sources so they appear in the generated Visual
# Studio project and its filters.
# ---------------------------------------------------------------------------

set(Map_FILES
   include/Map/Map.h
   src/Library.cpp
   src/Library.h
   src/Map_Data.cpp
   src/Model_RMCObject.cpp
   src/Model_RMPObject.cpp
   src/Model_RMRoot.cpp
   src/Model_RMTObject.cpp
   src/Package_IO.cpp
   src/Package_IO.h
   src/Package_SB.cpp
   src/Package_SB.h
   src/RMCommon.cpp
   src/Source_IO_Object.cpp
   src/Source_IO_RMCObject.cpp
   src/Source_IO_RMPObject.cpp
   src/Source_IO_RMRoot.cpp
   src/Source_IO_RMTObject.cpp
   src/Source_SB_Object.h
   src/Source_SB_RMCObject.cpp
   src/Source_SB_RMPObject.cpp
   src/Source_SB_RMRoot.cpp
   src/Source_SB_RMTObject.cpp
   src/pch.cpp
   src/pch.h)

add_library(Map STATIC ${Map_FILES})
add_library(Map::Map ALIAS Map)

target_compile_features(Map PUBLIC cxx_std_17)

target_include_directories(Map
   PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<INSTALL_INTERFACE:include>
   PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/include/Map
      ${CMAKE_CURRENT_SOURCE_DIR}/src)

# MSVC parity with the previous hand-authored project settings. The former DLL
# defines (MVRPMAPCPP_EXPORTS / _USRDLL) are intentionally dropped: this is now a
# static library (the source's __declspec export macro has been removed to match).
if(MSVC)
   target_compile_definitions(Map PRIVATE UNICODE _UNICODE _LIB _CRT_SECURE_NO_WARNINGS)
   target_compile_options(Map PRIVATE /permissive- /sdl /W3)
   set_target_properties(Map PROPERTIES
      INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
endif()

target_precompile_headers(Map PRIVATE src/pch.h)

# Visual Studio filters mirroring the on-disk folder layout (src, include).
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${Map_FILES})

# ---------------------------------------------------------------------------
# RMAP (COMPILED - not header-only). Map's primary dependency: RMAP now provides
# the former MVMF core plus the MVSB / MVRest / MVIO service layers, compiled
# into a single static RMAP.lib (libRMAP.a). Added the SAME way RMAP adds its own
# compiled third-party libraries (BoringSSL/curl/sioclient):
#   Map_USE_SYSTEM_RMAP=OFF -> git-clone + build RMAP from source at build time
#      into third_party/rmap (not committed), then consume its installed static
#      lib + headers directly (build-time ExternalProject, so we cannot
#      find_package it at configure time - same reason RMAP references its
#      compiled deps by path).
#   Map_USE_SYSTEM_RMAP=ON  -> find_package(RMAP CONFIG REQUIRED) -> RMAP::RMAP.
# Tracks the RMAP repo's main branch (it ships no release tags yet), mirroring
# how RMAP tracks BoringSSL's main. Because RMAP is a static archive whose own
# deps (BoringSSL/curl/sioclient) are linked PRIVATE, a final executable linking
# Map must also link those (see RMAP's README). Building RMAP from source thus
# inherits RMAP's build prerequisites (Go, plus NASM on Windows); point
# Map_USE_SYSTEM_RMAP at a prebuilt copy to skip them.
#
# NOTE: Map's sources still use the pre-RMAP names (<MVMF.h>, the MV:: namespace,
# SB_OBJECT, LIBRARY, PLUGIN, ...). Until that source migration is done - the
# same migration RMAP left to be completed by hand - Map configures but does not
# yet compile.
# ---------------------------------------------------------------------------

option(Map_USE_SYSTEM_RMAP "Use an external RMAP (find_package) instead of the git-built copy" OFF)

if(NOT Map_USE_SYSTEM_RMAP)
   include(ExternalProject)

   set(Map_RMAP_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/third_party/rmap")
   set(Map_RMAP_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/rmap/$<CONFIG>")
   set(Map_RMAP_LIB
      "${Map_RMAP_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}RMAP${CMAKE_STATIC_LIBRARY_SUFFIX}")

   if(EXISTS "${Map_RMAP_DIR}/.git")
      set(_rmap_git_args)
   else()
      set(_rmap_git_args
         GIT_REPOSITORY https://github.com/MetaversalCorp/RMAP.git
         GIT_TAG        main
         GIT_SHALLOW    ON)
   endif()

   ExternalProject_Add(rmap_build
      ${_rmap_git_args}
      SOURCE_DIR "${Map_RMAP_DIR}"
      BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/rmap/build"
      UPDATE_DISCONNECTED ON
      CMAKE_ARGS
         -DCMAKE_INSTALL_PREFIX=${Map_RMAP_PREFIX}
         -DCMAKE_BUILD_TYPE=$<CONFIG>
      BUILD_COMMAND   ${CMAKE_COMMAND} --build   <BINARY_DIR> --config $<CONFIG>
      INSTALL_COMMAND ${CMAKE_COMMAND} --install <BINARY_DIR> --config $<CONFIG>
      BUILD_BYPRODUCTS "${Map_RMAP_LIB}")

   add_dependencies(Map rmap_build)

   # Build-only PUBLIC include so Map's sources compile against <RMAP/...>. The
   # $<BUILD_INTERFACE:> keeps the build-tree path out of Map's exported
   # interface - an installed Map resolves RMAP via find_dependency (MapConfig).
   target_include_directories(Map PUBLIC
      $<BUILD_INTERFACE:${Map_RMAP_PREFIX}/include>)

   # Same $<BUILD_INTERFACE:> discipline for the link: keeps the absolute
   # build-tree path out of MapTargets.
   target_link_libraries(Map PUBLIC $<BUILD_INTERFACE:${Map_RMAP_LIB}>)
else()
   find_package(RMAP CONFIG REQUIRED)
   target_link_libraries(Map PUBLIC RMAP::RMAP)
endif()

# ---------------------------------------------------------------------------
# RMAP's third-party libraries, mirrored into Map the SAME way RMAP declares
# them. RMAP exposes these through its public headers (which Map includes via
# <RMAP/...>) and/or Map's own SB/IO source uses them, and RMAP adds them only as
# $<BUILD_INTERFACE:> (not installed), so Map must provide them on its own build.
# Every version/tag/define below matches RMAP exactly to avoid ABI skew across
# the shared API. Each has a Map_USE_SYSTEM_<NAME> option: OFF git-fetches/builds
# into third_party/<name> (not committed); ON consumes an external copy.
#
# When a compiled dep's Map_USE_SYSTEM_* is ON, point these at the parent build's
# install trees (each with include/ and lib/), mirroring RMAP's *_SYSTEM_*_ROOT.
# ---------------------------------------------------------------------------

set(Map_SYSTEM_BORINGSSL_ROOT "" CACHE PATH "Install tree of a prebuilt BoringSSL (when Map_USE_SYSTEM_BORINGSSL=ON)")
set(Map_SYSTEM_CURL_ROOT      "" CACHE PATH "Install tree of a prebuilt libcurl (when Map_USE_SYSTEM_CURL=ON)")
set(Map_SYSTEM_SIOCLIENT_ROOT "" CACHE PATH "Install tree of a prebuilt socket.io-client-cpp (when Map_USE_SYSTEM_SIOCLIENT=ON)")

# ---------------------------------------------------------------------------
# nlohmann_json (header-only). RMAP's public API (RMAP.h) exposes
# nlohmann::ordered_json, so Map's TUs that include <RMAP/RMAP.h> need the json
# headers on their include path. Pinned to 3.11.3 (RMAP's version).
# ---------------------------------------------------------------------------

option(Map_USE_SYSTEM_JSON "Use an external nlohmann_json (find_package) instead of the git-fetched copy" OFF)

if(Map_USE_SYSTEM_JSON)
   find_package(nlohmann_json 3.11.3 CONFIG REQUIRED)
   target_link_libraries(Map PUBLIC nlohmann_json::nlohmann_json)
else()
   include(ExternalProject)

   set(Map_JSON_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party/json")
   if(EXISTS "${Map_JSON_DIR}/.git")
      set(_json_git_args)
   else()
      set(_json_git_args
         GIT_REPOSITORY https://github.com/nlohmann/json.git
         GIT_TAG        v3.11.3
         GIT_SHALLOW    ON)
   endif()

   ExternalProject_Add(nlohmann_json_fetch
      ${_json_git_args}
      SOURCE_DIR          "${Map_JSON_DIR}"
      UPDATE_DISCONNECTED ON
      CONFIGURE_COMMAND ""
      BUILD_COMMAND     ""
      INSTALL_COMMAND   ""
      TEST_COMMAND      "")

   add_dependencies(Map nlohmann_json_fetch)

   target_include_directories(Map PUBLIC
      $<BUILD_INTERFACE:${Map_JSON_DIR}/include>)
endif()

# ---------------------------------------------------------------------------
# asio (standalone, header-only). Pinned to 1.30.2 (headers under asio/include).
# ASIO_STANDALONE forces the non-Boost header-only asio (matching RMAP).
# ---------------------------------------------------------------------------

option(Map_USE_SYSTEM_ASIO "Use an external asio (find_package) instead of the git-fetched copy" OFF)

if(Map_USE_SYSTEM_ASIO)
   find_package(asio 1.30.2 CONFIG REQUIRED)
   target_link_libraries(Map PUBLIC asio::asio)
else()
   include(ExternalProject)

   set(Map_ASIO_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party/asio")
   if(EXISTS "${Map_ASIO_DIR}/.git")
      set(_asio_git_args)
   else()
      set(_asio_git_args
         GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
         GIT_TAG        asio-1-30-2
         GIT_SHALLOW    ON)
   endif()

   ExternalProject_Add(asio_fetch
      ${_asio_git_args}
      SOURCE_DIR          "${Map_ASIO_DIR}"
      UPDATE_DISCONNECTED ON
      CONFIGURE_COMMAND ""
      BUILD_COMMAND     ""
      INSTALL_COMMAND   ""
      TEST_COMMAND      "")

   add_dependencies(Map asio_fetch)

   target_include_directories(Map PUBLIC
      $<BUILD_INTERFACE:${Map_ASIO_DIR}/asio/include>)
endif()

target_compile_definitions(Map PUBLIC ASIO_STANDALONE)

# ---------------------------------------------------------------------------
# websocketpp (header-only). Pinned to 0.8.2. Include dir is the clone root
# (headers are included as <websocketpp/...>). _WEBSOCKETPP_CPP11_STL_ makes it
# use the C++11 stdlib instead of Boost (matching RMAP).
# ---------------------------------------------------------------------------

option(Map_USE_SYSTEM_WEBSOCKETPP "Use an external websocketpp (find_package) instead of the git-fetched copy" OFF)

if(Map_USE_SYSTEM_WEBSOCKETPP)
   find_package(websocketpp 0.8.2 CONFIG REQUIRED)
   target_link_libraries(Map PUBLIC websocketpp::websocketpp)
else()
   include(ExternalProject)

   set(Map_WEBSOCKETPP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party/websocketpp")
   if(EXISTS "${Map_WEBSOCKETPP_DIR}/.git")
      set(_websocketpp_git_args)
   else()
      set(_websocketpp_git_args
         GIT_REPOSITORY https://github.com/zaphoyd/websocketpp.git
         GIT_TAG        0.8.2
         GIT_SHALLOW    ON)
   endif()

   ExternalProject_Add(websocketpp_fetch
      ${_websocketpp_git_args}
      SOURCE_DIR          "${Map_WEBSOCKETPP_DIR}"
      UPDATE_DISCONNECTED ON
      CONFIGURE_COMMAND ""
      BUILD_COMMAND     ""
      INSTALL_COMMAND   ""
      TEST_COMMAND      "")

   add_dependencies(Map websocketpp_fetch)

   target_include_directories(Map PUBLIC
      $<BUILD_INTERFACE:${Map_WEBSOCKETPP_DIR}>)
endif()

target_compile_definitions(Map PUBLIC _WEBSOCKETPP_CPP11_STL_)

# ---------------------------------------------------------------------------
# BoringSSL (COMPILED). Tracks google/boringssl main (RMAP's version). Built into
# static libcrypto/libssl via its own CMake build (parent generator, portable),
# linked PRIVATE (kept out of Map's exported interface), with build-only PUBLIC
# include. Build prereqs: Go + a C/C++ compiler (+ NASM on Windows x86/x64).
# ---------------------------------------------------------------------------

option(Map_USE_SYSTEM_BORINGSSL "Use an external BoringSSL instead of the git-built copy" OFF)

if(NOT Map_USE_SYSTEM_BORINGSSL)
   include(ExternalProject)

   set(Map_BORINGSSL_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/third_party/boringssl")
   set(Map_BORINGSSL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/boringssl/$<CONFIG>")
   set(Map_BORINGSSL_SSL_LIB
      "${Map_BORINGSSL_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}ssl${CMAKE_STATIC_LIBRARY_SUFFIX}")
   set(Map_BORINGSSL_CRYPTO_LIB
      "${Map_BORINGSSL_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}crypto${CMAKE_STATIC_LIBRARY_SUFFIX}")

   if(EXISTS "${Map_BORINGSSL_DIR}/.git")
      set(_boringssl_git_args)
   else()
      set(_boringssl_git_args
         GIT_REPOSITORY https://github.com/google/boringssl.git
         GIT_TAG        main
         GIT_SHALLOW    ON)
   endif()

   # BoringSSL's CMakeLists does enable_language(ASM_NASM) without probing common
   # install paths, so forward an absolute nasm path if one is found (winget drops
   # nasm under %LOCALAPPDATA%/bin/NASM, which is not on PATH out of the box).
   set(_boringssl_extra_args)
   if(WIN32  AND  NOT CMAKE_CROSSCOMPILING)
      find_program(NASM_EXECUTABLE nasm
         HINTS
            "$ENV{LOCALAPPDATA}/bin/NASM"
            "$ENV{ProgramFiles}/NASM"
            "$ENV{ProgramFiles\(x86\)}/NASM")
      if(NASM_EXECUTABLE)
         list(APPEND _boringssl_extra_args -DCMAKE_ASM_NASM_COMPILER=${NASM_EXECUTABLE})
      endif()
   endif()

   ExternalProject_Add(boringssl_build
      ${_boringssl_git_args}
      SOURCE_DIR "${Map_BORINGSSL_DIR}"
      BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/boringssl/build"
      UPDATE_DISCONNECTED ON
      CMAKE_ARGS
         -DCMAKE_INSTALL_PREFIX=${Map_BORINGSSL_PREFIX}
         -DBUILD_SHARED_LIBS=OFF
         -DCMAKE_BUILD_TYPE=$<CONFIG>
         -DBUILD_TESTING=OFF
         ${_boringssl_extra_args}
      BUILD_COMMAND   ${CMAKE_COMMAND} --build   <BINARY_DIR> --config $<CONFIG>
      INSTALL_COMMAND ${CMAKE_COMMAND} --install <BINARY_DIR> --config $<CONFIG>
      BUILD_BYPRODUCTS
         "${Map_BORINGSSL_SSL_LIB}"
         "${Map_BORINGSSL_CRYPTO_LIB}")

   add_dependencies(Map boringssl_build)

   target_include_directories(Map PUBLIC
      $<BUILD_INTERFACE:${Map_BORINGSSL_PREFIX}/include>)

   target_link_libraries(Map PRIVATE
      "${Map_BORINGSSL_SSL_LIB}"
      "${Map_BORINGSSL_CRYPTO_LIB}")
   if(WIN32)
      target_link_libraries(Map PRIVATE ws2_32 crypt32)
   elseif(UNIX  AND  NOT APPLE)
      target_link_libraries(Map PRIVATE pthread dl)
   endif()
else()
   set(Map_BORINGSSL_PREFIX "${Map_SYSTEM_BORINGSSL_ROOT}")
   set(Map_BORINGSSL_SSL_LIB
      "${Map_BORINGSSL_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}ssl${CMAKE_STATIC_LIBRARY_SUFFIX}")
   set(Map_BORINGSSL_CRYPTO_LIB
      "${Map_BORINGSSL_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}crypto${CMAKE_STATIC_LIBRARY_SUFFIX}")

   target_include_directories(Map PUBLIC
      $<BUILD_INTERFACE:${Map_BORINGSSL_PREFIX}/include>)

   target_link_libraries(Map PRIVATE
      "${Map_BORINGSSL_SSL_LIB}"
      "${Map_BORINGSSL_CRYPTO_LIB}")
   if(WIN32)
      target_link_libraries(Map PRIVATE ws2_32 crypt32)
   elseif(UNIX  AND  NOT APPLE)
      target_link_libraries(Map PRIVATE pthread dl)
   endif()
endif()

# ---------------------------------------------------------------------------
# libcurl (COMPILED). Pinned to 8.9.1 (RMAP's version). Static, minimal build.
# TLS: Schannel on Windows (no BoringSSL there); BoringSSL via curl's OpenSSL
# interface elsewhere. Linked PRIVATE; CURL_STATICLIB build-only for TUs that
# include <curl/curl.h>.
# ---------------------------------------------------------------------------

option(Map_USE_SYSTEM_CURL "Use an external libcurl instead of the git-built copy" OFF)

if(NOT Map_USE_SYSTEM_CURL)
   include(ExternalProject)

   set(Map_CURL_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/third_party/curl")
   set(Map_CURL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/curl/$<CONFIG>")
   if(WIN32)
      set(Map_CURL_LIB "${Map_CURL_PREFIX}/lib/libcurl$<$<CONFIG:Debug>:-d>${CMAKE_STATIC_LIBRARY_SUFFIX}")
   else()
      set(Map_CURL_LIB "${Map_CURL_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}curl${CMAKE_STATIC_LIBRARY_SUFFIX}")
   endif()

   if(EXISTS "${Map_CURL_DIR}/.git")
      set(_curl_git_args)
   else()
      set(_curl_git_args
         GIT_REPOSITORY https://github.com/curl/curl.git
         GIT_TAG        curl-8_9_1
         GIT_SHALLOW    ON)
   endif()

   if(WIN32)
      set(_curl_ssl_args -DCURL_USE_SCHANNEL=ON -DCURL_USE_OPENSSL=OFF)
   else()
      set(_curl_ssl_args
         -DCURL_USE_OPENSSL=ON
         -DCURL_USE_SCHANNEL=OFF
         -DOPENSSL_ROOT_DIR=${Map_BORINGSSL_PREFIX}
         -DOPENSSL_USE_STATIC_LIBS=TRUE
         -DOPENSSL_INCLUDE_DIR=${Map_BORINGSSL_PREFIX}/include
         -DOPENSSL_CRYPTO_LIBRARY=${Map_BORINGSSL_CRYPTO_LIB}
         -DOPENSSL_SSL_LIBRARY=${Map_BORINGSSL_SSL_LIB})
   endif()

   ExternalProject_Add(curl_build
      ${_curl_git_args}
      SOURCE_DIR "${Map_CURL_DIR}"
      BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/curl/build"
      UPDATE_DISCONNECTED ON
      CMAKE_ARGS
         -DCMAKE_INSTALL_PREFIX=${Map_CURL_PREFIX}
         -DCMAKE_BUILD_TYPE=$<CONFIG>
         -DBUILD_SHARED_LIBS=OFF
         -DBUILD_CURL_EXE=OFF
         -DBUILD_TESTING=OFF
         -DCURL_DISABLE_LDAP=ON
         -DCURL_DISABLE_LDAPS=ON
         -DUSE_LIBIDN2=OFF
         -DCURL_USE_LIBPSL=OFF
         -DCURL_USE_LIBSSH2=OFF
         -DCURL_ZLIB=OFF
         -DCURL_BROTLI=OFF
         -DCURL_ZSTD=OFF
         ${_curl_ssl_args}
      BUILD_COMMAND   ${CMAKE_COMMAND} --build   <BINARY_DIR> --config $<CONFIG>
      INSTALL_COMMAND ${CMAKE_COMMAND} --install <BINARY_DIR> --config $<CONFIG>
      BUILD_BYPRODUCTS "${Map_CURL_LIB}")

   if(NOT WIN32  AND  TARGET boringssl_build)
      add_dependencies(curl_build boringssl_build)
   endif()

   add_dependencies(Map curl_build)

   target_include_directories(Map PUBLIC
      $<BUILD_INTERFACE:${Map_CURL_PREFIX}/include>)

   target_compile_definitions(Map PUBLIC $<BUILD_INTERFACE:CURL_STATICLIB>)

   target_link_libraries(Map PRIVATE "${Map_CURL_LIB}")
   if(WIN32)
      target_link_libraries(Map PRIVATE ws2_32 wldap32 crypt32 normaliz)
   endif()
else()
   set(Map_CURL_PREFIX "${Map_SYSTEM_CURL_ROOT}")
   if(WIN32)
      set(Map_CURL_LIB "${Map_CURL_PREFIX}/lib/libcurl$<$<CONFIG:Debug>:-d>${CMAKE_STATIC_LIBRARY_SUFFIX}")
   else()
      set(Map_CURL_LIB "${Map_CURL_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}curl${CMAKE_STATIC_LIBRARY_SUFFIX}")
   endif()

   target_include_directories(Map PUBLIC
      $<BUILD_INTERFACE:${Map_CURL_PREFIX}/include>)

   target_compile_definitions(Map PUBLIC $<BUILD_INTERFACE:CURL_STATICLIB>)

   target_link_libraries(Map PRIVATE "${Map_CURL_LIB}")
   if(WIN32)
      target_link_libraries(Map PRIVATE ws2_32 wldap32 crypt32 normaliz)
   endif()
endif()

# ---------------------------------------------------------------------------
# socket.io-client-cpp / "sioclient" (COMPILED). Pinned to the SAME master commit
# RMAP uses (3b7be7e, 2025-08-28) - the 3.1.0 tag hard-caps its TLS target at
# C++11 while modern BoringSSL needs C++17; master relaxed that. Built into a
# static sioclient_tls, TLS backed by the BoringSSL above on every platform.
# Linked PRIVATE. On MSVC the build injects the NOMINMAX/NOCRYPT/EHsc flags RMAP
# documents. Pinned SHA -> GIT_SHALLOW OFF.
# ---------------------------------------------------------------------------

option(Map_USE_SYSTEM_SIOCLIENT "Use an external socket.io-client-cpp instead of the git-built copy" OFF)

if(NOT Map_USE_SYSTEM_SIOCLIENT)
   include(ExternalProject)

   set(Map_SIOCLIENT_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/third_party/socketio")
   set(Map_SIOCLIENT_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/socketio/$<CONFIG>")
   set(Map_SIOCLIENT_LIB
      "${Map_SIOCLIENT_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}sioclient_tls${CMAKE_STATIC_LIBRARY_SUFFIX}")

   if(EXISTS "${Map_SIOCLIENT_DIR}/.git")
      set(_sioclient_git_args)
   else()
      set(_sioclient_git_args
         GIT_REPOSITORY https://github.com/socketio/socket.io-client-cpp.git
         GIT_TAG        3b7be7e4173b5bdeed393966e3274f65d513a280
         # Only rapidjson is taken from socket.io. Its bundled asio (1.11) and
         # websocketpp submodules are deliberately NOT fetched - they are replaced
         # below with the SAME pinned copies the rest of Map uses (see PATCH_COMMAND).
         GIT_SUBMODULES "lib/rapidjson")
   endif()

   # ---- Version-unify socket.io's header-only deps with the rest of the stack ----
   # socket.io-client-cpp vendors its OWN asio (1.11.0, 2017) and websocketpp.
   # Linking that sioclient_tls alongside RMAP/Map - which are compiled against
   # asio 1.30.2 + websocketpp 0.8.2 - puts two incompatible asio layouts into one
   # binary. Both emit the same asio:: symbols, so the linker folds them to one
   # copy and an io_context/strand built by one asio has its win_mutex read at the
   # wrong offset by the other -> crash in asio::detail::win_mutex::lock() the
   # moment the socket.io run loop starts. Overwrite sioclient's bundled asio +
   # websocketpp headers with Map's pinned copies so the whole link resolves to a
   # single asio/websocketpp (rapidjson is used nowhere else, so it stays bundled).
   set(_sioclient_patch_cmd)
   if(DEFINED Map_ASIO_DIR AND DEFINED Map_WEBSOCKETPP_DIR)
      set(_sioclient_patch_cmd
         PATCH_COMMAND
            ${CMAKE_COMMAND} -E rm -rf <SOURCE_DIR>/lib/asio
            COMMAND ${CMAKE_COMMAND} -E copy_directory
               ${Map_ASIO_DIR}/asio/include <SOURCE_DIR>/lib/asio/asio/include
            COMMAND ${CMAKE_COMMAND} -E rm -rf <SOURCE_DIR>/lib/websocketpp
            COMMAND ${CMAKE_COMMAND} -E copy_directory
               ${Map_WEBSOCKETPP_DIR}/websocketpp <SOURCE_DIR>/lib/websocketpp/websocketpp)
   endif()

   set(_sioclient_cxx_flags "")
   if(MSVC)
      set(_sioclient_cxx_flags "/DWIN32 /D_WINDOWS /EHsc /permissive- /Zc:__cplusplus /DWIN32_LEAN_AND_MEAN /DNOMINMAX /DNOCRYPT")
   endif()

   ExternalProject_Add(sioclient_build
      ${_sioclient_git_args}
      SOURCE_DIR "${Map_SIOCLIENT_DIR}"
      BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/socketio/build"
      UPDATE_DISCONNECTED ON
      ${_sioclient_patch_cmd}
      CMAKE_ARGS
         -DCMAKE_INSTALL_PREFIX=${Map_SIOCLIENT_PREFIX}
         -DCMAKE_BUILD_TYPE=$<CONFIG>
         -DCMAKE_CXX_STANDARD=17
         -DCMAKE_CXX_STANDARD_REQUIRED=ON
         "-DCMAKE_CXX_FLAGS=${_sioclient_cxx_flags}"
         -DBUILD_SHARED_LIBS=OFF
         -DBUILD_UNIT_TESTS=OFF
         -DBUILD_TESTING=OFF
         -DUSE_SUBMODULES=ON
         -DOPENSSL_ROOT_DIR=${Map_BORINGSSL_PREFIX}
         -DOPENSSL_USE_STATIC_LIBS=TRUE
         -DOPENSSL_INCLUDE_DIR=${Map_BORINGSSL_PREFIX}/include
         -DOPENSSL_CRYPTO_LIBRARY=${Map_BORINGSSL_CRYPTO_LIB}
         -DOPENSSL_SSL_LIBRARY=${Map_BORINGSSL_SSL_LIB}
      BUILD_COMMAND   ${CMAKE_COMMAND} --build   <BINARY_DIR> --config $<CONFIG>
      INSTALL_COMMAND ${CMAKE_COMMAND} --install <BINARY_DIR> --config $<CONFIG>
      BUILD_BYPRODUCTS "${Map_SIOCLIENT_LIB}")

   if(TARGET boringssl_build)
      add_dependencies(sioclient_build boringssl_build)
   endif()

   # The PATCH_COMMAND copies from Map's git-fetched asio / websocketpp trees, so
   # those must be populated before sioclient is patched.
   if(TARGET asio_fetch)
      add_dependencies(sioclient_build asio_fetch)
   endif()
   if(TARGET websocketpp_fetch)
      add_dependencies(sioclient_build websocketpp_fetch)
   endif()

   add_dependencies(Map sioclient_build)

   target_include_directories(Map PUBLIC
      $<BUILD_INTERFACE:${Map_SIOCLIENT_PREFIX}/include>)

   target_link_libraries(Map PRIVATE "${Map_SIOCLIENT_LIB}")
else()
   set(Map_SIOCLIENT_PREFIX "${Map_SYSTEM_SIOCLIENT_ROOT}")
   set(Map_SIOCLIENT_LIB
      "${Map_SIOCLIENT_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}sioclient_tls${CMAKE_STATIC_LIBRARY_SUFFIX}")

   target_include_directories(Map PUBLIC
      $<BUILD_INTERFACE:${Map_SIOCLIENT_PREFIX}/include>)

   target_link_libraries(Map PRIVATE "${Map_SIOCLIENT_LIB}")
endif()

# ---------------------------------------------------------------------------
# The remaining Metaversal dependencies (MVRP, MVRP_Dev, MVXP) are not yet
# cross-platform CMake packages. Point Map_DEPENDENCY_INCLUDE_DIRS at their
# headers (and add their link libraries) until they are converted the same way
# RMAP was.
# ---------------------------------------------------------------------------

set(Map_DEPENDENCY_INCLUDE_DIRS "" CACHE STRING
   "Include dirs for the not-yet-converted dependencies (MVRP, MVRP_Dev, MVXP)")
if(Map_DEPENDENCY_INCLUDE_DIRS)
   target_include_directories(Map PRIVATE ${Map_DEPENDENCY_INCLUDE_DIRS})
endif()

# ---------------------------------------------------------------------------
# Install + find_package(Map) support -> target Map::Map
# ---------------------------------------------------------------------------

include(GNUInstallDirs)

install(TARGETS Map
   EXPORT MapTargets
   ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY include/
   DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT MapTargets
   FILE MapTargets.cmake
   NAMESPACE Map::
   DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Map)

include(CMakePackageConfigHelpers)

configure_package_config_file(
   ${CMAKE_CURRENT_SOURCE_DIR}/cmake/MapConfig.cmake.in
   ${CMAKE_CURRENT_BINARY_DIR}/MapConfig.cmake
   INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Map)

write_basic_package_version_file(
   ${CMAKE_CURRENT_BINARY_DIR}/MapConfigVersion.cmake
   VERSION ${PROJECT_VERSION}
   COMPATIBILITY SameMajorVersion)

install(FILES
   ${CMAKE_CURRENT_BINARY_DIR}/MapConfig.cmake
   ${CMAKE_CURRENT_BINARY_DIR}/MapConfigVersion.cmake
   DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Map)
