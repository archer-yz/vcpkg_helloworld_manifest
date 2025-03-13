# Mixed vcpkg Static and Dynamic Libraries in Manifest Mode

This project demonstrates how to use vcpkg installed static and dynamic libraries in manifest mode.
The [tutorial of vcpkg usage with CMake in VS
Code](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started-vscode?pivots=shell-cmd) can
be followed for development of manifest mode.

## Overlay Triplet

vcpkg triplets control how packages are built (static/dynamic, compiler options, etc.). A
*cmake/vcpkg_triplets* folder is created inside the project to hold new triplet files. Contents of
file *x64-windows-mixed.cmake* are:

```cmake
set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE dynamic)

# Force specific libraries to be static
if ("${PORT}" MATCHES "fmt|eigen3|boost-.*")
    set(VCPKG_CRT_LINKAGE static)
    set(VCPKG_LIBRARY_LINKAGE static)
endif()
```

**Explanation**
- Most packages are dynamic by default.
- fmt, eigen3 and boost-* are overridden to be static.

## CMake Variables

The following CMake variables are defined in *CMakePresets.json* for triplet overlay to work.

```json
"cacheVariables": {
    "CMAKE_TOOLCHAIN_FILE": "$env{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake",
    "VCPKG_OVERLAY_TRIPLETS": "${sourceDir}/cmake/vcpkg_triplets",
    "VCPKG_TARGET_TRIPLET": "x64-windows-mixed",
    "VCPKG_INSTALL_OPTIONS": "--clean-after-build",
    "CMAKE_BUILD_TYPE": "Release",
    "CMAKE_MSVC_RUNTIME_LIBRARY": "MultiThreaded"
}
```

"MultiThreaded" should be used for **CMAKE_MSVC_RUNTIME_LIBRARY** in *debug* build.
