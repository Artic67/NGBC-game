#include <gb/gb.h>
#include "CollisionArea.c"

const uint8_t tilesInSprite = 8;
typedef struct HouseBlock {
    UBYTE spriteIds[8];
    uint16_t posX;
    uint16_t posY;
    uint16_t width;
    uint16_t height;
    uint8_t fallSpeed;
    CollisionArea* area;
} HouseBlock;
