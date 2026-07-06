# Easy C++ Examples

A collection of practical C++ examples demonstrating modern language features, Windows GUI programming, and CMake build system usage. All examples are fully documented with Doxygen-compatible comments.

## Project Structure

```
EasyExamples/
├── PolimorficSmart/              # Advanced C++ with polymorphism & smart pointers
├── ModernCPP_Containers/         # STL containers, algorithms, and file I/O
├── ExceptionHandling/            # Custom exceptions and error recovery
├── WindowsHEasiest/              # Minimal Windows GUI example
├── WindowsDialog/                # Dialog boxes with input validation
├── WindowsAndCommctrlH/          # Windows with common controls
├── WindowsDrawing/               # Graphics drawing and mouse interaction
├── Gdiplus_H/                    # Windows GUI with GDI+ graphics
├── ResourcesAndGdiplus_H/        # Resources + GDI+ integration
├── ResourcesProgressBar/         # Progress bar control example
├── VsCodeCmakeEasiest/           # Minimal CMake project
├── VsCodeCmakeW2src/             # Multi-file CMake project
└── README.md                     # This file
```

---

## Difficulty Order (Numbered)

Here the examples are ordered from easiest to most advanced:

1. `VsCodeCmakeEasiest`
2. `VsCodeCmakeW2src`
3. `WindowsHEasiest`
4. `ModernCPP_Containers`
5. `ExceptionHandling`
6. `WindowsAndCommctrlH`
7. `WindowsDialog`
8. `Gdiplus_H`
9. `ResourcesAndGdiplus_H`
10. `ResourcesProgressBar`
11. `WindowsDrawing`
12. `PolimorficSmart`

## Examples Summary

### PolimorficSmart

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

### ExceptionHandling

**Location:** `ExceptionHandling/`

Comprehensive guide to exception handling with custom exceptions, error recovery, and exception safety guarantees.

**Key Features:**
- **Custom Exception Classes**: Inheriting from std::exception
- **Try/Catch Blocks**: Multiple catch blocks for different exception types
- **Exception Propagation**: Passing exceptions through function call stacks
- **RAII with Exceptions**: Exception-safe resource management
- **Exception Safety Guarantees**: Strong, basic, and no-throw guarantees
- **Catch Order**: Matching specific exceptions before generic ones
- **Transaction Rollback**: Undoing operations on failure
- **Practical Error Recovery**: Real-world error handling patterns

**Key Files:**
- `src/main.cpp` - Bank account system demonstrating exception handling patterns
- `CMakeLists.txt` - C++17 project configuration with exception flags

**Demonstrates:**
✓ Custom exception class design  
✓ Try/catch/throw mechanics  
✓ Multiple exception types  
✓ Exception propagation and stack unwinding  
✓ Exception safety guarantees  
✓ RAII with exception cleanup  
✓ Transaction safety and rollback  
✓ Real-world error scenarios  

**Build & Run:**
```bash
cd ExceptionHandling
mkdir build && cd build
cmake -S .. -B .
cmake --build .
./Debug/exception_example
```

---

### ModernCPP_Containers

**Location:** `ModernCPP_Containers/`

Comprehensive guide to STL containers, algorithms, and modern C++ features using practical examples.

**Key Features:**
- **Vector Operations**: Sorting, filtering, and aggregation
- **Map Containers**: Efficient key-value lookups
- **Set Operations**: Unique value management
- **String Manipulation**: Trimming, splitting, parsing
- **File I/O**: Reading and writing text files
- **Lambda Expressions**: Functional programming with STL
- **Range-based For Loops**: Clean iteration syntax
- **Structured Bindings**: C++17 feature demonstration
- **Algorithms**: std::sort, std::find, std::transform, std::accumulate

**Key Files:**
- `main.cpp` - Demonstrations of all STL features
- `CMakeLists.txt` - C++17 project configuration

**Demonstrates:**
✓ STL container types (vector, map, set)  
✓ Algorithms and functional operations  
✓ Lambda expressions and captures  
✓ File I/O with formatted output  
✓ String manipulation and parsing  
✓ C++17 structured bindings  
✓ Iterator patterns  

**Build & Run:**
```bash
cd ModernCPP_Containers
mkdir build && cd build
cmake -S .. -B .
cmake --build .
./Debug/containers_example
```

---

### WindowsHEasiest

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

### WindowsDialog

**Location:** `WindowsDialog/`

Demonstrates dialog-like windows with input controls, validation, and event handling.

**Key Features:**
- **Edit Controls**: Text input fields
- **Button Controls**: Click event handling
- **Static Text**: Display messages
- **Input Validation**: Age and name validation logic
- **Message Boxes**: User feedback dialogs
- **Window Message Handling**: WM_COMMAND, WM_CREATE, WM_DESTROY
- **Helper Functions**: Extracting and setting control text

**Key Files:**
- `src/main.cpp` - Dialog window with controls
- `CMakeLists.txt` - Windows subsystem configuration
- `src/resource.rc` - Resource file template

