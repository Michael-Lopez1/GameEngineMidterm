cmake_minimum_required(VERSION 3.15)
project(SDLLevels)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    Source/main.cpp
    Source/TGAReader.cpp
    Source/Texture.cpp
    Source/Renderer.cpp
    Source/AssetController.cpp
    Source/Warrior.cpp
    Source/Rock.cpp
    Source/Level.cpp
    Source/Level1.cpp
    Source/Level2.cpp
    Source/GameController.cpp
)

# Header files
set(HEADERS
    Include/StandardIncludes.h
    Include/Singleton.h
    Include/ObjectPool.h
    Include/StackAllocator.h
    Include/Serializable.h
    Include/Resource.h
    Include/Asset.h
    Include/FileController.h
    Include/TGAReader.h
    Include/Texture.h
    Include/Renderer.h
    Include/AssetController.h
    Include/Warrior.h
    Include/Rock.h
    Include/Level.h
    Include/Level1.h
    Include/Level2.h
    Include/GameController.h
)

# Create executable
add_executable(SDLLevels ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(SDLLevels PRIVATE 
    ${CMAKE_SOURCE_DIR}/Include
    ${CMAKE_SOURCE_DIR}/External/SDL3/include
)

# Find SDL3
find_package(SDL3 QUIET)

if(SDL3_FOUND)
    # Use system SDL3 if available
    target_link_libraries(SDLLevels PRIVATE SDL3::SDL3)
else()
    # Fall back to manual linking if SDL3 is in External/
    if(EXISTS "${CMAKE_SOURCE_DIR}/External/SDL3")
        target_link_directories(SDLLevels PRIVATE 
            ${CMAKE_SOURCE_DIR}/External/SDL3/lib/x64
        )
        target_link_libraries(SDLLevels PRIVATE SDL3)
    else()
        message(WARNING "SDL3 not found. Please install SDL3 or place it in External/SDL3/")
    endif()
endif()

# Copy assets to build directory
add_custom_command(TARGET SDLLevels POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Assets
        $<TARGET_FILE_DIR:SDLLevels>/Assets
)

# On Windows, copy SDL3.dll if it exists
if(WIN32)
    if(EXISTS "${CMAKE_SOURCE_DIR}/External/SDL3/lib/x64/SDL3.dll")
        add_custom_command(TARGET SDLLevels POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${CMAKE_SOURCE_DIR}/External/SDL3/lib/x64/SDL3.dll
                $<TARGET_FILE_DIR:SDLLevels>
        )
    endif()
endif()
