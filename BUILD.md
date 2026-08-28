# MPC-BE Build Steps

This document records the build steps for MPC-BE.

## Prerequisites

- Visual Studio 2022 (Community) with Desktop development with C++ workload (MSVC v143, Windows SDK, ATL/MFC)
- MSYS/MinGW-w64 GCC 15.2.1 installed at `<MSYS_INSTALL_DIR>`
- Git for Windows
- Git submodules initialized (`git submodule update --init --recursive`)

## Environment Setup

1. Create `environments.bat` in the repository root:

   ```bat
   @ECHO OFF
    SET "MPCBE_MSYS=<MSYS_INSTALL_DIR>"
    SET "MPCBE_MINGW=<MSYS_INSTALL_DIR>\mingw"
   ```

2. Run `update_gcc.bat` to copy the required GCC libraries (`libgcc.a`, `libmingwex.a`) into the `lib` and `lib64` directories.

3. Run `update_revision.cmd` to generate `revision.h` and update the manifest.

## Build Command

From the repository root (`<REPO_ROOT>`), run:

```bat
build.bat Build x64       # Release
build.bat Build x64 Debug # Debug (faster compile, no optimization, larger binary)
```

Default parameters used:
- **Build type**: Build
- **Platform**: x64
- **Configuration**: Release
- **Config**: MPCBE (main application)
- **Compiler**: VS2022 (auto-detected as latest)

## Build Output

Build time: ~12 minutes

Artifacts were generated in `<REPO_ROOT>\_bin`:

| Artifact | Path | Size |
|----------|------|------|
| MPC-BE x64 | `_bin\mpc-be_x64\mpc-be64.exe` | ~32 MB |
| Shell Ext x64 | `_bin\mpc-be_x64\MPCBEShellExt64.dll` | ~180 KB |
| Icon Library x64 | `_bin\mpc-be_x64\mpciconlib.dll` | ~5.7 MB |
| Language DLLs | `_bin\mpc-be_x64\Lang\*.dll` | 32 languages |
| Static libraries | `_bin\lib\Release_x64\*.lib` | Multiple |
| Shaders | `_bin\shaders\*.cso` | Multiple |

All error and warning log files in `_bin\logs` are empty (0 bytes).

## Verified Projects

- `mpc-be.sln` Release x64
- `mpciconlib.sln` Release x64
- `MPCBEShellExt.sln` Release x64
- `mpcresources.sln` resources compiled for all languages

## Debug Build

```bat
build.bat Build x64 Debug
```

## Troubleshooting

If the build fails:
1. Delete the `_bin` folder and retry.
2. Ensure `environments.bat` exists and points to the correct MSYS/MinGW paths.
3. Ensure `git submodule update --init --recursive` has been run.
4. Ensure Visual Studio 2022 with C++ ATL/MFC support is installed.
