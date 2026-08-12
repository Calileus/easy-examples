# Release Notes - Version 0.0.0

**Release Date**: 2026-08-12  
**Release Type**: Initial (Reference Collection)  
**Status**: Educational examples, Windows + Linux/macOS support

## Overview

**easy-examples** is a comprehensive collection of 12 progressive C++ learning examples demonstrating modern language features, Windows GUI programming, CMake build system usage, and design patterns. Ordered from beginner to advanced.

## What's Included in This Release (V0.0.0)

### Learning Examples (12 Total)

**Difficulty 1-2 (Beginner - CMake Basics)**
1. **VsCodeCmakeEasiest** - Minimal single-file CMake project
2. **VsCodeCmakeW2src** - Multi-file CMake project structure

**Difficulty 3-5 (Intermediate - Windows GUI)**
3. **WindowsHEasiest** - Minimal Windows window creation
4. **ModernCPP_Containers** - STL containers, algorithms, file I/O
5. **ExceptionHandling** - Custom exceptions and error recovery

**Difficulty 6-8 (Advanced - Windows GUI Features)**
6. **WindowsAndCommctrlH** - Windows with common controls
7. **WindowsDialog** - Dialog boxes with input validation
8. **Gdiplus_H** - Windows GUI with GDI+ graphics

**Difficulty 9-12 (Expert - Advanced Concepts)**
9. **ResourcesAndGdiplus_H** - Resources + GDI+ integration
10. **ResourcesProgressBar** - Progress bar control example
11. **WindowsDrawing** - Graphics drawing and mouse interaction
12. **PolimorficSmart** - Smart pointers, polymorphism, design patterns

### Framework Features
- **CMake Build System**: Cross-platform build configuration
- **Doxygen Documentation**: All examples documented with comments
- **Test Harness**: Unit tests included
- **Multiple Compilers**: MSVC, GCC, Clang support

## System Requirements

### Common
- **CMake**: 3.14 or higher
- **C++ Compiler**: C++17 compatible
  - Windows: MSVC 2019+ or MinGW
  - Linux: GCC 7+ or Clang 5+
  - macOS: Clang 9+
- **Git**: Required for cloning

### Windows GUI Examples
- **Windows OS**: Windows 7 or later
- **Visual Studio**: 2019+ (for Windows examples)
- **GDI+**: Included with Windows (for Gdiplus_H examples)
- **Common Controls**: Part of Windows SDK

### Console-Only Examples (Linux/macOS)
- Can run on Linux or macOS (5 examples: VsCodeCmakeEasiest, VsCodeCmakeW2src, ModernCPP_Containers, ExceptionHandling, PolimorficSmart)
- Windows GUI examples require Windows

## Quick Start

### Windows (All 12 Examples)

```bash
# Configure with Visual Studio generator
cmake -S . -B build -DBUILD_TESTING=ON

# Build
cmake --build build --config Debug

# Run tests
ctest --test-dir build -C Debug --output-on-failure
```

Expected: At least 7 tests discovered and passing

### Linux/macOS (Console-Only, 5 Examples)

```bash
# Configure for Linux/macOS (skips Windows GUI examples)
cmake -S . -B build_linux -DBUILD_TESTING=ON -DBUILD_WINDOWS_EXAMPLES=OFF

# Build
cmake --build build_linux

# Run tests
ctest --test-dir build_linux --output-on-failure
```

Expected: At least 6 tests discovered and passing

### CMake Presets (Recommended)

```bash
cmake --preset dev
cmake --build --preset dev-build
ctest --preset dev-test --output-on-failure
```

## Platform Matrix

| Example | Windows | Linux | macOS |
|---|---|---|---|
| VsCodeCmakeEasiest | ✅ | ✅ | ✅ |
| VsCodeCmakeW2src | ✅ | ✅ | ✅ |
| WindowsHEasiest | ✅ | ❌ | ❌ |
| ModernCPP_Containers | ✅ | ✅ | ✅ |
| ExceptionHandling | ✅ | ✅ | ✅ |
| WindowsAndCommctrlH | ✅ | ❌ | ❌ |
| WindowsDialog | ✅ | ❌ | ❌ |
| Gdiplus_H | ✅ | ❌ | ❌ |
| ResourcesAndGdiplus_H | ✅ | ❌ | ❌ |
| ResourcesProgressBar | ✅ | ❌ | ❌ |
| WindowsDrawing | ✅ | ❌ | ❌ |
| PolimorficSmart | ✅ | ✅ | ✅ |

