# SDLLevels - Implementation Verification Checklist

## Pre-Build Checks

### File Structure
- [ ] All header files present in `Include/` directory
- [ ] All implementation files present in `Source/` directory
- [ ] Asset files generated in `Assets/Textures/`
  - [ ] warrior_run.tga (384×64)
  - [ ] warrior_death.tga (512×64)
  - [ ] rock.tga (256×64)
- [ ] CMakeLists.txt configured correctly
- [ ] .gitignore excludes build artifacts

### Framework Classes (No Custom Implementations Allowed)
- [x] Singleton template implemented
- [x] ObjectPool template implemented
- [x] StackAllocator implemented
- [x] Serializable interface implemented
- [x] Resource base class implemented
- [x] FileController implemented
- [x] AssetController implemented
- [x] Asset class implemented

### Graphics Components
- [x] TGAReader implemented
- [x] Texture class with pooling implemented
- [x] Renderer with animation support implemented

### Game Entities
- [x] Warrior class (Resource + Serializable)
  - [x] Running state with animation
  - [x] Dying state with death animation
  - [x] Dead state
  - [x] Serialization support
- [x] Rock class (Resource + Serializable)
  - [x] Active/inactive states
  - [x] Animation support
  - [x] Serialization support

### Level System
- [x] Level base class implemented
- [x] Level1 implementation
  - [x] 10 warriors spawned correctly
  - [x] Grey background (128, 128, 128)
  - [x] Auto-save at 5 seconds
  - [x] Transition logic
- [x] Level2 implementation
  - [x] Warriors transferred from Level1
  - [x] 10 rocks spawned correctly
  - [x] Green background (0, 128, 0)
  - [x] Collision detection
  - [x] Auto-save at 5 seconds
  - [x] Quit conditions

### Game Controller
- [x] Main game loop implemented
- [x] Delta time calculation
- [x] FPS calculation
- [x] Event handling (quit, ESC key)
- [x] UI rendering (FPS, Time, Status)
- [x] Level transition handling

## Build Verification

### Compilation
- [ ] No compilation errors
- [ ] No compilation warnings
- [ ] All object files generated
- [ ] Executable created successfully

### Dependencies
- [ ] SDL3 headers found
- [ ] SDL3 library linked
- [ ] No missing symbols during linking

## Runtime Verification - Level 1

### Window and Display
- [ ] Window opens successfully
- [ ] Window title is "SDLLevels - Game Engine Midterm"
- [ ] Window resolution is 1920×1080
- [ ] Background color is grey (128, 128, 128)
- [ ] Window is visible and responsive

### Warrior Spawning
- [ ] Exactly 10 warriors spawn
- [ ] Warrior Y positions: 10, 110, 210, 310, 410, 510, 610, 710, 810, 910
- [ ] Warriors start at X = -100 (off-screen left)
- [ ] Warriors scale is 1.8× (approx 115×115 pixels)
- [ ] All warriors visible and rendering correctly

### Warrior Movement
- [ ] All warriors move left to right
- [ ] Warriors have different speeds (visible variation)
- [ ] Speed range appears to be 80-100 px/s
- [ ] Warriors move smoothly without stuttering
- [ ] Warriors eventually exit screen on the right

### Warrior Animation
- [ ] Running animation plays continuously
- [ ] Animation has 6 frames
- [ ] Different warriors have different animation speeds (visible)
- [ ] Animation speed range is 4.8-6.0 fps
- [ ] Faster moving warriors animate faster
- [ ] Animation is smooth and continuous

### UI Elements
- [ ] FPS label visible at (10, 10) in blue
- [ ] FPS value updates every second
- [ ] Time label visible at (200, 10) in blue
- [ ] Time increases continuously
- [ ] Status label visible at (400, 10) in blue
- [ ] Status shows "Not Saved" initially
- [ ] All labels are readable