**Demonstrates:**
✓ Creating child window controls  
✓ Button click event handling  
✓ Edit control text retrieval  
✓ Input validation patterns  
✓ Message boxes for user feedback  
✓ Control management  
✓ Window procedure message routing  

**Build & Run:**
```bash
cd WindowsDialog
mkdir build && cd build
cmake -S .. -B .
cmake --build .
./Debug/dialog_example.exe
```

---

### WindowsAndCommctrlH

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

### WindowsDrawing

**Location:** `WindowsDrawing/`

Interactive drawing application with GDI+ graphics, shape manipulation, and animation.

**Key Features:**
- **GDI+ Graphics**: Drawing circles, ellipses, and lines
- **Mouse Interaction**: Click-to-select and drag-to-move shapes
- **Animation**: Timer-driven shape rotation
- **Color Management**: Multiple colored shapes
- **Double-Buffering**: Smooth rendering without flicker
- **Shape Selection**: Visual feedback with highlighting
- **Real-time Rendering**: WM_PAINT message handling

**Key Files:**
- `src/main.cpp` - Drawing window with graphics and input handling
- `CMakeLists.txt` - GDI+ linking configuration

**Demonstrates:**
✓ GDI+ graphics initialization and cleanup  
✓ Drawing shapes (circles, lines)  
✓ Color and pen styling  
✓ Mouse event handling (down, move, up)  
✓ Hit detection for shape selection  
✓ Timer-based animation  
✓ Window class with member function callback  
✓ Double-buffering rendering pattern  

**Build & Run:**
```bash
cd WindowsDrawing
mkdir build && cd build
cmake -S .. -B .
cmake --build .
./Debug/drawing_example.exe
```

---

### Gdiplus_H

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

### ResourcesAndGdiplus_H

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

### ResourcesProgressBar

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

### VsCodeCmakeEasiest

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

### VsCodeCmakeW2src

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

### Repository-Wide Build (Recommended)

Use the root CMake project to configure and build all examples consistently:

```bash
cmake -S . -B build
cmake --build build --config Debug
```

Run tests discovered by CTest:

```bash
ctest --test-dir build -C Debug --output-on-failure
```

To disable Win32 GUI examples and build console examples only:

```bash
cmake -S . -B build -DBUILD_WINDOWS_EXAMPLES=OFF
cmake --build build --config Debug
```

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
4. Study `ModernCPP_Containers` - STL basics and practical usage

**Intermediate:**
1. Learn `ExceptionHandling` - error handling and recovery patterns
2. Explore `WindowsDialog` - interactive controls and validation
3. Study `WindowsAndCommctrlH` - Windows common controls
4. Learn `Gdiplus_H` - graphics programming basics
5. Try `WindowsDrawing` - interactive graphics with mouse handling

**Advanced:**
1. Deep dive into `PolimorficSmart/main.cpp` - smart pointer patterns
2. Study `PolimorficSmart/simple_test.cpp` - testing approach
3. Explore `PolimorficSmart/threaded_main.cpp` - concurrency patterns
4. Combine multiple concepts in custom projects

---

## Key Concepts Demonstrated

| Concept | Example |
|---------|---------|
| **Polymorphism** | PolimorficSmart |
| **Smart Pointers** | PolimorficSmart |
| **Factory Pattern** | PolimorficSmart |
| **STL Containers** | ModernCPP_Containers |
| **Algorithms & Lambdas** | ModernCPP_Containers |
| **File I/O** | ModernCPP_Containers |
| **String Manipulation** | ModernCPP_Containers |
| **Exception Handling** | ExceptionHandling |
| **Custom Exceptions** | ExceptionHandling |
| **Error Recovery** | ExceptionHandling |
| **Exception Safety** | ExceptionHandling |
| **CMake Basics** | VsCodeCmakeEasiest |
| **Multi-file Projects** | VsCodeCmakeW2src |
| **Windows GUI** | WindowsHEasiest |
| **Dialog Controls** | WindowsDialog |
| **Input Validation** | WindowsDialog |
| **Common Controls** | WindowsAndCommctrlH |
| **Graphics (GDI+)** | WindowsDrawing, Gdiplus_H |
| **Mouse Input** | WindowsDrawing |
| **Animation** | WindowsDrawing |
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

### CI Build or Test Failure
- Open the failed GitHub Actions run and download the diagnostics artifact for that job.
- Artifact names start with `diagnostics-` and include the failing matrix leg/job.
- Artifacts include CTest temporary logs, `Test.xml`, and CMake configure logs.
- Use the same configure flags locally to reproduce (examples):

```bash
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

```bash
cmake -S . -B build_strict_root -DBUILD_TESTING=ON -DEASYEXAMPLES_STRICT_WARNINGS=ON -DBUILD_WINDOWS_EXAMPLES=OFF
cmake --build build_strict_root --config Debug
ctest --test-dir build_strict_root -C Debug --output-on-failure
```

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

See governance and engineering process docs:

- `CONTRIBUTING.md`
- `SECURITY.md`
- `docs/RELEASE_CHECKLIST.md`
- `.github/CODEOWNERS`
