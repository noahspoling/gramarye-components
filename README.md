# gramarye-components

Component struct definitions library for the Gramarye game engine. Provides component data structures that can be shared across systems without pulling in implementation details or backend-specific dependencies.

## Overview

gramarye-components contains the struct definitions for all ECS components. This library is separate from gramarye-component-functions (which provides ECS helper functions) to allow systems to access component structs without depending on function implementations or backend-specific types.

## Architecture

### Separation of Concerns

- **gramarye-components**: Component struct definitions only (Position, Health, Sprite, etc.)
- **gramarye-component-functions**: ECS functions for manipulating components (Position_add, Health_get, etc.)

This separation is important because:
- Systems that only need to read struct definitions can include gramarye-components without pulling in function implementations
- Components with backend-specific types (like raylib's `Texture2D`) use forward declarations here, with full definitions in gramarye-component-functions
- Keeps dependencies minimal and clear

### Component Categories

Components are organized into categories:

- **core/**: Core game components with no backend dependencies
- **textures/**: Texture and rendering-related components (may use forward declarations for backend types)
- **tilemap/**: Tilemap and chunk-related components

## Component Types

### Core Components (`core/`)

- **Position**: 2D integer position (x, y)
- **Health/BarValue**: Health bar value with current and max
- **Key**: Key component for input handling
- **ScreenBuffer**: Screen buffer component

### Texture Components (`textures/`)

- **Sprite**: Sprite component referencing an atlas and tile ID
- **Atlas**: Texture atlas (forward declaration, full definition in component-functions)
- **AtlasTable**: Table of named atlases
- **Animation**: Animation component

### Tilemap Components (`tilemap/`)

- **Tilemap**: Main tilemap structure
- **Tile**: Individual tile data
- **Chunk**: Chunk data structure
- **ChunkRenderData**: Chunk rendering data (render textures, dirty flags)
- **ChunkObserver**: Observer structure for chunk loading
- **Coord**: Coordinate utilities (IntCoord, etc.)

## Usage

### Including Components

When you only need struct definitions:

```c
#include "core/position.h"  // Position struct
#include "core/health.h"    // BarValue struct (used by Health)
#include "textures/sprite.h"  // Sprite struct
```

### With Component Functions

When you need both structs and functions:

```c
// Component-functions headers include struct definitions
#include "core/position.h"  // Position struct + Position_add, Position_get, etc.
#include "core/health.h"     // BarValue struct + Health_add, Health_get, etc.
```

The component-functions headers include the struct definitions inline, so you don't need to include gramarye-components separately when using functions.

### Backend-Specific Types

For components that reference backend types (like Atlas with raylib's `Texture2D`):

- **In gramarye-components**: Forward declaration or minimal struct
- **In gramarye-component-functions**: Full struct definition with backend types

This allows systems to work with component structs without depending on specific backends.

## Dependencies

- **gramarye-libcore**: For Table, Arena, and other data structures used by components
- No backend dependencies (raylib, etc.) - these are handled in component-functions

## Building

This library is typically built as part of the main game project via CMake FetchContent or as a subdirectory. See the main project's CMakeLists.txt for build configuration.

## Integration

This library is designed to be used as a submodule in game projects. It provides the foundation for component definitions that are used across the ECS system and other game systems.

## Relationship to Component Functions

- **gramarye-components**: "What is a Position?" (struct definition)
- **gramarye-component-functions**: "How do I add/get a Position?" (ECS functions)

Systems can include gramarye-components to get struct definitions, then use gramarye-component-functions when they need to manipulate components via the ECS.
