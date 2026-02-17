# Visual Studio Setup Instructions

This guide explains how to build and run the SDLLevels project using Visual Studio 2022.

## Prerequisites

- **Visual Studio 2022** (Community, Professional, or Enterprise)
- **Desktop development with C++** workload installed
- **SDL3-3.4.0** development libraries

## SDL3 Setup

The project requires SDL3-3.4.0 to be placed in the `External/SDL3-3.4.0/` directory.

### Step 1: Download SDL3-3.4.0

1. Visit the SDL3 releases page: https://github.com/libsdl-org/SDL/releases
2. Download **SDL3-3.4.0** (or the closest available version)
3. Download the Windows development libraries (e.g., `SDL3-devel-3.4.0-VC.zip`)

### Step 2: Extract SDL3

Extract the downloaded archive and place it in your project directory with the following structure:

```
GameEngineMidterm/
├── External/
│   └── SDL3-3.4.0/
│       ├── include/
│       │   └── SDL3/
│       │       ├── SDL.h
│       │       └── (other SDL3 headers)
│       └── lib/
│           └── x64/
│               ├── SDL3.lib
│               └── SDL3.dll
├── SDLLevels.sln
├── SDLLevels.vcxproj
├── Include/
├── Source/
└── Assets/
```

**Important:** The path must be exactly `External\SDL3-3.4.0\` for the project settings to work.

### Alternative: Manual SDL3 Path Configuration

If you want to place SDL3 in a different location:

1. Open `SDLLevels.vcxproj` in a text editor
2. Find these lines:
   - `$(SolutionDir)External\SDL3-3.4.0\include`
   - `$(SolutionDir)External\SDL3-3.4.0\lib\x64`
3. Replace with your custom SDL3 path

## Building the Project

### Option 1: Using Visual Studio GUI

1. **Open the solution:**
   - Double-click `SDLLevels.sln` in Windows Explorer
   - Or in Visual Studio: File → Open → Project/Solution → Select `SDLLevels.sln`

2. **Select configuration:**
   - Choose `Debug` or `Release` from the configuration dropdown
   - Choose `x64` from the platform dropdown

3. **Build the project:**
   - Press `Ctrl+Shift+B` or
   - Menu: Build → Build Solution

4. **Run the project:**
   - Press `F5` to build and run with debugging
   - Press `Ctrl+F5` to build and run without debugging

### Option 2: Using Developer Command Prompt

```cmd
cd GameEngineMidterm
msbuild SDLLevels.sln /p:Configuration=Release /p:Platform=x64
```

## Project Structure in Visual Studio

When you open the solution, you'll see the following organization in Solution Explorer:

```
SDLLevels
├── Header Files
│   ├── Framework
│   │   ├── StandardIncludes.h
│   │   ├── Singleton.h
│   │   ├── ObjectPool.h
│   │   ├── StackAllocator.h
│   │   ├── Serializable.h
│   │   ├── Resource.h
│   │   ├── Asset.h
│   │   ├── FileController.h
│   │   ├── TGAReader.h
│   │   ├── Texture.h
│   │   ├── Renderer.h
│   │   └── AssetController.h
│   └── Game
│       ├── Warrior.h
│       ├── Rock.h
│       ├── Level.h
│       ├── Level1.h
│       ├── Level2.h
│       └── GameController.h
├── Source Files
│   ├── Framework
│   │   ├── TGAReader.cpp
│   │   ├── Texture.cpp
│   │   ├── Renderer.cpp
│   │   └── AssetController.cpp
│   ├── Game
│   │   ├── Warrior.cpp
│   │   ├── Rock.cpp
│   │   ├── Level.cpp
│   │   ├── Level1.cpp
│   │   ├── Level2.cpp
│   │   └── GameController.cpp
│   └── main.cpp
├── Resource Files
│   └── generate_textures.py
└── Documentation
    ├── BUILD.md
    ├── CMakeLists.txt
    ├── IMPLEMENTATION_SUMMARY.md
    ├── PROJECT_STATUS.md
    ├── README.md
    └── VERIFICATION.md
