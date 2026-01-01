#ifndef CHUNK_OBSERVER_H
#define CHUNK_OBSERVER_H

#include "gramarye_ecs/entity.h"

// Observer types
typedef enum {
    OBSERVER_ENTITY,    // Entity with Position component
    OBSERVER_MANUAL     // Manual position
} ObserverType;

typedef struct Observer {
    ObserverType type;
    union {
        EntityId entityId;      // For entity observers
        struct {
            int tileX, tileY;   // For manual observers
        } manual;
    } data;
} Observer;

#endif // CHUNK_OBSERVER_H