## Example Descriptions

### PolimorficSmart (Most Complex)
- Comprehensive modern C++ with financial instruments system
- **Concepts**: Polymorphism, smart pointers (unique_ptr, shared_ptr, weak_ptr)
- **Patterns**: Factory pattern, Observer pattern, RAII
- **Use Case**: Enterprise-grade C++ design

### ModernCPP_Containers
- STL containers and algorithms
- **Concepts**: vector, map, algorithm, file I/O
- **Use Case**: Data structure manipulation

### ExceptionHandling
- Custom exception classes
- **Concepts**: Exception hierarchy, error recovery
- **Use Case**: Robust error handling

### WindowsDrawing & GDI+ Examples
- Graphics and UI elements
- **Concepts**: GDI+, mouse handling, drawing primitives
- **Use Case**: Desktop application development

## Build Options

### Enable/Disable Windows Examples

```bash
cmake -S . -B build -DBUILD_WINDOWS_EXAMPLES=OFF  # Exclude Windows-specific
cmake -S . -B build -DBUILD_WINDOWS_EXAMPLES=ON   # Include all
```

### Build Individual Example

```bash
cmake --build build --target PolimorficSmart
```

## Running Examples

After building, executables are in:
- Windows: `build/Debug/` or `build/Release/`
- Linux/macOS: `build/`

Example:
```bash
./build/PolimorficSmart      # Linux/macOS
.\build\Debug\PolimorficSmart.exe  # Windows
```

## Testing

All examples include unit tests:

```bash
# Run all tests
ctest --test-dir build --output-on-failure

# Run specific example tests
ctest --test-dir build -R PolimorficSmart --output-on-failure

# Verbose output
ctest --test-dir build --output-on-failure -V
```

## Documentation

All source files include:
- **Doxygen comments**: Fully documented classes and functions
- **README.md**: Project structure documentation
- **TERMINOLOGY.md**: Common naming conventions (in docs/)
- **Difficulty ordering**: See README.md "Difficulty Order"

Generate Doxygen docs:
```bash
doxygen Doxyfile
# Open docs/html/index.html in browser
```

## Learning Path

### For Beginners
1. VsCodeCmakeEasiest - Learn basic CMake
2. VsCodeCmakeW2src - Learn multi-file projects
3. WindowsHEasiest - Learn Windows GUI basics
4. ModernCPP_Containers - Learn STL containers

### For Intermediate Developers
5. ExceptionHandling - Learn error handling
6. WindowsAndCommctrlH - Learn Windows controls
7. WindowsDialog - Learn dialog boxes
8. Gdiplus_H - Learn graphics programming

### For Advanced Developers
9. ResourcesAndGdiplus_H - Advanced graphics + resources
10. ResourcesProgressBar - UI control mastery
11. WindowsDrawing - Graphics and mouse handling
12. PolimorficSmart - Enterprise C++ design

## Known Limitations

1. **Windows GUI Examples**: Require Windows OS (build skipped on Linux/macOS)
2. **GDI+**: Limited to Windows (no cross-platform graphics in this release)
3. **Console-Only on Linux/macOS**: No GUI examples for non-Windows platforms

## Future Enhancements

- Cross-platform GUI examples (Qt, wxWidgets)
- Web/REST API example
- Networking examples
- Database integration examples
- Performance profiling examples

## License

Apache License 2.0 - See LICENSE file

## Contributing

See CONTRIBUTING.md for:
- Code style guidelines
- Adding new examples
- Pull request process
- Documentation standards

## Support & Feedback

- **Learning Questions**: See README.md
- **Issues**: GitHub Issues for bugs
- **Contributions**: See CONTRIBUTING.md
- **Feedback**: GitHub Discussions

## Release History

- **v0.0.0** (2026-08-12): Initial release
  - 12 examples: ✅ Complete
  - Windows support: ✅ Full (7 GUI + 5 console)
  - Linux/macOS support: ✅ Console-only (5 examples)
  - Documentation: ✅ Comprehensive