### Auto-Save Functionality
- [ ] Game runs for at least 5 seconds
- [ ] At 5.0 seconds, console shows "Level saved to: Level1.bin"
- [ ] Level1.bin file created in working directory
- [ ] Status label changes to "Saved"
- [ ] Game continues smoothly after save
- [ ] Warriors maintain their positions after save/reload
- [ ] No crashes or freezes during save/reload

### Level Transition
- [ ] First warrior eventually reaches X > 1920
- [ ] Transition to Level 2 occurs
- [ ] Console shows "Transitioned to Level 2"
- [ ] No crash during transition
- [ ] Warriors carry over to Level 2

## Runtime Verification - Level 2

### Window and Display
- [ ] Background color changes to light green (0, 128, 0)
- [ ] Window remains responsive
- [ ] No visual glitches during transition

### Warrior Continuation
- [ ] All 10 warriors present (unless some died in Level 1)
- [ ] Warriors at same positions as Level 1 end
- [ ] Warriors continue moving right
- [ ] Warriors maintain their animation states
- [ ] Warrior speeds unchanged

### Rock Spawning
- [ ] Exactly 10 rocks spawn
- [ ] Rock X positions: 50, 150, 250, 350, 450, 550, 650, 750, 850, 950
- [ ] Rocks start at Y = -100 (off-screen top)
- [ ] Rocks scale is 1.0× (64×64 pixels)
- [ ] All rocks visible and rendering correctly

### Rock Movement
- [ ] All rocks fall downward
- [ ] Rocks have different speeds (visible variation)
- [ ] Speed range appears to be 80-100 px/s
- [ ] Rocks move smoothly
- [ ] Rocks eventually exit screen at bottom

### Rock Animation
- [ ] Rock animation plays continuously
- [ ] Animation has 4 frames
- [ ] Different rocks have different animation speeds (visible)
- [ ] Animation speed range is 4.8-6.0 fps
- [ ] Animation is smooth

### Collision Detection
- [ ] Collisions detected when rock overlaps warrior
- [ ] Collision detection is accurate (AABB)
- [ ] No false positives (collision when not overlapping)
- [ ] No false negatives (missing actual collisions)

### Collision Response
- [ ] Warrior starts death animation on collision
- [ ] Rock disappears immediately after collision
- [ ] Rock only collides with one warrior
- [ ] Death animation plays completely (8 frames)
- [ ] Warrior removed after death animation completes
- [ ] No crashes during collision handling

### UI Elements
- [ ] FPS label still visible and updating
- [ ] Time label still visible and updating
- [ ] Status label shows "Not Saved" initially
- [ ] All labels remain readable

### Auto-Save Functionality
- [ ] Game runs for at least 5 seconds in Level 2
- [ ] At 5.0 seconds, console shows "Level saved to: Level2.bin"
- [ ] Level2.bin file created
- [ ] Status label changes to "Saved"
- [ ] Game continues smoothly after save

### Exit Conditions
**Test Scenario 1: First Warrior Exits**
- [ ] Let game run until first warrior reaches X > 1920
- [ ] Game exits cleanly
- [ ] No crash on exit
- [ ] Console shows no errors

**Test Scenario 2: All Warriors Dead**
- [ ] Ensure all warriors collide with rocks
- [ ] Wait for all death animations to complete
- [ ] Game exits when last warrior dies
- [ ] No crash on exit

## Performance Verification

### Frame Rate
- [ ] FPS consistently above 30
- [ ] FPS averages 60 or higher
- [ ] No significant frame drops
- [ ] Smooth gameplay throughout

### Memory
- [ ] No memory leaks (check Task Manager/htop)
- [ ] Memory usage stable over time
- [ ] No crashes from out-of-memory

### CPU Usage
- [ ] CPU usage reasonable (<50% on one core)
- [ ] No 100% CPU usage
- [ ] Responsive to input

## Serialization Verification

