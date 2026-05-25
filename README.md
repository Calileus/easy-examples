# Easy C++ Examples

A collection of practical C++ examples demonstrating modern language features, Windows GUI programming, and CMake build system usage. All examples are fully documented with Doxygen-compatible comments.

## Project Structure

```
EasyExamples/
├── PolimorficSmart/              # Advanced C++ with polymorphism & smart pointers
├── WindowsHEasiest/              # Minimal Windows GUI example
├── WindowsAndCommctrlH/          # Windows with common controls
├── Gdiplus_H/                    # Windows GUI with GDI+ graphics
├── ResourcesAndGdiplus_H/        # Resources + GDI+ integration
├── ResourcesProgressBar/         # Progress bar control example
├── VsCodeCmakeEasiest/           # Minimal CMake project
├── VsCodeCmakeW2src/             # Multi-file CMake project
└── README.md                     # This file
```

---

## Examples Summary

### 🏆 PolimorficSmart

**Location:** `PolimorficSmart/`

Comprehensive example of modern C++ features through a financial instruments system:

- **Polymorphism**: Abstract `FinancialInstrument` base class with `Stock`, `Bond`, and `Option` derived classes
- **Smart Pointers**: 
  - `unique_ptr` for exclusive ownership with move semantics
  - `shared_ptr` for shared ownership and reference counting
  - `weak_ptr` for non-owning references avoiding circular dependencies
- **Design Patterns**: Factory pattern for object creation, Observer pattern with weak_ptr
- **RAII**: Automatic resource management through smart pointers
- **Threading** (advanced): Thread-safe portfolio operations, market simulation with concurrent workers
- **Testing**: Simple test framework + Google Test (GTest) integration

**Key Files:**
- `financial_instrument.h` - Polymorphic class hierarchy
- `portfolio_market.h/cpp` - Portfolio and market management
- `main.cpp` - Demonstrations of all smart pointer types
- `simple_test.cpp` - Basic test framework
- `threaded_main.cpp` - Advanced threading examples
- `threaded_market.h` - Thread-safe concurrent operations

**Build & Run:**
```bash
cd PolimorficSmart
mkdir build && cd build
cmake -S .. -B .
cmake --build .
./Debug/financial_example      # Run main example
./Debug/simple_test            # Run simple tests
./Debug/threaded_example       # Run threading demo
./Debug/financial_tests        # Run GTest suite (if GTest installed)
```

**Demonstrates:**
✓ Inheritance and virtual functions  
✓ Smart pointer semantics and ownership models  
✓ Factory pattern  
✓ Reference counting  
✓ Move semantics  
✓ Circular reference prevention  
✓ Multithreading with smart pointers  
✓ Condition variables and producer-consumer pattern  

---

### 🪟 WindowsHEasiest

**Location:** `WindowsHEasiest/`

The simplest possible Windows GUI application using native Win32 API.

**Key Files:**
- `CMakeLists.txt` - Basic Windows project configuration
- `src/main.cpp` - Simple MessageBox example

**Demonstrates:**
✓ Windows.h header usage  
✓ MessageBox API  
✓ WinMain entry point  
✓ Basic CMake for Windows  

**Build & Run:**
```bash
cd WindowsHEasiest
mkdir build && cd build
cmake -S .. -B .
cmake --build .
./Debug/MyWindowsProject.exe
```

---

### 🎛️ WindowsAndCommctrlH

**Location:** `WindowsAndCommctrlH/`

Demonstrates using Windows Common Controls library for standard UI components.

**Key Files:**
- `CMakeLists.txt` - Link against comctl32
- `src/main.cpp` - InitCommonControlsEx initialization

**Demonstrates:**
✓ Common Controls initialization  
✓ ICC_WIN95_CLASSES flag  
✓ Standard Windows controls setup  
✓ Proper linking configuration  

**Build & Run:**
```bash
cd WindowsAndCommctrlH
mkdir build && cd build
cmake -S .. -B .
cmake --build .
./Debug/MyWindowsProject.exe
```

---

### 🎨 Gdiplus_H

**Location:** `Gdiplus_H/`

