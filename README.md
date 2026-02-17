# GameEngineMidterm - SDLLevels

A complete C++/SDL3 game engine implementation featuring a two-level game with animated warriors and rocks, collision detection, serialization, and auto-save functionality.

## Project Overview

This project implements a game engine midterm assignment with the following features:

### Level 1
- 10 animated warriors moving horizontally across the screen
- Randomized movement speeds (80-100 pixels/second)
- Animation speed scales with movement speed (4.8-6.0 fps)
- Grey background (RGB: 128, 128, 128)
- Auto-save at 5 seconds with reload verification
- Transitions to Level 2 when first warrior exits screen

### Level 2
- Warriors continue from Level 1 with preserved state
- 10 animated rocks falling vertically
- AABB collision detection between warriors and rocks
- Death animations for warriors on collision
- Light green background (RGB: 0, 128, 0)
- Auto-save at 5 seconds
- Game exits when first warrior exits OR all warriors are dead

### Framework Components
- **ObjectPool** - Entity pooling system
- **StackAllocator** - Memory allocation for assets
- **FileController** - File I/O operations
- **AssetController** - Asset loading and management
- **Resource** - Base class for game entities
- **Serializable** - Save/load interface
- **Singleton** - Manager class pattern
- **Renderer** - SDL3 rendering with animation support
- **Texture** - TGA texture loading
- **TGAReader** - TGA file parsing

## Requirements

- C++17 or higher
- SDL3 library
- CMake 3.15 or higher (or Visual Studio 2022)
- Python 3 (for generating test textures)

## Build Instructions

### Linux/Mac (CMake)

1. Install SDL3:
   ```bash
   # On Ubuntu/Debian
   sudo apt-get install libsdl3-dev
   
   # On Mac with Homebrew
   brew install sdl3
   ```

2. Build the project:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

3. Run:
   ```bash
   ./SDLLevels
   ```

### Windows (Visual Studio 2022)

#### Option 1: Using Visual Studio Solution (Recommended)

1. Download SDL3-3.4.0 development libraries from https://github.com/libsdl-org/SDL/releases
2. Extract to `External/SDL3-3.4.0/` directory
3. Double-click `SDLLevels.sln` to open in Visual Studio
4. Build and run (F5)

For detailed instructions, see [VISUAL_STUDIO_SETUP.md](VISUAL_STUDIO_SETUP.md)

#### Option 2: Using CMake

```cmd
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

For detailed CMake instructions, see [BUILD.md](BUILD.md)

## Project Structure

```
GameEngineMidterm/
├── SDLLevels.sln          # Visual Studio solution
├── SDLLevels.vcxproj      # Visual Studio project
├── SDLLevels.vcxproj.filters  # File organization
├── SDLLevels.vcxproj.user     # Debug settings
├── CMakeLists.txt         # CMake build file
├── Assets/
│   └── Textures/          # TGA sprite sheets
│       ├── warrior_run.tga    (384x64 - 6 frames)
│       ├── warrior_death.tga  (512x64 - 8 frames)
│       └── rock.tga           (256x64 - 4 frames)
├── Include/               # Header files
│   ├── StandardIncludes.h
│   ├── Singleton.h
│   ├── ObjectPool.h
│   ├── StackAllocator.h
│   ├── Serializable.h
│   ├── Resource.h
│   ├── Asset.h
│   ├── FileController.h
│   ├── AssetController.h
│   ├── TGAReader.h
│   ├── Texture.h
│   ├── Renderer.h
│   ├── Warrior.h
│   ├── Rock.h
│   ├── Level.h
│   ├── Level1.h
│   ├── Level2.h
│   └── GameController.h
├── Source/                # Implementation files
│   ├── main.cpp
│   ├── TGAReader.cpp
│   ├── Texture.cpp
│   ├── Renderer.cpp
│   ├── AssetController.cpp
│   ├── Warrior.cpp
│   ├── Rock.cpp
│   ├── Level.cpp
│   ├── Level1.cpp
│   ├── Level2.cpp
│   └── GameController.cpp
├── External/              # Third-party libraries
│   └── SDL3-3.4.0/
├── BUILD.md               # CMake build instructions
├── VISUAL_STUDIO_SETUP.md # VS setup instructions
└── README.md
```

## Controls

- **ESC** - Quit game
- Window close button - Quit game

## Technical Details

### Specifications
- Resolution: 1920×1080
- Target FPS: 60+
- SDL Version: SDL3.x
- C++ Standard: C++17

### Warrior Properties
- Scale: 1.8× texture size
- Movement: Horizontal (left to right)
- Speed: 80-100 px/s (randomized)
- Animation: 4.8-6.0 fps (based on speed)
- States: RUNNING, DYING, DEAD

### Rock Properties
- Scale: 1.0× texture size
- Movement: Vertical (top to bottom)
- Speed: 80-100 px/s (randomized)
- Animation: 4.8-6.0 fps (based on speed)

### Collision Detection
Uses AABB (Axis-Aligned Bounding Box) algorithm for efficient collision detection between warriors and rocks.

### Serialization
Binary serialization format for saving/loading game state:
- Level data (game time, auto-save status, background color)
- Warrior states (position, velocity, animation frame, state)
- Rock states (position, velocity, animation frame, active status)

### UI Elements
- FPS counter (top-left, blue text)
- Game time (top-left, blue text)
- Save status (top-left, blue text)

## Testing Checklist

### Level 1
- [x] Window opens at 1920×1080
- [x] Grey background (128, 128, 128)
- [x] 10 warriors spawn at correct Y positions
- [x] Warriors move at randomized speeds
- [x] Animations play at different speeds
- [x] UI labels display correctly
- [x] Auto-save triggers at 5 seconds
- [x] Level transitions when first warrior exits

### Level 2
- [x] Green background (0, 128, 0)
- [x] Warriors continue from Level 1
- [x] 10 rocks spawn at correct X positions
- [x] Rocks fall at randomized speeds
- [x] Collision detection works
- [x] Death animations play correctly
- [x] Auto-save triggers at 5 seconds
- [x] Game exits on correct conditions

## Development Notes

### Generated Files
The project includes a Python script (`generate_textures.py`) to create placeholder TGA textures for testing. These are simple colored shapes that demonstrate the animation system.

### Memory Management
- Object pools manage warrior, rock, and texture instances
- Stack allocator handles asset memory
- No manual new/delete for pooled objects

### Performance
- Targets 60+ FPS on modern hardware
- Delta time prevents physics issues on slow frames
- Efficient AABB collision detection

## License

Educational project for game engine development course.

## Author

Implementation for Game Engine Midterm Project