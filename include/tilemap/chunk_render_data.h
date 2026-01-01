#ifndef CHUNK_RENDER_DATA_H
#define CHUNK_RENDER_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "hash/int_coord_hash.h"

// Forward declaration - RenderTexture is defined in gramarye_renderer/renderer.h
// This avoids creating a dependency on raylib or any specific renderer backend
typedef struct RenderTexture RenderTexture;

// Chunk render data structure
// Contains render texture and state for a single chunk
typedef struct ChunkRenderData {
    RenderTexture* renderTexture;  // Render texture for this chunk (opaque pointer)
    int chunkX, chunkY;             // Chunk coordinates
    bool isDirty;                   // Needs re-rendering
    bool isLoaded;                  // Chunk data is loaded
    uint64_t lastUpdateFrame;       // Last frame this chunk was updated
} ChunkRenderData;

#endif // CHUNK_RENDER_DATA_H

