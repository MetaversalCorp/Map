# Map

Map is a cross-platform C++17 static library, `Map.lib` (`libMap.a` on Unix-like
platforms). It provides the RMRoot / RMCObject / RMTObject / RMPObject map model,
together with their SB and IO source and package plugins, on top of the RMAP
framework.

## Repository layout

```
Map/
  CMakeLists.txt              Top-level: builds the single Map.lib, wires the
                              upstream dependencies, install/export
  CMakePresets.json           Ready-made configure/build presets
  cmake/                      Package-config template for find_package(Map)
  include/Map/                Public headers (installed): Map.h, Map_ClassTypes.h
                              (consumed as <Map/Map.h>)
  src/                        Implementation + private headers (+ pch.h)
  third_party/                Dependencies fetched/built from git at build time (not committed):
    rmap/                       RMAP (compiled from source into the static RMAP.lib)
    json/                       nlohmann_json 3.11.3 (header-only)
    asio/                       standalone asio 1.30.2 (header-only)
    websocketpp/                websocketpp 0.8.2 (header-only)
    boringssl/                  BoringSSL (compiled: libssl/libcrypto)
    curl/                       libcurl 8.9.1 (compiled)
    socketio/                   socket.io-client-cpp (compiled: sioclient_tls)
```

CMake generates the Visual Studio project (and its Solution Explorer filters,
which mirror the on-disk `src` / `include` folders). There are no committed IDE
project files.

## Building

CMake is the single source of truth. It generates the Visual Studio solution on
Windows (and Makefiles/Ninja/Xcode elsewhere) from `CMakeLists.txt`.

### Prerequisites

| Tool | Needed for | Notes |
|------|-----------|-------|
| CMake ≥ 3.20 | everything | |
| A C++17 compiler | everything | MSVC on Windows; GCC/Clang on Linux; AppleClang on macOS |
| **Go** | building RMAP from source (its BoringSSL dependency) | Build-time only. `winget install GoLang.Go`. Skip by supplying a prebuilt RMAP via `Map_USE_SYSTEM_RMAP=ON`. |
| **NASM** | building RMAP from source on Windows (x86/x64) | `winget install NASM.NASM`. Skip via `Map_USE_SYSTEM_RMAP=ON`. |

### Visual Studio (Windows)

Generate the solution and open it:

```powershell
cmake --preset vs2022
start build\Map.sln
```

Or build from the command line:

```powershell
cmake --build --preset vs2022-release
```

> The generated solution under `build\` is a build artifact and is regenerated
> by CMake. Don't hand-edit project settings in the IDE — they would be
> overwritten. Make permanent changes in `CMakeLists.txt`.

### Cross-platform (Ninja / Make / etc.)

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
cmake --install build --prefix <install-dir>
```

## Dependencies

Map consumes the [RMAP](../RMAP) library — which now provides the former MVMF
core and the MVSB / MVRest / MVIO service layers — plus `MVRP`, `MVRP_Dev`, and
`MVXP`.