Graphics programming with GDI+ (Graphics Device Interface Plus) library on Windows.

**Key Files:**
- `CMakeLists.txt` - Link against gdi32 and gdiplus
- `src/main.cpp` - GdiplusStartup/Shutdown lifecycle

**Demonstrates:**
✓ GDI+ initialization and cleanup  
✓ Gdiplus namespace usage  
✓ Graphics library linking  
✓ Resource management with graphics APIs  

**Build & Run:**
```bash
cd Gdiplus_H
mkdir build && cd build
cmake -S .. -B .
cmake --build .
./Debug/MyexeWindowsProject.exe
```

---

### 📦 ResourcesAndGdiplus_H

**Location:** `ResourcesAndGdiplus_H/`

Integration of Windows resource files (.rc) with GDI+ graphics library.

**Key Files:**
- `CMakeLists.txt` - Resource file compilation configuration
- `resource.h` - Resource ID definitions
- `resource.rc` - Resource file with icon definition
- `src/main.cpp` - Loading and using resources
- `icon.ico` - Application icon resource

**Demonstrates:**
✓ Resource file compilation  
✓ Resource ID management  
✓ Icon loading with LoadIcon  
✓ Resource + graphics integration  
✓ hInstance usage for resource loading  

**Build & Run:**
```bash
cd ResourcesAndGdiplus_H
mkdir build && cd build
cmake -S .. -B .
cmake --build .
./Debug/MyWindowsProject.exe
```

---

### 📊 ResourcesProgressBar

**Location:** `ResourcesProgressBar/`

Demonstrates a progress bar Windows control with timer-driven updates.

**Key Files:**
- `CMakeLists.txt` - Common controls and resource configuration
- `resource.h` - Progress bar and timer IDs
- `resource.rc` - Icon resource definition
- `src/main.cpp` - Window procedure, progress bar creation, timer handling
- `icon.ico` - Application icon

**Demonstrates:**
✓ Progress bar control creation  
✓ Window message handling (WM_CREATE, WM_TIMER, WM_DESTROY)  
✓ SetTimer and KillTimer usage  
✓ Control message sending (PBM_SETPOS, PBM_SETRANGE)  
✓ Timer-driven UI updates  
✓ Resource loading and usage  

**Build & Run:**
```bash
cd ResourcesProgressBar
mkdir build && cd build
cmake -S .. -B .
cmake --build .
./Debug/MyWindowsProject.exe
```

---

### 🔨 VsCodeCmakeEasiest

**Location:** `VsCodeCmakeEasiest/`

Minimal CMake project with a single source file - the simplest possible C++ project.

**Key Files:**
- `CMakeLists.txt` - Minimal configuration
- `main.cpp` - Hello world program

**Demonstrates:**
✓ Basic CMakeLists.txt structure  
✓ project(), add_executable()  
✓ CMAKE_CXX_STANDARD setting  
✓ Minimal project organization  

**Build & Run:**
```bash
cd VsCodeCmakeEasiest
mkdir build && cd build
cmake -S .. -B .
cmake --build .
./Debug/MyProject.exe
```

---

### 📁 VsCodeCmakeW2src

**Location:** `VsCodeCmakeW2src/`

Multi-file CMake project demonstrating modular code organization across multiple source files.

**Key Files:**
- `CMakeLists.txt` - Multiple source file configuration
- `src/main.cpp` - Main entry point
- `src/helper.h` - Helper function declaration
- `src/helper.cpp` - Helper function implementation

**Demonstrates:**
✓ Multi-file project structure  
✓ Header/implementation separation  
✓ Linking multiple source files  
✓ Include directory management  
✓ Translation unit organization  

**Build & Run:**
```bash
cd VsCodeCmakeW2src
mkdir build && cd build
cmake -S .. -B .
cmake --build .
./Debug/MyProject.exe
```

---

## Building All Examples

### Prerequisites

- **C++ Compiler**: MSVC 2019+, GCC, or Clang with C++11+ support
- **CMake**: Version 3.10 or higher
- **Windows SDK** (for Windows examples)
- **Google Test** (optional, for GTest integration in PolimorficSmart)

