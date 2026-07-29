# Terminology Source of Truth

This document defines canonical names and commands for EasyExamples documentation.
When any document conflicts with code or CI behavior, code and CI are the source of truth.

## Product and Repository Names

- Canonical repository name: **EasyExamples**
- Canonical product display name: **Easy C++ Examples**

## Module Names (Canonical)

Use these exact names in docs and commands:

- `PolimorficSmart`
- `ModernCPP_Containers`
- `ExceptionHandling`
- `WindowsHEasiest`
- `WindowsDialog`
- `WindowsAndCommctrlH`
- `WindowsDrawing`
- `Gdiplus_H`
- `ResourcesAndGdiplus_H`
- `ResourcesProgressBar`
- `VsCodeCmakeEasiest`
- `VsCodeCmakeW2src`

## Target and Test Naming

- Prefer executable target names from module `CMakeLists.txt` as authoritative.
- Prefer CTest test names from `ctest -N` as authoritative.
- Use `financial_gtest_suite` when optional GTest target is available.

## Build Terminology

- **Root build**: Configure/build from repository root `CMakeLists.txt`.
- **Console-only build**: Root build with `-DBUILD_WINDOWS_EXAMPLES=OFF`.
- **Strict warnings build**: Build with `-DEASYEXAMPLES_STRICT_WARNINGS=ON`.
- **Coverage build**: Build with `-DEASYEXAMPLES_ENABLE_COVERAGE=ON` (GNU/Clang).

## Canonical Commands

### Windows root flow

```bash
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

### Linux/macOS console-only flow

```bash
cmake -S . -B build_linux -DBUILD_TESTING=ON -DBUILD_WINDOWS_EXAMPLES=OFF
cmake --build build_linux
ctest --test-dir build_linux --output-on-failure
```

## CMake and Compiler Baselines

- Minimum CMake version: **3.14**
- Language standards in use:
  - C++17: `PolimorficSmart`, `ModernCPP_Containers`, `ExceptionHandling`
  - C++11: remaining modules

## CI Discovery Baselines

- Root Windows build (`BUILD_WINDOWS_EXAMPLES=ON`): minimum **7** tests discovered.
- Root console-only build (`BUILD_WINDOWS_EXAMPLES=OFF`): minimum **6** tests discovered.
- Strict `PolimorficSmart` standalone build: minimum **2** tests discovered.

## Writing Rules for Docs

- Use exact module folder names when referring to module locations.
- If using a user-facing concept name (for example "Polymorphism example"), include the module alias once: `PolimorficSmart`.
- Do not use generator-specific run paths (for example `./Debug/...`) without noting generator assumptions.