- **RMAP** ([MetaversalCorp/RMAP](https://github.com/MetaversalCorp/RMAP)) —
  **compiled from source**, added the same way RMAP adds its own compiled
  third-party libraries. With `Map_USE_SYSTEM_RMAP=OFF` (the default) it is
  cloned from git (tracking `main`, which is what it ships today — no release
  tags yet) and built at build time into `third_party/rmap/` (not committed);
  Map then links the resulting static `RMAP.lib` and compiles against its
  installed `<RMAP/...>` headers. Because RMAP is itself a static archive whose
  own dependencies (BoringSSL, libcurl, socket.io-client-cpp) are linked
  **PRIVATE**, a final executable that links Map must also link those (see RMAP's
  README). Building RMAP from source inherits RMAP's build prerequisites (Go, and
  NASM on Windows). Set `Map_USE_SYSTEM_RMAP=ON` to consume a prebuilt RMAP via
  `find_package(RMAP)` instead (put its install tree on `CMAKE_PREFIX_PATH`),
  which also skips the Go/NASM toolchain.
- **RMAP's third-party libraries**, mirrored into Map the same way RMAP declares
  them (same versions/tags/defines, each with a `Map_USE_SYSTEM_<NAME>` option).
  RMAP exposes these through its public `<RMAP/...>` headers (and Map's own SB/IO
  source uses them) but adds them only as build-interface requirements, so a
  consumer such as Map must supply them itself:
  - **nlohmann_json** 3.11.3, **asio** 1.30.2 (standalone), **websocketpp** 0.8.2
    — header-only; git-fetched into `third_party/` and added to Map's build
    include path. `ASIO_STANDALONE` and `_WEBSOCKETPP_CPP11_STL_` are defined to
    match RMAP.
  - **BoringSSL** (tracks `main`), **libcurl** 8.9.1, **socket.io-client-cpp**
    (pinned to RMAP's `master` commit, built as `sioclient_tls`) — compiled from
    source via `ExternalProject` and linked **PRIVATE** (kept out of Map's
    exported interface). curl uses Schannel on Windows and BoringSSL elsewhere;
    sioclient's TLS is backed by the BoringSSL above. These inherit the Go/NASM
    build prerequisites already required for RMAP.
- **MVRP, MVRP_Dev, MVXP** have not yet been converted to cross-platform CMake
  packages. Until they are (the same way RMAP was), point
  `Map_DEPENDENCY_INCLUDE_DIRS` at their headers and add their link libraries.

> **Source migration still pending.** Map's sources still use the pre-RMAP names
> (`<MVMF.h>`, the `MV::` namespace, `SB_OBJECT`, `LIBRARY`, `PLUGIN`, …). Until
> that migration to the RMAP-era names is complete — the same migration RMAP
> left to be finished by hand — Map **configures but does not yet compile**. This
> conversion set up the cross-platform build system only.

## Options

| Option / cache variable       | Default | Effect                                                                      |
|-------------------------------|---------|-----------------------------------------------------------------------------|
| `Map_USE_SYSTEM_RMAP`         | `OFF`   | `ON` consumes an external RMAP via `find_package` (put its install tree on `CMAKE_PREFIX_PATH`) instead of git-building it from source (skips the Go/NASM toolchain). |
| `Map_USE_SYSTEM_JSON`         | `OFF`   | `ON` consumes an external nlohmann_json (3.11.3) via `find_package` instead of the git-fetched copy. |
| `Map_USE_SYSTEM_ASIO`         | `OFF`   | `ON` consumes an external asio (1.30.2) via `find_package` instead of the git-fetched copy. |
| `Map_USE_SYSTEM_WEBSOCKETPP`  | `OFF`   | `ON` consumes an external websocketpp (0.8.2) via `find_package` instead of the git-fetched copy. |
| `Map_USE_SYSTEM_BORINGSSL`    | `OFF`   | `ON` consumes a prebuilt BoringSSL from `Map_SYSTEM_BORINGSSL_ROOT` instead of building it from source. |
| `Map_USE_SYSTEM_CURL`         | `OFF`   | `ON` consumes a prebuilt libcurl from `Map_SYSTEM_CURL_ROOT` instead of building it from source. |
| `Map_USE_SYSTEM_SIOCLIENT`    | `OFF`   | `ON` consumes a prebuilt socket.io-client-cpp from `Map_SYSTEM_SIOCLIENT_ROOT` instead of building it from source. |
| `Map_SYSTEM_BORINGSSL_ROOT` / `Map_SYSTEM_CURL_ROOT` / `Map_SYSTEM_SIOCLIENT_ROOT` | *(empty)* | Install tree (with `include/` + `lib/`) of the corresponding prebuilt compiled dependency when its `Map_USE_SYSTEM_*` is `ON`. |
| `Map_DEPENDENCY_INCLUDE_DIRS` | *(empty)* | Extra include dirs for the not-yet-converted dependencies (MVRP, MVRP_Dev, MVXP). |

## Using Map from CMake

After installing, downstream projects consume the library through its exported
target:

```cmake
find_package(Map CONFIG REQUIRED)
target_link_libraries(my_target PRIVATE Map::Map)
```

If Map was built against RMAP, its package config pulls in `RMAP` for you.