### Quick Build (All Projects)

```bash
# Build all examples
for /d %i in (*) do (
    if exist "%i\CMakeLists.txt" (
        cd "%i"
        mkdir build 2>nul
        cd build
        cmake -S .. -B .
        cmake --build .
        cd ../..
    )
)
```

### Generator Options

**Visual Studio (Windows):**
```bash
cmake -S . -B build -G "Visual Studio 16 2019"
cmake --build build
```

**MinGW (Windows):**
```bash
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
```

**Unix/Linux:**
```bash
cmake -S . -B build
cmake --build build
```

---

## Documentation

All examples include comprehensive Doxygen documentation:

- **File-level docs**: `\file` and `\brief` tags describe purpose and scope
- **Class documentation**: Design patterns, usage notes, and inheritance structure
- **Function documentation**: Parameters, return values, and side effects
- **Code examples**: Inline `\code` blocks demonstrate usage patterns

### Generate Doxygen HTML

```bash
cd [example-directory]
doxygen Doxyfile  # If Doxyfile exists
# OR generate docs for all files
doxygen -g Doxyfile
doxygen Doxyfile
```

---

## Learning Path

**Beginners:**
1. Start with `VsCodeCmakeEasiest` - understand basic project setup
2. Move to `VsCodeCmakeW2src` - learn modular organization
3. Try `WindowsHEasiest` - first Windows GUI program

**Intermediate:**
1. Study `WindowsAndCommctrlH` - Windows common controls
2. Explore `Gdiplus_H` - graphics programming
3. Learn `ResourcesAndGdiplus_H` - resource management

**Advanced:**
1. Deep dive into `PolimorficSmart/main.cpp` - smart pointer patterns
2. Study `PolimorficSmart/simple_test.cpp` - testing approach
3. Explore `PolimorficSmart/threaded_main.cpp` - concurrency patterns
4. Run `PolimorficSmart/financial_tests` - GTest framework

---

## Key Concepts Demonstrated

| Concept | Example |
|---------|---------|
| **Polymorphism** | PolimorficSmart |
| **Smart Pointers** | PolimorficSmart |
| **Factory Pattern** | PolimorficSmart |
| **CMake Basics** | VsCodeCmakeEasiest |
| **Multi-file Projects** | VsCodeCmakeW2src |
| **Windows GUI** | WindowsHEasiest |
| **Common Controls** | WindowsAndCommctrlH |
| **Graphics (GDI+)** | Gdiplus_H |
| **Resources** | ResourcesAndGdiplus_H |
| **Progress Bar** | ResourcesProgressBar |
| **Threading** | PolimorficSmart (threaded_main.cpp) |
| **Unit Testing** | PolimorficSmart (simple_test.cpp, test_financial_instruments.cpp) |

---

## Troubleshooting

### CMake Configuration Fails
- Ensure CMake is installed and in PATH: `cmake --version`
- Try specifying a generator explicitly: `-G "Visual Studio 16 2019"`
- Delete `build/` directory and reconfigure

### Compilation Errors
- Check C++ standard: Projects use C++11 or C++17
- Verify Windows SDK is installed (for Windows examples)
- Check for missing dependencies (e.g., GTest for test_financial_instruments.cpp)

### Linking Errors
- Ensure all required libraries are linked in CMakeLists.txt
- Windows examples need: user32, gdi32, gdiplus, comctl32

### GTest Not Found
- Install Google Test: `vcpkg install gtest` or use package manager
- Optional - PolimorficSmart builds without GTest (skips test_financial_instruments.cpp)

---

## Project Information

- **Target Audience**: C++ learners, intermediate developers, educational use
- **Language**: C++11/17
- **Platforms**: Windows (primary), Unix/Linux compatible (CMake portions)
- **Build System**: CMake 3.10+
- **License**: Educational use

---

## Contributing

Improvements and additional examples are welcome! When contributing:
- Add comprehensive Doxygen documentation
- Update this README with new examples
- Include working CMakeLists.txt
- Test on both MSVC and GCC/Clang
- Follow existing code style
