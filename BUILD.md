# Build Instructions for SDLLevels

## Prerequisites

### Required Software
1. **C++ Compiler**: GCC 7+, Clang 6+, or MSVC 2019+
2. **CMake**: Version 3.15 or higher
3. **SDL3**: Development libraries
4. **Python 3**: For generating test textures

## SDL3 Installation

### Option 1: Build from Source (Recommended for SDL3)

Since SDL3 is relatively new, you may need to build it from source:

```bash
# Clone SDL3
git clone https://github.com/libsdl-org/SDL.git -b main
cd SDL
mkdir build && cd build

# Configure and build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
sudo cmake --install .
```

### Option 2: Use SDL2 (Fallback)

If SDL3 is not available, the code can be adapted to SDL2:

**Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install libsdl2-dev
```

**macOS (Homebrew):**
```bash
brew install sdl2
```

**Windows:**
1. Download SDL2 development libraries from https://www.libsdl.org/download-2.0.php
2. Extract to `External/SDL3/` (rename SDL2 to SDL3 for consistency)

To adapt the code for SDL2, make these changes:
1. Replace `#include <SDL3/SDL.h>` with `#include <SDL2/SDL.h>` in `StandardIncludes.h`
2. Update SDL3-specific API calls to SDL2 equivalents (mainly event types and rendering functions)

## Building the Project

### Linux/macOS

1. **Generate textures** (one-time setup):
   ```bash
   python3 generate_textures.py
   ```

2. **Configure and build**:
   ```bash
   mkdir build
   cd build
   cmake ..
   make -j$(nproc)
   ```

3. **Run the game**:
   ```bash
   ./SDLLevels
   ```

### Windows (Visual Studio)

#### Using CMake GUI:
1. Open CMake GUI
2. Set source directory to the project root
3. Set build directory to `build/`
4. Click "Configure" and select your Visual Studio version
5. Click "Generate"
6. Open `SDLLevels.sln` in Visual Studio
7. Build and run (F5)

#### Using CMake Command Line:
```cmd
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

#### Using Visual Studio Directly:
1. Create a new C++ project
2. Add all .cpp files from `Source/`
3. Add `Include/` to include directories
4. Configure SDL3 library paths:
   - Additional Include Directories: `$(ProjectDir)External\SDL3\include`
   - Additional Library Directories: `$(ProjectDir)External\SDL3\lib\x64`
   - Additional Dependencies: `SDL3.lib`
5. Copy SDL3.dll to output directory
6. Build and run

## Troubleshooting

### "SDL3/SDL.h: No such file or directory"

**Solution 1:** Install SDL3 system-wide (see installation instructions above)

**Solution 2:** Place SDL3 in `External/SDL3/`:
```
External/SDL3/
├── include/
│   └── SDL3/
│       └── SDL.h (and other headers)
├── lib/
│   └── x64/
│       ├── SDL3.lib (Windows)
│       └── libSDL3.a (Linux/Mac)
└── bin/ (Windows only)
    └── SDL3.dll
```

**Solution 3:** Use SDL2 instead (see SDL2 adaptation above)

### CMake can't find SDL3

Add SDL3 path to CMake:
```bash
cmake .. -DSDL3_DIR=/path/to/SDL3/lib/cmake/SDL3
```

Or set environment variable:
```bash
export SDL3_DIR=/path/to/SDL3/lib/cmake/SDL3
```

### Linker errors

**Linux:** You may need to link additional libraries:
```bash
sudo apt-get install libx11-dev libxext-dev libwayland-dev libxkbcommon-dev
```

**Windows:** Ensure SDL3.dll is in the same directory as the executable.

### Runtime errors - "Failed to initialize SDL"

- Check that SDL3.dll (Windows) or libSDL3.so (Linux) is in the correct location
- On Linux, update library cache: `sudo ldconfig`
- Try running with `SDL_VIDEODRIVER=x11` on Linux

### Missing textures

Run the texture generation script:
```bash
python3 generate_textures.py
```

This creates:
- `Assets/Textures/warrior_run.tga`
- `Assets/Textures/warrior_death.tga`
- `Assets/Textures/rock.tga`

## Testing the Build

After successful build, you should see:

1. **Window**: 1920×1080 titled "SDLLevels - Game Engine Midterm"
2. **Level 1**: Grey background with 10 warriors moving left to right
3. **UI**: Blue text showing FPS, Time, and Status
4. **Auto-save**: At 5 seconds, console shows "Level saved to: Level1.bin"
5. **Transition**: When first warrior exits, transitions to Level 2
6. **Level 2**: Green background with rocks falling
7. **Collision**: Warriors play death animation when hit by rocks
8. **Exit**: Game closes when first warrior exits or all die

## Performance Tips

If you experience low FPS:

1. **Reduce resolution**: Edit GameController.cpp line with `Initialize("SDLLevels", 1920, 1080)`
2. **Disable V-Sync**: Add to Renderer::Initialize():
   ```cpp
   SDL_SetRenderVSync(m_renderer, 0);
   ```
3. **Profile**: Run with a profiler to identify bottlenecks

## Development Build

For faster compilation during development:

```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j$(nproc)
```

Debug build includes:
- Debugging symbols
- No optimization
- More verbose error messages

## Release Build

For final submission:

```bash
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

Release build includes:
- Optimization flags
- No debugging symbols
- Smaller binary size
- Better performance

## Packaging for Submission

Create a zip file with:

```bash
zip -r SDLLevels_Submission.zip \
    Source/ \
    Include/ \
    Assets/ \
    CMakeLists.txt \
    README.md \
    BUILD.md \
    generate_textures.py \
    -x "*.o" "*.bin" "*~"
```

Do NOT include:
- build/ directory
- .vs/ directory
- *.user files
- Level1.bin / Level2.bin (generated at runtime)
- SDL3 binaries (document how to obtain them)

## Additional Resources

- SDL3 Documentation: https://wiki.libsdl.org/SDL3/
- SDL3 Migration Guide: https://github.com/libsdl-org/SDL/blob/main/docs/README-migration.md
- CMake Documentation: https://cmake.org/documentation/
- TGA File Format: http://www.paulbourke.net/dataformats/tga/

## Support

For build issues specific to your environment, please provide:
1. Operating system and version
2. Compiler version (`g++ --version` or `cl /?`)
3. CMake version (`cmake --version`)
4. SDL version and installation method
5. Complete error message and build log