```

## Output Directories

The project is configured with the following output structure:

- **Binary output:** `bin\Debug\` or `bin\Release\`
- **Intermediate files:** `obj\Debug\` or `obj\Release\`

The build process automatically:
1. Copies `SDL3.dll` to the output directory
2. Copies the `Assets/` folder to the output directory

## Generating Test Textures

Before running the game for the first time, generate the test textures:

```cmd
python generate_textures.py
```

This creates:
- `Assets/Textures/warrior_run.tga`
- `Assets/Textures/warrior_death.tga`
- `Assets/Textures/rock.tga`

## Troubleshooting

### Error: "Cannot open include file: 'SDL3/SDL.h'"

**Cause:** SDL3 is not in the expected location.

**Solution:**
1. Verify SDL3 is in `External\SDL3-3.4.0\include\`
2. Check that the path contains `SDL3\SDL.h`
3. Rebuild the project

### Error: "Cannot open file 'SDL3.lib'"

**Cause:** SDL3 library files are not in the expected location.

**Solution:**
1. Verify SDL3 is in `External\SDL3-3.4.0\lib\x64\`
2. Check that the folder contains `SDL3.lib`
3. Ensure you're building for x64 platform

### Error: "The program can't start because SDL3.dll is missing"

**Cause:** SDL3.dll was not copied to the output directory.

**Solution:**
1. Check that `SDL3.dll` exists in `External\SDL3-3.4.0\lib\x64\`
2. Rebuild the project (the pre-build event should copy it)
3. Manually copy `SDL3.dll` to `bin\Debug\` or `bin\Release\`

### Build Warning: "SDL3.dll not found"

**Cause:** This is a pre-build event warning when SDL3 is not installed.

**Solution:**
Follow the SDL3 setup instructions above to download and install SDL3.

### Missing textures or black screen

**Cause:** Texture files are not generated or copied.

**Solution:**
1. Run `python generate_textures.py` to create textures
2. Verify `Assets\Textures\` contains .tga files
3. Rebuild the project (post-build event copies Assets)

## Advanced Configuration

### Changing Output Directories

Edit the project properties in Visual Studio:
1. Right-click project → Properties
2. General → Output Directory / Intermediate Directory
3. Modify paths as needed

### Adding Include/Library Paths

Edit the project properties in Visual Studio:
1. Right-click project → Properties
2. C/C++ → General → Additional Include Directories
3. Linker → General → Additional Library Directories
4. Linker → Input → Additional Dependencies

### Debug vs Release Configuration

**Debug Configuration:**
- Includes debugging symbols
- No optimization
- Easier to debug with breakpoints
- Slower performance

**Release Configuration:**
- Optimized for performance
- No debugging symbols
- Smaller binary size
- Faster execution

## CMake Alternative

If you prefer using CMake instead of Visual Studio project files, see `BUILD.md` for instructions. The CMake build system is still supported and maintained alongside the Visual Studio project files.

## Running the Game

After successful build:

1. **Launch:** Press F5 in Visual Studio or run `bin\Debug\SDLLevels.exe`
2. **Level 1:** Watch warriors move across a grey background
3. **Auto-save:** At 5 seconds, level data is saved to `Level1.bin`
4. **Level 2:** After first warrior exits, transitions to Level 2 with falling rocks
5. **Collision:** Warriors play death animation when hit
6. **Exit:** Game closes when first warrior exits or all die

## Expected Output

When running correctly, you should see:

- Window: 1920×1080 titled "SDLLevels - Game Engine Midterm"
- Console: Shows FPS, loading messages, and save confirmation
- Level 1: Grey background with animated warriors
- Level 2: Green background with rocks and collision detection

## Support

For build issues:

1. Check this guide's troubleshooting section
2. Verify SDL3 is correctly installed
3. Review error messages in Visual Studio's Error List
4. Check the Output window for detailed build logs

For general project information, see:
- `README.md` - Project overview
- `BUILD.md` - CMake build instructions
- `VERIFICATION.md` - Testing and validation
- `IMPLEMENTATION_SUMMARY.md` - Technical details