### Level1.bin
- [ ] File created successfully
- [ ] File size reasonable (few KB)
- [ ] Can be read back
- [ ] Deserialized data matches original
- [ ] Warriors restored correctly

### Level2.bin
- [ ] File created successfully
- [ ] File size reasonable
- [ ] Contains both warrior and rock data
- [ ] Can be read back
- [ ] Data integrity maintained

## Code Quality Verification

### Organization
- [ ] Clear file structure
- [ ] Logical class hierarchy
- [ ] Appropriate use of inheritance
- [ ] Proper encapsulation

### Framework Usage
- [ ] Uses ObjectPool for warriors
- [ ] Uses ObjectPool for rocks
- [ ] Uses ObjectPool for textures
- [ ] Uses StackAllocator for assets
- [ ] Uses FileController for I/O
- [ ] Uses AssetController for asset management
- [ ] All entities inherit from Resource
- [ ] Serialization via Serializable interface
- [ ] Singleton pattern for managers

### Code Style
- [ ] Consistent naming conventions
- [ ] Appropriate comments where needed
- [ ] No unnecessary comments
- [ ] Clear variable names
- [ ] Reasonable function lengths

### Error Handling
- [ ] File I/O errors handled
- [ ] SDL initialization errors handled
- [ ] Texture loading errors handled
- [ ] No uncaught exceptions

## Edge Cases and Stress Tests

### Extended Play
- [ ] Game runs for 5+ minutes without issues
- [ ] No memory accumulation
- [ ] No performance degradation

### Rapid Events
- [ ] Multiple simultaneous collisions handled
- [ ] All warriors dying at once handled
- [ ] Rapid level transitions (if possible)

### File System
- [ ] Save works when files already exist (overwrite)
- [ ] Save works in read-only directory (fails gracefully)
- [ ] Load handles corrupted files

## Final Checks

### Documentation
- [ ] README.md complete and accurate
- [ ] BUILD.md provides clear build instructions
- [ ] Code has necessary comments
- [ ] No TODO markers in submitted code

### Submission Package
- [ ] All source files included
- [ ] All header files included
- [ ] Assets included
- [ ] Build files (CMakeLists.txt) included
- [ ] Documentation included
- [ ] No build artifacts included
- [ ] No binary files included (except textures)
- [ ] No .bin save files included

### Final Build
- [ ] Clean build from scratch succeeds
- [ ] No warnings in Release mode
- [ ] Executable runs without issues
- [ ] All tests pass

## Grading Criteria Self-Assessment

### Level 1 Implementation (8 marks)
- [ ] 10 warriors with correct spawning (2 marks)
- [ ] Movement and speed variation (2 marks)
- [ ] Animation with speed scaling (2 marks)
- [ ] Auto-save at 5s (2 marks)

### Level 2 Implementation (8 marks)
- [ ] Warriors transfer correctly (2 marks)
- [ ] 10 rocks with correct spawning (2 marks)
- [ ] Collision detection working (2 marks)
- [ ] Death animations and removal (2 marks)

### Framework Usage (4 marks)
- [ ] Proper use of ObjectPool (1 mark)
- [ ] Proper use of StackAllocator (1 mark)
- [ ] Proper serialization (1 mark)
- [ ] Proper resource management (1 mark)

### Code Quality (3 marks)
- [ ] Clear, readable code (1 mark)
- [ ] Good organization (1 mark)
- [ ] Proper commenting (1 mark)

### UI & Polish (2 marks)
- [ ] FPS/Time/Status labels (1 mark)
- [ ] Smooth gameplay (1 mark)

**Expected Total: 25/25 marks**

## Notes and Observations

### Issues Found
(Document any issues discovered during testing)

### Performance Notes
(Document FPS, memory usage, etc.)

### Known Limitations
(Document any known issues or limitations)

### Recommendations
(Document suggestions for improvements)

---

**Verification Date:** _______________
**Verified By:** _______________
**Overall Status:** [ ] PASS / [ ] FAIL
**Issues:** _______________
