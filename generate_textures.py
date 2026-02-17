#!/usr/bin/env python3
"""
Generate placeholder TGA files for the game engine project.
Creates simple colored sprite sheets for warriors and rocks.
"""

import struct
import os

def write_tga_header(width, height, bpp):
    """Write TGA header for uncompressed RGB/RGBA image."""
    header = struct.pack(
        '<BBBHHBHHHHBB',
        0,      # ID length
        0,      # Color map type
        2,      # Image type (uncompressed true-color)
        0,      # Color map origin
        0,      # Color map length
        0,      # Color map depth
        0,      # X origin
        0,      # Y origin
        width,  # Width
        height, # Height
        bpp,    # Bits per pixel
        0       # Image descriptor
    )
    return header

def create_warrior_run_tga():
    """Create warrior_run.tga - 384x64 (6 frames x 64px)"""
    width = 384
    height = 64
    bpp = 24
    
    pixels = []
    for y in range(height):
        for x in range(width):
            frame = x // 64
            # Different color per frame for testing
            colors = [
                (255, 100, 100),  # Red-ish
                (255, 150, 100),  # Orange
                (255, 200, 100),  # Yellow
                (200, 255, 100),  # Yellow-green
                (150, 255, 100),  # Light green
                (100, 255, 100),  # Green
            ]
            r, g, b = colors[frame % 6]
            
            # Create simple sprite shape (square in center)
            local_x = x % 64
            if 16 < local_x < 48 and 16 < y < 48:
                pixels.extend([b, g, r])  # TGA is BGR
            else:
                pixels.extend([0, 0, 0])  # Black background
    
    with open('Assets/Textures/warrior_run.tga', 'wb') as f:
        f.write(write_tga_header(width, height, bpp))
        f.write(bytes(pixels))
    
    print("Created warrior_run.tga")

def create_warrior_death_tga():
    """Create warrior_death.tga - 512x64 (8 frames x 64px)"""
    width = 512
    height = 64
    bpp = 24
    
    pixels = []
    for y in range(height):
        for x in range(width):
            frame = x // 64
            # Fade from red to gray
            intensity = 255 - (frame * 30)
            r = intensity
            g = max(0, intensity - 100)
            b = max(0, intensity - 100)
            
            # Create simple sprite shape
            local_x = x % 64
            if 16 < local_x < 48 and 16 < y < 48:
                pixels.extend([b, g, r])  # TGA is BGR
            else:
                pixels.extend([0, 0, 0])
    
    with open('Assets/Textures/warrior_death.tga', 'wb') as f:
        f.write(write_tga_header(width, height, bpp))
        f.write(bytes(pixels))
    
    print("Created warrior_death.tga")

def create_rock_tga():
    """Create rock.tga - 256x64 (4 frames x 64px)"""
    width = 256
    height = 64
    bpp = 24
    
    pixels = []
    for y in range(height):
        for x in range(width):
            frame = x // 64
            # Different shades of gray/brown
            colors = [
                (128, 128, 100),
                (140, 140, 110),
                (150, 150, 120),
                (160, 160, 130),
            ]
            r, g, b = colors[frame % 4]
            
            # Create circular-ish rock shape
            local_x = x % 64
            cx, cy = 32, 32
            dist_sq = (local_x - cx) ** 2 + (y - cy) ** 2
            if dist_sq < 400:  # radius ~20
                pixels.extend([b, g, r])  # TGA is BGR
            else:
                pixels.extend([0, 0, 0])
    
    with open('Assets/Textures/rock.tga', 'wb') as f:
        f.write(write_tga_header(width, height, bpp))
        f.write(bytes(pixels))
    
    print("Created rock.tga")

if __name__ == '__main__':
    # Create directories if they don't exist
    os.makedirs('Assets/Textures', exist_ok=True)
    
    create_warrior_run_tga()
    create_warrior_death_tga()
    create_rock_tga()
    
    print("\nAll TGA files created successfully!")
